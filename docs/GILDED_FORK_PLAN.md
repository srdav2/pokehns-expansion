# Pokémon Gilded Version: Build Plan (Heart & Soul fork)

**Audience:** the build agent working in the `srdav2/pokehns-expansion` repo (Pokémon Gilded), a fork of `PokemonHnS-Development/pokehns-expansion`.
**Story source:** `docs/GILDED_STORY_BIBLE.md`. All story, characters, teams and jokes come from there.
**This file replaces** the bible's §8 mission plan and the "two ROMs in one repo" parts of `FINAL_ACT_AND_TWO_ROM_HANDOVER.md`. Gilded is now its **own repo built on Heart & Soul**, which already has the full Johto + Kanto game working. Our job is to re-skin and extend it, not rebuild it.

The owner has written permission from the Heart & Soul developers to use and modify their files. Keep **all** existing HnS credits, and add our own below them.

---

## 0. Unattended rules (the owner is asleep)
1. **Never ask a question or wait for input.** If something is unclear, take the stated default, write one line in `docs/gilded/DECISIONS_LOG.md` (date | mission | decision | why), and continue.
2. **Branch:** work on `overnight/gemini`, created from the fork's default branch. Never push to the default branch. Never force-push.
3. **One mission = one commit.** Message: `Gilded <ID>: <title>`. **Push after every mission**, so nothing is lost if the session stops.
4. **A mission is "built" only when** `make -j8` succeeds with zero errors, **and** the self-review in §3 passes. Record it in `docs/gilded/mission_log.md` with `Status: BUILT — NEEDS PLAYTEST`. **Never write "verified" or "playtested."** Nobody plays the game overnight.
5. **Fix limit:** if the build won't pass after 3 attempts on the same error, revert the mission's changes (`git checkout .`), mark it `BLOCKED: <error>` in the queue, and move on to the next mission that doesn't depend on it.
6. **Scope cuts are allowed and preferred over blocking.** Build the core story beats and battles first. List anything skipped under `Deferred:` and mark the mission `BUILT_PARTIAL`.
7. **Registry:** every new flag, var, trainer, map and special goes in `docs/gilded/registry.md` with its value. Grep first to confirm a slot is unused. Never reuse an HnS slot that something still reads.
8. **Don't use `filler_*` save fields.** If you need save space, add a named field and confirm the save still fits.
9. **Content guardrails:** `GILDED_STORY_BIBLE.md` §0.2 is non-negotiable. Fictional stand-ins only. No real people's names, no slurs, no real extremist slogans or symbols, no real tragedies. The villains are the joke.
10. **Text** must fit the box: about 34 characters per line, 2 lines per box. Follow HnS's existing text conventions.
11. **Keep HnS's gym leaders, Elite Four, Champion and Red teams and levels.** Change their dialogue only, as the bible says.
12. **Don't touch any other repo** (in particular `pokeemerald-custom`). Its docs are read-only references.
13. **Stop** when the queue is finished, or 3 missions in a row are blocked. Then write `docs/gilded/MORNING_REPORT.md`: missions built, blocked or deferred, ROM size, and the top 5 things to playtest with debug-menu steps. Commit and push it.

## 1. Differences from the original bible plan
| Bible said | Now |
| --- | --- |
| G1: two-ROM split | **Not needed.** Gilded is its own repo. |
| G2: import HnS into Sovereign's repo | **Not needed.** HnS *is* the base. |
| G3: Rift Import from a Sovereign save | **Deferred** to mission GF-IMP. It needs Sovereign's final save layout, which is still being built. Tonight Gilded starts as a **New Game**. |
| Arceus returns 3 anchored Pokémon | Still happens. On a New Game, the trio is a generated **"Lost Rift" trio** (see GF1). The importer will later swap in the player's real Sovereign trio. |
| Bill unseals the Hoenn PC after the Johto League | Build the scene and the flag now. The unseal does nothing until GF-IMP exists; Bill's line works either way. |
| Level anchors | Read them from HnS's own trainer data (GF0). |

