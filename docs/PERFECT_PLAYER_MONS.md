# Brief: Perfect IVs and EVs for the player's Pokémon

**Repo:** `srdav2/pokehns-expansion` (Gilded / **Pokémon Left**), branch `left-rift`. See `docs/rift/COPILOT_RUN.md` for the branch set-up.
**Who:** GitHub Copilot. One task, one commit (`Left: perfect IVs/EVs for the player's Pokémon`). Pokémon Right has the same feature, so both games behave the same.

## What the owner wants

- **Every Pokémon the player owns** has perfect IVs and EVs:
  - Pokémon they catch, including when the party is full and the catch goes to the PC
  - the starter
  - gifts and fossils, and anything given by a script or the debug menu
  - eggs once they hatch
  - in-game trades
  - **every Pokémon already in an existing save** (party, all PC boxes, the Day Care).
- **Nothing else changes.** Wild Pokémon and trainers' Pokémon keep their normal random or hand-set IVs and EVs. The change happens only at the moment a Pokémon becomes the player's, and to the player's existing Pokémon when a save loads or is written.
- **Saves must stay compatible.** No change to the save format (§4).

## Values

- **IVs:** 31 in all six stats.
- **EVs:** 252 in all six stats (owner's choice: "full"). This is above the normal 510 total, so the Pokémon gain no further EVs from battles and vitamins have no effect. That's expected.
- Make both values config options so the owner can change them later. Add these to the end of `include/config/pokemon.h`:
  ```c
  // Pokémon Left: the player's own Pokémon always have these IVs/EVs (wild and trainer Pokémon are unaffected).
  #define P_PLAYER_MONS_PERFECT   TRUE
  #define P_PLAYER_MONS_IV_VALUE  MAX_PER_STAT_IVS   // 31
  #define P_PLAYER_MONS_EV_VALUE  MAX_PER_STAT_EVS   // 252
  ```
  `MAX_PER_STAT_IVS` and `MAX_PER_STAT_EVS` are defined in `include/constants/pokemon.h`.

## 1. New code (one new file pair)

`include/perfect_player_mons.h` and `src/perfect_player_mons.c`:
- `void MaxPlayerBoxMonStats(struct BoxPokemon *boxMon)`:
  - does nothing if `P_PLAYER_MONS_PERFECT` is FALSE, or if `GetBoxMonData(boxMon, MON_DATA_SANITY_HAS_SPECIES)` is 0
  - otherwise uses `SetBoxMonData` to set `MON_DATA_HP_IV`, `ATK_IV`, `DEF_IV`, `SPEED_IV`, `SPATK_IV` and `SPDEF_IV` to the IV value, and the six `*_EV` fields to the EV value.
  - Use a `u32` variable for the value you pass in.
- `void MaxPlayerMonStats(struct Pokemon *mon)`: calls the function above on `&mon->box`, then `CalculateMonStats(mon)` so the party stats update straight away.
- `void MaxAllPlayerMonStats(void)`: applies to:
  - every party slot (`gPlayerParty[i]`, using `MaxPlayerMonStats`)
  - every PC slot in every box (`gPokemonStoragePtr->boxes[box][pos]`), but only boxes where `static bool32 ShouldSweepBox(u8 boxId)` returns TRUE
  - both Day Care Pokémon (`gSaveBlock1Ptr->daycare.mons[i].mon`).

  `ShouldSweepBox` returns TRUE for now. Put this comment on it: `// Rift contract (docs/rift/RIFT_CONTRACT.md §2): LX2 changes this to return Rift_IsBoxDepositable(boxId) so we never write the other game's boxes.`
- Running it on a Pokémon that's already perfect must change nothing, so calling it often is safe.

## 2. Hooks (one line each, all calling the functions above)

| Where | What |
| --- | --- |
| `src/pokemon.c` `GiveCapturedMonToPlayer()` | `MaxPlayerMonStats(mon);` as the first line. Covers every catch, including straight to the PC. |
| `src/pokemon.c` `GiveScriptedMonToPlayer()` | `MaxPlayerMonStats(mon);` as the first line. Covers the starter, gifts, fossils, `givemon` and the debug-menu give. |
| `src/egg_hatch.c` `AddHatchedMonToParty()` | After the hatched Pokémon's data is set, before the function returns: `MaxPlayerMonStats(mon);` |
| `src/trade.c` `TradeMons()` | After the swap, on the player's new party slot: `MaxPlayerMonStats(&gPlayerParty[playerPartyIdx]);` |
| `src/load_save.c` `CopyPartyAndObjectsToSave()` | `MaxAllPlayerMonStats();` as the first line, before `SavePlayerParty()`. Every save writes perfect Pokémon. If LX1 later adds `Rift_StampForSave()` here, keep the sweep first. |
| `src/overworld.c` `CB2_ContinueSavedGame()` | `MaxAllPlayerMonStats();` after the save data is loaded, before the player can move. **This upgrades Pokémon in existing saves the moment they're loaded.** |

Do **not** touch `CreateMon`, `CreateBoxMon`, the wild-encounter code or the trainer-party code. Those make wild and enemy Pokémon, which must stay random.

## 3. Let the player see it

`P_SUMMARY_SCREEN_IV_EV_VALUES` is already `TRUE` in this repo. Check whether HnS's summary screen already lets the player view IVs and EVs:
- If it does, change nothing.
- If it doesn't, and a config switch in `include/config/summary_screen.h` turns it on, set that switch.
- Otherwise skip this step and note it.

## 4. Save compatibility (must hold)

- **Don't change** any struct in `include/global.h`, `include/pokemon.h`, `include/pokemon_storage_system.h` or `include/save.h`.
- **Don't add** flags, vars or save fields.
- Leave every save-version constant as it is.

IVs and EVs are existing fields inside each stored Pokémon. The only effect on a save is that those numbers get raised.

**What this means for the owner's saves:** saves from earlier Gilded/Left builds keep loading, and their Pokémon are upgraded on load. (LX1 later converts old saves for the Rift; that's separate and also keeps them loading.)

## 5. Build and check

1. Build with the command in `docs/rift/COPILOT_RUN.md` (`make hns -j8` with the long PATH). It must finish with zero errors.
2. **`git diff --stat`** should show only:
   - the two new files
   - `include/config/pokemon.h` (and the summary config if step 3 needed it)
   - one or two lines each in `pokemon.c`, `egg_hatch.c`, `trade.c`, `load_save.c` and `overworld.c`.
3. **Commit on `left-rift` and push.** Never push to `master`.
4. **Playtest checklist.** Add it to `docs/gilded/mission_log.md`; nobody has played it yet.
   - Load an existing save. Open the summary of a party Pokémon and of a PC Pokémon. Their IVs show 31 and EVs show 252.
   - Start a new game. The starter from Elm shows 31/252.
   - Catch a wild Pokémon. During the battle its stats are normal; after the catch its summary shows 31/252, including when the party is full and it goes to the PC.
   - Battle a trainer. Their Pokémon are unchanged.
   - Hatch an egg and do an in-game trade (if one is reachable), then check both.
