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

## GF3 — Team MEGA foundation

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Rebranded Team Rocket dialogue in HnS-specific maps and radio text as Team MEGA. Kanto map scripts shared with FRLG now select the Team MEGA text only in the HnS build. Updated HnS Rocket Grunt battle labels and red-tinted the existing male and female grunt palettes. Added the pressure-points var, RED CAP key item, and the 11 additional Team MEGA trainer-class identifiers.

The HnS ROM build passed with the required Arm GNU toolchain and remains 33,554,432 bytes (32 MiB).

**Deferred:**

- Add the 16 named boss trainer IDs and story-bible teams at their level-anchor bands; introduce each battle in its relevant act mission.
- Add palette-swapped trainer portraits for the 11 non-grunt classes; no new art was added.
- Add pressure-prompt choices and the Goldenrod RED CAP gift in their relevant act missions.
- Re-skin the named Giovanni scenes as President Rex Gaudy during their act missions.
- GF6–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…**, visit Slowpoke Well B1F and a Goldenrod Radio Tower floor, and read the dialogue for Team MEGA wording.
- [ ] In **R + Start → Trainers… → Choose trainer from map → Try Battle**, select a grunt in a Rocket Hideout or Radio Tower map; confirm the battle class reads **MEGA GRUNT** and the existing grunt portrait uses the updated red palette.
- [ ] Open **R + Start → Give X… → Give item XYZ…**, enter item ID **901** and quantity **1**, then check the Key Items pocket for the RED CAP and its icon.
- [ ] Open **R + Start → Flags & Vars… → Set Var XYZ…**, select `VAR_PRESSURE_POINTS`, set it to `0`, and confirm the value remains available after saving and reloading.
- [ ] In the HnS build, visit Viridian City Gym and read the Giovanni-slot dialogue for the Team MEGA text; in an FRLG build, confirm the original Team Rocket wording remains.

The Team MEGA foundation still needs the deferred boss teams, class-specific portraits, and playtesting.

## GF4 — Johto Act 1

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added the New Bark research-pressure prompt, Cherrygrove petition, Route 29 rally battles, Route 30 MEGA grunt, and the first two Arceus return events. The return events give anchors 1 and 2 through `ReturnAnchoredMon` and gate the second return behind the first. Sprout Tower now has a Seed Faith donation prompt and two Pastor of Growth battles. Updated New Bark's town-sign text, the Freedom Guide introduction, Elm's government-pressure lines, and Oak's "Patriot Edition" dialogue while leaving HnS's starter, rival, Mystery Egg, and Pokédex event flow in place. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Replace the HnS opening with the Act 1 arrival scene and add the Heritage Officer encounter.
- Add the "GAUDY 4 PRESIDENT (AGAIN)" lab-fence banner, the Route 29 Lawn Ranger, and the two yard signs.
- Add the Route 29 freedom toll/rally progression details and the full prepper-bunker re-skin at Mr. Pokémon's house.
- Re-skin the Falkner scene/dialogue and add the N.R.A. open-season line.
- Add the Sprout Tower Elder's non-endorsement line; the existing Elder/HM flow remains unchanged.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF6–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Start a fresh game; open **R + Start → Utilities… → Warp to map warp…** and visit New Bark Town Lab. Talk to the clerk as each player gender, choose yes/no, and confirm only yes increments `VAR_PRESSURE_POINTS`; the clerk should disappear after either choice.
- [ ] Visit Cherrygrove City and Sprout Tower 1F. Choose yes/no on the petition and Seed Faith prompts; confirm no never charges money, yes increments `VAR_PRESSURE_POINTS`, and each prompt disappears after the choice. Test Seed Faith with less than 1000 money and confirm the prompt remains available.
- [ ] Complete the Mr. Pokémon errand, return to Route 30, and talk to Arceus. Confirm anchor 1 returns at level 5, then leave and re-enter; the Arceus event should remain hidden and the anchor should not duplicate.
- [ ] After Return 1, walk south from Violet onto Route 32 and talk to Arceus. Confirm anchor 2 returns at level 10, then re-enter and confirm it cannot duplicate. Use **R + Start → Flags & Vars… → Set Var XYZ…** to set `VAR_CHERRYGROVE_CITY_STATE` to `3` and **Set Flag XYZ…** to set `FLAG_GILDED_RETURN_1_SEEN` only when testing this event in isolation.
- [ ] Use **R + Start → Trainers… → Choose trainer from map → Try Battle** on a Route 29 Rally Goer, the Route 30 grunt, and both new Sprout Tower Pastors; confirm the trainer classes, dialogue, teams, and levels (5–7).