## 2. Mission queue (top to bottom)
| ID | Mission | Spec | Depends on |
| --- | --- | --- | --- |
| GF0 | **Setup and audit.** Confirm the build passes and record the expansion version and ROM size. Create `docs/gilded/` (registry, mission log, decisions log, playtest queue). Fill in the bible §2 **level anchors** table from HnS's trainer data. List HnS's Team Rocket events, with file paths, mapped to the bible's Team MEGA replacements (bible §3.1). Add the Gilded working title to the ROM header and title screen. | this file, bible §2, §3.1 | — |
| GF1 | **Rift foundation (New Game version).** (a) A function that de-evolves a Pokémon to its base form and sets it to an exact level. Use `GetSpeciesPreEvolution` in a loop. Keep nickname, IVs, nature, shininess and OT; reset EVs, moves (level-up set) and experience. (b) A named save field holding 3 anchored Pokémon, their levels (5/10/15) and returned-bits. (c) On New Game, generate the "Lost Rift" trio: 3 random non-legendary base-form species, owner's OT. (d) A special `ReturnAnchoredMon(n)` that gives Pokémon n to the party, or to the PC if the party is full. (e) Debug-menu actions to fire each return. Add `make check` tests if the HnS test setup works. | bible §3.6, handover §2.4 ideas | GF0 |
| GF2 | **Quality of life:** party-wide Exp. Share obtained early (from Elm, right after the starter), using the expansion's Gen 6+ behaviour. Running Shoes from the start. | owner request | GF1 |
| GF3 | **Team MEGA foundation** (bible G4): rename Team Rocket to Team MEGA across all HnS scripts and text. Add the new trainer classes with palette-swapped existing sprites (bible §4), `VAR_PRESSURE_POINTS` (bible §5.1), the RED CAP key item, and the boss trainer constants (bible §3.2) with teams set to the anchor bands. | bible §3–5 | GF2 |
| GF4 | Johto Act 1, New Bark → Violet (including Arceus Returns 1–2) | bible §6 Act 1 | GF3 |
| GF5 | Johto Act 2, Union Cave → Azalea (Return 3) | bible §6 Act 2 | GF4 |
| GF6 | Johto Act 3, Goldenrod | bible §6 Act 3 | GF5 |
| GF7 | Johto Act 4, Ecruteak | bible §6 Act 4 | GF6 |
| GF8 | Johto Act 5, Olivine & Cianwood | bible §6 Act 5 | GF7 |
| GF9 | Johto Act 6, Mahogany & Lake of Rage | bible §6 Act 6 | GF8 |
| GF10 | Johto Act 7, the Radio Tower takeover | bible §6 Act 7 | GF9 |
| GF11 | Johto Act 8, Blackthorn | bible §6 Act 8 | GF10 |
| GF12 | Johto Act 9: Border Wall, Victory Road, Indigo siege, E4 dialogue, Bill's PC scene (stub unseal) | bible §6 Act 9 | GF11 |
| GF13 | Kanto Acts 10–11 | bible §7 | GF12 |
| GF14 | Kanto Acts 12–13 | bible §7 | GF13 |
| GF15 | Kanto Act 14, the Comeback Rally | bible §7 | GF14 |
| GF16 | Finale and epilogue | bible §7 Act 15 | GF15 |
| GF17 | Side quests | bible §5.3 | GF16 |
| GF-IMP | Sovereign save importer | later brief | **SKIP tonight** |

**Opening note:** HnS has its own intro. Replace it with the bible's Act 1 arrival only where the bible says so. Elm's lab, the starter choice, the rival theft and the Egg flow stay as HnS has them, with new text.

## 3. Self-review before every commit (all must pass)
1. `make -j8` succeeds with zero errors.
2. `git diff --stat` only touches what the mission needs.
3. Every new constant is in `docs/gilded/registry.md`.
4. **Trace each new or changed script by hand:**
   - every flag and var it checks is set somewhere reachable
   - every warp target exists
   - every trainer battle uses a trainer that exists
   - there's no way to get permanently stuck
   - re-entering the map behaves correctly
5. Text fits the box and follows the guardrails. Grep the diff for real names; there must be none.
6. Write the mission log entry with `Status: BUILT — NEEDS PLAYTEST`, a `Deferred:` list, and a **playtest checklist with exact debug-menu steps**.
