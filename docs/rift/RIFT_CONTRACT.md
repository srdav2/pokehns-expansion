# The Rift Contract (v2): Pokémon Right ⇄ Pokémon Left

**This file is identical in both repos.** Never change it in one repo alone; see §10.

| Game | Repo | Was called | Region | You fight |
| --- | --- | --- | --- | --- |
| **Pokémon Right** | `srdav2/pokeemerald-custom` | Sovereign | Hoenn | the extreme left |
| **Pokémon Left** | `srdav2/pokehns-expansion` | Gilded | Johto + Kanto | the extreme right |

The player picks a side and plays that game as a normal, complete game. At its finale, Giratina spins the world and Arceus carries 3 Pokémon across. The player then plays the other game. At *that* game's finale they fight Giratina and Arceus (both catchable), and the first game's PC boxes unseal. **Either game can be played first; the rules below are symmetrical.**

## 0. Shared files (must be byte-identical in both repos)

| Master copy | Live copy (compiled) | What |
| --- | --- | --- |
| `docs/rift/rift_contract.h` | `include/rift_contract.h` | `struct RiftRecord`, constants, layout numbers |
| `docs/rift/rift_shared.h` | `include/rift_shared.h` | Shared API |
| `docs/rift/rift_shared.c` | `src/rift_shared.c` | Shared logic: checksum, box rules, crossing, arrival, migration |
| `tools/rift/rift_savetool.py` | (same) | Read a `.sav` and print the Rift record and box occupancy (`--selftest`) |
| `tools/rift/rift_fingerprint.py` | (same) | Records and compares the two games' numbering and struct layouts |
| `docs/rift/fingerprint_right.json`, `docs/rift/fingerprint_left.json` | (same) | Last recorded fingerprints of both games. The first versions (18 Oct 2026) are the **target** state, recorded with `struct RiftRecord rift;` already added to each game's storage struct. Each game's integration mission regenerates its own. |

Each repo adds **one** game-specific file: `include/config/rift_game.h`:
```c
#ifndef GUARD_CONFIG_RIFT_GAME_H
#define GUARD_CONFIG_RIFT_GAME_H
#define RIFT_THIS_GAME  RIFT_GAME_RIGHT   // Left: RIFT_GAME_LEFT
#define RIFT_OTHER_GAME RIFT_GAME_LEFT    // Left: RIFT_GAME_RIGHT
#endif
```

**Status of the shared C (18 Oct 2026):** `rift_shared.c` was compiled with each repo's real compiler flags (`-Werror -Wall`) against both games' headers, with `struct RiftRecord rift;` added to `struct PokemonStorage`. Every `STATIC_ASSERT` passed in both, so the record sits at the same offset (34,144) and the storage is the same size (34,484) in both games. It has **not** been linked or run yet; the per-game missions do that and add tests.

## 1. Player journey

1. **First game.** Normal game. The other game's 7 boxes are sealed and empty.
2. **First finale.** Giratina appears and spins the world (not catchable). Arceus offers to carry 3 Pokémon:
   - The player picks up to 3 from the party and ranks them; rank decides the return level (5 / 10 / 15).
   - The player is warned about what can't cross (§5).
   - The trio leaves the party and is stored in the Rift record.
   - Everything in this game's 7 boxes is sanitised for crossing.
   - The record is marked "first finish", the game saves, and it shows how to copy the save file (§5.5).
   - The player can keep playing this game's post-game afterwards.
3. **Copy the save.** For example, `pokeright.sav` → `pokeleft.sav`, keeping a backup.
4. **Second game.** The title screen offers **ARRIVE THROUGH THE RIFT**. The game:
   - starts a new adventure, keeping the player's name, gender and trainer ID
   - keeps both halves of the PC; the other half stays sealed
   - has Arceus return the trio one by one in the early game, reset to levels 5, 10 and 15.
