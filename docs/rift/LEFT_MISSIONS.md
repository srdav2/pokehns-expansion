# Pokémon Left: Rift missions (any-order two-game build)

**Repo:** `srdav2/pokehns-expansion` (Gilded, becoming **Pokémon Left**).
**Read first:** `docs/rift/RIFT_CONTRACT.md`. It is the spec for everything below and wins over `docs/GILDED_STORY_BIBLE.md` wherever they disagree about order, the Hoenn PC or the Rift. The bible still owns story, characters, jokes and the §0.2 guardrails.

**Pokémon Left owns PC boxes 8–14.** Boxes 1–7 belong to Pokémon Right.

## 0. Rules (unattended)

1. **Never ask a question or wait for input.** If something is unclear, take the documented default, log it in `docs/gilded/DECISIONS_LOG.md`, and continue.
2. **Branch:** `git fetch origin`, then `git checkout -b left-rift origin/gilded-pass-2`, then `git merge origin/master`. The merge only adds `docs/rift/` and `tools/rift/`; resolve nothing else. Work only on `left-rift`. Never push to `master`. Never force-push.
3. **One mission = one commit** (`Left LX<n>: <title>`). Push after every mission.
4. **Build:**
   ```
   PATH="/Users/stuartdavis/.gemini/antigravity/brain/f8571f88-b293-4162-b3ea-cfb03abd1a26/scratch/arm-gnu-toolchain/Payload/bin:/usr/bin:/bin:/usr/sbin:/sbin" make hns -j8
   ```
   It must finish with zero errors. After LX7 the output is `pokeleft.gba`.
5. **Shared files are copy-only.** Never edit the shared files listed in contract §0, except to copy them from `docs/rift/` to `include/` and `src/`. If the contract seems wrong, log `CONTRACT REQUEST: …`, work around it in Left-only code, and carry on. Pokémon Right is a different repo; don't touch it.
6. **Fix limit:** 3 attempts on the same build error, then revert the mission, mark it `BLOCKED: <error>` in `docs/gilded/mission_log.md`, and continue with the next mission that doesn't depend on it.
7. **Status:** `BUILT — NEEDS PLAYTEST`. Never "verified" or "playtested".
8. **Text:** at most 34 characters per line, 2 lines per box. Use the contract §12 wording **exactly** for T1–T9.
9. **Keep all Heart & Soul credits.** Keep HnS's gym, Elite Four, Champion and Red teams unchanged.
10. **Self-review before every commit:**
    - the build passes
    - `git diff --stat` touches only what the mission needs
    - every script you changed is traced by hand: flags set somewhere reachable, no softlock, re-entry OK
    - text width is OK
    - mission log entry written with `Deferred:` and **exact debug-menu playtest steps**.
11. **Stop** after LX8, or after 3 blocked missions in a row. Write `docs/rift/LEFT_REPORT.md`, commit and push.

---

## LX0: Test setup

- Try to fix the existing `make check BUILD=hns` blocker (`include/fake_rtc.h` / `struct SaveBlock3`). If it isn't fixed after 3 attempts, mark LX0 `BUILT_PARTIAL`, log the error, and still write the LX1–LX5 tests as `test/rift_left.c` so they run once it's fixed.
- `python3 tools/rift/rift_savetool.py --selftest` must print `selftest OK`.

## LX1: Integrate the contract

1. **Copy the shared files:**
   - `docs/rift/rift_contract.h` → `include/rift_contract.h`
   - `docs/rift/rift_shared.h` → `include/rift_shared.h`
   - `docs/rift/rift_shared.c` → `src/rift_shared.c`

   Create `include/config/rift_game.h` with `RIFT_THIS_GAME RIFT_GAME_LEFT` and `RIFT_OTHER_GAME RIFT_GAME_RIGHT` (contract §0).
2. **Storage struct** (`include/pokemon_storage_system.h`):
   - Add `#include "rift_contract.h"` near the top.
   - **Delete** the pass-1 fields `gildedRiftAnchoredMons[3]`, `gildedRiftAnchorLevels[3]` and `gildedRiftReturnedBits`.
   - Add `struct RiftRecord rift;` as the **last** member, directly after `fusions`.

   The `STATIC_ASSERT`s in `src/rift_shared.c` must pass **without editing that file**. The shared C has already been compiled against Left's headers with exactly this change.
