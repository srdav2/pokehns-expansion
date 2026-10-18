# Pokémon Gilded Version: agent instructions

This repo is a fork of Pokémon Heart & Soul (pokeemerald-expansion based). It's being turned into **Pokémon Gilded Version**, the sequel to *Pokémon Sovereign Version*.

**Before doing anything, read:**
1. `docs/GILDED_FORK_PLAN.md`: the rules, mission queue and self-review checklist. Follow it exactly.
2. `docs/GILDED_STORY_BIBLE.md`: all story, characters, teams, jokes and content guardrails (§0.2).

Reference only (partly out of date; the plan says which parts still apply):
- `docs/gilded/REFERENCE_sovereign_handover.md`
- `docs/gilded/REFERENCE_how_to_continue_your_save.md`

Key rules (full list in the plan):
- Work on branch `overnight/gemini`. Never push to `master`. Never force-push.
- One mission = one commit, and push after each one.
- `make -j8` must pass before every commit.
- Never write "verified" or "playtested". Status is `BUILT — NEEDS PLAYTEST`.
- Unattended: never ask questions. Log decisions in `docs/gilded/DECISIONS_LOG.md`.
- Keep all Heart & Soul credits. The owner has the HnS developers' permission to use and modify their files.
- Don't modify any other repo (in particular `pokeemerald-custom`, which is a separate project).
