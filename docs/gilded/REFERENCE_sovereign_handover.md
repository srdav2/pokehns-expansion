# Sovereign → Gilded: Final Act & Two-ROM Save Handover

**Audience:** the build agent for `pokeemerald-custom`.
**Supersedes:** `postgame_rift_brief.md` (the single-ROM plan). The design is now **two ROMs built from this one repo, sharing one save format**:

- **Game 1 – Pokémon Sovereign Version** (Hoenn). This is the existing game; Missions 01–18 are per `docs/MASTER_EXECUTION_BLUEPRINT.md`.
- **Game 2 – Pokémon Gilded Version** (working title). Johto and Kanto, built from Pokémon Heart & Soul's open-source maps. The full story is in `GILDED_STORY_BIBLE.md`.

This file covers:
1. the two-ROM architecture and the save contract,
2. Sovereign's Final Act (Missions 19–21),
3. Gilded's Rift Import (Mission G3, referenced from the story bible),
4. how the handover is tested.

The player-facing instructions are in `HOW_TO_CONTINUE_YOUR_SAVE.md`.

---

## 0. Working rules (unchanged from the blueprint, restated because they matter more here)

1. One mission = one commit. Build with `make` (Sovereign) **and** `make gilded` (Gilded) before every commit, once G1 exists. A save-format change that breaks either ROM is a blocker.
2. "Done" = built + played + logged. Every mission's playtest checklist is run in mGBA and the results are written to `docs/agent_mission_log.md`. Pure logic gets `make check` tests.
3. **Save-format changes happen in one place, once.** All save-struct changes for the whole two-game project go in Mission 19. After M19, any change to a save struct requires bumping `SAVE_FORMAT_VERSION` and writing a line in the mission log explaining why.
4. No `filler_*` storage. Named fields only, with a `STATIC_ASSERT` that every save block still fits its sectors.
5. Registry discipline: every flag, var, trainer ID, map, MAPSEC, special and save field is recorded in `docs/story_state_registry.md`. Gilded's own entries go in a new section, "Gilded Version".

---

## 1. Architecture: one repo, two ROMs, one save format

### 1.1 Why
- The GBA cartridge address space is 32 MB, a hard limit. Hoenn plus Johto plus Kanto plus 1,000+ species will not fit in one ROM.
- Two ROMs built from the **same engine code** guarantee identical save structs (party, PC, Pokédex, player info, settings). Gilded can then read a Sovereign save directly, with no format conversion.
- The expansion already builds two games from one codebase (`IS_FRLG`, `*_Frlg` maps, `flags_frlg.h`). **Copy that pattern.** Study how `IS_FRLG` selects map groups, scripts, flags, vars, opponents, heal locations and the region map, and add a third variant the same way.

### 1.2 Build targets
| Command | Output | Variant macro |
| --- | --- | --- |
| `make` | `pokesovereign.gba` | `IS_SOVEREIGN` (default, Hoenn) |
| `make gilded` | `pokegilded.gba` | `IS_GILDED` (Johto + Kanto) |

The ROM header title and game code may differ, but **both must use FLASH 128K (`FLASH1M`) saves**, exactly as Emerald does. Emulators detect save type from strings in the ROM, so confirm `FLASH1M_V` is present in both.

### 1.3 What is shared and what is per-variant
| Shared (must stay byte-identical in both ROMs) | Per-variant |
| --- | --- |
| All `struct SaveBlock1/2`, `PokemonStorage`, `BoxPokemon`, `Pokemon` layouts | Maps, layouts, tilesets, map groups |
| Species, move, item, ability IDs and data | Event scripts and text |
| `include/config/save.h` toggles | Story flags and vars (`flags_gilded.h` / `vars_gilded.h` pattern) |
| **Shared flags and vars** (see 1.4) | Trainer IDs and parties (`opponents_gilded.h`, `trainers_gilded.party`) |
| `struct RiftState` (see 1.5) | MAPSECs, region map, heal locations, Fly destinations |
| `SAVE_FORMAT_VERSION` | Wild encounter tables |
| Followers, difficulty, randomizer and Nuzlocke engine code | Level-cap table, badge names and icons |

