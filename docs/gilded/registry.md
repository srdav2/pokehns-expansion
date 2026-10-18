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
