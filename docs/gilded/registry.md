# Gilded registry

## Baseline

- Expansion version: **1.15.2**, from `include/constants/expansion.h`.
- HnS baseline ROM: **33,554,432 bytes (32 MiB)**, `pokehns.gba`.
- ROM header title: `pokemon gilded version`; GBA title field: `POKEMON GIL`; title-screen version banner reads `GILDED`.
- GF0 introduced no flags, vars, trainers, maps, or specials.

## Level anchors

Values are the highest Pokémon level in the first HnS story battle for each leader, read from `src/data/trainers_hns.party`.

| Token | Trainer data | Level |
| --- | --- | ---: |
| `A_FALK` | `TRAINER_FALKNER_1_HNS` | 11 |
| `A_BUG` | `TRAINER_BUGSY_1_HNS` | 16 |
| `A_WHIT` | `TRAINER_WHITNEY_1_HNS` | 21 |
| `A_MORT` | `TRAINER_MORTY_1_HNS` | 25 |
| `A_CHUCK` | `TRAINER_CHUCK_1_HNS` | 31 |
| `A_JAS` | `TRAINER_JASMINE_1_HNS` | 36 |
| `A_PRYCE` | `TRAINER_PRYCE_1_HNS` | 33 |
| `A_CLAIR` | `TRAINER_CLAIR_1_HNS` | 45 |
| `A_LANCE` | `TRAINER_LANCE_1_HNS` | 56 |
| `A_BROCK` | `TRAINER_BROCK_HNS` | 66 |
| `A_MISTY` | `TRAINER_MISTY_HNS` | 63 |
| `A_SURGE` | `TRAINER_LTSURGE_HNS` | 60 |
| `A_ERIKA` | `TRAINER_ERIKA_HNS` | 62 |
| `A_JANINE` | `TRAINER_JANINE_HNS` | 64 |
| `A_SABRINA` | `TRAINER_SABRINA_HNS` | 66 |
| `A_BLAINE` | `TRAINER_BLAINE_HNS` | 67 |
| `A_BLUE` | `TRAINER_BLUE_HNS` | 69 |
| `A_RED` | `TRAINER_RED_HNS` | 93 |

## Team Rocket event mapping (GF0 audit notes)

HnS event scripts and map objects are organized in these paths. Preserve their event flow when re-skinning them as the specified Team MEGA characters:

| HnS event / role | Gilded replacement | HnS source paths |
| --- | --- | --- |
| Slowpoke Well Proton and Azalea grunts | Chad Grindwell and MEGA Grunts | `data/maps/SlowpokeWell_B1F_hns/scripts.inc`, `data/maps/SlowpokeWell_B1F_hns/map.json`, `data/maps/AzaleaTown_hns/scripts.inc`, `data/maps/AzaleaTown_hns/map.json` |
| Mahogany radio signal, hideout events, and Petrel | Barry Blaster | `data/maps/Mahoganytown_hns/scripts.inc`, `data/maps/MahoganyTown_Shop_hns/scripts.inc`, `data/maps/MahoganyTown_Shop_hns/map.json`, `data/maps/RocketHideout_B1F_hns/scripts.inc`, `data/maps/RocketHideout_B1F_hns/map.json`, `data/maps/RocketHideout_B2F_hns/scripts.inc`, `data/maps/RocketHideout_B2F_hns/map.json`, `data/maps/RocketHideout_B3F_hns/scripts.inc`, `data/maps/RocketHideout_B3F_hns/map.json` |
| Radio Tower Proton, Petrel/fake Director, Ariana, Archer, and floor grunts | Chad Grindwell, Barry Blaster, Colonel Buckshot Beaumont, Warden Pell, and MEGA Grunts | `data/maps/GoldenrodCity_RadioTower_1F_hns/` through `data/maps/GoldenrodCity_RadioTower_5F_hns/` (`scripts.inc` and `map.json` in each floor); radio-takeover progression in `data/maps/Mahoganytown_hns/scripts.inc` |
| Goldenrod Underground Ariana and grunts | Colonel Buckshot Beaumont and MEGA Grunts | `data/maps/GoldenrodCity_UndergroundSwitches_hns/scripts.inc`, `data/maps/GoldenrodCity_UndergroundSwitches_hns/map.json`, `data/maps/GoldenrodCity_UndergroundStorage_hns/scripts.inc`, `data/maps/GoldenrodCity_UndergroundStorage_hns/map.json`, `data/maps/GoldenrodCity_UndergroundTunnel_hns/scripts.inc`, `data/maps/GoldenrodCity_hns/scripts.inc` |
| Giovanni story appearance slot | President Rex Gaudy | `data/maps/GoldenrodCity_RadioTower_5F_hns/scripts.inc`, `data/maps/TohjoFalls_GiovanniRoom_hns/scripts.inc`, `data/maps/ViridianCity_Gym_Frlg/scripts.inc` |