### 1.4 Shared flags and vars
These keep **the same number and meaning in both games**. Gilded's import preserves them. Everything else in the flag and var ranges is per-variant, and Gilded's import clears it.
- Settings: `FLAG_SYS_FOLLOWERS_DISABLED` (0x2B), `FLAG_SYS_NUZLOCKE_MODE` (0x32), `FLAG_SYS_RANDOMIZE_STARTERS` (0x33), `FLAG_SYS_RANDOMIZE_WILD` (0x34), `FLAG_SYS_RANDOMIZE_TRAINERS` (0x35), `FLAG_SYS_HARD_LEVEL_CAP` (0x36), `VAR_DIFFICULTY_MODE` (0x40A1).
- Engine and system flags that must survive: running shoes (`FLAG_SYS_B_DASH`), National Dex enabled, Pokédex obtained.
- **Action:** in M19, write `docs/shared_save_contract.md`, which lists every shared flag and var with its number. `flags_gilded.h` must define these at the same numbers, and the build must fail if they differ. Use `STATIC_ASSERT`s in a small `src/shared_contract.c` compiled into both ROMs.

### 1.5 `struct RiftState` (new, named, in SaveBlock1)
```c
struct RiftState {
    u16 saveFormatVersion;      // == SAVE_FORMAT_VERSION
    u8  lastWrittenBy;          // ROM_VARIANT_SOVEREIGN or ROM_VARIANT_GILDED
    u8  stage;                  // RIFT_NONE, RIFT_EXPORTED, RIFT_IMPORTED, RIFT_HOENN_PC_UNSEALED
    u8  sealedBoxCount;         // boxes [0, sealedBoxCount) are sealed Hoenn storage in Gilded
    u8  anchoredReturned;       // bit 0..2 = anchored mon N has been returned
    u8  anchoredLevel[3];       // 5 / 10 / 15, player-assigned
    u32 anchoredOrigPersonality[3]; // to find and remove the originals on import
    u32 anchoredOrigOtId[3];
    struct BoxPokemon anchored[3];  // snapshot of the 3 chosen Pokémon, UNMODIFIED
    u16 riftCode;               // checksum shown on both transfer screens
};
```
- This is about 290 bytes. **Measure the real free space** in SaveBlock1 first. If it doesn't fit, enable `FREE_MYSTERY_EVENT_BUFFERS` (1,104 bytes) and, if needed, `FREE_MYSTERY_GIFT` (876 bytes) in `include/config/save.h`. Those toggles are shared, so they apply to both ROMs.
- **Enabling these toggles invalidates every existing save.** Do it once, in M19, and tell the owner in the mission log.

