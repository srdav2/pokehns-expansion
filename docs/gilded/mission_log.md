# Gilded mission log

## Perfect IVs/EVs for player Pokémon

**Status: BUILT — NEEDS PLAYTEST**

Added configurable perfect IVs (31) and EVs (252 per stat) for owned Pokémon. The sweep covers the party, every PC box, and both Day Care slots; acquisition hooks cover catches, scripted gifts, hatches, and trades. Existing Pokémon are upgraded after loading and before each normal save. Summary-screen IV/EV values were already enabled. The save layout is unchanged.

**Deferred:**

- None.

**Playtest checklist:**

- [ ] Load an existing save. Open the summary of a party Pokémon and a PC Pokémon; confirm all IVs are 31 and all EVs are 252.
- [ ] Start a new game and check the Elm starter's summary for 31 IVs and 252 EVs in every stat.
- [ ] Catch a wild Pokémon and confirm its battle stats are unaffected; after capture, check its summary. Repeat with a full party so it goes to the PC.
- [ ] Battle a trainer and confirm the trainer's Pokémon retain their normal IVs/EVs.
- [ ] Hatch an egg and complete an in-game trade, if reachable; confirm each received Pokémon has the configured values.

## LX0 — Test setup

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

`python3 tools/rift/rift_savetool.py --selftest` passed. Rebuilt the HnS ROM successfully with the documented command.

**Deferred:**

- `make check BUILD=hns` and C test setup were skipped as instructed.

**Playtest checklist:**

- [ ] No in-game debug-menu steps apply to this tooling-only mission; rerun `python3 tools/rift/rift_savetool.py --selftest` and confirm it prints `selftest OK`.

## LX1 — Integrate the contract

**Status: BUILT — NEEDS PLAYTEST**

Copied the shared Rift contract/header/source without edits and added the Left-specific game configuration. `PokemonStorage` now ends in the shared `RiftRecord`; fresh games initialize it and `CopyPartyAndObjectsToSave()` stamps it before every full-save copy. This covers normal, Hall of Fame, overwrite, link/e-Reader, and link-full-save preparation paths; link/e-Reader saves write only SaveBlocks and do not persist PC storage. Legacy Left saves migrate Pokémon from boxes 1–7 into boxes 8–14 and discard the obsolete pass-1 anchors. Anchor returns use the shared record and can fall back to a depositable box. The title screen classifies foreign records, shows T1–T4, hides Continue for foreign saves, and asks for a second confirmation before erasing; arrival is currently a placeholder. Added the debug fixture **Rift: fake a Right first-finish save**. `make hns -j8` completed with zero errors, and fingerprint comparison printed `Rift compatibility: OK`.

**Deferred:**

- ARRIVE THROUGH THE RIFT still says "coming soon"; implement the arrival sequence in LX4.
- PC box ownership enforcement and migration overflow UX are LX2.
- Finale crossing is LX3; second-finale behavior is LX5.
- No on-device save/reload or title-screen playtest has been performed.

**Playtest checklist:**

- [ ] Start a fresh Left game; open **R + Start → Utilities… → Lost Rift anchors… → Rift: fake a Right first-finish save**. Save in-game, reset, and confirm T1 appears, Continue is absent, and **ARRIVE THROUGH THE RIFT** is the first menu option.
- [ ] Select **NEW GAME** on that foreign save; confirm the erase warning requires a second YES/NO and that NO returns without erasing.
- [ ] Select **ARRIVE THROUGH THE RIFT**; confirm the LX1 placeholder appears without modifying the foreign save.
- [ ] Load a pre-contract Left save with Pokémon in boxes 1–7; confirm migration packs them into boxes 8–14 and the next save stamps Left.
- [ ] In a Right first-finish fixture, call each **Return anchor 1/2/3** debug action; confirm the returned Pokémon has levels 5/10/15 and cannot be returned twice. Fill party and depositable boxes to check the no-room path leaves the anchor returnable.

## LX2 — PC box ownership

**Status: BUILT — NEEDS PLAYTEST**

Every PC insertion and free-space path now uses Left's depositable boxes, including catches, gifts, eggs, Day Care, scripted storage, bug-contest storage, PC fullness checks, and anchor returns. The storage UI skips boxes that cannot be viewed, and scripted box-mon selection, Move Items, placement, release/marking, wallpaper changes, and box renaming cannot modify sealed boxes. Legacy overflow remains viewable and withdraw-only; summary viewing is retained, but move reordering and PokéNav markings are blocked there. Box healing and the perfect-stats sweep write only to depositable boxes. General debug PC-fill actions also skip sealed boxes; the LX1 fake-Right fixture intentionally populates Right-owned boxes for testing. Current-box normalization and wallpaper index clamping are in place. `make hns -j8` completed with zero errors; ROM size is **33,554,432 bytes (32 MiB)**.

**PC loop/access inventory** (`R` = reads box data; `W` = writes box data; policy-only loops are marked):

