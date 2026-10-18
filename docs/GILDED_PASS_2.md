# Pokémon Gilded Version: Pass 2 brief (depth pass)

**Audience:** the coding agent (GitHub Copilot desktop app, or any other agent) working in `srdav2/pokehns-expansion`.
**Starts from:** branch `srdav2-gilded-overnight-missions`, the result of pass 1 (GF0–GF17).
**Story source:** `docs/GILDED_STORY_BIBLE.md`. The content guardrails in §0.2 still apply and are non-negotiable.

## What pass 1 got right, and what pass 2 is for

Pass 1 built the skeleton:
- the Rift save fields and the Arceus return special
- the Team MEGA rename (the visible text is essentially done)
- 13 new trainers
- 11 Pressure Prompts
- re-texted dialogue for most acts

Every act mission ended `BUILT_PARTIAL`. The gaps that matter most to the owner:

1. **Boss fights have no real design.** Every new trainer has species and levels only. There are no moves, held items, abilities, natures, IVs or EVs, and the AI is mostly `Basic Trainer` or `Check Bad Move`. The HnS gym leaders they sit next to have moves, IVs and Full Restores. Today the villains are easier than the gym trainers.
2. **Half the boss roster doesn't exist yet**, including:
   - Brad Grindwell
   - Chad 2/3, Buckshot 2/3, Pell 2/3
   - Gaudy 2 with Mega Tyranitar
   - Barry's Radio Tower fight
   - the Grindwell double battle
   - the Giratina finale
3. **Bug:** `TRAINER_BARRY_BLASTER_MAHOGANY_HNS` is battled twice: in `RocketHideout_B3F_hns` (Lv 32–34) and again as the fake Director in `GoldenrodCity_RadioTower_5F_hns`. The second fight is a level-34 team in a level-45 area. It needs its own trainer ID.
4. **No new areas or dungeons**, including:
   - the Border Wall
   - the meme-coin mine
   - the Big Game Ranch
   - D.O.G.E. HQ
   - the Giratina Axis
   - the Comeback Rally
   - the epilogue
5. **No overworld life:** no wandering Pokémon and few new NPCs.
6. **Some Kanto edits landed on unreachable maps.** HnS's Kanto uses the `_hns` maps. Pass 1 added `#if IS_HNS` text to `SilphCo_*_Frlg`, `SaffronCity_Frlg` and other `_Frlg` maps, but `make hns` players never visit them: Saffron's Silph Co. door warps to `MAP_SAFFRON_CITY_SILPH_CO_HNS`. **Pass 2 never edits `_Frlg` maps.** Before editing any map, confirm a reachable `_hns` map warps to it.

Pass 2 fills all of this in. **This pass allows no scope cuts on boss teams, battle placement or the trainer bug.** `BUILT_PARTIAL` is only allowed for cosmetic map art and for scenes listed as optional below.

---

## 0. Rules

1. **Unattended.** Never ask a question or wait for input. If something is unclear, take the default stated here, log one line in `docs/gilded/DECISIONS_LOG.md` (`date | mission | decision | why`), and continue.
2. **Branch.** Create `gilded-pass-2` from `srdav2-gilded-overnight-missions` and work only there. Never push to `master`. Never force-push.
3. **One mission = one commit.** Message: `Gilded P2-xx: <title>`. **Push after every mission.**
4. **Build command.** This exact command is required on this Mac; Homebrew's gcc does not work:
   ```
   PATH="/Users/stuartdavis/.gemini/antigravity/brain/f8571f88-b293-4162-b3ea-cfb03abd1a26/scratch/arm-gnu-toolchain/Payload/bin:/usr/bin:/bin:/usr/sbin:/sbin" make hns -j8
   ```
   - It must finish with zero errors and produce `pokehns.gba`.
   - `make check BUILD=hns` is blocked by an existing `include/fake_rtc.h` / `struct SaveBlock3` error. Ignore it unless you choose to do optional mission P2-15.
5. **Fix limit.** If the build won't pass after 3 attempts on the same error, revert that mission (`git checkout .`), mark it `BLOCKED: <error>` in `docs/gilded/mission_log.md`, and go on to the next mission that doesn't depend on it.
6. **Never write "verified" or "playtested".** Status is `BUILT — NEEDS PLAYTEST`.
7. **Keep HnS's gym leader, Elite Four, Champion and Red teams and levels unchanged.** Change dialogue only.
8. **Registry.** Every new flag, var, trainer, map and special goes in `docs/gilded/registry.md`. Grep before allocating, and never reuse a slot something still reads. Continue the pass-1 allocation pattern (`FLAG_UNUSED_EXTENDED_9x` and beyond), checking each slot first.
9. **Text** fits the box: about 34 characters per line, 2 lines per box. Use `\n` for the second line, `\l` to scroll, `\p` for a new box, and `$` to end. Follow HnS's style.
10. **Names.** No real people's names. The Sovereign cameo is **Commissar Bleak** (renamed from "Blair" in Sovereign). Use "Bleak" everywhere, and fix the two "Blair" mentions in the bible (§3.5 and Act 15) in P2-00.
11. **Don't touch any other repo.**
12. **Stop** when the queue is done or 3 missions in a row are blocked. Then write `docs/gilded/MORNING_REPORT_PASS2.md` (§9), commit and push.

---

## 1. Difficulty design: how every boss fight is built

The owner wants fights that are **hard but fair**. Two things make levels alone useless:
- the party-wide Exp. Share (GF2)
- HnS's optional level cap (`src/caps.c`, chosen at New Game; Normal caps at the next leader's ace level, Hard caps lower)

A player with the Exp. Share is usually at or above the anchor, and a Hard-cap player is 2–3 levels below it. So difficulty comes from **sets, items, IVs/EVs and AI**, not from inflated levels. Keep the bible's level bands (§2).

### 1.1 Tiers

