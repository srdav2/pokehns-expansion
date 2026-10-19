# Pokémon Left Rift implementation report

**Branch:** `left-rift`  
**Status:** `BUILT — NEEDS PLAYTEST`  
**ROM:** `pokehns.gba`, 33,554,432 bytes (32 MiB)

## Mission status

| Mission | Status | Commit |
| --- | --- | --- |
| Perfect IVs/EVs | BUILT — NEEDS PLAYTEST | `1872396ee4` |
| LX0 — Test setup | BUILT_PARTIAL — NEEDS PLAYTEST | `f6e1de2680` |
| LX1 — Integrate the contract | BUILT — NEEDS PLAYTEST | `bc926de04f` |
| LX2 — PC box ownership | BUILT — NEEDS PLAYTEST | `af0a2b1b68` |
| LX3 — First finale | BUILT — NEEDS PLAYTEST | `ae2957e848` |
| LX4 — Arrival | BUILT — NEEDS PLAYTEST | `773e5c01a7` |
| LX5 — Second finale | BUILT — NEEDS PLAYTEST | `fe93b30c24` |
| LX6 — Any-order story audit | Deferred | — |
| LX7 — Rename to Pokémon Left | Deferred | — |
| LX8 — Final checks and report | BUILT — NEEDS PLAYTEST | This report |

The perfect-stats sweep sets owned player Pokémon to 31 IVs and 252 EVs per stat. `MaxPlayerMonStats` returns before `CalculateMonStats` for an empty party slot.

## Build and checks

- `PATH="/Users/stuartdavis/.gemini/antigravity/brain/f8571f88-b293-4162-b3ea-cfb03abd1a26/scratch/arm-gnu-toolchain/Payload/bin:/usr/bin:/bin:/usr/sbin:/sbin" make hns -j8` completed with exit code 0 after LX5.
- `python3 tools/rift/rift_savetool.py --selftest` printed `selftest OK`.
- Regenerated `docs/rift/fingerprint_left.json`. `python3 tools/rift/rift_fingerprint.py --compare docs/rift/fingerprint_right.json docs/rift/fingerprint_left.json` printed:

  ```text
  info: items: 917 shared, 1 renumbered ['ITEM_FIELD_ARROW'], 0 only in Right, 28 only in Left (never cross: held items are stripped)
  Rift compatibility: OK
  ```

- No `.sav` or `.srm` files were present in the repository, so the save-tool was not run against LX3/LX4 save files.
- `make check BUILD=hns` and its C-test setup were skipped as instructed for LX0. No emulator playtesting was performed.

## Contract requests

- **T8 anchor-held-item totals:** `Rift_StoreAnchor` does not expose held-item totals to the crossing report. Left measures each item's Bag quantity before and after `Rift_StoreSelectedAnchor`; the local count contributes to T8 and identifies items that did not fit. This request is recorded in `docs/gilded/DECISIONS_LOG.md`.

## PC writes and gates

- `src/pokemon.c`: `CopyMonToPC` and `IsPokemonStorageFull` use only depositable Left boxes. Catch, gift, hatch, trade, and other normal placement paths use this shared destination path.
- `src/pokemon_storage_system.c`: `StorePokemonInBox`, `GetFirstFreeBoxSpot`, and free-space checks use depositable boxes. Multi-move editing is limited to depositable boxes; overflow boxes remain withdraw-only. `ResetPokemonStorageSystem` clears storage only during normal new-game initialization.
- `src/field_specials.c`: `ReturnAnchoredMon` gives an anchor to the party or a depositable box; when neither has room, the anchor remains unreturned.
- `src/perfect_player_mons.c` and `src/script_pokemon_util.c`: the perfect-stat sweep and box healing write only to depositable boxes.
- `src/debug.c`: generic PC fill actions use depositable boxes. The LX1 `Rift: fake a Right first-finish save` fixture intentionally clears boxes 1–7 and writes test Pokémon there to simulate a foreign save.
- `src/rift_shared.c`: legacy migration packs Pokémon from the foreign half into this game's free boxes and leaves any overflow flagged and withdraw-only; crossing sanitizes only this game's boxes. `Rift_FinishArrival` restores the backed-up storage only after the title-screen arrival action runs, then sanitizes the foreign half. The second-finish helper unseals boxes only after both finale battles succeed.

The read-only whole-PC scans in PokéNav, lottery, storage summaries, and Pokédex-related code do not modify sealed boxes.

## Top 10 playtest steps

1. Start a Left game. Open **R + Start → Utilities… → Lost Rift anchors… → Rift: fake a Right first-finish save**; save in-game and reset.
2. Confirm T1 appears, Continue is absent, and **ARRIVE THROUGH THE RIFT** is the first title-menu option. Choose it and confirm no name/gender prompt appears.
3. Confirm the original name, gender, and trainer ID remain; the Arceus arrival introduction plays once at the player's house.
4. Open the PC and confirm boxes 1–7 are sealed and readable; check the Cherrygrove Pokémon Center gentleman's sealed-box explanation.
5. Confirm Arceus Returns 1–3 are available only for existing, unreturned anchors. Use **R + Start → Utilities… → Lost Rift anchors… → Return anchor 1/2/3** to check the saved trio levels 5/10/15, one-time return, and held-item removal.
6. Use **R + Start → Utilities… → Warp to map warp…** to warp to Giratina Axis. Confirm the second-game scene starts without the Red flag.
7. Run from or lose to Giratina, return to the Axis, and confirm it is offered again. Win or catch it; confirm the game saves before Arceus appears.
8. Run from or lose to Arceus, return to the Axis, and confirm the successful Giratina battle is not repeated. Win or catch Arceus; confirm boxes 1–7 unseal, the save completes, and the CROSSFIRE/Route 29 ending plays.
9. Start a fresh Left game. Open **R + Start → Flags & Vars… → Set Flag XYZ…**, set `FLAG_DEFEATED_RED` (`0x23B`), then use **R + Start → Utilities… → Warp to map warp…** to warp to Giratina Axis. Exercise the fusion/overflow blockers, decline T7, then complete the first-finish crossing with three held-item anchors.
10. Use **R + Start → Give X… → Pokémon (Basic)** to fill party and boxes 8–14; confirm another placement reports PC full rather than writing to boxes 1–7. Check perfect IVs/EVs on party and PC Pokémon and confirm trainer Pokémon remain unchanged.

## Deferred

- LX6 story audit and LX7 title/logo rename were skipped under the credit-limited task order.
- Save-file inspection and all in-game/emulator playtesting remain for the owner.
