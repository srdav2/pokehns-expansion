# Gilded registry

## Baseline

- Expansion version: **1.15.2**, from `include/constants/expansion.h`.
- ROM size: **not available**. `make -j8` did not produce a ROM.
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
| Slowpoke Well leader Proton | Chad Grindwell | `data/maps/AzaleaTown_hns/`; `data/maps/SlowpokeWell_B1F_hns/` |
| Mahogany hideout and transmitter Petrel events | Barry Blaster | `data/maps/Mahoganytown_hns/`; `data/maps/MahoganyTown_Shop_hns/`; `data/maps/RocketHideout_B1F_hns/`; `data/maps/RocketHideout_B2F_hns/`; `data/maps/RocketHideout_B3F_hns/` |
| Radio Tower Proton, Petrel, Ariana, Archer, and floor grunts | Chad Grindwell, Barry Blaster, Colonel Buckshot Beaumont, Warden Pell, and MEGA Grunts | `data/maps/GoldenrodCity_RadioTower_1F_hns/` through `data/maps/GoldenrodCity_RadioTower_5F_hns/`; `data/maps/Mahoganytown_hns/` |
| Goldenrod Underground Ariana and grunts | Colonel Buckshot Beaumont and MEGA Grunts | `data/maps/GoldenrodCity_UndergroundSwitches_hns/`; `data/maps/GoldenrodCity_UndergroundStorage_hns/`; `data/maps/GoldenrodCity_UndergroundTunnel_hns/`; `data/maps/GoldenrodCity_hns/` |
| Giovanni story appearances | President Rex Gaudy | `data/maps/GoldenrodCity_RadioTower_5F_hns/`; `data/maps/TohjoFalls_GiovanniRoom_hns/`; `data/maps/ViridianCity_Gym_Frlg/` |

These are audit notes only; GF0's Rocket-to-MEGA script changes are deferred because the required build could not complete.