The Act 1 additions still need playtesting.

## GF5 — Johto Act 2

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added the Azalea SLOWPOKE-T prompt, re-skinned the Slowpoke Well boss battle as Chad Grindwell using a new Sigma Bro trainer with a level 14–16 team, and added Arceus Return 3 outside the Azalea Gym. Return 3 is gated until Kurt's post-Well scene and gives the third anchored Pokémon at level 15. Kept the existing Slowpoke Well/Kurt event progression and the HnS Gym/forest flow in place. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the Union Cave Freedom Toll checkpoint and its two MEGA grunts.
- Add the Ruins of Alph Heritage scholar, Chairman Klaus cameo, SLOWPOKE-T billboard, Bugsy gym picket, and Route 33 yard signs.
- Reclass the Slowpoke Well grunts as Sigma Bros/MEGA grunts and add the remaining act-specific dialogue.
- Re-skin Bugsy's dialogue and add the Ilex Forest Silver dialogue and act-end Giratina scene.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF6–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Start a fresh game; open **R + Start → Utilities… → Warp to map warp…** and visit Azalea Town. Talk to the SLOWPOKE-T promoter by the Mart, choose yes/no, and confirm only yes increments `VAR_PRESSURE_POINTS` and the promoter disappears after either choice.
- [ ] Play the Slowpoke Well sequence through the Proton-slot character. Confirm the battle starts with Chad's dialogue/class and the new team is Machop Lv. 14, Mankey Lv. 15, and Tauros Lv. 16; confirm Kurt's existing return scene still runs afterward.
- [ ] After Kurt's house scene sets `VAR_AZALEA_TOWN_STATE` to 4, talk to Arceus outside the Gym. Confirm anchor 3 returns at level 15; re-enter Azalea Town and confirm the event is hidden and the anchor cannot be duplicated.
- [ ] For an isolated Return 3 test, use **R + Start → Flags & Vars… → Set Var XYZ…** to set `VAR_AZALEA_TOWN_STATE` to `4`, then clear `FLAG_GILDED_RETURN_3_SEEN`; use **R + Start → Utilities… → Warp to map warp…** to return to Azalea and trigger Arceus.
- [ ] Use **R + Start → Flags & Vars… → Set Var XYZ…** to set `VAR_PRESSURE_POINTS` to `0`, test both promoter responses, then inspect the var again to confirm the yes/no behavior.

The Act 2 additions still need playtesting.

## GF6 — Johto Act 3

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added the GAUDY TOWER sign text, a Radio Tower RED CAP offer that gives `ITEM_RED_CAP` and increments pressure only when accepted, and the Dept. Store Ball Show prompt. Added an optional Colonel Buckshot battle with a four-Pokémon team at levels 20–22. Both prompts can be declined without a penalty. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the six Goldenrod rally NPCs, gold-lettered tower treatment, and Dept. Store floor signs.
- Add the station MEGA grunt(s), Whitney's post-gym scripted scene and dialogue, and Bill's PC-reunion setup.
- Add the Goldenrod Underground Debate Club and Commissar Blair cameo.
- Re-text the National Park contest as Open Season and add Colonel Buckshot's catch-and-release exchange.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF7–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Start a fresh game; use **R + Start → Utilities… → Warp to map warp…** to visit Goldenrod Radio Tower 1F. Choose yes on the RED CAP offer and confirm the item is received once, the prompt disappears, and `VAR_PRESSURE_POINTS` increases by one.
- [ ] Start another test save or reset the prompt flag; choose no on the RED CAP offer and confirm neither the item nor a pressure point is awarded, and the prompt disappears. Fill Key Items before choosing yes and confirm the offer remains available after the bag-full message.
- [ ] Use **R + Start → Utilities… → Warp to map warp…** to visit Goldenrod Dept. Store 7F. Choose yes/no on the Ball Show prompt and confirm only yes increments `VAR_PRESSURE_POINTS`.
- [ ] Challenge Colonel Buckshot on the 7F roof; confirm the optional battle uses Remoraid Lv. 20, Krabby Lv. 20, Magnemite Lv. 21, and Clauncher Lv. 22, and cannot be repeated after defeat.
- [ ] Read the Radio Tower sign in Goldenrod City and confirm it displays GAUDY TOWER while the underlying HnS map/warp flow remains unchanged.