- `src/rift_shared.c`: `Rift_FirstDepositableBox` (policy read); `Rift_CountMonsInBoxes` (R); `Rift_MigrateLegacyStorage` (R/W, packs into owned boxes and clears migrated sources); `Rift_FinishArrival` (R/W, defensive contract sanitation); `Rift_PrepareCrossing` (R/W, own boxes only).
- `src/field_specials.c`: `ReturnAnchoredMon` (R/W, depositable fallback); `IsDestinationBoxFull` (R, searches only depositable boxes).
- `src/pokenav.c`: ribbon-presence scan (R, all boxes); `src/lottery_corner.c`: lottery scan (R, all boxes).
- `src/pokenav_ribbons_list.c`: `BuildBoxMonRibbonList` and `PlayerHasRibbonsMon` (R, all boxes); `src/pokenav_conditions_search_results.c`: `BuildBoxMonSearchResults` (R, all boxes).
- `src/debug.c`: the LX1 fake-Right fixture clears boxes 1–7 and writes ten fixture Pokémon there (W, intentional test setup); Pokédex-completion scan (R); fast/slow PC-fill scans (R/W, depositable boxes only).
- `src/pokemon.c`: `CopyMonToPC` (R/W, depositable boxes only); `IsPokemonStorageFull` (R, depositable boxes only).
- `src/perfect_player_mons.c`: stats sweep (R/W, depositable boxes only); `src/script_pokemon_util.c`: `HealPlayerBoxes` (R/W, depositable boxes only).
- `src/pokemon_storage_system.c`: `CountMonsInBox` (R, specified box); `GetFirstFreeBoxSpot` (R, depositable box only); `ResetPokemonStorageSystem` clears all box contents and initializes box names/wallpapers for a new game (W); `GetNextAllowedBox` reads ownership/viewability policy; `AtLeastThreeUsableMons`, `RunCanReleaseMon`, `CountStorageNonEggMons`, `CountAllStorageMons`, and `AnyStorageMonWithMove` (R, whole-PC scans); `CheckFreePokemonStorageSpace` (R, depositable boxes only); `MultiMove_SaveMons` and `MultiMove_CreatePlacedMonIcons` (R, current box); `MultiMove_RemoveMonsFromBox` (W, current box; Move Items is restricted to depositable boxes); `MultiMove_SetPlacedMonData` (R/W, current depositable box); `StorePokemonInBox` (R/W, depositable boxes only); `GetFirstAliveBoxPokemon` (R, viewable boxes).

**Deferred:**

- `make check BUILD=hns` was skipped as instructed for LX0; no new C test harness was added.
- No on-device PC/full-box playtest has been performed.

**Playtest checklist:**

- [ ] Start a test save and fill all six party slots. With **R + Start → Give X… → Pokémon (Basic)**, give 210 Pokémon so they fill boxes 8–14; give one more and confirm the normal PC-full message appears rather than writing into boxes 1–7.
- [ ] Open **R + Start → Utilities… → Lost Rift anchors… → Rift: fake a Right first-finish save**, then open the PC. Confirm boxes 1–7 cannot be opened or chosen as a deposit target, while Left boxes can.
- [ ] In a fixture with legacy overflow, confirm an overflow box can be viewed and Pokémon withdrawn, but wallpaper/name changes, Move Items, release, marking, summary move reordering, and scripted selection cannot write to it.

## LX3 — First finale

**Status: BUILT — NEEDS PLAYTEST**

The Axis now separates the first-game crossing from the existing second-game ending. The first-game scene is cutscene-only for Giratina, checks both contract blockers, shows T5–T7, allows up to three ranked party selections while retaining at least one Pokémon, sanitizes the owned PC boxes, saves the first-finish record, shows T8/T9, and starts credits. Selected Pokémon are rejected if eggs; selected held items are included in the T8 item totals, including when the Bag is full. Returning after a completed first finish no longer replays the scene. `make hns -j8` completed with zero errors; ROM size is **33,554,432 bytes (32 MiB)**. No shared Rift file was modified.

**Deferred:**

- `make check BUILD=hns` remains skipped per the LX0 instruction; no on-device crossing playtest has been performed.
- LX4 arrival and LX5 second-finale flow remain deferred to their missions.
- The contract's `Rift_StoreAnchor` API does not return anchor-held-item counts; Left works around this locally. See the LX3 contract request in `DECISIONS_LOG.md`.

**Playtest checklist:**

- [ ] Start a fresh Left save. Open **R + Start → Flags & Vars… → Set Flag XYZ…**, set `FLAG_DEFEATED_RED` (`0x23B`), then use **R + Start → Utilities… → Warp to map warp…** to choose Giratina Axis.
- [ ] With a fused Pokémon in fusion storage, trigger the Axis scene; confirm T5 appears and crossing does not begin. Remove the fusion, leave overflow in boxes 1–7, and confirm T6 also appears.
- [ ] Clear both blockers, then refuse T7; confirm no party Pokémon or PC data changes.
- [ ] Accept T7 with at least four party Pokémon, including an egg and three eligible Pokémon with held items. Select the egg first, then select three valid Pokémon in a known order; confirm the egg is rejected, the party retains one Pokémon, and ranks follow selection order.
- [ ] Check the Bag and T8 counts with room for all three items, then repeat with a full Bag to confirm anchor-held items that do not fit are included in the lost-item count.
- [ ] Inspect the save with `python3 tools/rift/rift_savetool.py <save>`; confirm Left is first-finished, the anchor count/levels are correct, and boxes 8–14 contain no held items.
- [ ] Re-enter the Axis after first finish; confirm the scene does not replay.

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