5. **Second finale.**
   - Giratina-Origin, then Arceus, both catchable and retriable.
   - All 14 boxes unseal, and the Pokédex registers everything in them.
   - The true ending: "the middle is quiet".

## 2. PC box ownership

| Boxes (player-facing) | Index | Owner |
| --- | --- | --- |
| 1–7 | 0–6 | **Right** |
| 8–14 | 7–13 | **Left** |

Rules for every game:
- **Deposit** (any way a Pokémon enters a box, including catching with a full party, gifts, Day Care, "move to box" and swaps): only into `Rift_IsBoxDepositable(box)`.
- **View / withdraw:** only `Rift_IsBoxViewable(box)` (depositable boxes, plus legacy overflow boxes, §8).
- **Box navigation** (arrows, jump list, "select box"): skips boxes that aren't viewable.
- **"PC is full":** when no depositable box has space. Use the game's normal "no room" message.
- **Wallpaper and box rename:** only on depositable boxes.
- **Read-only scans** of the whole PC (e.g. Mirage Island-style checks) may read sealed boxes but never write them.
- After `Rift_MarkSecondFinish`, `boxesUnsealed = 1` and every box is usable in this game.
- **Never** write to a box this game doesn't own unless `boxesUnsealed` is set. That data belongs to the other game.

## 3. Save layout

| Flash sectors | Contents | Shared? |
| --- | --- | --- |
| 0–4 | SaveBlock2 + SaveBlock1: this game's progress | **No.** Different in each game; never read across. |
| 5–13 | `struct PokemonStorage`: boxes, names, wallpapers, fusions, **then `struct RiftRecord rift`** | **Yes.** Identical layout in both games. |
| 14–27 | Backup slot (same as 0–13) | same rules |
| 28–31 | Hall of Fame, Trainer Hill, recorded battle | No |

Both games keep game code `BPEE`, so emulators use the same 128 KiB flash save type.

`struct RiftRecord` (340 bytes) is the **last member** of `struct PokemonStorage`, directly after `fusions`. See the header for fields. Key rules:
- `Rift_StampForSave()` runs immediately before **every** save write. It stamps magic, version and `lastWrittenBy`, copies the player's identity, and recomputes the checksum.
- `Rift_InitForNewGame()` runs at the end of `NewGameInitData()`, after the trainer ID exists.
- Checksum: CRC-16/CCITT-FALSE (poly 0x1021, init 0xFFFF) over bytes 0x000–0x14F. Test vector: `"123456789"` → `0x29B1`.

## 4. Loading a save (title screen)

Call `Rift_ClassifyLoadedSave()` **straight after the save loads, before anything reads SaveBlock1/2.** The main menu's name, time, badges and Pokédex would show garbage for a foreign save.

| Result | Continue | New Game menu | Message (shared wording, §12) |
| --- | --- | --- | --- |
| `RIFT_SAVE_OWN` | yes | normal (with the usual overwrite warning) | none |
| `RIFT_SAVE_OWN_LEGACY` | yes, after `Rift_MigrateLegacyStorage()` | normal | none |
| `RIFT_SAVE_FOREIGN_READY` | hidden | **ARRIVE THROUGH THE RIFT** (first option) and NEW GAME | T1 |
| `RIFT_SAVE_FOREIGN_UNFINISHED` | hidden | NEW GAME only, after warning T2 and a second YES/NO | T2 |
| `RIFT_SAVE_FOREIGN_DONE` | hidden | NEW GAME only, after warning T3 and a second YES/NO | T3 |
| `RIFT_SAVE_UNREADABLE` | hidden | NEW GAME only, after warning T4 and a second YES/NO | T4 |

## 5. The crossing (first finale; only when `!Rift_IsSecondGame()`)