The Act 3 additions still need playtesting.

## GF7 — Johto Act 4

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Warden Pell's Heritage Officer battle at the Burned Tower entrance with a three-Pokémon Team 1 at levels 24–26; defeating him clears the doorway and records the gate flag. Added the opt-in Unown Ancestry Kit prompt at the Dance Theatre, which increments `VAR_PRESSURE_POINTS` only on yes. Added Eusine's Suicune corkboard text in the Ecruteak Pokémon Center and updated Morty's Gym introduction while preserving his battle and badge flow. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the three Heritage Officer battles on Routes 37/38 and a dedicated Pedigree Certificate booth NPC.
- Gate both Burned and Tin Towers through one shared Heritage Order check; this partial build places Pell at the Burned Tower entrance only.
- Add Pell's wall-plan poster in the Pokémon Center and the full Act 4 tower scene and Silver dialogue revisions.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF8–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Ecruteak City. Approach the Burned Tower entrance; confirm Pell's pedigree challenge starts and blocks entry. Defeat him, then confirm the tower entrance is reachable and Pell stays gone after leaving and returning.
- [ ] Open **R + Start → Trainers… → Choose trainer from map → Try Battle** in Ecruteak City; select Pell and confirm the Heritage Officer class and Dunsparce Lv. 24, Stantler Lv. 25, and Sudowoodo Lv. 26.
- [ ] Visit **Ecruteak City Pokémon Center** and interact with the board on the upper wall; confirm Eusine's blue, majestic, running Suicune claim appears.
- [ ] Visit **Ecruteak City Dance Theatre** and speak with the ancestry-kit promoter. Set `VAR_PRESSURE_POINTS` to `0` through **R + Start → Flags & Vars… → Set Var XYZ…**, choose yes, and confirm it increments to `1`; for a separate no test, clear `FLAG_GILDED_PRESSURE_PROMPT_ECRUTEAK` through **R + Start → Flags & Vars… → Set Flag XYZ…**, reset the var to `0`, and confirm declining adds no point.
- [ ] Challenge Morty through the existing Ecruteak Gym flow; confirm the revised introduction appears and the original battle, Fog Badge, TM, and post-battle state still occur.

The Act 4 additions still need playtesting.

## GF8 — Johto Act 5

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Sage Purely at the top of Olivine Lighthouse with the Rapidash Paste pressure prompt and Team 1 battle. The prompt increases `VAR_PRESSURE_POINTS` only when accepted; both choices continue into the story battle, and defeating Purely removes her from the map. Her four-Pokémon team uses the `A_JAS` 34–36 anchor band. The existing Jasmine-to-Cianwood medicine quest remains unchanged. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the Tariff Trouble side quest and the normal-price port shop.
- Reclass two Lighthouse trainers as Wellness Gurus and add the Cianwood Alpha Dojo with Brad Grindwell and its temporary trainer-class changes.
- Add the Cianwood pharmacy dialogue, cold-plunge beach NPC, and Olivine Café tariff menu.
- Add the remaining Jasmine/Amphy re-skin and the requested Lighthouse dialogue dressing.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF9–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Olivine City Lighthouse. Approach Jasmine's floor; choose yes on Sage Purely's Rapidash Paste prompt and confirm `VAR_PRESSURE_POINTS` increases by one before the battle. Confirm Jasmine's objection says real medicine is still needed.
- [ ] For a separate no test, use **R + Start → Flags & Vars… → Set Flag XYZ…** to clear `FLAG_GILDED_PRESSURE_PROMPT_OLIVINE` and `FLAG_GILDED_SAGE_PURELY_DEFEATED`, set `VAR_PRESSURE_POINTS` to `0`, and decline the paste. Confirm no pressure point is added and Sage still challenges the player.
- [ ] Use **R + Start → Trainers… → Choose trainer from map → Try Battle** on Sage Purely; confirm the Wellness Guru class and Gloom Lv. 34, Weepinbell Lv. 35, Foongus Lv. 35, and Comfey Lv. 36.
- [ ] Defeat Sage, leave and re-enter the Lighthouse, and confirm she stays gone while Jasmine remains available.
- [ ] Continue through Jasmine's existing medicine request; confirm `VAR_OLIVINE_CITY_STATE` advances to `3` and the Cianwood pharmacy quest remains reachable.

The Act 5 additions still need playtesting.