3. **Rewire the pass-1 Rift code:**
   - `src/field_specials.c` `ReturnAnchoredMon()` (reads `VAR_0x8004`): use `Rift_TakeAnchor(index, &boxMon)`, then `BoxMonToMon`, then `DevolvePokemonToBaseAtLevel(&mon, Rift_GetAnchorLevel(index))`, then give it to the party or a depositable box. If `Rift_TakeAnchor` returns FALSE, give nothing and set `VAR_RESULT = FALSE`.
   - `src/pokemon.c` `InitGildedAnchoredMons()`: **remove it and its call.** A fresh game has no trio (contract §1).
   - Debug menu "Lost Rift anchors": rewire to the new record. Add a debug action "Rift: fake a Right first-finish save". It fills `rift` as if Pokémon Right had exported: 3 anchors (copies of party slot 1–3 at levels 5/10/15), `firstGame = RIFT_GAME_RIGHT`, `progressRight = FIRST_FINISH`, and 10 test Pokémon in boxes 1–7. This lets the owner test arrival without Right.
4. **Hooks:**
   - Call `Rift_StampForSave()` immediately before every save-slot write. Find the single choke point that all normal saves pass through in `src/save.c` / `src/load_save.c`, and list every save type you covered.
   - Call `Rift_InitForNewGame()` at the end of `NewGameInitData()` (`src/new_game.c`).
5. **Title screen** (`src/main_menu.c`, where the save is checked after loading): call `Rift_ClassifyLoadedSave()` **before anything reads SaveBlock1/2**, and implement the contract §4 table exactly:
   - Continue is hidden for foreign saves.
   - Show T1–T4.
   - Erasing needs a second YES/NO.
   - Run `Rift_MigrateLegacyStorage()` for `OWN_LEGACY`. Old Left saves have their Pokémon in boxes 1–7; migration packs them into 8–14 automatically.
   - Add the ARRIVE THROUGH THE RIFT option now; it can say "coming soon" until LX4.
6. **Fingerprint:**
   ```
   python3 tools/rift/rift_fingerprint.py --game left --out docs/rift/fingerprint_left.json
   python3 tools/rift/rift_fingerprint.py --compare docs/rift/fingerprint_right.json docs/rift/fingerprint_left.json
   ```
   This must print `Rift compatibility: OK`. A difference that exists only because Right hasn't integrated yet is fine; note it.

**Done when:** the build passes, an old Left save loads with its Pokémon now in boxes 8–14, and a new game's `.sav` passes `rift_savetool.py` with `last written by Left`.

## LX2: PC box ownership (Left = boxes 8–14)

Implement contract §2 everywhere Left touches the PC:
- **Every "send to PC" path:** catching with a full party, gifts, eggs, the Day Care, HnS's gift and trade scripts, and anything in `src/pokemon_storage_system.c` / `src/pokemon.c` that searches for a free box slot.
- **The storage UI:**
  - box arrows and the jump list skip non-viewable boxes
  - depositing, moving or swapping into a non-depositable box is refused
  - wallpaper and rename work on depositable boxes only
  - Move Items can't touch sealed boxes
  - **any HnS-only PC features** (box link, PC-from-bag or similar): find them and gate them the same way.
- **Current box on load:** if it isn't viewable, use `Rift_FirstDepositableBox()`.
- **Wallpapers:** clamp any index ≥ `WALLPAPER_COUNT` to 0, inside `pokemon_storage_system.c`. Data from the other game may use a different range.
- **Sealed-box note** on the PC menu: `Boxes 1-7 are sealed by\nthe Rift.`

- **Perfect-stats sweep:** if `src/perfect_player_mons.c` exists (P0), make `ShouldSweepBox()` return `Rift_IsBoxDepositable(boxId)`.

**Perfect-stats sweep:** make `ShouldSweepBox()` in `src/perfect_player_mons.c` return `Rift_IsBoxDepositable(boxId)`.

List every loop over `boxes[`, `GetBoxedMonPtr` or `TOTAL_BOXES_COUNT` in the mission log, marked read or write.

**Playtest steps:** debug-give 211 Pokémon. The 211th must say the PC is full, and boxes 1–7 must not be selectable.

## LX3: First finale (Left played first)

Left's finale is the Giratina Axis after Red (`data/maps/GiratinaAxis_hns/scripts.inc`), from pass-2 P2-09. Branch it with a new special, `IsRiftSecondGame` (returns `Rift_IsSecondGame()`):
- **First game (`FALSE`):**
  1. Giratina appears and spins the world: **cutscene only, no battle.**
  2. Arceus makes the offer.
  3. Check blockers (T5/T6).
  4. Show T7 and a YES/NO.
  5. The player picks up to 3 party Pokémon (no eggs, at least 1 stays; use the party menu three times; the pick order is the rank).
  6. For each pick: `Rift_StoreAnchor(rank, &gPlayerParty[slot].box)`, then remove it from the party and compact.
  7. `Rift_PrepareCrossing` → T8 with counts.
  8. `Rift_MarkFirstFinish` → save → T9.
  9. A short first-finish ending: Giratina's line *"Spin it the other way. I want to see their faces."*, then credits.

  Put the crossing logic in small specials in a new `src/rift_left.c`; scripts call them.