These paths are the source-event map for the subsequent Team MEGA re-skin missions. No HnS flags, vars, trainer IDs, or event behavior are changed in GF0.

## GF1 — Rift foundation

Named save fields appended to `struct PokemonStorage`:

| Field | Meaning |
| --- | --- |
| `gildedRiftAnchoredMons[3]` | Three saved anchored Pokémon as `struct BoxPokemon` |
| `gildedRiftAnchorLevels[3]` | Target levels, in anchor order: 5, 10, and 15 |
| `gildedRiftReturnedBits` | Bit `n` records that zero-based anchor `n` was returned |

Special: `ReturnAnchoredMon`, reading the zero-based anchor index from `VAR_8004`. It returns the anchor to the party or PC and prevents duplicate returns. The GF1 debug menu exposes each index under **Utilities… → Lost Rift anchors…**. No new flags or vars were allocated.

## GF2 — Quality of life

- `ITEM_EXP_SHARE` is awarded in `NewBarkTown_Lab_hns` after the starter and uses the existing `FLAG_EXP_SHARE_ENABLED` toggle with `I_EXP_SHARE_ITEM == GEN_6`.
- New Game sets existing `FLAG_RECEIVED_RUNNING_SHOES` and `FLAG_SYS_B_DASH`; Mom's existing shoe handoff is skipped when the received flag is already set.
- No new flags, vars, trainers, maps, or specials were allocated.

## GF3 — Team MEGA foundation

- `VAR_PRESSURE_POINTS = 0x40E5`, replacing unused HnS slot `VAR_UNUSED_HNS_0x40E5`. It is reserved for the pressure-prompt system; prompt scripts are deferred to act missions.
- `ITEM_RED_CAP = 901`, a key item using the existing scarf icon and red palette. The mission adds the item definition; the Goldenrod gift event is deferred to its act mission.
- Existing `TRAINER_CLASS_TEAM_ROCKET_HNS` and `TRAINER_CLASS_ROCKET_ADMIN_HNS` identifiers remain unchanged for trainer-data and code compatibility; their visible labels are now `MEGA GRUNT` and `MEGA ADMIN`.
- New HnS trainer-class constants: `TRAINER_CLASS_SIGMA_BRO_HNS`, `TRAINER_CLASS_CRYPTO_BRO_HNS`, `TRAINER_CLASS_BALL_CARRIER_HNS`, `TRAINER_CLASS_HERITAGE_OFFICER_HNS`, `TRAINER_CLASS_TALK_RADIO_HOST_HNS`, `TRAINER_CLASS_WELLNESS_GURU_HNS`, `TRAINER_CLASS_TRADWIFE_INFLUENCER_HNS`, `TRAINER_CLASS_PREPPER_HNS`, `TRAINER_CLASS_RALLY_GOER_HNS`, `TRAINER_CLASS_BORDER_AGENT_HNS`, and `TRAINER_CLASS_DOGE_AUDITOR_HNS`. Visible labels are shortened to fit the 13-byte trainer-class name field.
- The existing male and female HnS Rocket Grunt trainer palettes are tinted red for Team MEGA. No new trainer pictures or trainer IDs were added.
- Dialogue in HnS-only map scripts and radio strings uses Team MEGA. Shared FRLG Kanto map scripts choose the Team MEGA variant under `IS_HNS` and retain their original strings in FRLG.
- No new flags, maps, or specials were allocated. Boss trainer IDs and anchor-band teams are deferred to the act missions.

## GF4 — Johto Act 1

### Flags