## GF9 — Johto Act 6

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Pressure Prompt 9 at the Mahogany shop counter: Gaudy Gold Kicks cost 9999, and accepting gives one Iron Ball and one pressure point. Declining has no penalty and continues to the regular mart; insufficient money or bag space does not charge the player or consume the prompt. Replaced the B3F Petrel-slot battle with Barry Blaster using the `A_PRYCE` 32–34 team, and retained the HnS password and hideout progression while changing the reveal and transmitter-shutdown dialogue. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Re-skin the Lake of Rage Red Gyarados/Lance sequence and the remaining Mahogany town, hideout-floor, and grunt dialogue.
- Rebrand the remaining Rocket Hideout password/interim-boss text and map presentation as Rage Radio.
- Re-skin Barry's fake-Director role in the Radio Tower during GF10, along with the full Team MEGA hideout trainer reclassification.
- Update Pryce's dialogue and Glacier Badge scene.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF10–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Open **R + Start → Flags & Vars… → Set Var XYZ…** and set `VAR_MAHOGANY_TOWN_STATE` to `14`; set `VAR_PRESSURE_POINTS` to `0`. Then use **Utilities… → Warp to map warp…** to visit the Mahogany shop and talk to the clerk. Choose **No**; confirm no money or pressure points are lost and the regular mart opens.
- [ ] For a fresh prompt state, clear `FLAG_GILDED_PRESSURE_PROMPT_MAHOGANY` through **R + Start → Flags & Vars… → Set Flag XYZ…** and set money with **R + Start → Give X… → Max Money**. Return to the shop, choose **Yes**, and confirm the 9999 cost, one Iron Ball, one pressure point, and that the regular mart is available on the next interaction.
- [ ] Clear the prompt flag, set `VAR_PRESSURE_POINTS` to `0`, and choose yes with a full Items pocket; confirm no money is removed, no pressure point is added, and the offer remains available. Repeat with less than 9999 money and confirm the same no-charge behavior.
- [ ] Play through the existing Mahogany/Lake of Rage route until the Rocket Hideout B3F boss event; confirm Barry's battle uses Exploud Lv. 32, Primeape Lv. 33, Noibat Lv. 33, and Gyarados Lv. 34, and that the Murkrow/password/stair progression completes after the battle.
- [ ] Leave and re-enter the shop and hideout after the choices/battle; confirm the prompt and boss do not repeat, the regular shop remains reachable, and the existing HnS route progression is intact.

The Act 6 additions still need playtesting.

## GF10 — Johto Act 7

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Pressure Prompt 10 to the 4F stair-side grunt encounter: yes adds one pressure point, no does not, and either choice continues into the existing battle. Re-skinned the 5F fake Director as Barry Blaster using the GF9 Barry trainer and retained the Basement Key/warehouse progression. Replaced the final Archer-slot battle with President Rex Gaudy's Radio Tower Team 1 at levels 44–46, updated the takeover/defeat dialogue, and retained the existing Radio Tower state transitions and real-Director rescue. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the Chad and Colonel Buckshot Team 2 battles and the Warden Pell Team 2 battle; reclass and re-text the other Radio Tower floor trainers.
- Rework the full tower takeover broadcast/cutscene and add the gold exterior sign treatment.
- Add Gaudy's gold Pidgeot departure, Silver's reaction, and the act-end Giratina scene.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.
- GF11–GF17 have not started. GF-IMP remains skipped as directed by the plan.

**Playtest checklist:**

- [ ] Play through the Radio Tower takeover or open **R + Start → Utilities… → Warp to map warp…** to reach 4F after the takeover; clear `FLAG_GILDED_PRESSURE_PROMPT_TOWER_STAIRS` and set `VAR_PRESSURE_POINTS` to `0` with **Flags & Vars…**. Speak with the stair-side grunt and choose yes; confirm one pressure point is added and the existing battle still starts.
- [ ] For a separate test, clear the prompt flag again, reset `VAR_PRESSURE_POINTS` to `0`, and choose no. Confirm no point is added and the same battle/progression remains available.
- [ ] Use **R + Start → Trainers… → Choose trainer from map → Try Battle** on the 5F President; confirm the MEGA ADMIN battle contains Persian Lv. 44, Gholdengo Lv. 44, Copperajah Lv. 45, Kingambit Lv. 45, and Donphan Lv. 46.
- [ ] Play the 5F office sequence; confirm Barry's disguise reveal, battle, Basement Key reward, and Underground Warehouse clue remain reachable. Continue to the final battle and confirm Gaudy's lines, the Radio Tower state transition, and the real Director scene.
- [ ] Leave and re-enter the tower after the boss event; confirm the takeover battles and fake Director do not restart and the real Director remains available.

The Act 7 additions still need playtesting.

## GF11 — Johto Act 8

**Status: BUILT — NEEDS PLAYTEST**

Added Clair's recount line and yes/no reply choice after the existing battle. Either reply continues through the original Dragon's Den challenge setup without changing Clair's team, badge flow, or event state. Added the Elder's sixth quiz question; choosing “Demand a recount” displays the required response and repeats the question, while “Train harder” continues through the existing badge/Dratini flow. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- None for the Act 8 story beats in scope.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Blackthorn City Gym. Defeat Clair; confirm her recount line and reply prompt appear. Choose **Yes**, confirm “That's what THEY say.” appears, then confirm the existing Dragon's Den directions and challenge state continue.
- [ ] For a separate reply test, use **R + Start → Utilities… → Warp to map warp…** to return to Blackthorn Gym after resetting the test save or gym state; choose **No** and confirm “…Fine.” appears before the same Dragon's Den progression.
- [ ] To test the Elder directly, open **R + Start → Flags & Vars… → Set Var XYZ…**, set `VAR_BLACKTHORN_CITY_STATE` to `2`, and set `VAR_DRAGONS_DEN_QUIZ` to `0`; use **Utilities… → Warp to map warp…** to enter Dragon's Den Shrine and complete the first five questions correctly.
- [ ] At question six, choose **Demand a recount**. Confirm “…Go away and come back.” appears, the Elder quiz remains active, and no badge/Dratini progression occurs. Then choose **Train harder** and confirm the original quiz completion and Clair event flow continue.
- [ ] Complete the canonical flow, leave and re-enter the Shrine, and confirm the existing Elder/Dratini behavior is unchanged; confirm Clair's HnS party and levels remain unchanged.

The Act 8 changes still need playtesting.