### 1.6 Load-time guards (both ROMs)
| Situation | Behaviour |
| --- | --- |
| `saveFormatVersion` doesn't match | Title screen message: "This save is from a different version. Update both games to the same release." Continue disabled. |
| Sovereign loads a save with `lastWrittenBy == GILDED` | Message: "This journey continues in GILDED VERSION." Continue disabled. A New Game is allowed with the standard overwrite warning. |
| Gilded loads a save with `lastWrittenBy == SOVEREIGN` and `stage == RIFT_EXPORTED` | Run **Rift Import** (§3), once. |
| Gilded loads a Sovereign save with `stage == RIFT_NONE` | Message: "Complete the Distortion Rift in SOVEREIGN VERSION first, or start a New Game." |
| Gilded New Game (no import) | `DECISION:` default allowed. Generate 3 "Lost Rift" Pokémon (random non-legendary base forms, owner's OT) as the anchored trio, so the Arceus returns still happen. |

---

## 2. Sovereign Final Act: Missions 19–21

**Placement:** after Mission 18 (`VAR_MAIN_QUEST_STATE = 20`). Mission 19 is engineering only and can be done **as soon as the current mission is committed**: doing the save-format change early means fewer broken test saves later. Missions 20–21 come after Mission 18.

### Mission 19: Two-ROM split and save contract (engineering only)
- **Scope:**
  - The `make gilded` target with `IS_GILDED`. It contains one placeholder map (an empty Elm's Lab interior) so it boots.
  - The variant-split headers.
  - `shared_save_contract.md` and the `STATIC_ASSERT`s.
  - `struct RiftState` and `SAVE_FORMAT_VERSION`.
  - The load guards in §1.6.
  - Selecting the FREE_* toggles.
  - Moving the Mission 06 outfit choice out of `gSaveBlock2Ptr->filler_90[0]` into a named field `playerOutfit`, and updating every reader (`main_menu.c`, `event_object_movement.c`, `battle_controller_player.c`, `pokemon.c`, `trainer_card.c`).
  - A shared function library `src/rift.c`: `ResetMonForRift`, `SealHoennStorage`, `UnsealHoennStorage`, `ComputeRiftCode`. These are described in §3; they live in shared code but are called only by Gilded.
- **Automated tests (`make check`):**
  - `ResetMonForRift`: Pikachu becomes Pichu, Hisuian Arcanine becomes Hisuian Growlithe, Tauros stays Tauros, Lv 5/10/15 have exact minimum experience, moves are the level-up moveset, nickname/IVs/nature/shininess/OT are preserved, EVs are 0.
  - Seal/unseal round trip with 0, 1, 299 and 300 stored Pokémon.
  - `ComputeRiftCode` is deterministic.
- **Playtest:** both ROMs boot. A Sovereign save loads in Sovereign. Copy that save to Gilded and you get the "complete the Rift first" message. A Gilded New Game reaches the placeholder map.
- **Commit message:** `Mission 19: two-ROM split, shared save contract, RiftState`.

### Mission 20: The Tear and the Distortion World
- **Trigger:** `VAR_MAIN_QUEST_STATE == 20`. The TV in the player's house: *"Breaking: Wingull spotted flying upside-down over Sky Pillar. Experts blame 'vibes'."* Norman: *"Champion, there's something wrong with the sky. And not the normal amount of wrong."*
- **Sky Pillar summit:** a rift tile event (palette-warped tiles). Giratina (Altered) emerges. Its telepathic text:
  > "Sovereign Champion. You saved Hoenn from the Committee. So tidy. So *righteous*."
  > "Did you ever wonder what the world looks like… spun the other way?"
  > "Follow me. Mind the gravity."
- **Distortion World:** 3 new maps, using recoloured Sky Pillar and Sootopolis tiles. Each is small, with some floating platforms (warp tiles) and boulder pushes.
  - **DW-1, "The Slant":** an NPC echo of a Hoenn townsperson stuck mid-argument with itself. Purely a joke map: *"I believe the opposite of what I believed five minutes ago. Is that growth?"*
  - **DW-2, "The Echo Chamber":** a **double battle vs. Distortion Echoes of Commissar Blair and Chief Thorne** from Mission 04, at Lv **72–74**, using their M04 species fully evolved. Pre-battle: *"We're not real. We're vibes. We've never been stronger."* Post-battle: *"Nobody… is listening…"* `DECISION:` default levels sit just under the Mission 18 post-game bosses (Lv 73–78).
  - **DW-3, "The Axis":** the confrontation (Mission 21).
- **Pre-rift gates:** these run at the DW-3 entrance and block with Giratina dialogue.
  - Party + PC must total **≤ 300 Pokémon** (≥ 4 free boxes after compaction in Gilded). Giratina: *"Your PC is a hoard. Release some. I can't spin a world this heavy."*
  - The Day Care must be empty. *"Collect your Pokémon from the Day-Care couple. They charge by the timeline."*
- **Playtest:** trigger from a debug post-game save. Check each gate blocks and then passes, and that the double battle works.

### Mission 21: Arceus's Offer, the Spin, and the Transfer Screen
- **The Axis:** Arceus descends.
  > Arceus: "Giratina. You spin the world for sport."
  > Giratina: "Sport? I spin it for *balance*. Left, right, left. It's the only cardio I get."
  > Arceus (to player): "It is going to spin you into another timeline. The crossing unmakes what it carries. I can anchor three of your companions. They will be reborn small, and I will return them to you, one by one."
- **Selection flow:**
  1. *"Arrange the three you wish to save into your party."* The PC opens (`special ShowPokemonStorageSystemPC`).
  2. Call `special ChoosePartyMon` 3 times, with no repeats.
  3. **Ineligible:** eggs, legendary, mythical, sub-legendary, Ultra Beast and Paradox Pokémon. This includes Mission 18's Zacian, Koraidon, Miraidon, Chien-Pao and Ogerpon. Arceus: *"That one belongs to the timeline. Choose another."*
  4. **Level assignment:** *"Which will return first, smallest?"* then the same for the second and third. They become Lv 5 / 10 / 15 respectively.
  5. Write the **unmodified** snapshots, the original personality and OT ID, and the levels into `RiftState`. Compute and store the `riftCode`.
  6. **Do not change the Pokémon in the Sovereign save.** The Sovereign file stays fully playable; see "Canon" below.
- **The Spin:**
  - The player's sprite spins (use the existing spin movement), screen shake, and white flashes.
  - Giratina: *"Let's see how you like it when the whole world leans… RIGHT."*
  - Fade to black.
- **Transfer Screen:** a new full-screen text window. Set `stage = RIFT_EXPORTED` and `lastWrittenBy = SOVEREIGN`, then **force a save** before showing it.
  ```
  THE RIFT IS OPEN

  Your journey continues in
  POKéMON GILDED VERSION.

  1. Your game has been saved.
  2. Close the game completely.
  3. Copy this save to Gilded Version
     (see HOW_TO_CONTINUE_YOUR_SAVE).

  RIFT CODE: 7F3A
  (Gilded will show the same code.)

  Press A to continue in Hoenn.
  ```
- **Canon: the file copy is in the story.** After pressing A, the player wakes at the Sky Pillar summit in Sovereign. Arceus:
  > "In one timeline, you stayed. In another, you fell. Both are you. Try not to think about it too hard. I don't."

  The Sovereign file keeps playing normally, with `stage = RIFT_EXPORTED`. Re-entering the Axis shows *"The rift is quiet."*
- **Playtest:**
  - Choose a mix that includes an evolved Pokémon, a held-item Pokémon and a party member. Try a legendary and confirm it's rejected.
  - The transfer screen shows a code.
  - After continuing, all party and PC Pokémon in Sovereign are unchanged.
  - Save/reload keeps `RIFT_EXPORTED`.
  - **Then run the full handover test (§4).**

---

## 3. Gilded: Rift Import (Mission G3 in the story bible)

Runs once, on Continue, when §1.6 says so. **Order matters**:
1. Verify `saveFormatVersion`, then verify `riftCode` by recomputing it from the snapshots.
2. **Remove the originals:** search the party and all boxes for each `anchoredOrigPersonality` + `anchoredOrigOtId` pair and delete the matches. This prevents a duplicate (the original Lv 70+ plus the reset copy) at the Hoenn PC reunion. If an original isn't found, log it and continue.
3. **Reset the snapshots:** call `ResetMonForRift` on each `anchored[i]` at `anchoredLevel[i]`. Held items are discarded.
4. **Seal Hoenn storage:** run `SealHoennStorage()`. Compact all box Pokémon into the lowest boxes, move the remaining party into the sealed area, and set `sealedBoxCount`. The Gilded PC UI and every send-to-PC path only use boxes ≥ `sealedBoxCount`. Rename the visible boxes "GILDED 1…n".
5. **Reset per-variant state:**
   - clear all per-variant flags and vars (everything not in the shared contract)
   - clear the bag (all pockets and PC items) and set money to ₽3000
   - clear the Nuzlocke area flags (Gilded needs its own range sized to Johto+Kanto MAPSECs; remove the `% 88` wrap)
   - reset the Pokédex? `DECISION:` default **keep seen/caught**
   - clear badges, reset the play clock? `DECISION:` default **keep the play clock**
   - keep the player name, gender, outfit (`playerOutfit`, not `filler_90`), trainer ID and settings.
6. Give the starter kit: 5 Poké Balls, 3 Potions, Town Map.
7. Set `stage = RIFT_IMPORTED`, `lastWrittenBy = GILDED`. Warp to New Bark Town, Elm's Lab arrival cutscene. **Save.**
8. On first save after import, show *"RIFT CODE 7F3A confirmed."* once.

**Hoenn PC reunion:** after the Johto Hall of Fame (see the story bible), `UnsealHoennStorage()` sets `sealedBoxCount = 0` and `stage = RIFT_HOENN_PC_UNSEALED`. Nothing moves; every box becomes visible.

**Arceus returns:** the special `ReturnAnchoredMon(n)` copies the already-reset `anchored[n]` to the party, or to the first unsealed box if the party is full, and sets bit n of `anchoredReturned`.

---

## 4. Handover test protocol (required before G4 starts)
1. In mGBA, play a debug Sovereign save through Missions 20–21. Note the Rift Code.
2. Close mGBA. Copy `pokesovereign.sav` to `pokegilded.sav` next to `pokegilded.gba`.
3. Launch Gilded, then Continue. Check:
   - the import runs once
   - the Rift Code matches
   - you're in Elm's Lab with an empty party
   - the PC shows only the Gilded boxes
   - the bag holds only the starter kit
   - settings are preserved (try Hard Mode and Nuzlocke)
4. Save and reload: no re-import.
5. Using debug, fire all three `ReturnAnchoredMon` events. Check level, species (base form), nickname and IVs, and that no originals remain anywhere.
6. Using debug, unseal the Hoenn PC. Every Hoenn Pokémon is present, with no duplicates of the anchored three.
7. Load `pokegilded.sav` in Sovereign and get the refusal message. Load a version-mismatched save in either ROM and get the refusal message.
8. Repeat steps 1–3 with RetroArch (mGBA core) using `.srm` files.
9. Write all results in the mission log.