1. **Blockers:** `Rift_CheckCrossingBlockers()`. If non-zero, show T5 (fusion) and/or T6 (overflow) and end the scene without crossing; the player can retry.
2. **Warning (T7), then YES/NO:**
   - held items go to the Bag and stay in this world
   - the party and the Day Care stay behind
   - only Pokémon in this game's boxes cross
   - the 3 chosen Pokémon will be reset.
3. **Pick and rank the trio** from the party (no eggs; at least 1 Pokémon must stay in the party, so pick `min(3, party count − 1)`). For rank `n` (0–2), call `Rift_StoreAnchor(n, &party[slot].box)`, which copies and sanitises it (held item → Bag). Then remove that Pokémon from the party and compact the party.
4. `Rift_PrepareCrossing(&report)` sanitises every Pokémon in this game's half:
   - **held item → Bag** (if the Bag is full, the item is lost and counted)
   - **ball > 27 → Poké Ball**
   - **met location → "fateful encounter" (0xFF)**, because each game's map sections differ.

   Show T8 with the counts.
5. `Rift_MarkFirstFinish()`, then save, then the copy instructions (T9), then this game's first-finish ending.

**The owner's rule: no item ever crosses.** Neither held items nor the Bag. The arriving game also strips held items again, defensively (`Rift_FinishArrival`).

## 6. Arrival (second game)

When the player picks ARRIVE THROUGH THE RIFT:
1. `backup = Rift_BackupStorage()` (34 KiB from the heap; if NULL, show T4 and abort).
2. Run the game's normal new-game initialisation, which calls `Rift_InitForNewGame()` and wipes the PC. **Skip the name/gender entry.**
3. `Rift_FinishArrival(backup)`: restores the PC and record, applies the saved name, gender and trainer ID, sanitises the other half again, clears fusion storage, and sets the current box to this game's first box.
4. Play this game's arrival opening (Arceus, short), then its normal story.

**Trio returns.** Three early-game scenes call `Rift_TakeAnchor(n, &boxMon)`, then the game's reset function sets the Pokémon to `Rift_GetAnchorLevel(n)`. The reset de-evolves to the base form and sets the exact level. It keeps nickname, OT, IVs, nature, shininess and ability slot; it resets EVs, moves (to the level-up set) and experience. The Pokémon goes to the party, or to a depositable box. These scenes only run when `Rift_IsSecondGame()`.

## 7. Second finale (only when `Rift_IsSecondGame()`)

- **Giratina-Origin** (holding the Griseous Core), then **Arceus**: both are wild battles and catchable. If the player loses or runs, the battle can be retried; set the done-flag only after a win or a catch.
- Level for both: this game's top story trainer's ace level, minus 5.
- `Rift_MarkSecondFinish()` unseals all boxes. Then mark Pokédex seen and caught for every Pokémon in the other half, and save.
- The true ending. In this game's first-finish ending, Giratina and Arceus are not catchable.

## 8. Legacy saves (made before this contract)

`Rift_MigrateLegacyStorage()` moves every Pokémon outside this game's half into free slots inside it.
- Pokémon that don't fit stay where they are, and their boxes are marked in `overflowBoxes`: viewable and withdraw-only.
- The file can't cross until the overflow boxes are empty (blocker T6).
- Any old anchor data at the record's position is discarded, including Left's pass-1 "Lost Rift trio" and Right's v1 `RiftState`. Log it in the game's decisions log.

## 9. Compatibility facts (checked 18 Oct 2026; Right expansion 1.17.2, Left 1.15.2)

- **Identical** in both games:
  - `struct BoxPokemon` (80 bytes), its substructs and `struct Pokemon`
  - `struct PokemonStorage` up to `fusions`: 14 boxes × 30, 4 fusion slots
  - all 1,670 species numbers and all move numbers.