- **Second game (`TRUE`):** LX5.

**Playtest steps:**
- debug-warp to the Axis with `FLAG` set as if Red were beaten
- do the crossing with 3 party Pokémon holding items
- check: the Bag gained the items, the party shrank, and `rift_savetool.py` shows Left "first finish" with 3 anchors and no items in boxes 8–14.

## LX4: Arrival (Left played second)

- **ARRIVE THROUGH THE RIFT** runs contract §6:
  1. `Rift_BackupStorage()`; if NULL, show T4 and stop.
  2. HnS's normal new-game init, **skipping the name and gender entry**.
  3. `Rift_FinishArrival(backup)`.
  4. A short Arceus arrival intro (3–5 boxes; bible §3.6 tone).
  5. HnS's normal opening (Elm's lab, starter and so on).
- **Arceus Returns 1–3** (pass 1 placed them on Route 30, Route 32 and in Azalea): they now run **only if `IsRiftSecondGame`**. Each calls `ReturnAnchoredMon` with index 0/1/2 and sets `FLAG_GILDED_RETURN_n_SEEN` after a successful return. In a first game they don't appear.
- **Sealed-box explainer NPC** in the Cherrygrove Pokémon Center.

**Playtest steps:**
1. Use the LX1 debug action "fake a Right first-finish save".
2. Save, reset and choose ARRIVE.
3. Check:
   - the name is kept
   - boxes 1–7 are sealed but show their counts on the PC note
   - Returns 1–3 give the trio at 5/10/15 with no held items, once each.

## LX5: Second finale (Left played second)

At the Axis, when `IsRiftSecondGame` is `TRUE`:
- Giratina-Origin with the Griseous Core (already built in P2-09, level 90), then **Arceus** (new; `setwildbattle SPECIES_ARCEUS, 90`).
- Both are catchable and retriable. Set the done-flag only after a win or a catch.
- Then a new special calls `Rift_MarkSecondFinish()`, then Pokédex seen/caught for every Pokémon in boxes 1–7, then save.
- Then the existing true ending: Arceus's "the middle is quiet" line, the CROSSFIRE TV room, the Route 29 walk-out, and the three `VAR_PRESSURE_POINTS` tiers.

**Check:** nothing else in Left gives Giratina or Arceus. If something does, gate it and log the decision.

## LX6: Any-order story audit

Left was written as the sequel. Everything that assumes the player came from Hoenn, or already saw the "left spin", needs to be neutral, or to have two versions behind `IsRiftSecondGame`. At minimum:

| Line (bible ref) | First game (Left first) | Second game |
| --- | --- | --- |
| Pell's "the Hoenn transplant" | "the un-pedigreed local" | keep |
| Act 1 arrival scene | HnS's normal opening, plus the "…AGAIN" sign joke | Arceus arrival (LX4) |
| Giratina "Last time it was pronouns. This time it's protein powder." | "Spun right. Let's see who notices." | keep |
| Axis "You've seen it spun left. You've seen it spun right." | "Spun right. Next time, the other way." | keep |
| Bill's Hoenn PC scene (GF12) | Bill teases "boxes 1–7 are sealed by something old" | same tease (the unseal now happens at the second finale) |
| Commissar Bleak cameo | keep (it works as a standalone cameo) | keep |

Grep for `HOENN`, `Hoenn`, `SOVEREIGN`, `Sovereign`, `transplant`, `last time`, `spun` and `Rift` in `data/` and `src/data/text`, and list every change.

## LX7: Rename to Pokémon Left

- **Makefile `hns` target:** `TITLE := PKMN LEFT`, output `pokeleft.gba`. **`GAME_CODE` stays `BPEE`.** Update `.github/workflows/*`, docs and scripts that name `pokehns.gba`.
- **Title screen logo:** edit or recolour it to read LEFT, in blue. A text-based version is acceptable; mark it `BUILT_PARTIAL` and leave a preview PNG for the owner.
- **In-game text:** "Gilded"/"GILDED" as the **game name** → "Left". **Keep every Heart & Soul credit.**

## LX8: Final checks and report

- Regenerate `docs/rift/fingerprint_left.json` and run the `--compare` (paste the output into the report).
- Run `rift_savetool.py --selftest`, and the savetool on a `.sav` from LX3 and from LX4 if you can produce them.
- Write `docs/rift/LEFT_REPORT.md`:
  - status per mission and the ROM size
  - every `CONTRACT REQUEST`
  - every place that writes to the PC and how it's gated
  - the top 10 playtest steps (debug menu).