| Tier | Used for | IVs | EVs | Nature | AI line | Trainer bag (`Items:`) |
| --- | --- | --- | --- | --- | --- | --- |
| T1 | Before badge 4: Chad 1, Buckshot 1, Pell 1, Bleak | 18 all | none | chosen | `AI: Basic Trainer` | `Super Potion` |
| T2 | Badges 4–7: Sage, Brad 1, Barry 1 | 22 all | 128 / 128 in the two stats that matter | chosen | `AI: Basic Trainer` | `Super Potion / Super Potion` |
| T3 | Radio Tower and Border Wall: Barry 2, Chad 2, Buckshot 2, Pell 2, Pell 3 | 26 all | 252 / 252 / 4 | chosen | `AI: Smart Trainer` | `Hyper Potion / Hyper Potion`; Pell 3 gets `Full Restore / Full Restore` |
| G1 | Gaudy at the Radio Tower | 31 all | 252 / 252 / 4 | chosen | `AI: Smart Trainer` | `Full Restore / Full Restore` |
| T4 | Kanto: Brad 2, the Grindwell double, Buckshot 3 | 31 all | 252 / 252 / 4 | chosen | `AI: Smart Trainer` | `Full Restore / Full Restore` |
| G2 | Gaudy at the Comeback Rally | 31 all | 252 / 252 / 4 | chosen | `AI: Smart Trainer / Prediction` | `Full Restore / Full Restore / Full Restore` |

For comparison, HnS's leaders are IVs 12 (Johto) or 24 (Clair and Kanto), no EVs, `AI: Basic Trainer`, 2 potions. The villains are deliberately a notch above the leader they precede.

### 1.2 Fairness rules (every boss must pass all of these)

- **No** OHKO moves, evasion-raising moves, Moody, Baton Pass, Perish trapping, Swagger, or Double Team/Minimize.
- **At most one sleep-inducing move per team.**
- **At most one stat-setup sweeper per team.** Gaudy 2 may have two.
- **At most one Focus Sash per team.**
- **Every team has a clear weakness** the player can exploit with Pokémon catchable before that fight. Name it in the design note (§1.3).
- **Every boss mon has exactly 4 moves, a held item or a deliberate "none", an ability, a nature, and IVs.** T2 and above also have EVs.
- Moves should be ones the species can plausibly learn by that level (level-up, TM or tutor). trainerproc doesn't check learnsets, so this is on you. Where a set below looks wrong for the species, swap in a move of the same role and log it.

### 1.3 Design notes

For every boss, add an entry to a new file, `docs/gilded/BOSS_DESIGN.md`, in this format:

```
## Chad Grindwell 1 — Slowpoke Well (TRAINER_CHAD_GRINDWELL_SLOWPOKE_WELL_HNS)
Levels: 14–16 (A_BUG 16, band -2..0). Tier T1.
Gimmick: "grindset" — Guts Machop, Intimidate Tauros ace.
Threat: Bulk Up Machop snowballs if ignored; Tauros Pursuit punishes switching out a Ghost/Psychic.
Intended counterplay: Flying (Pidgey line from Route 29/30), Psychic (Abra, Route 34? check), Gastly (Sprout Tower area).
What the player likely has: starter at ~16, plus Route 29–33 catches.
Hard-cap check: winnable at Lv 13–15 with a Flying type and two potions.
```

### 1.4 Party file syntax (`src/data/trainers_hns.party`)

Copy this shape exactly. It's the pokeemerald-expansion Showdown format compiled by trainerproc:

```
=== TRAINER_EXAMPLE_HNS ===
Name: CHAD
Class: Sigma Bro Hns
Pic: Proton Hns
Gender: Male
Music: Hg Suspicious 1
Double Battle: No
AI: Basic Trainer
Items: Super Potion
Mugshot: Purple

Machop @ Oran Berry
Ability: Guts
Level: 14
Adamant Nature
IVs: 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- Karate Chop
- Bulk Up
- Rock Smash
- Leer
```

- **EVs line:** `EVs: 252 Atk / 252 Spe / 4 HP`.
- **Mugshot:** keep `Mugshot:` only if HnS already uses it for that class; otherwise omit it.
- **Forms:** `Lycanroc-Midnight`, `Tauros-Paldea-Combat`, `Giratina-Origin`.
- **Name errors:** if trainerproc rejects a move, item or ability name, grep `include/constants/moves.h`, `items.h` or `abilities.h` for the constant and fix the spelling.

**Existing IDs are edited in place.** Don't rename them, because scripts reference them. For new IDs:
- add a constant to `include/constants/opponents_hns.h`
- bump `TRAINERS_COUNT_HNS` if the file uses it
- log it in the registry.

### 1.5 In-battle boss lines (optional polish, after the teams are done)

pokeemerald-expansion supports trainer slides in `src/trainer_slide.c` (`sTrainerSlides[DIFFICULTY_NORMAL][TRAINER_X][TRAINER_SLIDE_...]`):
- `TRAINER_SLIDE_LAST_SWITCHIN`
- `TRAINER_SLIDE_MEGA_EVOLUTION`
- `TRAINER_SLIDE_BEFORE_FIRST_TURN`

Use them for:
- Pell's Ursaluna: "…Desperate times."
- Gaudy's Mega: "MEGA! Make Evolution Great Again!"
- Gaudy's Gholdengo: "MAKE IT RAIN! …Somebody pick that up."

If the HnS trainer IDs don't fit that array, or the build fails, skip this and log it.

---

## 2. Boss teams (complete; copy them in)

Levels follow the bible's bands. Opponent Mega Evolution needs only the held stone (`CanMegaEvolve` checks the Mega Ring for the player only).

Every block below goes in with:
- the tier's IVs/EVs (§1.1) unless the block says otherwise
- the trainer header lines (Name, Class, Pic, Gender, Music, Double Battle, AI, Items)
- the pass-1 Class/Pic for existing IDs

New IDs reuse the same Class/Pic as that boss's existing entry.