- **Abilities:** shared numbers are identical. Right has 9 extra Legends Z-A Mega abilities, which exist only mid-battle. Boxes store an ability **slot**, not an ID.
- **Balls:** identical up to Cherish (27). Left adds `BALL_GS` (28), which is clamped at the crossing.
- **Items:** 917 shared and identical. Left adds 28 Heart & Soul items (874–901), and `ITEM_FIELD_ARROW` is numbered differently. **This doesn't matter, because no item crosses.**
- **Re-check after any expansion upgrade**, or after editing `pokemon.h`, `pokemon_storage_system.h` or the constants:
  - `python3 tools/rift/rift_fingerprint.py --game <right|left> --out docs/rift/fingerprint_<game>.json`
  - then `--compare docs/rift/fingerprint_right.json docs/rift/fingerprint_left.json`, which must print `Rift compatibility: OK`.

## 10. Change control

- Changing anything in §0's shared files means bumping `RIFT_CONTRACT_VERSION`, updating `RIFT_RECORD_SIZE`/`OFFSET` and `STORAGE_SIZE`, and adding a migration in `Rift_ClassifyLoadedSave`.
- Change **both** repos in the same session, regenerate both fingerprints, and get the owner's OK first. An agent working in one repo must **not** edit the shared files; it logs a `CONTRACT REQUEST` in its decisions log instead.
- Fixing a bug in `rift_shared.c` without changing the layout is allowed. Copy the identical file to the other repo in the same session if you can; otherwise log `CONTRACT SYNC NEEDED: <commit>`.

## 11. Tests each game must have

**`make check`** where it works:
- the layout asserts compile
- the CRC vector
- `Rift_ClassifyLoadedSave` for all six cases
- box rules: catching with a full party never lands in a sealed box, and returns "no room" when the own half is full; after unsealing, all boxes are used
- migration packing, including overflow
- crossing sanitisation (item removed, ball clamped, met location)
- arrival: the PC survives new-game init, and the identity is applied.

**Save tool:** `python3 tools/rift/rift_savetool.py --selftest` passes. On any real save it prints a sensible record.

**Cross-game:** Right's QA harness runs both ROMs through the journeys (Right mission RX7).

## 12. Shared player-facing text (both games use this wording)

Lines are at most 34 characters; `\n` is a new line, `\p` a new box.

- **T1:** `A traveller's save from the\nother world was found.\pThe Rift is open. You may\narrive with your Pokémon.`
- **T2:** `This save belongs to the other\nworld, and that journey isn't\pfinished. Starting a new game\nhere will ERASE it.`
- **T3:** `Both worlds are complete in\nthis save.\pStarting a new game here will\nERASE it.`
- **T4:** `This save can't be read by\nthis version of the game.\pStarting a new game here will\nERASE it.`
- **T5:** `A fused Pokémon is holding its\npartner. Separate them first.`
- **T6:** `Some Pokémon are still in the\nother world's boxes.\pMove them into your own boxes\nbefore crossing.`
- **T7:** `Nothing you carry can cross the\nRift. Held items go to your BAG.\pYour party and the DAY CARE stay\nhere. Only Pokémon in your PC\pboxes will cross, and the three\nyou choose will start anew.`
- **T8:** `{STR_VAR_1} Pokémon will cross.\n{STR_VAR_2} held items went to the BAG.` If any items were lost, add the box `{STR_VAR_3} items didn't fit and\nwere left behind.`
- **T9:** `Your journey continues in the\nother world.\pCopy this save file to the other\ngame and choose ARRIVE THROUGH\pTHE RIFT on its title screen.\nKeep a backup copy, too.`
- **Sealed-box note** (PC menu, when sealed boxes exist): `Boxes {STR_VAR_1} are sealed by\nthe Rift.`

## 13. Names

- **ROM files:** `pokeright.gba` / `pokeleft.gba`.
- **Header titles:** `PKMN RIGHT` / `PKMN LEFT`.
- **Game code:** `BPEE` for both, unchanged.
- **Tagline:** *Pick a side. Then switch.*
- **Colours (owner default, US convention):** Right = red, Left = blue.
- **GitHub repos keep their names for now.**
