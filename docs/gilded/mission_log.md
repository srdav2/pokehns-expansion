# Gilded mission log

## GF0 — Setup and audit

**Status: BUILT — NEEDS PLAYTEST**

Built the HnS target with the requested Arm GNU toolchain PATH. The bare default `make -j8` selects the Emerald target in this checkout; the HnS ROM is built with `make hns -j8`. The resulting baseline ROM is **33,554,432 bytes (32 MiB)**. The title/header now use the Gilded working title.

Expansion version found in `include/constants/expansion.h`: **1.15.2**.

**Deferred:**

- Apply the Team MEGA mapping to HnS event scripts (scheduled for GF3 and act missions).
- GF1–GF17 are not started in this GF0 commit.
- GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Boot the HnS ROM to the title screen; confirm the GILDED banner and game header name, then start a fresh game and follow HnS starter flow.
- [ ] Open the overworld debug menu with **R + Start**; use **ROM Info… → Expansion Version** and **ROM space**.
- [ ] Use **Utilities… → Warp to map warp…** to inspect the audited Johto event maps.
- [ ] Use **Trainers… → Choose trainer from map → Try Battle** on a selected event-map trainer.
- [ ] Use **Flags & Vars… → Set Flag XYZ… / Set Var XYZ…** only with documented test values; confirm save/reload preserves the event state.

This baseline and title/header change still need playtesting.

## GF1 — Rift foundation (New Game version)

**Status: BUILT — NEEDS PLAYTEST**

Added the New Game Lost Rift trio at levels 5, 10, and 15. Each is a distinct, randomly selected enabled non-legendary base species, created with the player's OT and stored in named Pokémon Storage save fields. Added the base-form/level reset helper and the `ReturnAnchoredMon` special, which returns each anchor once to the party or PC. Added a debug submenu for testing all three returns.

**Deferred:**

- Importing the player's actual Sovereign Pokémon remains deferred to GF-IMP.
- Story scenes that call the return special are deferred to the act missions.
- Exercising de-evolution with an evolved/imported anchor is deferred until GF-IMP or a dedicated test fixture; the New Game trio begin as base species.
- GF2–GF17 are not started.
- `make check BUILD=hns -j8` could not reach the tests: `test/test_runner.c` fails to compile because `include/fake_rtc.h` uses `struct SaveBlock3` before its definition. No GF1 test was added because the HnS test setup does not currently build.

**Playtest checklist:**

- [ ] Start a new game; open the overworld debug menu with **R + Start** and select **Utilities… → Lost Rift anchors… → Return anchor 1/2/3**. Confirm each returned Pokémon has its saved level (5/10/15), a base species, and the player's OT.
- [ ] Invoke the same **Return anchor** action twice; confirm it is returned only once.
- [ ] Fill the party, then invoke an unused anchor; confirm it is stored in the PC and its return is recorded.
- [ ] Save and reload after returning one anchor; confirm the remaining anchors can still be returned and the first cannot be duplicated.
- [ ] Once an evolved anchor test fixture is available, open **R + Start → Utilities… → Lost Rift anchors…**, return that anchor, and confirm it de-evolves to base at its saved level while preserving nickname, IVs, nature, shininess, and OT; check EVs reset and level-up moves/experience match.

The Rift foundation and debug actions still need playtesting.

## GF2 — Quality of life

**Status: BUILT — NEEDS PLAYTEST**

Moved the party-wide Gen 6 Exp. Share from New Game initialization to Elm's starter-receipt sequence and enabled it when awarded. New games now begin with the existing Running Shoes flags set; Mom's intro skips the already-completed shoe handoff.

**Deferred:**

- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF3–GF17 are not started.

**Playtest checklist:**

- [ ] Start a new game, take a few steps before speaking to Mom downstairs, and confirm B-dash works immediately.
- [ ] Finish Elm's starter choice; open the Bag's Key Items pocket and confirm the Exp. Share was received once and is enabled. Confirm the scene continues through the nickname prompt and starter flow.
- [ ] Battle with multiple Pokémon in the party while the Exp. Share is enabled; confirm non-participants gain experience.
- [ ] Use the Exp. Share in Key Items to turn it off, battle again and confirm the party-wide effect stops; turn it back on and confirm it resumes.
- [ ] Open the overworld debug menu with **R + Start → Flags & Vars… → Toggle Running Shoes**; confirm the debug toggle still switches the run flag both ways.

GF2's startup flow and experience behavior still need playtesting.