## GF12 — Johto Act 9

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Pressure Prompt 11 at the Indigo Plateau Pokémon Center entrance, with two Rally Goer battles and teams in the Elite Four level band. Updated Will, Koga, Bruno, and Karen's first-challenge dialogue without changing their teams or the League sequence. Added Giratina's appearance and “Halfway. Keep spinning.” line to the first Hall of Fame cutscene. Bill now gives the post-League Hoenn-storage line once and records the scene flag; the storage unlock itself remains a stub. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Build the three-tile Route 27 / Tohjo Falls wall, two Border Agent battles, and Warden Pell's Team 3 gate battle.
- Add physical “STOP THE STEEL!” rally signs and the revolving-door scene.
- Re-skin the Victory Road Silver encounter.
- Implement and call `UnsealHoennStorage()` when GF-IMP provides the importer-backed storage behavior; this mission only adds Bill's scene and one-time flag.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Flags & Vars… → Set Var XYZ…**, set `VAR_PRESSURE_POINTS` to `0`, clear `FLAG_GILDED_PRESSURE_PROMPT_INDIGO`, and warp through **Utilities… → Warp to map warp…** to Indigo Plateau's Pokémon Center. Choose **Yes** at the entrance prompt and confirm the counter increases to `1` and the prompt disappears.
- [ ] Clear `FLAG_GILDED_PRESSURE_PROMPT_INDIGO` again, reset `VAR_PRESSURE_POINTS` to `0`, and choose **No**. Confirm the counter stays at `0`, the prompt disappears, and the two rally battles remain reachable.
- [ ] Use **R + Start → Trainers… → Choose trainer from map → Try Battle** on both new Indigo Rally Goers; confirm their teams are Machoke Lv. 54 / Primeape Lv. 55 and Torkoal Lv. 55 / Houndoom Lv. 56.
- [ ] Play the first Elite Four challenge; confirm Will, Koga, Bruno, and Karen's new introductory lines appear while their HnS teams, room progression, and rematches remain unchanged.
- [ ] Complete the Johto League through the normal route; confirm Giratina appears during the first Hall of Fame scene, speaks “Halfway. Keep spinning.”, and the Hall of Fame recording/game-clear sequence still completes.
- [ ] After becoming Champion and receiving Bill's Eevee, visit **Goldenrod City → Bill's House** and speak with Bill. Confirm the storage message appears once, then confirm the scene flag prevents the one-time message from replaying; PC storage behavior remains deferred until GF-IMP.

The Act 9 changes still need playtesting.

## GF13 — Kanto Acts 10–11

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Rebranded the S.S. Aqua boarding desk, onboard route/arrival announcements, and captain's ride line as the Mar-a-Magikarp while preserving ticket checks and travel state. Replaced Lt. Surge's opening dialogue with the National Rattata Association recruiter rejection; his battle and badge flow are unchanged. The HnS ROM build passed with the required Arm GNU toolchain and is **33,554,432 bytes (32 MiB)**.

**Deferred:**

- Add the first-class washroom “TOP SECRET POKéDEX ENTRIES” gag and reclass the S.S. Aqua sailors as Rally Goers/Crypto Bros.
- Add the full Vermilion N.R.A. recruitment booth scene; Surge currently delivers the refusal in his gym introduction.
- Implement the Act 11 Grindwell Power Plant/Machine Part sequence, $GAUDY mining interior, Chief Thorne cameo, Chad + Brad double battle, Machine Part return, and Misty's date.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit the Vermilion City Port. Speak with the sailor; confirm the Mar-a-Magikarp name and existing ticket/boarding choices.
- [ ] Board using the existing S.S. Ticket; speak with the onboard sailor on both the Vermilion and Olivine routes. Confirm the Mar-a-Magikarp en-route and arrival messages appear and the existing return-to-port flow still works.
- [ ] Visit the captain's room; confirm the updated Mar-a-Magikarp ride line fits its boxes and the grandchild rescue scene is unchanged.
- [ ] Visit Vermilion Gym and speak with Lt. Surge. Confirm the National Rattata Association refusal appears before his unchanged HnS battle; win and confirm the Thunder Badge and existing rewards/state still occur.
- [ ] Confirm Lt. Surge's team and levels remain unchanged; continue to Diglett's Cave and confirm Snorlax is unaffected.

The Kanto Acts 10–11 changes still need playtesting.

## GF14 — Kanto Acts 12–13

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Updated Sabrina's Gym introduction with the D.O.G.E. auditor exchange and “I replied with my mind,” while preserving her existing battle and badge flow. Updated Erika's fountain dialogue with the banned-scent joke and her sleepy reaction. Replaced Celadon Game Corner sign text with the GAUDY CASINO and its fourth-bankruptcy notice. No gym leader teams or levels were changed.

**Deferred:**

- Rebrand Silph Co. as D.O.G.E. headquarters, add Pressure Prompt 12, and add the three auditor battles.
- Add Erika's physical perfume-shop notice and remaining Celadon/Gaudy Casino content.
- Re-skin Fuchsia's Safari Zone entrance as the Big Game Ranch; add Colonel Buckshot and Janine's dialogue.
- Add Cinnabar MEGA officials and the Pewter Museum Kabutops exhibit/Brock/Pell content.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Saffron City Gym. Speak with Sabrina; confirm the auditor exchange and “I replied with my mind” fit the boxes, then confirm the existing battle, Marsh Badge, TM, and post-battle state work.
- [ ] Confirm Sabrina's HnS team and levels remain unchanged.
- [ ] Warp to Celadon City and speak with Erika at the fountain. Confirm the banned-scent and sleepy lines appear, then confirm the existing transition moves her to the Fighting Dojo.
- [ ] Interact with the Game Corner sign in Celadon City; confirm it reads GAUDY CASINO, BANKRUPT (4th time), and UNDER NEW GAUDY MANAGEMENT.
- [ ] Re-enter Celadon City after Erika's fountain event; confirm she remains at the Dojo and the existing Erika battle/state flow is unchanged.

The Act 12–13 additions still need playtesting.

## GF15 — Kanto Act 14: Comeback Rally

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Replaced Viridian City's secondary sign text with the “THE COMEBACK RALLY — BIGGER THAN EVER” banner. No Gym battle, trainer party, or progression state was changed.

