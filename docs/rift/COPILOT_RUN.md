# Copilot run: perfect Pokémon + Pokémon Left (Rift) build

**Who:** the GitHub Copilot desktop app, in this repo (`srdav2/pokehns-expansion`). **The owner is asleep:** never ask a question or wait for input.

## Order

1. **Branch setup** (exactly as `docs/rift/LEFT_MISSIONS.md` §0.2 says):
   ```
   git fetch origin
   git checkout -b left-rift origin/gilded-pass-2
   git merge origin/master
   git push -u origin left-rift
   ```
   The merge only brings in `docs/` and `tools/rift/`.
2. **P0, perfect IVs/EVs:** do `docs/PERFECT_PLAYER_MONS.md` exactly. Commit `Left P0: …`, push.
3. **LX0 → LX8:** do the missions in `docs/rift/LEFT_MISSIONS.md` in order, one commit each, pushed after each. The rules in its §0 apply to everything in this run, including P0.
   - In **LX2**, also change `ShouldSweepBox()` in `src/perfect_player_mons.c` to `return Rift_IsBoxDepositable(boxId);`, so the perfect-stats sweep never writes the other game's boxes (1–7).
   - In **LX4**, returned Arceus Pokémon go through `GiveScriptedMonToPlayer`, so they become perfect too. That's intended.
4. **Stop** after LX8, or after 3 blocked missions in a row. Then write `docs/rift/LEFT_REPORT.md`, commit and push.

## Priority if you run short

P0, then LX1–LX5: the save, the box rules, both finales and the arrival. LX6–LX7 (story audit, rename) can wait. LX0's `make check` fix is nice to have, not essential.

## Never

- push to `master`, or force-push
- edit the shared Rift files except to copy them (LEFT_MISSIONS §0.5)
- edit `_Frlg` maps
- touch any other repo
- change HnS's gym, Elite Four, Champion or Red teams
- remove any Heart & Soul credit
