# Copilot run: perfect Pokémon + Pokémon Left (Rift) build

**Who:** GitHub Copilot (desktop app), repo `srdav2/pokehns-expansion`.
**The owner is asleep.** Never ask a question or wait for input. If something is unclear, take the safest documented option, log one line in `docs/gilded/DECISIONS_LOG.md`, and continue.

## Set-up (once)

```
git fetch origin
git checkout -b left-rift origin/gilded-pass-2
git merge origin/master
git push -u origin left-rift
```
The merge only adds files under `docs/` and `tools/rift/`. If git reports a conflict anywhere else, stop the merge (`git merge --abort`), log it, and continue on `left-rift` without it.

**All work stays on `left-rift`. Never push to `master`. Never force-push.**

## Build

```
PATH="/Users/stuartdavis/.gemini/antigravity/brain/f8571f88-b293-4162-b3ea-cfb03abd1a26/scratch/arm-gnu-toolchain/Payload/bin:/usr/bin:/bin:/usr/sbin:/sbin" make hns -j8
```
It must finish with zero errors. After LX7 the ROM is `pokeleft.gba`; before that it's `pokehns.gba`.

## Order of work (one commit each, push after each)

| Order | Task | Brief |
| --- | --- | --- |
| 1 | **Perfect IVs/EVs** for the player's Pokémon | `docs/PERFECT_PLAYER_MONS.md` |
| 2–10 | **LX0 → LX8**, the Pokémon Left / Rift missions | `docs/rift/LEFT_MISSIONS.md`, with `docs/rift/RIFT_CONTRACT.md` as the spec |

`LEFT_MISSIONS.md` §0 has the rest of the rules: fix limit, status wording, self-review, text width, shared files copy-only, and keep the HnS credits and teams. Its branch step is already done by the set-up above.

**Two links between the tasks:**
- In **LX2**, change `ShouldSweepBox()` in `src/perfect_player_mons.c` to `return Rift_IsBoxDepositable(boxId);`, so the perfect-stats sweep never writes Pokémon Right's boxes (1–7).
- In **LX1**, if `CopyPartyAndObjectsToSave()` is the save choke point, keep the order: `MaxAllPlayerMonStats();` first, then `Rift_StampForSave();`, then the rest.

**Priority if you run short:** LX1–LX5 are the core: the save, the box rules, both finales and the arrival. LX6–LX7 (story audit, rename) can wait. LX8 (report) always runs last.

## When you stop

Write `docs/rift/LEFT_REPORT.md` (LX8) and push it to `left-rift`. Mention the perfect-IVs/EVs task in it too.