**Deferred:**

- Add Silver's confrontation cutscene, President Gaudy's Comeback Rally Team 2 battle and Mega Tyranitar, and his retirement/Team MEGA ending.
- Integrate the rally around the Viridian Giovanni slot without changing HnS Gym team/badge progression; preserve Blue's existing Viridian Gym battle.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Viridian City. Read the city's secondary sign; confirm it displays “THE COMEBACK RALLY — BIGGER THAN EVER.”
- [ ] Visit Viridian City Gym through the existing route and confirm the HnS Gym trainer teams, Blue/Giovanni state, and badge progression are unchanged.
- [ ] Save and reload in Viridian City; confirm the banner text remains available and the existing map state is unchanged.

The Act 14 rally cutscene and battle remain deferred; the banner still needs playtesting.

## GF16 — Finale and epilogue

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added Giratina's “You've seen it spun left” exchange and Arceus's “The world is not a top” response after the first Red victory, before HnS's existing GameClear sequence. The dialogue is skipped on subsequent Red wins using the existing `FLAG_DEFEATED_RED`; Red's team, levels, battle, and original GameClear flow remain unchanged.

**Deferred:**

- Add the two recruitment NPCs at Mt. Silver's cave entrance.
- Add the Giratina Origin appearance/Axis map and catchable battle at the specified level band.
- Add Arceus's centering animation and scene.
- Add the Goldenrod CROSSFIRE scene, Route 29 party run, all pressure-point epilogue variants, credits integration, and post-credits Giratina line.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and reach Mt. Silver Summit after meeting the existing Red battle requirements. Defeat Red; confirm the Giratina/Arceus exchange appears before the existing GameClear transition.
- [ ] Confirm the dialogue fits its boxes and the original Red battle, Land Ribbon, respawn, GameClear, and credits flow still run.
- [ ] Return to the Summit for a Red rematch; confirm `FLAG_DEFEATED_RED` prevents replaying the new dialogue.
- [ ] Confirm Red's HnS team and levels remain unchanged.

The Act 15 additions still need playtesting; most of the finale remains deferred.

## GF17 — Side quests

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Added the Raw Moomoo overlay to the existing Route 39 sick-Miltank dialogue: an influencer claims raw milk cures everything, but the farmer explains that Oran Berries are what Miltank needs. The original berry-feeding progression, recovery, and rewards remain unchanged.

**Deferred:**