`HNS_EXTENDED_CONTENT_START = 0x36A`; each flag below has an otherwise-unused HnS extended slot.

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_LAB` | `0x3B9` | Hide the New Bark Lab clerk after the player chooses yes or no. |
| `FLAG_GILDED_PRESSURE_PROMPT_CHERRYGROVE` | `0x3BA` | Hide the Cherrygrove petition NPC after the player chooses yes or no. |
| `FLAG_GILDED_PRESSURE_PROMPT_SPROUT_TOWER` | `0x3BB` | Record the Sprout Tower Seed Faith choice. |
| `FLAG_GILDED_RETURN_1_SEEN` | `0x3BC` | Hide Route 30's Arceus after anchor 1 is returned. |
| `FLAG_GILDED_RETURN_2_SEEN` | `0x3BD` | Hide Route 32's Arceus after anchor 2 is returned. |

No new vars were allocated. The three prompts use the GF3 `VAR_PRESSURE_POINTS = 0x40E5`.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_RALLY_GOER_1_GILDED_HNS` | 653 | Rally Goer; Sentret Lv. 5, Hoothoot Lv. 6 |
| `TRAINER_RALLY_GOER_2_GILDED_HNS` | 654 | Rally Goer; Pidgey Lv. 5, Rattata Lv. 6 |
| `TRAINER_MEGA_GRUNT_ROUTE30_HNS` | 655 | MEGA Grunt; Rattata Lv. 6, Zubat Lv. 7 |
| `TRAINER_PASTOR_GROWTH_1_HNS` | 656 | Pastor; Bellsprout Lv. 5 and 6 |
| `TRAINER_PASTOR_GROWTH_2_HNS` | 657 | Pastor; Bellsprout Lv. 6 and 7 |

`TRAINERS_COUNT_HNS` is now 658. The new `TRAINER_CLASS_PASTOR_HNS` class displays as `PASTOR`.

### Maps and specials

- Modified HnS maps: `NewBarkTown_hns`, `NewBarkTown_Lab_hns`, `CherrygroveCity_hns`, `Route29_hns`, `Route30_hns`, `Route32_hns`, and `SproutTower_1F_hns`.
- No new maps or specials were allocated. Route 30 Return 1 and Route 32 Return 2 call the existing `ReturnAnchoredMon` special with zero-based indices 0 and 1, respectively.

## GF5 — Johto Act 2

### Flags

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_RETURN_3_SEEN` | `0x3BE` | Hide Azalea's Arceus after anchor 3 is returned. |
| `FLAG_GILDED_PRESSURE_PROMPT_AZALEA` | `0x3BF` | Hide the Azalea SLOWPOKE-T promoter after the choice. |

No vars were allocated. The SLOWPOKE-T prompt uses `VAR_PRESSURE_POINTS = 0x40E5`.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_CHAD_GRINDWELL_SLOWPOKE_WELL_HNS` | 658 | Sigma Bro; Machop Lv. 14, Mankey Lv. 15, Tauros Lv. 16 |

`TRAINERS_COUNT_HNS` is now 659. The party uses the existing `TRAINER_CLASS_SIGMA_BRO_HNS` class.

### Maps and specials

- Modified HnS maps: `AzaleaTown_hns` and `SlowpokeWell_B1F_hns`.
- No new maps or specials were allocated. Azalea Return 3 calls the existing `ReturnAnchoredMon` special with zero-based index 2.

## GF6 — Johto Act 3

### Flags

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_RADIO_TOWER` | `0x3C0` | Hide the Radio Tower RED CAP offer after the choice/gift. |
| `FLAG_GILDED_PRESSURE_PROMPT_BALL_SHOW` | `0x3C1` | Record the Dept. Store Ball Show prompt choice. |

No vars were allocated. Both prompts use `VAR_PRESSURE_POINTS = 0x40E5`.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_COLONEL_BUCKSHOT_BALL_SHOW_HNS` | 659 | Ball Carrier; Remoraid Lv. 20, Krabby Lv. 20, Magnemite Lv. 21, Clauncher Lv. 22 |

`TRAINERS_COUNT_HNS` is now 660. The trainer uses the existing `TRAINER_CLASS_BALL_CARRIER_HNS` class.

### Maps and specials

- Modified HnS maps: `GoldenrodCity_hns`, `GoldenrodCity_RadioTower_1F_hns`, and `GoldenrodCity_DepartmentStore_7F_hns`.
- No new maps or specials were allocated.

## GF7 — Johto Act 4

### Flags

