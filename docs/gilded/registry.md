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