- Implement Yard Sign Cleanup and its 5/10/15 rewards.
- Add the Ruins of Alph Fact-Check the Unown chamber and Grass Knot reward.
- Add the Goldenrod Underground Debate Club and Choice Specs reward.
- Implement Tariff Trouble and the normal-price Olivine port shop.
- `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile error noted under GF1.

**Playtest checklist:**

- [ ] Open **R + Start → Utilities… → Warp to map warp…** and visit Route 39 Farmhouse before healing Miltank. Speak with the farmer; confirm the raw-milk claim and Oran Berry reply render correctly.
- [ ] Visit Route 39 Barn and complete the existing five-Oran-Berry Miltank healing flow. Confirm each berry is consumed once, the health stages advance, and the existing post-quest reward remains available.
- [ ] Return to the farmhouse after `VAR_ROUTE39_BARN` reaches `5`; confirm the recovery dialogue and existing TM reward work.
- [ ] Confirm the farmer's milk shop still checks money and bag space and charges the existing price.

The Raw Moomoo side-quest overlay still needs playtesting; four of the five side quests remain deferred.

# Pass 2 (docs/GILDED_PASS_2.md)

## P2-00 — Setup

**Status: BUILT — NEEDS PLAYTEST**

Branch `gilded-pass-2` created from `srdav2-gilded-overnight-missions`. Baseline `make hns` passed (ROM 31,710,340 B, 94.50% of 32 MB). Created `docs/gilded/BOSS_DESIGN.md`. Fixed "Blair" → "Bleak" in the bible.

**Deferred:** none.

## P2-01 — Johto boss data

**Status: BUILT — NEEDS PLAYTEST**

Full sets (moves, items, abilities, natures, IVs, EVs per tier, AI, trainer bags) for Chad 1, Buckshot 1, Pell 1, Sage Purely, Barry 1, Gaudy 1 (edited in place) and new IDs 666–672: Bleak, Barry 2 (Radio Tower), Chad 2, Buckshot 2, Pell 2, Pell 3 (Border Wall), Brad 1. New IDs are not placed yet (P2-02/03/04). Design notes are in `BOSS_DESIGN.md`.

Boss check (script equivalent of the §8 grep): every mon in the entries above has 4 `- ` moves, `Ability:`, a nature line and `IVs:`; the only hits are the pre-existing HnS `TRAINER_BARRY_HNS` Tentacruel/Nidoking.

**Deferred:** none for data.

**Playtest checklist:**
- [ ] Debug menu → Battle → trainer battle (or warp and talk) vs. each placed boss; confirm 4 moves and items show.

## P2-02 — Barry bug and early placements

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

- **Barry bug fixed:** `GoldenrodCity_RadioTower_5F_hns` now uses `TRAINER_BARRY_BLASTER_RADIO_TOWER_HNS`; the Mahogany ID is only used in `RocketHideout_B3F_hns` (grep: `grep -rn TRAINER_BARRY_BLASTER data/maps`).
- **Brad 1:** `CianwoodGym_EventScript_BradFirst` runs from Chuck's script before his intro (only until Brad is defeated); Chuck's team and badge flow are unchanged.
- **Bleak:** new NPC in `GoldenrodCity_UndergroundTunnel_hns` at (3,14), optional battle, re-talk gives the after line.
- **Ecruteak:** a second Warden Pell guard object at the Tin Tower door (37,15), sharing the Burned Tower Pell's script and `FLAG_GILDED_WARDEN_PELL_DEFEATED`, so one check gates both towers.
- **Reclass:** Heritage Officers = Greg (Route 37), Toby and Harry (Route 38) with new text and class/pic (overworld sprites unchanged). Wellness Gurus = Connie and Alfred (Olivine Lighthouse), class only.

**Deferred:**
- Union Cave Freedom Toll grunts: needs two new trainer objects whose tiles are unverifiable without Porymap, and no flags are free to hide them after defeat (only `FLAG_UNUSED_EXTENDED_97–99` remain); a blocking NPC could soft-lock a corridor.
- Chuck's gym Sigma Bro reclass: cosmetic; skipped to avoid restoring classes later.
- Heritage/Wellness overworld sprite swaps (cosmetic).

**Playtest checklist:**
- [ ] Warp to Radio Tower 5F, reach the fake Director; confirm Barry 2 (Exploud/Noivern/Primeape/Gyarados Lv 43–45) and that Barry 1 at Mahogany hideout B3F is still Lv 32–34.
- [ ] Warp to Cianwood Gym, talk to Chuck; confirm Brad battles first (Lv 30–32), then Chuck's intro continues.
- [ ] Warp to Goldenrod Underground tunnel; find the girl at (3,14), battle Bleak. Check she is reachable and not blocking the corridor.
- [ ] Ecruteak City: approach both the Burned Tower and Tin Tower doors; Pell fights from either; both guards vanish after.
- [ ] Routes 37/38: three Heritage Officer fights and text.

## P2-03 — Radio Tower takeover

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

Placed the Radio Tower bosses by converting one existing grunt/scientist trainer object per floor (same tiles, same re-entry behaviour, no new flags):
- 2F `GoldenrodRaidoTower2_EventScript_Grunt5` → Buckshot 2 (Fisherman sprite)
- 3F `GoldenrodRaidoTower3_EventScript_Grunt6` → Chad 2 (Black Belt sprite)
- 4F `GoldenrodCity_RadioTower_4F4_EventScript_Scientist` → Pell 2 (Officer sprite)
- 5F: Barry 2 (new ID, P2-02) and Gaudy 1 (full G1 team). Gaudy's exit now includes the gold PIDGEOT text.

**Deferred:**
- Pidgeot fly-off movement (text only; no sprite).
- Silver's reaction and the act-end Giratina line on 5F (not re-verified in pass 2).
- Per-floor grunt re-text beyond the three converted objects.

**Playtest checklist:**
- [ ] Warp to Goldenrod Radio Tower 2F/3F/4F (after the takeover state, `VAR_GOLDENROD_CITY_STATE` ≥ the Rocket takeover value; set `FLAG_HIDE_GOLDENROD_ROCKETS` clear). Fight Buckshot 2, Chad 2, Pell 2 once each; they don't reappear after.
- [ ] 5F: Barry 2 then Gaudy 1; Kingambit is Gaudy's last Pokémon. Confirm the Pidgeot text and Director scene.

## P2-04 — Border Wall + Victory Road

**Status: BUILT_PARTIAL — NEEDS PLAYTEST**

- `Route27_hns`: two Border Agents (new trainers 673/674, Lv 50–52), Pell 3 (`TRAINER_WARDEN_PELL_BORDER_WALL_HNS`) at (71,19) facing west, and a two-boulder wall at (72,18)/(72,19) in the two-tile-wide corridor east of Tohjo Falls. Wall objects are hidden by `FLAG_UNUSED_EXTENDED_97`, set only after Pell is beaten, so a whiteout leaves the wall up and Pell rematchable.
- Victory Road 1F Silver: added "I unsubscribed from the GRINDWELLS. I just… train now."
- Indigo lobby rally goers and revolving-door gag: already in pass 1 (unchanged).

**Deferred:** wall is 2 tiles, not 3 (corridor is 2 wide; the third tile is solid rock). Wall sign is an NPC boulder, not a metatile. "Walk around" is impossible by design.

**Playtest:** warp to Route 27 (x≈66–72, y 18–19). Walk east: Agent 1, Agent 2, Pell 3 each trigger once; after Pell, boulders vanish and flag 97 is set. Lose to Pell: wall stays, Pell fights again. 
Boss grep: Border Agents are regular trainers (no moves required); Pell 3 was done in P2-01.

## P2-05 — Kanto boss data

**Status: BUILT — NEEDS PLAYTEST** (data only; no placement yet, that is P2-06 to P2-08)

Added trainers 675–686 (see registry). Boss grep: `python3 /tmp/check.py` flagged only the pre-existing `TRAINER_BARRY_HNS` Tentacruel/Nidoking; every new boss mon has 4 moves, ability, nature, IVs and (T4/G2) EVs.

**Deferred:** Crypto Bros are new trainers rather than a reclass of S.S. Aqua sailors.

**Playtest:** trainers can be battled once placed. Until then use the debug menu's trainer battle if available.

## P2-06 — Kanto Act 11: crypto mine, Brad 2

**Status: BUILT — NEEDS PLAYTEST**

- New map `CeruleanCity_CryptoMine_hns` (`MAP_CERULEAN_CITY_CRYPTO_MINE_HNS`, group Dungeons, layout copied from `CeruleanCave_B2F_hns`; hidden items/mons/warps removed). Appended to the end of `gMapGroup_Dungeons_Hns`.
- Entry: Foreman NPC at (9,20) in `Route10_PowerPlantEntrance_hns`, shown once `VAR_KANTO_ROCKET_STORY_STATE` ≥ 1 (script `warp` to (4,18)). Exit: engineer at (3,18) in the mine, `warp` back to (9,21).
- Mine contents: Thorne cameo (3,19), Crypto Bros 1/2 (sight trainers), Grindwell Bros double battle (single trainer object, sight 2), 2 rig signs.
- Misty date (Route 25 Cape): the date NPC is now Brad (Archer sprite); `Route25_EventScript_Misty` runs Brad 2 (`trainerbattle_no_intro`), then "Thanks. He kept explaining water to me."
- Machine Part flow (Cerulean Gym / Manager) untouched: the mine is optional and sets no story var.

**Deferred:** no reward for the Grindwell double (text only); the mine's battle objects have no re-entry flag (trainer-defeated check hides repeat). Misty text order slightly rearranged.

**Playtest:**
- [ ] Debug: set `VAR_KANTO_ROCKET_STORY_STATE` = 1, go to Power Plant Entrance, talk to the engineer at (9,20), say Yes. Land at (4,18) in the mine. Fight Bro 1, Bro 2, then Grindwell Bros (should be a double battle with 6 mons, Electivire/Gallade lead). Talk to the engineer at (3,18) to leave.
- [ ] Route 25 east end: with `VAR_CERULEAN_CITY_STATE` at the pre-date value and `FLAG_HIDE_ROUTE25_MISTY` cleared, trigger the date: Brad 2 battle, then Misty lines.
Boss grep: `/tmp/check.py` passes for 675–678 (P2-05 run); no new boss entries in P2-06.

## P2-07: D.O.G.E. HQ, Big Game Ranch, Cinnabar, Pewter
Status: BUILT_PARTIAL — NEEDS PLAYTEST
- Silph Co: 3 Auditor trainers (679-681), Pressure Prompt 12 terminal, D.O.G.E. signs.
- Safari entrance: optional Buckshot 3 fight (talk to Fisherman at (6,8)); Scope Lens once.
- Cinnabar: MEGA Official NPC (38,22). Pewter Museum 1F: Pell exhibit NPC (20,5).
Deferred: Safari chart "Big Game Ranch" re-text (shared scripts), Janine/Sabrina extra lines, Brock museum line.
Playtest: warp to SaffronCity_SilphCo_hns, walk into auditor sight lines, use terminal at (8,6); talk to Fisherman in Safari entrance; talk to NPCs at Cinnabar and Pewter Museum.

## P2-08: Comeback Rally
Status: BUILT — NEEDS PLAYTEST
- `ViridianCity_hns`: coord triggers at (42..44,15), the approach to the gym door. Active once `FLAG_HIDE_CINNABAR_BLUE` is set (Blue back in his gym) and Gaudy 2 is not defeated.
- Crowd (3 NPCs), Silver and Gaudy appear via `FLAG_TEMP_5` (cleared on map load only while the rally is active). Silver confrontation, Gaudy 2 (trainer 678, Mega Tyranitar), exit line, and MEGA disbands text; objects removed after.
- Blue's team and badge flow untouched. After a win, the trainer-defeated check blocks repeats; after a loss, the rally retriggers.
Deferred: Silver is a talk NPC (no movement/entrance choreography); no MEGA disband changes elsewhere.
Playtest: set FLAG_HIDE_CINNABAR_BLUE via debug menu, warp to Viridian, step on (43,15); win and confirm gym is enterable and the rally doesn't return; lose and confirm retry.

## P2-09: Finale
Status: BUILT_PARTIAL — NEEDS PLAYTEST
- Mt. Silver Outside: MEGA and Committee recruiters near the cave entrance (16,9), (19,9).
- Red script: first Red win now warps to new map `GiratinaAxis_hns` (fog). Re-talking to Red after a loss/run skips straight to the Axis (retriable: DEFEATED_RED is set only at the end).
- Axis: Giratina/Arceus dialogue, `setwildbattle SPECIES_GIRATINA_ORIGIN, 90, ITEM_GRISEOUS_CORE` (catchable), run → back to the summit; Arceus white flash; CROSSFIRE + Route 29 text; three-tier epilogue on VAR_PRESSURE_POINTS (0 / 1–5 / 6+); post-credits Giratina line before `GameClear`.
Deferred: epilogue is text-only (no Goldenrod TV room or Route 29 walk-out); no Giratina sprite on the Axis; the line is shown before credits.
Playtest: debug-warp to MtSilver summit, beat Red; check Axis scene, lose/run and re-talk to Red; set VAR_PRESSURE_POINTS to 0/3/8 and compare epilogues; confirm Hall of Fame/credits afterwards.

## P2-12 / P2-13: Overworld Pokémon + town NPCs (Johto and Kanto)
Status: BUILT — NEEDS PLAYTEST
- HnS already places 2–25 wandering Pokémon in every Johto/Kanto town and route (653 objects). 570 of them had no script. All 570 now have one (177 per-species scripts in `data/scripts/gilded_ow_mons.inc`: cry plus a cute line; about a third carry an act joke; 12 long names fall back to "cries out!").
- 20 towns × 3 new NPC lines (59 total; Olivine has 2 new, because auto-placement found only two safe tiles). In `data/scripts/gilded_town_npcs.inc`, objects appended to each town `map.json`, placed by a collision-based script.
Deferred: the per-map "≤3 species" palette check was not audited (HnS's own placement); Olivine's third line (its Café tariff menu text is pass 1); NPC tiles were auto-picked from collision data and not seen in-game.
Playtest: walk each town; confirm new NPCs don't block doors/paths; talk to several overworld mons on Routes 29/30/1.

## P2-14: Side quests
Status: BUILT_PARTIAL — NEEDS PLAYTEST
- Yard Sign Cleanup: 15 signs on Routes 29–32, 34–39, 42–46 (VAR_GILDED_YARD_SIGNS 0x40DE); Lawn Ranger on Route 29 gives Leftovers (5), Lucky Egg (10), Ability Capsule (15) once each (VAR_GILDED_SIDEQUESTS 0x40DF bits 0–2).
- Debate Club: 3 Debate Bros (trainers 687–689) in Goldenrod Underground Tunnel; Choice Specs after all three (bit 3).
- Tariff Trouble: Olivine Mart clerk text + dealer in Olivine Port (separate pokemart, no price code changed).
Deferred: Fact-Check the Unown (chamber map, Grass Knot TM) — not built.
Playtest: debug-warp to Route 29, talk to signs, then Lawn Ranger; fight Debate Bros in order in Goldenrod tunnel; talk to dealer in Olivine Port.

## P2-10/P2-11: Pass-1 deferred dialogue (talk NPCs)
Status: BUILT_PARTIAL — NEEDS PLAYTEST
- 44 talk NPCs/signs appended (scripts `Gilded_D1_<n>` in `data/scripts/gilded_dialogue1.inc`): prepper bunker, lab-fence banner, Falkner/N.R.A., Sprout Elder non-endorsement, Ruins scholar + Chairman Klaus cameo, SLOWPOKE-T billboard, Route 33 yard sign, Bugsy picket, Ilex Silver, six Goldenrod rally NPCs, Dept. Store floor signs, station MEGA grunt, Whitney, Bill, Commissar Blair, Open Season + Buckshot (National Park), Café tariff menu, Cianwood pharmacy/cold plunge, Jasmine/Amphy, Mahogany Rage Radio/shop, Lake of Rage, Pryce, Vermilion N.R.A. booth, S.S. Aqua washroom gag, Erika notice, Casino, Safari entrance sign, Janine, Sabrina, Brock.
- Positions auto-placed (see mission 6 audit below).
Deferred: Heritage Officer battles (Routes 37/38) and shared Heritage Order gate; Pell poster; Alpha Dojo; Lighthouse Wellness reclass; Slowpoke Well reclass (items 4/later commits); full Rage Radio rebrand of hideout text.
Playtest: warp to each map listed and talk to the new NPC; confirm text fits the box and the NPC does not block a path.

## P2-14 (finish): Fact-Check the Unown
Status: BUILT — NEEDS PLAYTEST
- New map `RuinsOfAlph_FactCheck_hns` (`MAP_RUINS_OF_ALPH_FACT_CHECK_HNS`, appended to Dungeons group, reuses the Words Room 1 layout). Entered via the Fact-Checker NPC in Ruins of Alph Outside (26,24), gated on `FLAG_COMPLETED_KABUTO_PUZZLE`, by script `warp` to (10,13). Exit: coord triggers on row y=15 (x 8–12) warp back to Outside (22,22).
- Three Unown talk objects; the third says TOUCH GRASS and gives TM Grass Knot once (VAR_GILDED_SIDEQUESTS bit 4).
Deferred: none for this quest. Debate Club / Tariff / Yard Signs already built.
Playtest: set FLAG_COMPLETED_KABUTO_PUZZLE via Flags & Vars, warp to Ruins of Alph Outside, talk to the scientist at (26,24); talk to each Unown; confirm TM once; walk down to leave.

## P2-09 (finish): Epilogue TV room, Route 29 walk-out, Pidgeot fly-off
Status: BUILT — NEEDS PLAYTEST
- Finale now: Axis -> `GoldenrodCity_TVRoom_hns` (CROSSFIRE + pressure-tier epilogue; ON_FRAME on `VAR_GILDED_FINALE`=1) -> `Route29_hns` (30,16) (ON_FRAME on var=2: player walks east 6 tiles, party-run text, post-credits Giratina line, then sets FLAG_DEFEATED_RED / FLAG_END_NUZLOCKE and runs GameClear; var reset to 0).
- Radio Tower 5F: Gaudy (the Archer object) plays Pidgeot cry + wing SE and walks fast north 3 tiles before the existing removal.
Deferred: no Giratina sprite on the Axis; the party does not appear as overworld followers on Route 29 (text only).
Playtest: use Flags & Vars to set VAR_GILDED_FINALE=1 and warp to Goldenrod TV Room (or beat Red, then Giratina); check TV text, walk-out, credits. Beat Gaudy on Radio Tower 5F and watch the fly-off.

## Pass 2 follow-up: Union Cave, Chuck, Safari, P2-15
Status: BUILT — NEEDS PLAYTEST
- Union Cave 1F: two MEGA toll grunts (trainers 690–691), sight 3, at (12,28) and (16,28).
- Chuck gym: YOSHI, LAO, NOB, LUNG reclassed to Sigma Bro (teams unchanged).
- Safari: Fuchsia sign/teacher/entrance re-texted to BIG GAME RANCH.
- Janine/Sabrina/Brock lines delivered as NPC lines in P2-10/11; Heritage/Wellness reclasses already existed.
- P2-15: MAPSEC_ROCKET_HIDEOUT_HNS now "MEGA HIDEOUT" (region_map.c, sections json); player-facing ROCKET grep clean in _hns content (remaining hits are FRLG-only). Arceus Returns 1–3 wired (Route 30, Route 32, Azalea).
Deferred: Chuck team rework.
Playtest: debug warp to Union Cave 1F, walk south corridor; check Fuchsia sign; open region map.

## Pass 2 placement audit
Status: BUILT — NEEDS PLAYTEST
- Moved Debate Bros (were out of bounds) and both Warden Pell objects in Ecruteak (were on wall tiles). Audit checks collision, event tiles, warp adjacency, reachability. Ledge behaviour not checked.

## Pass 2 fix round 2
Status: BUILT — NEEDS PLAYTEST
- Border Agents T3 sets; 7 pass-1 trainers got 4 moves/mon; Tin Tower gated by Pell at Bellchime Trail (35,42).
Playtest: debug-warp to Bellchime Trail, walk to (35,42) without FLAG_GILDED_WARDEN_PELL_DEFEATED: Pell fights; after winning, press up to enter. Route 27 Border Agents.