`HNS_EXTENDED_CONTENT_START = 0x36A`; both values were unused before this mission.

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_WARDEN_PELL_DEFEATED` | `0x3C2` | Hide Warden Pell after his Burned Tower gate battle. |
| `FLAG_GILDED_PRESSURE_PROMPT_ECRUTEAK` | `0x3C3` | Hide the Dance Theatre ancestry-kit promoter after either choice. |

No vars were allocated. The prompt uses `VAR_PRESSURE_POINTS = 0x40E5`.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_WARDEN_PELL_ECRUTEAK_GATE_HNS` | 660 | Heritage Officer; Dunsparce Lv. 24, Stantler Lv. 25, Sudowoodo Lv. 26 |

`TRAINERS_COUNT_HNS` is now 661. The levels use the `A_MORT` 24–26 anchor band. The party reuses the existing `TRAINER_CLASS_HERITAGE_OFFICER_HNS` class.

### Maps and specials

- Modified HnS maps: `EcruteakCity_hns`, `EcruteakCity_Theater_hns`, `EcruteakCity_PokemonCenter_hns`, and `EcruteakCity_Gym_hns`.
- No new maps or specials were allocated.

## GF8 — Johto Act 5

### Flags

`HNS_EXTENDED_CONTENT_START = 0x36A`; both values were unused before this mission.

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_OLIVINE` | `0x3C4` | Record Sage Purely's Rapidash Paste choice and prevent repeated pressure points. |
| `FLAG_GILDED_SAGE_PURELY_DEFEATED` | `0x3C5` | Hide Sage Purely after the Lighthouse battle. |

No vars were allocated. The prompt uses `VAR_PRESSURE_POINTS = 0x40E5`.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_SAGE_PURELY_OLIVINE_LIGHTHOUSE_HNS` | 661 | Wellness Guru; Gloom Lv. 34, Weepinbell Lv. 35, Foongus Lv. 35, Comfey Lv. 36 |

`TRAINERS_COUNT_HNS` is now 662. The team uses the `A_JAS` 34–36 anchor band and the existing `TRAINER_CLASS_WELLNESS_GURU_HNS` class.

### Maps and specials

- Modified HnS map: `OlivineCity_Lighthouse_hns`.
- No new maps or specials were allocated.

## GF9 — Johto Act 6

### Flags

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_MAHOGANY` | `0x3C6` | Record the Mahogany Gaudy Gold Kicks choice and prevent repeat prompts. |

The prompt uses `VAR_PRESSURE_POINTS = 0x40E5`; no new vars or specials were allocated.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_BARRY_BLASTER_MAHOGANY_HNS` | 662 | Talk Radio Host; Exploud Lv. 32, Primeape Lv. 33, Noibat Lv. 33, Gyarados Lv. 34 |

`TRAINERS_COUNT_HNS` is now 663. The team uses the `A_PRYCE` 32–34 anchor band.

### Maps and specials

- Modified HnS maps: `MahoganyTown_Shop_hns` and `RocketHideout_B3F_hns`.
- No new maps or specials were allocated.

## GF10 — Johto Act 7

### Flags

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_TOWER_STAIRS` | `0x3C7` | Record the Radio Tower stair-side loyalty prompt choice and prevent repeat pressure points. |

The prompt uses `VAR_PRESSURE_POINTS = 0x40E5`; no new vars or specials were allocated.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_PRESIDENT_REX_GAUDY_RADIO_TOWER_HNS` | 663 | MEGA Admin; Persian Lv. 44, Gholdengo Lv. 44, Copperajah Lv. 45, Kingambit Lv. 45, Donphan Lv. 46 |

`TRAINERS_COUNT_HNS` is now 664. The party uses the `A_CLAIR` 44–46 Radio Tower band. Barry's fake-Director battle reuses `TRAINER_BARRY_BLASTER_MAHOGANY_HNS` (662).

### Maps and specials

- Modified HnS maps: `GoldenrodCity_RadioTower_4F_hns` and `GoldenrodCity_RadioTower_5F_hns`.
- No new maps or specials were allocated.

## GF11 — Johto Act 8

### Script menus

- `MULTI_ELDERQUIIZ6 = 178`: sixth Dragon's Den Elder quiz question, with “Demand a recount” and “Train harder” choices.

### Maps and specials

