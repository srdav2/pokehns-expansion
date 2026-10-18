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
