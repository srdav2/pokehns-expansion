# Gilded overnight report

## Mission status

- **Built:** GF0 — Setup and audit. The HnS/Gilded target builds with the requested Arm GNU toolchain PATH; the HnS target is `make hns -j8`.
- **Partial:** none.
- **Blocked:** none.
- **Not started:** GF1–GF17.
- **Skipped:** GF-IMP, as directed.

## ROM size

The baseline `pokehns.gba` is **33,554,432 bytes (32 MiB)**. The source declares expansion version **1.15.2** in `include/constants/expansion.h`.

## Playtest queue

Use the existing overworld debug menu (hold **R** and press **Start**) for these five checks:

1. **Title and New Game:** boot the HnS target ROM, inspect the new GILDED title banner and ROM header, start a fresh save, then follow starter selection. In the overworld, open **ROM Info… → Expansion Version / ROM space**.
2. **Rift trio returns (GF1):** use each new GF1 return action; confirm levels 5, 10, and 15, exactly-once returns, and PC fallback when the party is full. Reach return locations with **Utilities… → Warp to map warp…**.
3. **Team MEGA event chain:** warp to Slowpoke Well, Mahogany hideout, Radio Tower, and Goldenrod Underground; check that each battle and story transition proceeds. Use **Trainers… → Choose trainer from map → Try Battle** for event-map trainers.
4. **Pressure Prompt branches:** on separate save copies, choose YES and NO for each prompt and confirm both continue. Reach each prompt with **Utilities… → Warp to map warp…**; inspect state with **Flags & Vars… → Set Flag XYZ… / Set Var XYZ…**.
5. **Save/reload and event persistence:** save before and after a mission event, reload, then confirm event state and returned Pokémon are preserved without duplication. Use **Utilities… → Warp to map warp…** and **ROM Info… → Save Block space**.

These are queued checks only; no in-game checks have been run.