- Modified HnS maps: `BlackthornCity_Gym_hns` and `DragonsDen_Shrine_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. Clair continues to use the existing `TRAINER_CLAIR_1_HNS` team and level.

## GF12 — Johto Act 9

### Flags

| Flag | Value | Purpose |
| --- | ---: | --- |
| `FLAG_GILDED_PRESSURE_PROMPT_INDIGO` | `0x3C8` | Hide Pressure Prompt 11 after the player's choice. |
| `FLAG_HIDE_GILDED_HOF_GIRATINA` | `0x3C9` | Hide Giratina outside the first Hall of Fame cutscene. |
| `FLAG_GILDED_HOENN_PC_SCENE` | `0x3CA` | Record that Bill's post-League storage scene has run. |

Pressure Prompt 11 uses `VAR_PRESSURE_POINTS = 0x40E5`. No new vars or specials were allocated.

### Trainers

| Trainer ID | Value | Class / party |
| --- | ---: | --- |
| `TRAINER_GILDED_RALLY_GOER_INDIGO_1_HNS` | 664 | Rally Goer; Machoke Lv. 54, Primeape Lv. 55 |
| `TRAINER_GILDED_RALLY_GOER_INDIGO_2_HNS` | 665 | Rally Goer; Torkoal Lv. 55, Houndoom Lv. 56 |

`TRAINERS_COUNT_HNS` is now 666. Both use the existing `TRAINER_CLASS_RALLY_GOER_HNS` class. The Elite Four and Lance trainer parties are unchanged.

### Maps and specials

- Modified HnS maps: `IndigoPlateau_PokemonCenter_hns`, `PokemonLeague_WillsRoom_hns`, `PokemonLeague_KogasRoom_hns`, `PokemonLeague_BrunosRoom_hns`, `PokemonLeague_KarensRoom_hns`, `PokemonLeague_ChampionsRoom_hns`, `PokemonLeague_HallOfFame_hns`, and `GoldenrodCity_BillsHouse_hns`.
- The first Hall of Fame cutscene displays an existing Giratina overworld species sprite; no maps or specials were added.
- Route 27 / Tohjo Falls border content and `UnsealHoennStorage()` remain deferred.

## GF13 — Kanto Acts 10–11

### Maps and specials

- Modified HnS maps: `VermilionCity_PortInside_hns`, `SSAqua_1F_hns`, `SSAqua_CaptainsRoom_hns`, and `VermilionCity_Gym_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. Lt. Surge's HnS team and level are unchanged.
- The Act 11 Power Plant, Cerulean mine, and Misty date events remain deferred.

## GF14 — Kanto Acts 12–13

### Maps and specials

- Modified HnS maps: `SaffronCity_Gym_hns` and `CeladonCity_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. Sabrina's and Erika's HnS teams and levels are unchanged.
- The D.O.G.E. headquarters, Pressure Prompt 12, auditor battles, and Fuchsia/Cinnabar/Pewter content remain deferred.

## GF15 — Kanto Act 14: Comeback Rally

### Maps and specials

- Modified HnS map: `ViridianCity_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. All HnS Gym teams and levels remain unchanged.
- The Gaudy rally cutscene/battle and its post-battle state remain deferred.

## GF16 — Finale and epilogue

### Maps and specials

