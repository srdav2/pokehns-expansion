# Pokémon Gilded Version: instructions for coding agents (GitHub Copilot and others)

This repo is a fork of Pokémon Heart & Soul (pokeemerald-expansion based). It's being turned into **Pokémon Gilded Version**, the sequel to *Pokémon Sovereign Version*. The owner has the Heart & Soul developers' permission to use and modify their files. Keep all existing HnS credits.

## Read first
1. `docs/GILDED_FORK_PLAN.md`: rules, the mission queue (GF0–GF17) and the self-review checklist.
2. `docs/GILDED_STORY_BIBLE.md`: all story, characters, teams, jokes, and the **content guardrails in §0.2** (non-negotiable).

## How to work when you're GitHub Copilot (cloud agent)
- **Each task is ONE mission** from the queue in `docs/GILDED_FORK_PLAN.md` §2. The task text names the mission ID (for example "Do GF0"). Do only that mission.
- Your session is limited to about **59 minutes**. Keep the mission's scope tight:
  - Commit as soon as something builds.
  - If time runs short, finish with what builds, mark the mission `BUILT_PARTIAL`, and list the rest under `Deferred:` in `docs/gilded/mission_log.md`.
- Your branch and PR target `master`. One PR per mission, titled `Gilded <ID>: <title>`.
- **Build:** `make -j$(nproc)` must succeed with zero errors before you finish. The setup steps already installed the toolchain and ran a first build. The repo's CI workflow also builds the ROM on your PR; make sure it passes.
- **Before finishing**, run the self-review in `docs/GILDED_FORK_PLAN.md` §3. Then:
  - update `docs/gilded/mission_log.md` with `Status: BUILT — NEEDS PLAYTEST`, a `Deferred:` list, and a playtest checklist with debug-menu steps
  - update `docs/gilded/registry.md` for every new flag, var, trainer, map and special.
- Never write "verified" or "playtested". Nobody has played it.
- Ask no questions. Take the documented default and record it in `docs/gilded/DECISIONS_LOG.md`.

## Hard rules
- Don't use `filler_*` save fields. Add named fields only.
- Never reuse an existing HnS flag, var or trainer slot that something still reads. Grep before allocating.
- Text must fit the message box: about 34 characters per line, 2 lines per box.
- No real people's names, no slurs, no real extremist slogans or symbols, no real tragedies (bible §0.2).
- Keep HnS's gym leader, Elite Four, Champion and Red teams and levels. Change dialogue only.