### 2.1 Chad Grindwell 1, Slowpoke Well (edit `TRAINER_CHAD_GRINDWELL_SLOWPOKE_WELL_HNS`)
T1. Gimmick: grindset. One setup move (Bulk Up); Tauros punishes switching.
```
Machop @ Oran Berry / Ability: Guts / Level: 14 / Adamant Nature
- Karate Chop / Bulk Up / Rock Smash / Leer
Mankey @ Oran Berry / Ability: Vital Spirit / Level: 15 / Jolly Nature
- Low Kick / Fury Swipes / Pursuit / Covet
Tauros @ Sitrus Berry / Ability: Intimidate / Level: 16 / Adamant Nature
- Horn Attack / Pursuit / Rage / Scary Face
```
**Shorthand used in all of §2:** `Species @ Item / Ability / Level / Nature: move / move / move / move`. In the party file, put each field and each move on its own line, exactly as in §1.4, and add the tier's `IVs:` and `EVs:` lines.

### 2.2 Colonel Buckshot 1, Ball Show, optional (edit `TRAINER_COLONEL_BUCKSHOT_BALL_SHOW_HNS`)
T1, levels 21–23 (optional battles may go +2). Gimmick: "every Pokémon is a cannon"; crit fishing with Sniper and Scope Lens.
```
Remoraid @ Scope Lens / Sniper / 21 / Modest: Bubble Beam / Psybeam / Aurora Beam / Supersonic
Krabby @ Oran Berry / Hyper Cutter / 21 / Adamant: Bubble Beam / Metal Claw / Stomp / Harden
Magnemite / Sturdy / 22 / Modest: Spark / Sonic Boom / Thunder Wave / Supersonic
Clauncher @ Mystic Water / Mega Launcher / 23 / Modest: Water Pulse / Aqua Jet / Smack Down / Swords Dance
```
Counterplay: Grass (Bellsprout, Oddish), and Electric for the water mons except Magnemite.