- Modified HnS map: `MtSilver_SummitDay_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. The existing `FLAG_DEFEATED_RED` gates the added one-time dialogue; Red's HnS team and levels are unchanged.
- The Axis map, Giratina Origin battle, and epilogue content remain deferred.

## GF17 — Side quests

### Maps and specials

- Modified HnS map: `Route39_FarmHouse_hns`.
- No new flags, vars, trainers, maps, or specials were allocated. The existing `VAR_ROUTE39_BARN` berry-feeding progression is unchanged.
- Yard Sign Cleanup, Fact-Check the Unown, Debate Club, and Tariff Trouble remain deferred.

## P2-01 — Johto boss data

### Trainers
| Constant | ID | Notes |
| --- | --- | --- |
| `TRAINER_COMMISSAR_BLEAK_GOLDENROD_HNS` | 666 | T1, Lv 22–23, optional |
| `TRAINER_BARRY_BLASTER_RADIO_TOWER_HNS` | 667 | T3, Lv 43–45 (Radio Tower 5F) |
| `TRAINER_CHAD_GRINDWELL_RADIO_TOWER_HNS` | 668 | T3, Lv 43–45 |
| `TRAINER_COLONEL_BUCKSHOT_RADIO_TOWER_HNS` | 669 | T3, Lv 43–45 |
| `TRAINER_WARDEN_PELL_RADIO_TOWER_HNS` | 670 | T3, Lv 44–46 |
| `TRAINER_WARDEN_PELL_BORDER_WALL_HNS` | 671 | T3, Lv 52–54 |
| `TRAINER_BRAD_GRINDWELL_ALPHA_DOJO_HNS` | 672 | T2, Lv 30–32 |

`TRAINERS_COUNT_HNS` is now 673.

## P2-02 — placements

No new flags, vars or trainers (uses the P2-01 IDs). New object events: `LOCALID_GILDED_WARDEN_PELL_TIN` on `EcruteakCity_hns` (hidden by `FLAG_GILDED_WARDEN_PELL_DEFEATED`), Bleak on `GoldenrodCity_UndergroundTunnel_hns` (hidden by `FLAG_HIDE_GOLDENROD_NPCS`). Reclassed: `TRAINER_GREG_HNS`, `TRAINER_TOBY_HNS`, `TRAINER_HARRY_HNS` → Heritage Officer; `TRAINER_CONNIE_HNS`, `TRAINER_ALFRED_HNS` → Wellness Guru.
**Flag pool warning:** only `FLAG_UNUSED_EXTENDED_97–99` remain free; use trainer-defeated checks and var bitfields instead of new flags.

## P2-03 — Radio Tower
No new constants. Trainer placements: `TRAINER_COLONEL_BUCKSHOT_RADIO_TOWER_HNS` (2F), `TRAINER_CHAD_GRINDWELL_RADIO_TOWER_HNS` (3F), `TRAINER_WARDEN_PELL_RADIO_TOWER_HNS` (4F), `TRAINER_BARRY_BLASTER_RADIO_TOWER_HNS` (5F). Displaced HnS trainers: `TRAINER_GRUNT_5_HNS`, `TRAINER_GRUNT_6_HNS`, `TRAINER_RICH_HNS` no longer battled in the tower (their scripts now call the bosses).

## P2-04
- `FLAG_UNUSED_EXTENDED_97`: Border Wall down (used by `Route27_hns`). Only 98 and 99 remain.
- Trainers 673 `TRAINER_BORDER_AGENT_1_HNS`, 674 `TRAINER_BORDER_AGENT_2_HNS` (count now 675).
- Route27 local IDs: `LOCALID_GILDED_BORDER_AGENT_1/2`, `_BORDER_PELL`, `_BORDER_WALL_1/2`.

## P2-05 trainers (opponents_hns.h)
675 `TRAINER_BRAD_GRINDWELL_CERULEAN_CAPE_HNS`, 676 `TRAINER_GRINDWELL_BROS_CRYPTO_MINE_HNS` (double), 677 `TRAINER_COLONEL_BUCKSHOT_BIG_GAME_RANCH_HNS`, 678 `TRAINER_PRESIDENT_REX_GAUDY_COMEBACK_RALLY_HNS`, 679–681 `TRAINER_DOGE_AUDITOR_1..3_HNS`, 682–683 `TRAINER_CRYPTO_BRO_1..2_HNS`, 684–686 `TRAINER_RALLY_GOER_VIRIDIAN_1..3_HNS`. Count 687.

## P2-06
- Map `MAP_CERULEAN_CITY_CRYPTO_MINE_HNS` (group Dungeons). Local IDs `LOCALID_GILDED_MINE_EXIT/THORNE/BRO_1/BRO_2/GRINDWELLS`, `LOCALID_GILDED_MINE_FOREMAN` (Power Plant Entrance). No new flags or vars.

- P2-07: FLAG_GILDED_PRESSURE_PROMPT_SAFFRON (was FLAG_UNUSED_EXTENDED_98). LOCALID_GILDED_CINNABAR_OFFICIAL, LOCALID_GILDED_MUSEUM_PELL (unused ids, local_id strings only).

- P2-08: Viridian objects 24-28 use FLAG_TEMP_5 (no new persistent flags); coord triggers use VAR_TEMP_1.

- P2-09: map MAP_GIRATINA_AXIS_HNS (end of Dungeons_Hns group). No new flags; uses VAR_TEMP_0.
