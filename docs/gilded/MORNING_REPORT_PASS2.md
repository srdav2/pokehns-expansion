# Pass 2 Morning Report
ROM: 31,740,644 B (94.59%). All status is BUILT — NEEDS PLAYTEST; nothing has been played.

## Missions
- P2-00–P2-06: built (setup, Johto/Radio Tower/Kanto bosses, Barry fix, Border Wall, crypto mine, Brad 1/2).
- P2-07 Silph/Safari/Cinnabar/Pewter: BUILT_PARTIAL.
- P2-08 Comeback Rally: built. P2-09 Finale (GiratinaAxis_hns): BUILT_PARTIAL (text-only epilogue).
- P2-12/13: 570 overworld mons scripted (177 species scripts), 59 new town NPC lines.
- P2-14 Side quests: BUILT_PARTIAL (Yard Signs, Debate Club, Tariff; Unown chamber missing).
- P2-10/11 (remaining pass-1 dialogue), P2-15 (ROCKET residue / MEGA HIDEOUT label): NOT DONE.
- Trainers added: 666–689. New maps: CeruleanCity_CryptoMine_hns (via Foreman at Route10 Power Plant entrance), GiratinaAxis_hns (after beating Red).

## Top playtests (debug steps: warp via debug menu, set flags as needed)
1. Barry fix (Johto) 2. Gaudy 2 Mega 3. Giratina Origin retry/epilogue 4. Border Wall on Route 27
5. Crypto mine warps 6. Viridian Comeback Rally / Blue gating 7. Silph terminals/auditors
8. Debate Bros order + Choice Specs 9. Yard signs + Lawn Ranger 10. Olivine port dealer

## Follow-up round (all six items done)
Final ROM: 31,748,276 B (94.62% of 32 MB). Build passes.
1. P2-10/11: 44 talk NPCs/signs (data/scripts/gilded_dialogue1.inc) covering bunker, Falkner/N.R.A., Sprout/Ruins/Klaus, Bugsy picket, Silver, rally NPCs, Dept. Store signs, Whitney, Bill, Blair, Open Season/Buckshot, Cafe tariff menu, Cianwood, Jasmine, Rage Radio, Pryce, Vermilion, Erika, Casino, Janine/Sabrina/Brock.
2. P2-14: Fact-Check the Unown chamber (RuinsOfAlph_FactCheck_hns, Grass Knot once). Scientist at Ruins Outside (26,24), needs FLAG_COMPLETED_KABUTO_PUZZLE.
3. P2-09: GoldenrodCity_TVRoom_hns epilogue, Route 29 walk-out (VAR_GILDED_FINALE), Radio Tower Pidgeot fly-off.
4. Union Cave toll grunts (trainers 690-691), Chuck gym Sigma Bro reclass (teams unchanged), Safari "Big Game Ranch" re-text, Janine/Sabrina/Brock lines.
5. P2-15: MEGA HIDEOUT region-map label; player-facing ROCKET grep clean in _hns content (remaining hits are FRLG-only); Arceus Returns 1-3 wired (Routes 30, 32, Azalea).
6. Placement audit (collision + events + reachability, script /tmp only): found and fixed Debate Bros placed out of map bounds (Underground Tunnel, now (1,4), (2,6), (3,10)) and both Warden Pell objects in Ecruteak standing on wall tiles behind doors (now (20,15) and (38,23)). Every other auto-placed Gilded NPC/sign passes. Pre-existing HnS Gilded_Ow overworld mons were not moved.

## Playtest steps (new)
Union Cave 1F south corridor; Chuck gym trainer class names; Fuchsia sign/Safari entrance; region map label; Underground Tunnel Debate Bros; Ecruteak Pell trigger near Burned Tower; finish game via Red -> Axis -> TV room -> Route 29.

## Fix round 2
- Border Agents 1/2 now have full T3 sets (4 moves, item, ability, nature, IVs 26, EVs 252/252/4, Smart Trainer, Hyper Potions).
- Seven pass-1 trainers (Rally Goers 1/2, Route 30 MEGA grunt, Sprout Pastors 1/2, Indigo Rally Goers 1/2) have 4 moves per mon. IVs 0, matching the HnS trainers on Route 30 / Sprout Tower / Route 27 (all 0). Route 29 and Indigo Center have no HnS trainers, so I used the same 0.
- Tin Tower gate: the Ecruteak warp (37,16) sits on a solid wall in the HnS layout and cannot be reached. The only real entrance is the door at Bellchime Trail (35,41), approached only from (35,42) (neighbours are walls). A coord trigger at (35,42) plus a Pell object at (36,42) now run the Pell battle until `FLAG_GILDED_WARDEN_PELL_DEFEATED` is set. The decoy Pell I put at Ecruteak (38,23) is removed. The Burned Tower Pell still shares the flag. Not played; trace is from map.json collision.
- Final ROM 31,748,420 B.

## Unverified assumptions
Ledge/water metatile behaviour was not checked by the audit (collision only). Ecruteak Tin Tower warps (36-37,16) sit inside a solid building (pre-existing HnS geometry); Tin Tower is now gated at Bellchime Trail (35,42); the metatile at (35,41) is assumed to be a door-behaviour tile. Border Wall geometry; Silph sight lines; Axis/TV room/Route 29 warp coords; Pidgeot fly-off may bump a wall.

## Deferred
Chuck gym team rework; sprite swaps; Border Wall is 2 tiles; Grindwell double reward; no Giratina sprite on Axis; party text-only on Route 29; Crypto Bros are new trainers; overworld palette audit; Silver act-end reaction; full Rage Radio rebrand; Pell poster.