### 2.3 Warden Pell 1, Ecruteak gate (edit `TRAINER_WARDEN_PELL_ECRUTEAK_GATE_HNS`)
T1, levels 24–26. Gimmick: "pure single types"; paralysis plus flinch (Serene Grace, King's Rock).
```
Dunsparce @ King's Rock / Serene Grace / 24 / Careful: Headbutt / Glare / Rollout / Defense Curl
Stantler @ Persim Berry / Intimidate / 25 / Adamant: Stomp / Hypnosis / Confuse Ray / Take Down
Sudowoodo @ Sitrus Berry / Rock Head / 26 / Adamant: Rock Slide / Double-Edge / Low Kick / Wood Hammer
```
Counterplay: Fighting types and Ghosts (immune to Normal), Water and Grass for Sudowoodo.

### 2.4 Commissar Bleak, Goldenrod Underground, optional (new `TRAINER_COMMISSAR_BLEAK_GOLDENROD_HNS`)
T1, levels 22–23 (A_WHIT +2). Female; Aroma Lady pic. Her Sovereign team evolved, plus a sponsor.
```
Hattrem @ Leftovers / Magic Bounce / 23 / Bold: Psybeam / Draining Kiss / Calm Mind / Brutal Swing
Primeape @ Sitrus Berry / Defiant / 23 / Jolly: Karate Chop / Rage Fist / Pursuit / Leer
Slowpoke @ Oran Berry / Own Tempo / 22 / Relaxed: Water Pulse / Confusion / Yawn / Slack Off
```
After-battle line: "SLOWPOKE-T sponsors this episode. I hate that I'm saying that."

### 2.5 Sage Purely, top of the Olivine Lighthouse (edit `TRAINER_SAGE_PURELY_OLIVINE_LIGHTHOUSE_HNS`)
T2, levels **29–31**. The player meets her before Chuck (31), so the bible's `A_JAS` band (34–36) is too high. Log this.
- Gimmick: status plus drain stall.
- Trainer items: `Energy Root / Heal Powder`, as an herbal-remedy joke. If either is missing, use `Super Potion / Full Heal`.
```
Gloom @ Big Root / Stench / 29 / Bold / EVs 128 HP 128 Def: Giga Drain / Stun Spore / Acid / Moonlight
Weepinbell @ Miracle Seed / Chlorophyll / 29 / Modest / EVs 128 SpA 128 Spe: Sleep Powder / Razor Leaf / Poison Jab / Growth
Foongus @ Black Sludge / Regenerator / 30 / Calm / EVs 128 HP 128 SpD: Stun Spore / Giga Drain / Clear Smog / Protect
Comfey @ Leftovers / Triage / 31 / Calm / EVs 128 HP 128 SpD: Draining Kiss / Floral Healing / Calm Mind / Grass Knot
```
Counterplay: Fire, Flying and Psychic types, plus Steel (Magnemite/Magneton walls the whole team).

### 2.6 Brad Grindwell 1, Alpha Dojo, Cianwood (new `TRAINER_BRAD_GRINDWELL_ALPHA_DOJO_HNS`)
T2, levels 30–32. Class: Sigma Bro Hns; pick a different pic from Chad's, e.g. `Rich Boy`-style if available. Gimmick: speed snowball, then a Counter trap.
```
Rapidash @ Charcoal / Flash Fire / 30 / Jolly / EVs 128 Atk 128 Spe: Flame Charge / Stomp / Agility / Low Kick
Electabuzz @ Magnet / Static / 31 / Hasty / EVs 128 SpA 128 Spe: Thunder Punch / Quick Attack / Low Kick / Light Screen
Varoom @ Black Sludge / Overcoat / 31 / Adamant / EVs 128 Atk 128 HP: Poison Jab / Iron Head / Taunt / Screech
Lycanroc-Midnight @ Life Orb / No Guard / 32 / Adamant / EVs 128 Atk 128 Spe: Rock Slide / Counter / Crunch / Sucker Punch
```
Counterplay: Water and Ground; special attackers bypass Counter.

### 2.7 Barry Blaster 1, Mahogany hideout (edit `TRAINER_BARRY_BLASTER_MAHOGANY_HNS`; keep it **only** in `RocketHideout_B3F_hns`)
T2, levels 32–34. Gimmick: rage; Anger Point plus Moxie snowball.
```
Exploud @ Throat Spray / Scrappy / 32 / Modest / EVs 128 SpA 128 HP: Hyper Voice / Bite / Stomp / Roar
Primeape @ Scope Lens / Anger Point / 33 / Jolly / EVs 128 Atk 128 Spe: Cross Chop / Rage Fist / Seismic Toss / Focus Energy
Noibat @ Sitrus Berry / Infiltrator / 33 / Timid / EVs 128 SpA 128 Spe: Air Cutter / Super Fang / Bite / Supersonic
Gyarados @ Lum Berry / Moxie / 34 / Adamant / EVs 128 Atk 128 Spe: Waterfall / Thrash / Ice Fang / Dragon Dance
```
Counterplay: Electric, Rock and Fairy.

### 2.8 Barry Blaster 2, fake Director, Radio Tower 5F (**new** `TRAINER_BARRY_BLASTER_RADIO_TOWER_HNS`)
Replace the trainer ID in the `trainerbattle_no_intro` on `GoldenrodCity_RadioTower_5F_hns/scripts.inc` line ~33 with this new ID. T3, levels 43–45.
```
Exploud @ Throat Spray / Scrappy / 43 / Modest: Boomburst / Flamethrower / Ice Beam / Surf
Noivern @ Sitrus Berry / Infiltrator / 44 / Timid: Boomburst / Dragon Pulse / Air Slash / Super Fang
Primeape @ Choice Scarf / Defiant / 44 / Jolly: Close Combat / Rage Fist / U-turn / Stone Edge
Gyarados @ Lum Berry / Moxie / 45 / Jolly: Waterfall / Bounce / Ice Fang / Dragon Dance
```

### 2.9 Chad Grindwell 2, Radio Tower (new `TRAINER_CHAD_GRINDWELL_RADIO_TOWER_HNS`)
T3, levels 43–45. Gimmick: Fighting-type wall of pressure; No Guard Dynamic Punch is his signature threat.
```
Machamp @ Black Belt / No Guard / 45 / Adamant: Dynamic Punch / Knock Off / Bullet Punch / Stone Edge
Primeape @ Sitrus Berry / Defiant / 43 / Jolly: Close Combat / U-turn / Rage Fist / Bulk Up
Hitmontop @ Leftovers / Intimidate / 43 / Impish: Fake Out / Close Combat / Sucker Punch / Rapid Spin
Tauros @ Choice Band / Intimidate / 44 / Jolly: Double-Edge / Earthquake / Zen Headbutt / Close Combat
Pangoro @ Assault Vest / Iron Fist / 44 / Adamant: Drain Punch / Hammer Arm / Crunch / Bullet Punch
```
Counterplay: Psychic, Flying and Fairy; Ghosts dodge the Fighting moves (watch Knock Off and Crunch).

### 2.10 Colonel Buckshot 2, Radio Tower (new `TRAINER_COLONEL_BUCKSHOT_RADIO_TOWER_HNS`)
T3, levels 43–45. Gimmick: the cannon battery; Mega Launcher and Sniper.
```
Octillery @ Scope Lens / Sniper / 43 / Modest: Octazooka / Fire Blast / Ice Beam / Focus Energy
Kingler @ Life Orb / Sheer Force / 44 / Adamant: Liquidation / Rock Slide / X-Scissor / Swords Dance
Clawitzer @ Wise Glasses / Mega Launcher / 45 / Modest: Water Pulse / Dark Pulse / Aura Sphere / Dragon Pulse
Magneton @ Sitrus Berry / Analytic / 44 / Modest: Thunderbolt / Flash Cannon / Thunder Wave / Tri Attack
Cramorant @ Sharp Beak / Gulp Missile / 43 / Modest: Surf / Drill Peck / Roost / Ice Beam
```
Counterplay: Grass and Electric (watch Octillery's Fire Blast and Ice Beam), and Ground for Magneton.

### 2.11 Warden Pell 2, Radio Tower (new `TRAINER_WARDEN_PELL_RADIO_TOWER_HNS`)
T3, levels 44–46. Gimmick: bulky single-types, hazards and Guts.
```
Ursaring @ Flame Orb / Guts / 46 / Adamant: Facade / Crunch / Hammer Arm / Swords Dance
Granbull @ Leftovers / Intimidate / 44 / Impish: Play Rough / Thunder Wave / Earthquake / Crunch
Donphan @ Sitrus Berry / Sturdy / 45 / Adamant: Earthquake / Ice Shard / Knock Off / Rapid Spin
Sudowoodo @ Rocky Helmet / Rock Head / 44 / Impish: Head Smash / Wood Hammer / Sucker Punch / Stealth Rock
Stantler @ Persim Berry / Intimidate / 44 / Jolly: Double-Edge / Hypnosis / Megahorn / Jump Kick
```

### 2.12 President Rex Gaudy 1, Radio Tower (edit `TRAINER_PRESIDENT_REX_GAUDY_RADIO_TOWER_HNS`)
G1, levels 44–46. **Kingambit is listed last** in the file; Supreme Overlord scales with fainted allies, so it's the closer. Gimmick: gold, money and inevitability.
```
Persian @ King's Rock / Technician / 44 / Jolly: Fake Out / Pay Day / Power Gem / Taunt
Gholdengo @ Leftovers / Good as Gold / 45 / Modest: Make It Rain / Shadow Ball / Thunder Wave / Recover
Copperajah @ Sitrus Berry / Sheer Force / 45 / Adamant: Iron Head / Play Rough / High Horsepower / Rock Slide
Donphan @ Leftovers / Sturdy / 44 / Impish: Earthquake / Ice Shard / Knock Off / Stealth Rock
Kingambit @ Black Glasses / Supreme Overlord / 46 / Adamant: Kowtow Cleave / Iron Head / Sucker Punch / Swords Dance
```
Counterplay: Fire and Ground for the Steel types, Fighting for Kingambit (4× weak), Water for Donphan.

### 2.13 Warden Pell 3, Route 27 Border Wall (new `TRAINER_WARDEN_PELL_BORDER_WALL_HNS`)
T3 with Full Restore ×2, levels 52–54. Ursaluna last ("…Desperate times.").
```
Ursaring @ Flame Orb / Guts / 52 / Adamant: Facade / Crunch / Close Combat / Swords Dance
Granbull @ Leftovers / Intimidate / 52 / Impish: Play Rough / Earthquake / Thunder Wave / Roar
Donphan @ Sitrus Berry / Sturdy / 53 / Adamant: Earthquake / Ice Shard / Knock Off / Stealth Rock
Miltank @ Leftovers / Thick Fat / 52 / Careful: Body Slam / Milk Drink / Curse / Earthquake
Dudunsparce @ King's Rock / Serene Grace / 53 / Bold: Glare / Hyper Drill / Coil / Roost
Ursaluna @ Flame Orb / Guts / 54 / Adamant: Headlong Rush / Facade / Fire Punch / Rest
```
- Ursaring keeps Swords Dance as the team's one sweeper, so Ursaluna has no setup move.
- Counterplay: Fighting, Water and Grass; Ghosts for the Normal types.
- Intimidate and burn don't work against Guts, so the player has to outspeed or wall it.

### 2.14 Brad Grindwell 2, Cerulean Cape "date" (new `TRAINER_BRAD_GRINDWELL_CERULEAN_CAPE_HNS`)
T4, levels 62–64.
```
Rapidash @ Charcoal / Flash Fire / 62 / Jolly: Flare Blitz / Wild Charge / High Horsepower / Morning Sun
Revavroom @ Leftovers / Filter / 63 / Adamant: Shift Gear / Spin Out / Gunk Shot / High Horsepower
Lycanroc-Midnight @ Focus Sash / No Guard / 62 / Jolly: Stone Edge / Counter / Crunch / Stealth Rock
Arcanine @ Sitrus Berry / Intimidate / 63 / Adamant: Extreme Speed / Flare Blitz / Wild Charge / Morning Sun
Electivire @ Life Orb / Motor Drive / 64 / Adamant: Wild Charge / Ice Punch / Cross Chop / Earthquake
```

### 2.15 Grindwell Bros double battle, $GAUDY meme-coin mine (new `TRAINER_GRINDWELL_BROS_CRYPTO_MINE_HNS`)
T4, `Double Battle: Yes`, levels 63–65. This is a single trainer entry named `GRINDWELL BROS`, with three Pokémon from each brother. Gimmick: Follow Me redirection plus a setup partner.
```
Electivire @ Expert Belt / Motor Drive / 63 / Adamant: Follow Me / Wild Charge / Ice Punch / Cross Chop
Gallade @ Life Orb / Sharpness / 64 / Jolly: Sacred Sword / Psycho Cut / Leaf Blade / Swords Dance
Arcanine @ Sitrus Berry / Intimidate / 63 / Adamant: Extreme Speed / Flare Blitz / Snarl / Protect
Annihilape @ Leftovers / Defiant / 65 / Careful: Rage Fist / Drain Punch / Bulk Up / Protect
Tauros-Paldea-Combat @ Choice Band / Intimidate / 64 / Jolly: Close Combat / Raging Bull / Earthquake / Zen Headbutt
Revavroom @ Air Balloon / Filter / 64 / Adamant: Shift Gear / Gunk Shot / Spin Out / Protect
```
- Lead with Electivire and Gallade. Order the file so they're the first two.
- The Machamp from the bible is dropped for the six-slot limit. Log this.
- Counterplay: spread moves, Psychic/Fairy/Flying types, and Intimidate.

### 2.16 Colonel Buckshot 3, Fuchsia Big Game Ranch (new `TRAINER_COLONEL_BUCKSHOT_BIG_GAME_RANCH_HNS`)
T4, levels 65–67. No Mega here: only the President gets one.
```
Blastoise @ White Herb / Torrent / 67 / Modest: Shell Smash / Hydro Pump / Ice Beam / Aura Sphere
Clawitzer @ Choice Specs / Mega Launcher / 66 / Modest: Water Pulse / Dark Pulse / Aura Sphere / Dragon Pulse
Magnezone @ Assault Vest / Analytic / 66 / Modest: Thunderbolt / Flash Cannon / Volt Switch / Body Press
Armarouge @ Leftovers / Flash Fire / 65 / Modest: Armor Cannon / Psychic / Aura Sphere / Calm Mind
Revavroom @ Sitrus Berry / Filter / 65 / Adamant: Spin Out / Gunk Shot / High Horsepower / Taunt
Octillery @ Scope Lens / Sniper / 65 / Modest: Octazooka / Fire Blast / Ice Beam / Focus Energy
```
Armarouge's Calm Mind is the second setup move. Logged exception: Blastoise's Shell Smash is the main one.

### 2.17 President Rex Gaudy 2, Viridian Comeback Rally (new `TRAINER_PRESIDENT_REX_GAUDY_COMEBACK_RALLY_HNS`)
G2, levels 71–73, the hardest story fight. Tyranitar is the ace and Mega Evolves; it goes last.
```
Persian @ Choice Scarf / Technician / 71 / Jolly: Fake Out / U-turn / Knock Off / Pay Day
Gholdengo @ Choice Specs / Good as Gold / 72 / Modest: Make It Rain / Shadow Ball / Trick / Focus Blast
Copperajah @ Leftovers / Heavy Metal / 71 / Adamant: Heavy Slam / Play Rough / High Horsepower / Stealth Rock
Donphan @ Sitrus Berry / Sturdy / 71 / Adamant: Earthquake / Ice Shard / Knock Off / Rapid Spin
Kingambit @ Assault Vest / Supreme Overlord / 72 / Adamant: Kowtow Cleave / Iron Head / Sucker Punch / Low Kick
Tyranitar @ Tyranitarite / Sand Stream / 73 / Jolly: Stone Edge / Crunch / Earthquake / Dragon Dance
```
- Counterplay: Fighting (Tyranitar and Kingambit 4× weak), Water and Ground.
- Sand chip punishes non-Rock/Ground/Steel teams.

### 2.18 Giratina (Origin), the finale (static encounter, not a trainer)
- Use `setwildbattle SPECIES_GIRATINA_ORIGIN, 90, ITEM_GRISEOUS_CORE` and then `dowildbattle`, so the battle is catchable. The macro's third argument is the held item (see `asm/macros/event.inc`). Copy the music and setup of HnS's Ho-Oh/Lugia scripts.
- **Level 90** (A_RED −5 to A_RED = 88–93).
- The Griseous Core is required, or it reverts to Altered Forme.
- Set a "seen/caught" flag so the encounter can't repeat. If the player loses or runs, the scene must remain retriable: don't set the done-flag until after a win or catch.

### 2.19 Other new trainers (regular fights, all with full movesets)

T1/T2/T3 rules apply by location. Regular trainers use `AI: Check Bad Move / Try To Faint / Check Viability`, IVs equal to the HnS trainers on the same route, no EVs, 4 moves each. Use the bible §4 class templates and levels at the HnS trainers' levels on that route.

| Group | Count | Where | Levels |
| --- | --- | --- | --- |
| MEGA Grunts at the Union Cave Freedom Toll | 2 | Union Cave entrance | ~12–14 |
| Heritage Officers | 3 | Routes 37 and 38 | ~24–27 |
| Wellness Gurus (reclass two existing lighthouse trainers; keep their IDs, change class, pic and moves) | 2 | Olivine Lighthouse | as HnS |
| Sigma Bros (reclass Chuck's two gym trainers while Brad occupies the Dojo; restore them after) | 2 | Cianwood Gym | as HnS |
| Debate Bros (Debate Club side quest) | 3 | Goldenrod Underground | 22–25 |
| Border Agents | 2 | Route 27 Border Wall | 50–52 |
| D.O.G.E. Auditors: Porygon2, Magnezone, Klinklang templates | 3 | Silph Co. (`SaffronCity_SilphCo_hns`) | 60–63, T4-lite: IVs 24, `AI: Basic Trainer` |
| Crypto Bros (reclass S.S. Aqua sailors) | 2 | S.S. Aqua | as HnS |
| Rally Goers at the Comeback Rally | 2–3 | Viridian | 64–66 |

---

## 3. New areas and dungeons: how to build them without Porymap

You can't run Porymap. Use these techniques; they're reliable from text:

1. **New map from an existing layout.** Copy a map folder (`data/maps/<Existing>_hns/`) to a new name.
   - In `map.json`, change `id`, `name` and the events, but **keep `layout`** pointing at the existing layout ID. You don't need a new layout or new `map.bin`.
   - Add the map to the right group in `data/maps/map_groups.json`.
   - Build once so `MAP_*` constants regenerate.
   - Give it a `region_map_section` that already exists.
2. **Enter and exit new maps with scripts, not tile warps.** Tile warps need a door/stair metatile behaviour. Instead, put an NPC, sign or object (ladder, boulder, door-guard) on the source map whose script calls `warp MAP_NEW_MAP, x, y`, and do the same in reverse inside the new map. Make sure the target x/y is walkable.
3. **"Slightly changed areas"** (walls, barriers, debris): in the map's `MAP_SCRIPT_ON_LOAD`, use `setmetatile x, y, METATILE_<existing>, TRUE` gated by a flag.
   - Pick metatiles that already exist in that map's tileset: grep `include/constants/metatile_labels.h` for the tileset's labels.
   - For removable barriers, add an object event (a boulder, Sudowoodo-style or NPC) with a flag that hides it.
4. **Object limits.** At most **16 object events are loaded at once** (the player and follower take two). Keep each map to **≤ 13 visible objects** and **≤ 3 distinct overworld-Pokémon species** (each species uses a sprite palette slot).
5. **Re-entry.** Every new scene sets a flag and checks it on re-entry. Trace leaving mid-scene and coming back.

### 3.1 Areas to build (all required unless marked optional)

| Area | Map approach | Content |
| --- | --- | --- |
| **Union Cave Freedom Toll** | Existing Union Cave entrance; 2 grunts + a toll-booth NPC | Pay-or-battle joke; the battle is always allowed, never pay-to-pass. |
| **Goldenrod Underground: Debate Club + Bleak's podcast corner** | Existing `GoldenrodCity_UndergroundTunnel_hns` or another underground map | Debate Club (side quest 4); Bleak optional battle (§2.4). |
| **Ecruteak towers: Heritage Order check** | Existing maps | Gate **both** Burned Tower and Tin Tower through the one Pell check (pass 1 gated Burned only). Pedigree Certificate booth NPC; Pell's wall-plan poster in the Pokémon Center (sign). |
| **Cianwood Alpha Dojo** | The existing Cianwood Gym, re-dressed while Brad is present | A podcast-mic sign; Brad 1 battle before Chuck. Chuck's gym trainers temporarily become Sigma Bros, and the original trainers return after Brad loses. Chuck's own fight is unchanged. |
| **Radio Tower takeover** | Existing 1F–5F | Reclass and re-text every floor's grunts. Add the Chad 2, Buckshot 2 and Pell 2 fights on floors 2–4 (one each). Barry 2 at 5F (§2.8); Gaudy 1 at the top. Gaudy leaves on a gold Pidgeot (fly-off movement plus text). Silver's reaction, then the act-end Giratina line (bible §3.6). |
| **Route 27 Border Wall** | `Route27_hns`, near the Tohjo Falls side | Three-tile wall via `setmetatile` (or 3 barrier objects). 2 Border Agents, then Pell 3 at the gate. After Pell loses, the wall comes down (flag clears tiles or hides objects). Physical "STOP THE STEEL!" signs. |
| **Indigo / Victory Road** | Existing | Re-skin the Victory Road Silver encounter (dialogue). Add the revolving-door rally-goer gag. |
| **Kanto Act 11: Power Plant → $GAUDY meme-coin mine** | **New map** `CeruleanCity_CryptoMine_hns`, copying a cave layout (e.g. a `CeruleanCave_*_hns` floor). Enter via a script on an NPC or door-guard in a Cerulean building or near the Power Plant (`Route10_PowerPlantEntrance_hns`) | Mining-rig signs; Chief Thorne cameo (bible §3.5); 2 Crypto Bros; the Grindwell Bros double battle (§2.15); the Machine Part return; then Misty's date and Brad 2 at Cerulean Cape. |
| **Saffron: D.O.G.E. HQ** | Existing **`SaffronCity_SilphCo_hns`** (not the `_Frlg` maps) | Re-text the signs; 3 Auditor battles; Pressure Prompt 12 (bible §5.1). |
| **Celadon** | Existing | Erika's perfume-shop notice (sign); Gaudy Casino leftovers. |
| **Fuchsia: Big Game Ranch** | The Safari Zone entrance building used by `make hns` (find it from `FuchsiaCity_hns` warps) | Re-text it as the "Big Game Ranch"; Buckshot 3 (§2.16); Janine's line. |
| **Cinnabar and Pewter** | Existing | MEGA officials (NPCs); the Pewter Museum Kabutops exhibit with Brock and Pell (dialogue). |
| **Viridian: Comeback Rally** | Existing `ViridianCity_hns` (and the Giovanni slot that HnS uses there) | Rally crowd (3–6 red-cap NPCs) → Silver confrontation → Gaudy 2 → the "retiring to a very big, very beautiful island" exit → Team MEGA disbands. **Gate it before Blue's gym battle without changing Blue's team or badge flow.** |
| **Mt. Silver** | Existing | Two recruiter NPCs (MEGA and Sovereign's Committee) at the cave entrance, with the Red joke (bible Act 15). |
| **Giratina Axis + finale** | **New map** `GiratinaAxis_hns`, copying the `MtSilver_SummitNight_hns` layout. Enter by script after Red is beaten (a summit ripple with a fade, then `warp`) | `setweather` for a distinct look (fog or shade); Giratina–Arceus dialogue; Giratina battle (§2.18); Arceus centring scene (white flash: `fadescreen`, or the expansion's flash special). |
| **Epilogue** | Existing Goldenrod house with a TV, plus `Route29_hns` | CROSSFIRE TV scene (Bleak vs Pell). The party runs into the grass on Route 29. The final text depends on the three `VAR_PRESSURE_POINTS` tiers. Then credits. Post-credits Giratina line ("…I wonder what it looks like spun UP."). If hooking credits is too risky, show the line just before the credits call and log it. |

---

## 4. Conversations and overworld life

### 4.1 Overworld Pokémon (required)

Every Johto town and route, and every Kanto town and route the player visits in the story, gets **2–4 wandering Pokémon** from that map's own wild table (`src/data/wild_encounters.json`, the `_hns` entry for that map). Rules:
- `"graphics_id": "OBJ_EVENT_GFX_SPECIES(SENTRET)"` (the macro HnS already uses, e.g. `AkalaIsle_hns`)
- `"movement_type": "MOVEMENT_TYPE_WANDER_AROUND"`, with `movement_range_x/y` of 2–3
- place them on grass or path, never blocking a ledge, door or one-tile path
- **≤ 3 distinct species per map** (palette limit)
- each one has a script. Template:

```
Route29_EventScript_OwSentret::
	lock
	faceplayer
	playmoncry SPECIES_SENTRET, CRY_MODE_NORMAL
	msgbox Route29_Text_OwSentret, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route29_Text_OwSentret:
	.string "SENTRET is standing guard over a\n"
	.string "GAUDY yard sign. It looks unsure why.$"
```

About a third of the flavour lines should carry a joke tied to the act: yard signs, red caps, SLOWPOKE-T, rally noise, D.O.G.E. layoffs. The rest are just cute.

### 4.2 NPC conversations (required)

- **Each Johto and Kanto town:** **at least 3 new or re-texted NPC lines** that react to the current act. Reuse existing NPCs where possible, and add new NPC objects only if the object budget allows.
- **Bible §5.2 dressing:** check what pass 1 did and finish the rest:
  - vandalised town signs (New Bark "…AGAIN" and each other town)
  - MEGA billboards on every route
  - rally crowds in Goldenrod, Ecruteak and Viridian.
- **Bible §3.4 reactions:** every one of the canon characters' one-line reactions must be present. Grep for each and add any that are missing.
- **Pass-1 deferred dialogue:** finish all of the following.
  - the Act 1 arrival and Heritage Officer encounter
  - the Elm lab-fence banner
  - Route 29's Lawn Ranger and two yard signs
  - the prepper bunker at Mr. Pokémon's
  - Falkner's N.R.A. line
  - the Sprout Elder
  - Ruins of Alph: the scholar, the Klaus cameo, the SLOWPOKE-T billboard
  - Bugsy's picket
  - Silver in Ilex, and the Azalea act-end Giratina scene
  - Goldenrod rally NPCs and Dept. Store floor signs
  - Whitney's post-gym scene
  - the National Park "Open Season" contest
  - Olivine Café tariff menu, Cianwood pharmacy, cold-plunge beach NPC
  - Jasmine and Amphy
  - Lake of Rage, the Mahogany shop, Rage Radio hideout text, Pryce
  - the Vermilion N.R.A. booth
  - the S.S. Aqua washroom gag

---

## 5. Side quests (bible §5.3; all four required)

1. **Yard Sign Cleanup.**
   - 15 sign objects across Johto routes (Routes 29–46). Each has a hidden flag and a "Remove the sign?" YES/NO prompt.
   - Track the count in a var. The Lawn Ranger on Route 29 gives Leftovers at 5, Lucky Egg at 10 and Ability Capsule at 15, each once.
   - Count **flags at talk time**, not an incrementing var only, so the count can't desync.
2. **Fact-Check the Unown.**
   - After the player solves one HnS Ruins puzzle (check its flag), a new chamber shows "TOUCH GRASS".
   - Reuse an existing Ruins chamber layout as a new map (per §3) with a script-warp entrance.
   - Reward: TM Grass Knot, once.
3. **The Debate Club.**
   - Three Debate Bros back to back. Before each battle, a `multichoice` reply that only changes their reaction line.
   - Reward after all three: Choice Specs.
4. **Tariff Trouble.**
   - The Olivine Mart clerk complains. A port NPC opens a **separate `pokemart` list** at normal prices ("off the books").
   - Don't change any price code.

(Raw Moomoo was done in pass 1. Check it's there.)

---

## 6. Small fixes

- **Team MEGA residue.**
  - The region map still says `ROCKET HIDEOUT` (`src/region_map.c`, `MAPSEC_ROCKET_HIDEOUT_HNS`). Change it to `MEGA HIDEOUT` for HnS only (`#if IS_HNS`).
  - Then run the check below. It must print nothing outside `_Frlg` and `#else` branches; fix anything it finds:
    ```
    grep -rIn -E '"[^"]*(ROCKET|Rocket)[^"]*"' data/maps/*_hns src/data/text src/*.c | grep -v "#else"
    ```
- **New trainer classes on pass-1 trainers.** Use palette-swapped portraits if the expansion supports per-trainer palettes cheaply; otherwise keep pic reuse and log it. **Optional.**
- **Arceus Returns 1–3.** Confirm each `ReturnAnchoredMon` call is placed where bible Act 1/Act 2 say, with `FLAG_GILDED_RETURN_n_SEEN` set after. If any is not wired into a story scene, wire it.

---

## 7. Mission queue (top to bottom)

| ID | Mission | Done when |
| --- | --- | --- |
| P2-00 | **Setup.** Branch; baseline build; create `docs/gilded/BOSS_DESIGN.md`; fix Blair → Bleak in the bible; add pass-2 sections to the mission log. | The build passes. |
| P2-01 | **Johto boss data:** §2.1–2.13 teams in the party file (edit existing IDs, add new ones); design notes for each. Placement comes later; new IDs only need to exist. | Every Johto boss mon has 4 moves, an item, an ability, a nature, IVs, and EVs where the tier says. A grep over those entries finds no mon block without `- ` move lines. |
| P2-02 | **Barry bug + early placements:** create Barry 2 and swap it into Radio Tower 5F. Place Brad 1 (Alpha Dojo), Bleak (Underground), and the Union Cave toll grunts; reclass the lighthouse Wellness Gurus and dojo Sigma Bros; gate both Ecruteak towers; add Routes 37/38 Heritage Officers. | Each battle is reachable and traced by hand. |
| P2-03 | **Radio Tower takeover, complete:** floor re-text, Chad 2, Buckshot 2, Pell 2, Barry 2, Gaudy 1, Pidgeot exit, Silver, Giratina line. | The whole tower is traced from entry to the end flag. |
| P2-04 | **Border Wall + Victory Road + Indigo leftovers.** | The wall blocks before Pell 3 and opens after. There's no softlock if the player loses (whiting out returns them, and the wall is still passable after a later win). |
| P2-05 | **Kanto boss data:** §2.14–2.17 and the Auditors, Crypto Bros and Rally Goers, with design notes. | Same as P2-01. |
| P2-06 | **Kanto Act 11:** the crypto mine (new map), Thorne, Grindwell double, Machine Part, Misty date, Brad 2. | The new map is enterable and exitable by script warp; the HnS Machine Part flow is unchanged in outcome. |
| P2-07 | **Kanto Acts 12–13:** D.O.G.E. HQ on `_hns` Silph, Pressure Prompt 12, Auditors, Celadon, Big Game Ranch and Buckshot 3, Cinnabar, Pewter. | Everything is on reachable `_hns` maps. |
| P2-08 | **Comeback Rally:** crowd, Silver, Gaudy 2 with the Mega, exit, MEGA disbands. | Blue's battle and badge are untouched, and the rally can't be skipped or repeated. |
| P2-09 | **Finale:** Mt. Silver recruiters, Giratina Axis map, Giratina battle, Arceus scene, epilogue with three tiers, post-credits line. | Giratina stays in Origin Forme (holding the Griseous Core) and is retriable on a loss. |
| P2-10 | **Johto dialogue completion (Acts 1–4)**, from §4.2. | Every pass-1 "Deferred" dialogue item for GF4–GF7 is done or logged with a reason. |
| P2-11 | **Johto dialogue completion (Acts 5–9) + Kanto Acts 10–14 leftovers.** | Same, for GF8–GF15. |
| P2-12 | **Overworld Pokémon + town NPCs, Johto.** | Every Johto town and route has 2–4 overworld mons with scripts, and every town has ≥ 3 new lines. |
| P2-13 | **Overworld Pokémon + town NPCs, Kanto.** | Same for Kanto. |
| P2-14 | **Side quests:** all four in §5. | Each reward is given exactly once, and the counts can't desync. |
| P2-15 | **Optional:** in-battle boss lines (§1.5); palette-swapped portraits; fix the `make check` blocker. | Optional; skip freely. |
| P2-16 | **Final audit + morning report** (§9). | Pushed. |

Work top to bottom. Don't reorder P2-01 → P2-09. If one blocks, skip only the missions that depend on it.

---

## 8. Self-review before every commit (all must pass)

1. `make hns` (the long PATH command) succeeds with zero errors.
2. `git diff --stat` touches only what the mission needs, and **no `_Frlg` file**.
3. Every new constant is in `docs/gilded/registry.md`.
4. **Boss check:** in every trainer entry you added or edited, every Pokémon has 4 `- ` move lines, an `Ability:`, a nature line and an `IVs:` line. Paste the grep you used into the mission log.
5. **Trace each new or changed script by hand.**
   - Every flag/var it checks is set somewhere reachable.
   - Every warp target exists **and** is reachable from a map players visit.
   - Every trainer battle uses a trainer that exists.
   - No one trainer ID is battled in two places.
   - No permanent softlock, including losing a scripted battle.
   - Re-entering the map behaves.
   - Object count ≤ 13 visible.
6. Text fits the box and follows the guardrails. Grep the diff for real names; there must be none.
7. The mission log entry has `Status: BUILT — NEEDS PLAYTEST`, `Deferred:` (empty for boss and battle work), and a **playtest checklist with exact debug-menu steps**: warp location, flags to set, and who to talk to.

---

## 9. Morning report (`docs/gilded/MORNING_REPORT_PASS2.md`)

Include:
- each mission's status
- the ROM size
- a **boss table** (trainer, location, levels, tier, ace, intended counterplay)
- the list of new maps and how to reach each one
- how many overworld Pokémon and new NPC lines were added, per region
- anything still deferred, with the reason
- the **top 10 playtest priorities**, with debug-menu steps
  - Put first: the Barry fix, Gaudy 2's Mega, the Giratina Origin form, the Border Wall gate, the crypto-mine warps, and the Comeback Rally/Blue gating.
