# Gilded overnight report

## Mission status

- **Built:** GF0 — Setup and audit; GF1 — Rift foundation; GF2 — Quality of life; GF11 — Johto Act 8.
- **Partial:** GF3–GF10, GF12–GF17. See `docs/gilded/mission_log.md` for each mission's implemented scope and deferred work.
- **Blocked:** none.
- **Skipped:** GF-IMP, as directed.

Every mission commit was pushed to `srdav2-gilded-overnight-missions`. The final mission commit is `78e9dce5ce` (`Gilded GF17: Side quests`).

## Build and ROM

The HnS target builds with the required Arm GNU toolchain:

`PATH="/Users/stuartdavis/.gemini/antigravity/brain/f8571f88-b293-4162-b3ea-cfb03abd1a26/scratch/arm-gnu-toolchain/Payload/bin:/usr/bin:/bin:/usr/sbin:/sbin" make hns -j8`

Latest `pokehns.gba`: **33,554,432 bytes (32 MiB)**. Expansion version: **1.15.2**. The build completed with zero errors; existing warnings remain in `UlaUla_Forest_hns` (`setvar`/`copyvar`) and the linker RWX segment. `make check BUILD=hns -j8` remains blocked before tests by the existing `include/fake_rtc.h` / `struct SaveBlock3` compile issue recorded under GF1.

## Top five playtests

Use the overworld debug menu (**R + Start**) for the setup and isolated checks. These are queued checks only; no in-game checks have been run.

1. **New Game and Rift anchors (GF0–GF2):** Boot the HnS ROM and inspect **ROM Info… → Expansion Version / ROM space**. Start a fresh save; confirm Running Shoes work before speaking to Mom and Elm awards the enabled Exp. Share. Use **Utilities… → Lost Rift anchors… → Return anchor 1/2/3**; confirm the levels, one-time behavior, and PC fallback when the party is full.
2. **Johto event choices and battles (GF4–GF10):** Use **Utilities… → Warp to map warp…** for New Bark Lab, Cherrygrove, Azalea, Ecruteak, Olivine Lighthouse, Goldenrod, Mahogany, and Radio Tower. For each prompt, set `VAR_PRESSURE_POINTS` to `0` with **Flags & Vars… → Set Var XYZ…**, test YES and NO on separate saves, and confirm only YES increments the var. Use **Trainers… → Choose trainer from map → Try Battle** on the added battles.
3. **Blackthorn and League progression (GF11–GF12):** Warp to Blackthorn Gym and Dragon's Den Shrine; use **Flags & Vars… → Set Var XYZ…** for `VAR_BLACKTHORN_CITY_STATE` and `VAR_DRAGONS_DEN_QUIZ` to test both quiz answers. Then exercise the Indigo prompt, new Rally Goers, unchanged Elite Four/Lance teams, first Hall of Fame Giratina dialogue, and Bill's one-time post-League message.
4. **Kanto dialogue and preserved routes (GF13–GF15):** Warp to Vermilion Port and Gym, Saffron Gym, and Celadon City. Check Mar-a-Magikarp ticket travel, Surge's refusal, Sabrina's auditor line, Erika's banned-scent dialogue/Dojo move, and the GAUDY CASINO sign. Warp to Viridian City for the Comeback Rally banner and confirm existing Gym progression remains intact.
5. **Red finale and Raw Moomoo overlay (GF16–GF17):** After meeting the existing Red battle requirements, warp to Mt. Silver Summit, defeat Red, and confirm the Giratina/Arceus exchange precedes GameClear and does not replay after a Red rematch. Warp to Route 39 Farmhouse before Miltank is healed, read the raw-milk dialogue, then complete the existing five-Oran-Berry barn flow and claim the unchanged reward.

See each GF entry in the mission log for additional exact map, flag, and trainer checks. All listed changes still need playtesting.
