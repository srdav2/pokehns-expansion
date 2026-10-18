# Pokémon Gilded Version: Story Bible & Build Plan

**Audience:** the build agent. **Prerequisites:** `FINAL_ACT_AND_TWO_ROM_HANDOVER.md` (architecture, save contract, Rift Import) and Sovereign Mission 19.
**Base content:** Pokémon Heart & Soul (HnS), an open-source pokeemerald-expansion remake of Johto and Kanto (`github.com/PokemonHnS-Development/pokehns-expansion`).
**The one-line pitch:** Giratina has spun the world to the right. Johto is now run by a gold-plated tycoon president and his movement, Team MEGA. You are the Sovereign Champion of Hoenn, and they think you're one of them.

---

## 0. Rules for this build

### 0.1 Engineering
All rules in the handover doc apply. In addition:
- **Re-skin HnS before adding to it.** HnS already has the full Gold/Silver story flow (Team Rocket events, gyms, rival, Kanto post-game). Wherever possible, **keep HnS's event logic and replace the characters, text and teams**. Build new maps or events only where this bible asks for them.
- **Keep HnS's gym leaders, Elite Four, Champion and Red at HnS's teams and levels.** Only rewrite dialogue as this bible says.
- **Keep HnS's ordinary route trainers.** Give roughly 1 in 4 of them one extra line of MEGA-flavoured dialogue.
- **Text fits the box.** Emerald's message box holds about 34 characters per line and 2 lines per box. Lines written here are *intent*; wrap them with `\n`, `\l` and `\p` and test them on screen. No NPC speaks for more than 3 boxes unless it's a cutscene.

### 0.2 Content guardrails (non-negotiable)
1. **Fictional stand-ins only.** Never use the names, likenesses, photos or exact logos of real people or organisations. Puns that *evoke* are the point (the "National Rattata Association"); real names are not. Don't write dialogue presented as a real person's actual words.
2. **No slurs and no real extremist material.** No real hate-group names, slogans, numbers, symbols or imagery (hoods, torches, insignia). The Heritage Order is mocked through its absurd obsession with "pure single-type, Johto-born Pokémon". Never make jokes at the expense of any real ethnic, religious or national group.
3. **No real tragedies.** No references to real shootings, attacks or deaths. The N.R.A. jokes target lobbying, merch and gear-hoarding, never violence against people.
4. **No sexual content.** Manosphere jokes target grindset culture, supplements, crypto, cold plunges and "alpha" posturing, not anyone's body.
5. **The player can always say no**, and refusing is never punished mechanically.
6. **The villains are the joke.** Townsfolk, gym leaders and professors are mostly sane people reacting to the nonsense. Keep jokes short and frequent, with no lectures.
7. **Keep the two-sided symmetry.** Sovereign mocked the left and Gilded mocks the right. Sovereign's villains make cameo appearances, and the jokes land on them too. The ending lands on "both extremes are ridiculous".

---

## 1. Premise & themes

- **The world:** the Gold/Silver-era Johto and Kanto of HnS, three years after Red. In this timeline, **President Rex Gaudy** (gold everything, a gold Persian, name on every building) runs the Indigo Republic. His movement, **Team MEGA** ("Make Everything Great Again"; the gag is that they're obsessed with Mega Evolution), has absorbed Team Rocket's remnants and runs Rocket's old schemes with more merch.
- **The player:** the Sovereign Champion of Hoenn, fallen through Giratina's rift. Team MEGA have heard of the "Sovereign Champion who crushed the Committee" and **assume the player is on their side**. That assumption is the engine of the pressure comedy: everyone keeps trying to recruit you.
- **Arceus** found three of your Pokémon in the timeline and returns them early in the journey.
- **Giratina** appears at each act's end, delighted with the chaos: *"Isn't it fun? Last time it was pronouns. This time it's protein powder."*
- **The arc:** the player beats Team MEGA's schemes across Johto, wins the Johto League, and the Hoenn PC is restored. In Kanto, the player unravels the President's comeback and faces Red. At Mt. Silver's summit, the player stops Giratina's spinning, and Arceus **centres** the world. The epilogue shows both games' villains shouting at each other on a TV panel show while the player goes outside.

---

## 2. Level system

HnS has its own balance. **Do not invent absolute levels.** Before writing any team, read HnS's trainer data and record these values in the registry (the "Gilded level anchors" table):

| Token | Meaning |
| --- | --- |
| `A_FALK`, `A_BUG`, `A_WHIT`, `A_MORT`, `A_CHUCK`, `A_JAS`, `A_PRYCE`, `A_CLAIR` | Highest level on each Johto gym leader's team in HnS |
| `A_LANCE` | Lance's ace |
| `A_BROCK`, `A_MISTY`, `A_SURGE`, `A_ERIKA`, `A_JANINE`, `A_SABRINA`, `A_BLAINE`, `A_BLUE` | Kanto gym aces |
| `A_RED` | Red's ace |

**Bands:**
- Grunts: anchor of the *next* gym −6 to −3, with 1–3 Pokémon.
- Wing commanders (bosses): next anchor −1 to +1.
- President Gaudy: next anchor +1 to +3.
- Optional battles may go +2 over.

**Level caps:** with `FLAG_SYS_HARD_LEVEL_CAP`, Gilded's cap table is the anchors, in badge order.

---

## 3. Cast

### 3.1 Team MEGA
Look: Team Rocket grunt sprites with **red caps** (palette swap). The "R" on the uniform becomes a gold "M". Hideouts are merch shops.

| Wing | Leader | What they parody | Type theme |
| --- | --- | --- | --- |
| **The Executive** | **President Rex Gaudy** | a bombastic tycoon-politician | Gold and Steel, "luxury" |
| **The Sigma Brotherhood** | **Chad & Brad Grindwell** ("the Grindwell Brothers") | manosphere influencer brothers: grindset, courses, supplements, supercars, crypto | Fighting, Fire, Normal |
| **The National Rattata Association (N.R.A.)** | **Colonel Buckshot Beaumont** | a gun lobby, re-imagined as a Poké Ball lobby | "cannon" Pokémon: Water, Steel |
| **The Heritage Order** | **Warden Augustus Pell** | nativist "heritage" types, obsessed with pedigree and purity | **single-type, Johto-native Pokémon only** |
| *(Affiliated)* **Rage Radio** | **Barry Blaster** | outrage talk radio and rage-bait | loud Pokémon, rage |
| *(Affiliated)* Wellness grifters | **Sage Purely** | anti-medicine wellness influencers | Grass, Poison, "natural remedies" |

**HnS Team Rocket mapping:**
- Proton → **Chad Grindwell** (Slowpoke Well, Radio Tower)
- Petrel → **Barry Blaster** (Mahogany hideout / Lake of Rage transmitter, and the fake Director)
- Ariana → **Colonel Buckshot** (Radio Tower, Goldenrod Underground)
- Archer → **Warden Pell** (Radio Tower top floor)
- Giovanni → **President Gaudy** (Radio Tower finale, then the Viridian comeback rally)

Grunt classes are renamed. Event logic is kept.

### 3.2 Bosses

#### President Rex Gaudy
- **Bio:** He put his name on the Radio Tower ("GAUDY TOWER") and is sure he built it. Owns a gold Persian. Says everything is the greatest in history. Never admits a loss.
- **Sample lines:**
  - *"People are saying this is the greatest Radio Tower in the history of towers. I built it. Well — I put my name on it. Same thing."*
  - *"My Persian is solid gold. Fourteen karat. Maybe twelve. It's gold-ish."*
  - *(Gholdengo uses Make It Rain)* *"MAKE IT RAIN! …Somebody pick that up."*
  - *On defeat: "I won. I won by a lot. That was a total win for me."*
  - *Mega Evolution (Kanto rally): "MEGA! Make Evolution Great Again!"*
- **Team 1, Radio Tower** (`A_CLAIR` −1 to +1; this fight comes before Clair, so it's tough): Persian (Pay Day), Gholdengo (Make It Rain), Copperajah, Kingambit, Donphan.
- **Team 2, Viridian Comeback Rally** (`A_BLUE` +2 to +4): Persian, Gholdengo, Kingambit, Copperajah, Donphan, **Tyranitar @ Tyranitarite** (Mega Evolves).

#### Chad Grindwell (Sigma Brotherhood, "Alpha")
- **Bio:** wakes at 3 a.m. and wants you to know it. Sells **SLOWPOKE-T** ("pure Slowpoke Tail testosterone"). Has never finished a book, but sells a course about reading.
- **Lines:**
  - *"3 a.m. Cold plunge. Black coffee. Battle. That's the GRINDSET."*
  - *"You still use a Pokédex? Brokie behaviour."*
  - *"My Machamp never skips leg day. He has four arms. He skips arm day."*
  - *Selling: "SLOWPOKE-T. 400% more alpha. Side effects include yawning."*
  - *On defeat: "This is a learning experience. I'll monetise it."*
- **Team 1, Slowpoke Well** (`A_BUG` −2 to 0): Machop, Mankey, **Tauros** (ace, "Bull Market").
- **Team 2, Radio Tower** (`A_CLAIR` −2 to 0): Machamp, Primeape, Hitmontop, Tauros, Pangoro.
- **Team 3, Cerulean crypto mine, double battle with Brad** (`A_MISTY` 0 to +2): Machamp, Annihilape, Gallade ("Sigma"), Paldean Tauros (Combat).

#### Brad Grindwell (Sigma Brotherhood, "Lifestyle")
- **Bio:** the supercar-and-crypto brother. Calls his Rapidash a "hypercar". Runs the **$GAUDY** meme-coin. Lives at Cianwood's "Alpha Dojo", which is Chuck's gym with a podcast mic duct-taped to it.
- **Lines:**
  - *"Chuck trains under a waterfall. Cringe. I do a cold plunge. It's a waterfall you can film."*
  - *"Escape the Poké Ball, bro. Wake up."*
  - *On Misty's date: "I was explaining Water-types to her. She's a Water-type leader? …Okay but did she do her own research?"*
- **Team 1, Alpha Dojo, Cianwood** (`A_CHUCK` −1 to +1): Rapidash, Electabuzz, Lycanroc (Midnight, "lone wolf"), Varoom.
- **Team 2, Cerulean Cape date** (`A_MISTY` −1 to +1): Rapidash, Revavroom, Lycanroc-Midnight, Arcanine, Electivire.
- **Team 3:** double battle with Chad (above): Rapidash, Revavroom, Arcanine, Electivire.

#### Colonel Buckshot Beaumont (N.R.A.)
- **Bio:** head of the National Rattata Association. Has never served in anything, including food. Every Pokémon he owns is a cannon.
- **Lines:**
  - *"Section Two of the League Charter: a well-regulated Party being necessary to the security of a free Route, the right of the trainers to keep and bear Poké Balls shall not be infringed."*
  - *"The only thing that stops a bad trainer with a Pokémon is a good trainer with six."*
  - *"Ball Show this weekend! No waiting period! No idea what's in the ball!"*
  - *On defeat: "This is why we need MORE Poké Balls."*
- **Team 1, Goldenrod Dept Store "Ball Show" (optional)** (`A_WHIT` −1 to +1): Remoraid, Krabby, Magnemite, **Clauncher** (ace).
- **Team 2, Radio Tower** (`A_CLAIR` −2 to 0): Octillery, Kingler, Clawitzer, Magneton, Cramorant.
- **Team 3, Fuchsia "Big Game Ranch"** (`A_JANINE` +1 to +3): Blastoise, Clawitzer, Magnezone, Armarouge, Revavroom, Octillery.

#### Warden Augustus Pell (Heritage Order)
- **Bio:** carries a clipboard of "Pedigree Certificates". Thinks dual-type Pokémon are a plot. Wants a wall between Johto and Kanto. Calls the player "the Hoenn transplant".
- **Lines:**
  - *"Papers, please. Johto-born? No? HOENN? A transplant."*
  - *"My Pokémon are pure single-types. No mixing. Mixing is how you get… Steel/Fairy."*
  - *"We're building a wall between Johto and Kanto. And Kanto is going to pay for it."*
  - *On defeat: "Fine. Your Pokémon may stay. But they must learn the Johto anthem."*
  - *Sending out Ursaluna, his only dual-type: "…Desperate times."*
- **Team 1, Ecruteak tower gate** (`A_MORT` −1 to +1): Dunsparce, Stantler, **Sudowoodo** (ace). *"A rock pretending to be a tree. Like our heritage."*
- **Team 2, Radio Tower** (`A_CLAIR` −1 to +1): Ursaring, Granbull, Donphan, Sudowoodo, Stantler.
- **Team 3, Route 27 Border Wall** (`A_LANCE` −4 to −2): Ursaring, Granbull, Donphan, Miltank, Dudunsparce, Ursaluna (sent last, with the line above).

#### Barry Blaster (Rage Radio)
- **Bio:** broadcasts outrage 24/7 from a transmitter under the Mahogany merch store. The rage signal is what's forcing Lake of Rage's Magikarp to evolve. (This is the same plot as HnS's Mahogany radio signal; only the reason changes.)
- **Lines:**
  - *"The Lake of Rage didn't name itself, folks! WE did! Stay angry, stay listening!"*
  - *"Coming up after the break: why is grass green? Who decided that? Wake up."*
  - *On defeat: "This just in: I lost. Fake news."*
- **Team, Lake of Rage / Mahogany hideout** (`A_PRYCE` −1 to +1): Exploud, Primeape, Noibat, Gyarados (ace).
- He then poses as the "Director" in the Radio Tower (the fake-Director role): *"Everything you heard is fake news. Except me. Trust me."*

#### Sage Purely (wellness grifter)
- **Bio:** a "wellness" influencer who has convinced the Olivine Lighthouse keeper that Amphy doesn't need medicine.
- **Lines:**
  - *"Doctors don't want you to know about Rapidash Paste. Big Potion is SCARED."*
  - *"Do your own research! I did. It was a video."*
  - *On defeat: "Okay but have you considered… vibes?"*
- **Team, top of Olivine Lighthouse** (`A_JAS` −2 to 0): Gloom, Weepinbell, Foongus, Comfey (ace, "nature's band-aid").

### 3.3 Silver (rival)
- **The canon role stands:** he steals Elm's Pokémon and is the President's estranged son (HnS's Giovanni-son arc, re-pointed).
- **Arc:** a grindset wannabe who slowly works out that his dad is a fraud.
  - Early: *"Alphas don't ask. Alphas TAKE."*
  - Mid: *"My dad says winning is everything. He also says he's never lost. Those can't both be true."*
  - Late: *"I unsubscribed from the Grindwells. I just… train now."*
  - Viridian rally: Silver confronts his father before the player does.
- **Teams:** HnS's rival teams and levels, unchanged.

### 3.4 Canon characters' one-line reactions (dialogue only; teams unchanged)
| Character | Gilded take |
| --- | --- |
| Prof. Elm | Frazzled, decent, permanently filling in government forms. *"This is a research lab, not a permit office!"* |
| Mr. Pokémon | A doomsday prepper with a bunker of canned Leftovers. Still gives you the Egg. |
| Prof. Oak | His radio show is being pressured to rebrand as "Pokémon Talk: Patriot Edition". He refuses, politely. |
| Falkner | The N.R.A. declared "open season on Flying-types". He is furious. |
| Bugsy | The Heritage Order pickets his gym, convinced it's a front for making people "eat the bugs". *"I just like bugs!"* |
| Whitney | A grunt calls her crying "hysteria". She cries, wins, and Rollouts him. |
| Morty | Conspiracy theorists say his Ghost gym is "the deep state". He finds this flattering. |
| Eusine | A full-on Suicune truther with a corkboard. Harmless. Correct, as it turns out. |
| Chuck | The real waterfall guy. The Grindwells filmed him for content without asking. |
| Jasmine | Nearly fooled by Sage Purely into skipping Amphy's medicine. Grateful. |
| Pryce | *"Back in my day we were angry WITHOUT a radio telling us to be."* |
| Clair | Loses to you, then demands a recount. *"I… I demand a recount."* (The player can reply: *"That's what THEY say."*) |
| Will | Accused of mind control. *"I'm a Psychic-type trainer. I'm not doing anything. I'm bored."* |
| Koga | The N.R.A. idolise him. *"A ninja carries one blade. He does not post about it."* |
| Bruno | The Sigma Brothers' idol. *"Rest days matter. And sleep. Go to bed."* |
| Karen | Grunts keep asking to speak to the manager. *"I AM the manager."* |
| Lance | The only adult in the room. Sincere throughout. |
| Lt. Surge | *"Kid, I was in a real war. These guys bought their belts at the mall."* |
| Misty | On a date with Brad Grindwell at Cerulean Cape. *"Thanks. He kept explaining water to me."* |
| Sabrina | The D.O.G.E. auditors emailed her gym asking "what did you do this week?" *"I replied with my mind."* |
| Erika | Her perfume shop was banned for "woke scents". She is unbothered and still asleep. |
| Blaine | Cinnabar's volcano erupted. MEGA officials insist *"it's just weather"*. Blaine is now based in Seafoam. |
| Brock | Pewter Museum exhibits are being "revised" by the Heritage Order. Brock quietly puts them back. |
| Blue | Viridian Gym leader. *"Gramps told me about you. You're the one everyone's trying to recruit."* |
| Red | The only person in either timeline with no opinion. Everyone wants him as a spokesman. He says *"…"*. |
| Bill | Patches the PC to unseal your Hoenn storage after the Johto League. *"Timelines are just really big boxes."* |

### 3.5 Sovereign cameos (both-sides jokes)
- **Commissar Blair** (Goldenrod Underground): now hosts a *"Recovering Leftist"* podcast, sponsored by SLOWPOKE-T. *"Turns out you can grift in both directions. Who knew?"* Optional battle (`A_WHIT` +2), with their Sovereign species evolved.
- **Chairman Klaus** (Azalea, park bench): *"Ze bugs… zey were never ze problem."*
- **Chief Thorne** (Cerulean crypto mine, Kanto): *"We burned COAL to mine Equi-Coin. These idiots hooked a meme-coin rig to an entire POWER PLANT. Amateurs."*

### 3.6 Arceus & Giratina
- **Arceus** is calm, dry and faintly tired. It returns your anchored Pokémon:
  - **Return 1:** *"I found this one wandering the timeline. It was very confused about who the president is."*
  - **Return 2:** *"This one tried to subscribe to a course. I intervened."*
  - **Return 3:** *"The last of them. Rest. The road ahead is loud."*
- **Giratina** appears at the end of each act (a 1–2 box scene with a screen ripple):
  - After Azalea: *"Isn't it fun? Last time it was pronouns. This time it's protein powder."*
  - After the Radio Tower: *"A Persian made of gold. I couldn't have designed that if I tried. And I did try."*
  - After the Johto League: *"Halfway. Keep spinning."*

---

## 4. New trainer classes
Reuse existing trainer pics with palette swaps. **No new trainer art in v1.**

| Class | Sprite base | Team template | Sample line |
| --- | --- | --- | --- |
| MEGA Grunt (M/F) | Rocket grunt, red cap | Rattata, Zubat, Koffing, Grimer, Houndour, Murkrow | *"Nice hat. Oh, you're not wearing one. Yet."* |
| Sigma Bro | Black Belt | Machop, Mankey, Makuhita, Tyrogue, Timburr | *"I don't have friends. I have a network."* |
| Crypto Bro | Rich Boy | Meowth, Magnemite, Porygon, Gimmighoul | *"Down 98%. That's just the dip."* |
| Ball Carrier (N.R.A.) | Gentleman / Cooltrainer M | Krabby, Remoraid, Magnemite, Clauncher, Octillery | *"I carry six Poké Balls. And a seventh, for freedom."* |
| Heritage Officer | Policeman | Dunsparce, Stantler, Sentret, Hoothoot (single-type only, enforced) | *"Is that Pokémon Johto-born? Show me the tag."* |
| Talk Radio Host | Gentleman / Guitarist | Whismur, Loudred, Noibat, Exploud | *"I'm just asking questions! Loudly!"* |
| Wellness Guru | Aroma Lady | Oddish, Bellsprout, Comfey, Foongus | *"I cured my Zubat's Confusion with crystals."* |
| Tradwife Influencer | Lady | Chansey, Miltank, Skitty, Flabébé | *"I quit being an Ace Trainer to bake sourdough. Anyway, here's my 4-hour morning routine."* |
| Prepper | Hiker | Geodude, Phanpy, Swinub, Snorlax (rare) | *"I have 400 cans of Leftovers. You're welcome to none of them."* |
| Rally Goer | Youngster / Lass | Pidgey, Rattata, Sentret, Wooloo | *"I'm here for the free hat."* |
| Border Agent | Policeman | Growlithe, Houndour, Stantler | *"Purpose of visit? Wrong answer. Battle."* |
| D.O.G.E. Auditor (Kanto) | Scientist | Porygon2, Magnezone, Klinklang | *"Your position has been made efficient. You're fired."* |

---

## 5. Game-wide systems

### 5.1 Pressure Prompts
- A new var, `VAR_PRESSURE_POINTS`. About a dozen YES/NO moments where MEGA tries to recruit or upsell you. Saying YES adds 1 and gives a joke outcome. Saying NO gives a different joke. **Never block progress either way.**
- The epilogue reads the total (see §7).
- List:
  1. **Elm's Lab, the "Department of Traditional Values" clerk.**
     - Boy: *"Alpha Assessment! Firm handshake please."* YES → *"Your grip registered as 'Magikarp'. Our 12-week course is ₽0. Upsells sold separately."*
     - Girl: *"Trainer licences require a husband's co-signature."* YES → *"Wonderful! Please list your husband." (You have none.) "…We'll circle back."* Elm rips up the form either way.
  2. **Cherrygrove, petition "Make Cherrygrove Great Again".** YES → *"Thank you! What was wrong with it?" "I don't know."*
  3. **Sprout Tower, Bellsprout Ministries "Seed Faith".** Donate ₽1000? YES → you lose ₽1000. *"Your Bellsprout will evolve… spiritually."*
  4. **Azalea, SLOWPOKE-T.** Buy for ₽3000? YES → you get an X Attack: *"It's an X Attack with a sticker on it."*
  5. **Goldenrod, a free RED CAP.** YES → key item **RED CAP**. Some grunts change their pre-battle line if you have it: *"Nice hat. You're one of us!" (Battle anyway.)*
  6. **Dept Store Ball Show, "mystery ball" (₽2000).** YES → it's a Voltorb, and you battle it.
  7. **Ecruteak, Unown Ancestry Kit.** YES → *"Results: 100% Hoenn. The Heritage Order would like a word."*
  8. **Olivine, Sage Purely's Rapidash Paste for Amphy.** YES → Jasmine is horrified. You still have to fetch real medicine.
  9. **Mahogany merch store, "Gaudy Gold Kicks" (₽9999).** YES → **Iron Ball**. *"They're heavy because they're premium."*
  10. **Radio Tower: swear loyalty to the President?** YES → *"Great! Now fight me anyway. It's a loyalty test."*
  11. **Indigo Plateau siege: sign an affidavit that the League was rigged.** YES → *"Excellent. Rigged by who?" "…Unclear."*
  12. **Saffron, D.O.G.E. email: "Reply with 5 things you did this week."** YES → *"Thank you. You're fired from a job you never had."*

### 5.2 Overworld dressing (everywhere)
- **MEGA billboards and yard signs:** re-text existing signposts. Examples:
  - *"GAUDY: The Best Route. Maybe Ever."*
  - *"Pure Johto Since Forever (Est. Last Year)"*
  - *"Don't Tread On My Tauros"*
  - *"Real Trainers Wake Up At 3AM — Grindwell Bros"*
- **Town entrance signs** get a vandalised second line. New Bark Town's sign reads *"Winds of a New Beginning"*, and someone has added *"…AGAIN"*.
- **Rally crowds:** 3–6 static NPCs with red caps in the city squares of Goldenrod, Ecruteak and Viridian. Each says one line.

### 5.3 Side quests
1. **Yard Sign Cleanup.** 15 MEGA yard signs across the Johto routes, as interactable objects you remove with a hidden flag each. The "Lawn Ranger" on Route 29 tracks your count. Rewards: 5 → Leftovers, 10 → Lucky Egg, 15 → Ability Capsule. *"A clean lawn is a free lawn."*
2. **Fact-Check the Unown** (Ruins of Alph). A Heritage scholar claims the Unown walls spell "JOHTO FIRST". After one HnS Ruins puzzle, a new chamber shows they spell **"TOUCH GRASS"**. Reward: TM (Grass Knot).
3. **Raw Moomoo** (Route 39). Overlay text on HnS's sick-Miltank quest: a wellness influencer insists the farm's raw milk "cures everything", including the sick Miltank. It doesn't. Berries do.
4. **The Debate Club** (Goldenrod Underground). Three "Debate Bro" trainers back to back. Before each battle, they pose an absurd claim (*"Magikarp is the strongest Pokémon, prove me wrong"*) and you pick a reply from a multichoice. The reply only changes their line. Reward: Choice Specs.
5. **Tariff Trouble** (Olivine). The Mart clerk complains about "tremendous tariffs on Kanto imports". A port NPC sells a few items at normal price "off the books". (Use a separate shop list, not a code change to prices.)

---

## 6. Walkthrough: Johto

Each act lists: **Beats**, **Battles**, **Overworld additions**, **HnS notes**. "Return N" means `ReturnAnchoredMon(N-1)`, guarded by its own flag.

### Act 1: New Bark Town → Violet City (badge 1)

**Beats**
1. **Arrival** (post-import cutscene): the player wakes on Elm's lab floor. Elm: *"You fell through my ceiling. Again, someone fell through my ceiling. Is this a regional thing?"* A Heritage Officer arrives with a clipboard: *"A HOENN transplant? Where are your papers?"* Elm vouches for you.
2. Pressure Prompt 1 (the clerk). Elm explains that President Gaudy's government now "streamlines" research. Choose a starter (HnS's choice).
3. Silver steals a starter from the lab window (the HnS event), with the line *"Alphas don't ask. Alphas TAKE."* The player gets HnS's normal first rival battle at Cherrygrove.
4. **Mr. Pokémon errand:** the prepper bunker, with Oak present. Oak: *"They want me to rebrand my show. 'Patriot Edition'. I said, the Pokémon don't vote!"* Oak gives the Pokédex.
5. **Return 1** (Route 30, on the way back): Arceus appears on the path. The Lv 5 anchored Pokémon is returned.
6. Violet City. **Sprout Tower** is now "Bellsprout Ministries", a prosperity gospel (Pressure Prompt 3). Sages are now "Pastors of Growth". The Elder still gives Flash: *"I don't endorse any of this. I just live here."*
7. **Falkner** (HnS team). Pre-battle: *"The N.R.A. declared open season on Flying-types! On MY birds!"* Zephyr Badge.
8. **Return 2** (Route 32, just south of Violet): *"This one tried to subscribe to a course. I intervened."*

**Battles**
- Route 29/30: 2 Rally Goers and 1 MEGA Grunt (at `A_FALK` −6 to −4).
- Sprout Tower: replace 2 HnS Sages with 2 "Pastors of Growth" (Bellsprout teams); keep the rest.

**Overworld additions**
- New Bark: the vandalised sign, plus a **"GAUDY 4 PRESIDENT (AGAIN)"** banner on Elm's lab fence.
- Cherrygrove: petition NPC (Prompt 2). The Guide Gent is now a "Freedom Guide": *"I'll show you the town. It's free. As in, freedom."*
- Route 29: Lawn Ranger (side quest 1) and 2 yard signs.

**HnS notes:** keep HnS's lab, rival, Egg and Pokédex events, with text changes only.

### Act 2: Union Cave → Azalea → Ilex Forest (badge 2)

**Beats**
1. Ruins of Alph exterior: the Heritage scholar (side quest 2 hook).
2. Union Cave: a MEGA "Freedom Toll" checkpoint (2 grunts). *"This tunnel is free. Toll is ₽500. For freedom."* You battle through.
3. Azalea: the Slowpoke tails are missing (HnS event). Kurt: *"Some muscle-bound clowns are selling the tails as supplements!"* Pressure Prompt 4 is at the Mart entrance.
4. **Slowpoke Well:** the SLOWPOKE-T "production line". Grunts, then **Chad Grindwell (Team 1)**.
5. Chairman Klaus cameo (park bench).
6. **Return 3** (Azalea, outside the gym after the Well): *"The last of them. Rest. The road ahead is loud."*
7. **Bugsy:** Heritage Officers picket outside with *"WE WON'T EAT THE BUGS"* signs. Bugsy: *"Nobody is asking you to eat the bugs!"* Hive Badge.
8. Ilex Forest: HnS's Farfetch'd and Charcoal events, plus the Silver battle (HnS). Silver: *"I bought the Grindwell course. Module one is 'Take What You Want'. Module two costs extra."*
9. Act-end Giratina scene: *"Isn't it fun? Last time it was pronouns. This time it's protein powder."*

**Battles:** Slowpoke Well uses 4 HnS grunts (re-classed as Sigma Bros and MEGA Grunts) plus Chad.

**Overworld additions:** a SLOWPOKE-T billboard in Azalea, the picket NPCs outside the gym, and 2 yard signs on Route 33.

### Act 3: Goldenrod City (badge 3)

**Beats**
1. Goldenrod is gold-plated. The Radio Tower is now **"GAUDY TOWER"** (exterior sign re-text, with a gold palette tweak if cheap). The Rally crowd is in the square. Pressure Prompt 5 (the RED CAP) is given at the station.
2. **Dept Store rooftop "Ball Show"** (N.R.A.): Pressure Prompt 6, and the optional **Colonel Buckshot (Team 1)** battle.
3. **Whitney:** a grunt is outside the gym. *"Lady gym leaders get too emotional."* Whitney wins, cries, and Rollouts him (scripted text after the player beats her). Plain Badge.
4. **Bill** (HnS gives Eevee). Bill: *"Your PC's acting weird, huh? Timeline stuff. Win the League and I'll patch it."* This sets up the Hoenn PC reunion.
5. **Goldenrod Underground:** the Debate Club (side quest 4) and the **Commissar Blair cameo**.
6. **National Park:** the HnS Bug-Catching Contest is re-texted as the N.R.A.'s **"Open Season"**. *"It's catch-and-release, Colonel." "…Fine. Catch and RE-LEASE. Freedom."*

**Battles:** 1–2 MEGA grunts in the station, the optional Buckshot, and the 3 Debate Bros.

**Overworld additions:** 6 rally NPCs with one line each, a gold-lettered GAUDY TOWER sign, and Dept Store floor signs (*"5F: Freedom Balls"*).

### Act 4: Ecruteak City (badge 4)

**Beats**
1. **The Heritage Order controls access to the Burned and Tin Towers.** *"Pure Johtonians only. Pedigree certificate?"* **Warden Pell (Team 1)** blocks the gate. Defeat him to enter (his gate check is replaced by the HnS Burned Tower entry flow).
2. Burned Tower: HnS's legendary beasts and the Silver battle. Silver: *"My dad says winning is everything. He also says he's never lost. Those can't both be true."*
3. **Eusine**, the Suicune truther, has a corkboard in the Pokémon Center: *"Everyone laughs. But I've SEEN it. It's blue. It's majestic. It runs."*
4. Pressure Prompt 7 (the Unown Ancestry Kit) at the Dance Theatre. The Kimono Girls are pressured into "tradwife content". *"We are dancers." "Yes, but have you tried dancing… traditionally?" "That's what we do."*
5. **Morty:** *"They say my gym is the 'deep state'. I'm honestly flattered."* Fog Badge.

**Battles:** 3 Heritage Officers on Route 37/38 and Pell at the gate.

**Overworld additions:** a "Pedigree Certificate" booth NPC, and Pell's wall-plan poster in the Pokémon Center (*"PHASE 1: WALL. PHASE 2: ???"*).

### Act 5: Olivine & Cianwood (badges 5 & 6)
The HnS order of these two gyms is kept. Anchors follow whichever comes first in HnS.

**Beats**
1. Olivine: side quest 5 (Tariff Trouble). Jasmine is up the lighthouse with sick Amphy, and **Sage Purely** is at the top. Pressure Prompt 8. Beat Sage (her team above).
2. Cianwood: the Pharmacy gives real medicine. Pharmacist: *"It's been tested. It's boring. It works."* The **Alpha Dojo** sits in Chuck's gym, with **Brad Grindwell (Team 1)** before Chuck. Chuck: *"They keep calling my waterfall a 'cold plunge'. It's a waterfall."* Storm Badge.
3. Return the medicine to Jasmine. Jasmine: Mineral Badge.

**Battles:** 2 Wellness Gurus on the lighthouse floors, 2 Sigma Bros in the dojo (Chuck's gym trainers re-classed for this visit only; restore them afterwards), Sage and Brad.

**Overworld additions:** Olivine Café menu re-text (*"Moomoo Latte — now 145% more expensive (tariffs)"*), and a Cianwood beach NPC doing a cold plunge on camera.

### Act 6: Mahogany & Lake of Rage (badge 7)

**Beats**
1. Mahogany's souvenir shop is now the **MEGA Merch Store**. Pressure Prompt 9 is at the counter.
2. Lake of Rage: the Red Gyarados event (HnS). **Lance** appears (HnS) and works out that the signal is coming from Mahogany.
3. **Hideout** (HnS's Rocket Hideout under the shop) becomes the **Rage Radio studio**. Floors of grunts and Talk Radio Hosts lead to **Barry Blaster**, who shuts down the transmitter. Lance: *"Turns out you can make a lot of creatures angry with a radio."*
4. **Pryce:** *"Back in my day, we were angry WITHOUT a radio telling us to be."* Glacier Badge.

**Battles:** keep HnS's hideout grunts (re-classed) and add Barry.

### Act 7: The Radio Tower Takeover (Goldenrod)

**Beats**
1. **President Gaudy** takes over GAUDY TOWER to broadcast his announcement: *"I alone can evolve your Magikarp."* The Johto-wide broadcast scene uses HnS's Radio Tower takeover flow.
2. **The fake Director** is Barry Blaster in disguise (HnS's fake-Director role): *"Everything you've heard is fake news. Except me."* The real Director is in the Underground warehouse (HnS).
3. Tower floors: grunts, then **Chad (Team 2)** and **Buckshot (Team 2)**, then **Pell (Team 2)**. Pressure Prompt 10 is on the stairs.
4. Top floor: **President Gaudy (Team 1)**. After his loss: *"I won. I won by a lot. That was a total win for me."* He announces he's "disbanding Team MEGA to start a new, better party", and leaves on a gold Pidgeot ("Gaudy Air One").
5. Silver watches his father leave. *"…That's my dad."*
6. Act-end Giratina scene: *"A Persian made of gold. I couldn't have designed that if I tried. And I did try."*

### Act 8: Blackthorn (badge 8)

**Beats**
1. Ice Path (HnS).
2. **Clair** loses, refuses the badge (canon), then: *"I… demand a recount."* The player picks one of two replies (*"That's what THEY say."* / *"…Fine."*). The Dragon's Den test runs as in HnS. Rising Badge.
3. The Dragon's Den Elder quizzes you as in HnS, with one extra joke question: *"What do you do when you lose a battle?" (1) Demand a recount (2) Train harder.* Picking (1) gets *"…Go away and come back."* The canon flow then continues.

### Act 9: The Border Wall, Victory Road & the Johto League

**Beats**
1. **Route 27 / Tohjo Falls:** the Heritage Order is building **THE WALL**. It's 3 tiles long; you can walk around it. Border Agents (2 battles), then **Warden Pell (Team 3)**. Pell: *"And Kanto is going to pay for it." (Kanto has not been informed.)*
2. **Victory Road:** HnS's Silver battle. *"I unsubscribed from the Grindwells. I just… train now."*
3. **Indigo Plateau siege:** MEGA rally-goers occupy the lobby with **"STOP THE STEEL!"** signs (they think Jasmine's Steelix rigged the League). Pressure Prompt 11 is at the door. Battle 2 Rally Goers to reach the Center counter. One wears a Tauros-horn helmet and is stuck in the revolving door. *"I've been here three days."*
4. **Elite Four and Lance** (HnS teams, new dialogue per §3.4).
5. **Hall of Fame.** Giratina appears: *"Halfway. Keep spinning."*

**Johto post-game unlocks**
- **Bill's PC patch:** call `UnsealHoennStorage()`. Bill phones: *"Your old boxes are back. Timelines are just really big boxes."* The whole Hoenn PC is visible.
- Elm gives the S.S. Ticket (HnS).

---

## 7. Walkthrough: Kanto & the finale

Kanto gym order is free, as in HGSS/HnS. Each scene stands alone and gates on its own flags.

### Act 10: The S.S. Aqua → Vermilion
- The S.S. Aqua is now the **"Mar-a-Magikarp"**, the President's resort cruise. Sailors become Rally Goers and Crypto Bros. **Gag:** in the first-class washroom, stacks of boxes marked *"TOP SECRET POKéDEX ENTRIES"*. *"Why are these in the bathroom?" "Storage."*
- **Vermilion:** an N.R.A. booth tries to recruit Lt. Surge, who is having none of it (§3.4). Snorlax at Diglett's Cave is unchanged (HnS).

### Act 11: The Power Plant → Cerulean crypto mine
- The Power Plant's Machine Part is stolen (HnS event). The thieves are the **Grindwell Brothers**, powering a **$GAUDY meme-coin mining rig** in a new interior (re-dressed from a Cerulean house or cave map).
- **Chief Thorne cameo** (§3.5).
- **Chad + Brad double battle (Team 3s).** On defeat: *"$GAUDY is down 98%." "That's just the dip." "It's the whole coin, bro."* The part is returned.
- **Misty's date** at Cerulean Cape (HnS event): her date is **Brad Grindwell (Team 2)**. Misty: *"Thanks. He kept explaining water to me."*

### Act 12: Saffron & Celadon
- **Saffron:** Silph Co is now the HQ of the **D.O.G.E. (Department Of Gym Efficiency)**. Auditors have "made efficient" the gym trainers in Sabrina's gym. Pressure Prompt 12. Battle 3 D.O.G.E. Auditors. Sabrina: *"I replied with my mind."* The HnS Magnet Train part quest is unchanged.
- **Celadon:** the Game Corner is now the **"GAUDY CASINO"**, with a *"BANKRUPT (4th time) — UNDER NEW GAUDY MANAGEMENT"* sign. Erika's perfume shop has a "banned: woke scents" notice. Erika: *"Zzz… they can ban whatever. Zzz."*

### Act 13: Fuchsia, Cinnabar, Pewter
- **Fuchsia:** the old Safari Zone gate is the N.R.A. **"Big Game Ranch"**. *"It's catch-and-release, Colonel." "We've been over this."* **Colonel Buckshot (Team 3).** Koga's daughter Janine: *"Dad says don't trust anyone who brags about their gear."*
- **Cinnabar:** MEGA officials on the ruined island: *"It's just weather. Islands explode sometimes."* Blaine in Seafoam is unchanged (HnS).
- **Pewter:** Museum signs read *"Exhibit REMOVED: Kabutops (too divisive)"*. Brock is quietly putting them back. An optional Pell sighting with a single line: *"I'm here to correct the fossils."*

### Act 14: Viridian, the Comeback Rally
- President Gaudy returns: **"THE COMEBACK RALLY — BIGGER THAN EVER"** in Viridian's square (the HnS Giovanni slot).
- **Silver confronts his father first** (cutscene): *"You never built anything. You just put your name on it."* Gaudy: *"Who is this kid? Never met him. Great kid."*
- **President Gaudy (Team 2)**, with Mega Tyranitar: *"MEGA! Make Evolution Great Again!"* After his loss, he announces he's *"retiring to a very big, very beautiful island"* and leaves. MEGA is gone for good.
- Then **Blue** (HnS Viridian Gym).

### Act 15: Mt. Silver & the finale
1. **Red** (HnS). *"…"* Two NPCs at the cave entrance, one from MEGA and one from Sovereign's Committee, are both trying to recruit him. *"He'd be perfect. He never says anything we disagree with."*
2. After Red, the summit ripples. **Giratina (Origin)** opens the Axis (reuse Sovereign's DW-3 map in Gilded with a new palette):
   > Giratina: "You've seen it spun left. You've seen it spun right. Aren't they *fun*?"
   > Arceus: "Enough. The world is not a top."
3. **Battle: Giratina (Origin)** at `A_RED` −5 to `A_RED`, catchable. `DECISION:` the default allows catching.
4. **Arceus centres the world:** a white flash, then the spin reverses. Arceus:
   > "Left was loud. Right was loud. The middle is quiet, and quiet is where people actually live."
5. **Epilogue (Goldenrod, TV):** a panel show, **"CROSSFIRE"**, has **Commissar Blair and Warden Pell** shouting over each other. The player turns off the TV. The final scene is Route 29, where your party runs into the grass. A final text box depends on `VAR_PRESSURE_POINTS`:
   - 0: *"You said no to everything. Exhausting. Correct."*
   - 1–5: *"Go outside. Touch grass. Route 29 has excellent grass."*
   - 6+: Arceus, *"You agreed to a great many things. Read the fine print next time."*
6. **Credits.** Then a post-credits gag: Giratina, *"…I wonder what it looks like spun UP."*

---

## 8. Mission plan (one commit each)

| # | Mission | Scope | Done when |
| --- | --- | --- | --- |
| **G0** | Permission, credits & audit | Owner asks on the HnS Discord for permission (agent drafts the message). Copy HnS credits into `CREDITS.md`. Audit HnS's expansion version (1.15.x) against ours (1.17.2) and list what breaks. Fill in the **Gilded level anchors** table from HnS data. Measure HnS's map/tileset/graphics size. | Audit report in `docs/gilded_import_audit.md`. Owner confirms permission. |
| **G1** | (= Sovereign M19) | Two-ROM split and save contract. | See the handover doc. |
| **G2** | HnS content import | Bring HnS's Johto + Kanto maps, layouts, tilesets, MAPSECs, region map, heal locations, wild tables, trainers, scripts and text into the `IS_GILDED` variant. Port 1.15 → 1.17 syntax. Map HnS's flags/vars onto `flags_gilded.h` / `vars_gilded.h` around the shared contract. Rename nothing yet. | `make gilded` builds. A Gilded New Game plays New Bark → Violet as plain HnS. ROM size reported. |
| **G3** | Rift Import | §3 of the handover doc, plus the New Game fallback trio. | Handover test protocol (handover §4) passes in mGBA and RetroArch. |
| **G4** | Team MEGA foundation | Trainer classes (§4) and palette swaps, the Rocket → MEGA rename across all HnS scripts, `VAR_PRESSURE_POINTS`, the RED CAP key item, and the `ReturnAnchoredMon` events wired to placeholder triggers. | All grunts show as MEGA. Debug-fire all returns. |
| **G5** | Act 1 | §6 Act 1 | Play to the Zephyr Badge; Returns 1–2 fire once. |
| **G6** | Act 2 | §6 Act 2 | Play to the Hive Badge; Return 3; Giratina scene. |
| **G7** | Act 3 | §6 Act 3 | Play to the Plain Badge; all Goldenrod optional content works. |
| **G8** | Act 4 | §6 Act 4 | Fog Badge; Pell gate works and can't be skipped. |
| **G9** | Act 5 | §6 Act 5 | Both badges; the dojo trainers are restored after the visit. |
| **G10** | Act 6 | §6 Act 6 | Glacier Badge; Red Gyarados event intact. |
| **G11** | Act 7 | §6 Act 7 | The Radio Tower full chain, start to finish. |
| **G12** | Act 8 | §6 Act 8 | Rising Badge; recount gag branches both ways. |
| **G13** | Act 9 + Johto post-game | §6 Act 9, `UnsealHoennStorage` via Bill | Hall of Fame; Hoenn PC fully restored, no duplicates. |
| **G14** | Kanto I–II | §7 Acts 10–11 | Power Plant restored; double battle; Misty's date. |
| **G15** | Kanto III–IV | §7 Acts 12–13 | All four scenes play in any order. |
| **G16** | Kanto V | §7 Act 14 | Mega Evolution triggers; rally cutscene. |
| **G17** | Finale & epilogue | §7 Act 15 | All 3 epilogue variants verified via debug var. |
| **G18** | Side quests | §5.3 | All 5 completable; rewards given once. |
| **G19** | Polish | A full playthrough from a real Sovereign save, a text pass (every box fits), a balance pass against the anchors, and a check that both ROM sizes are under 32 MB with ≥ 1 MB spare. | Owner plays it. |

**Each act mission's playtest also checks:**
- that act's Pressure Prompts, both YES and NO
- the act's text renders without overflow
- level caps match the anchors
- no MEGA dressing is left over in areas a later act has "cleared" (if applicable)
- save/reload mid-act.

---

## 9. Decisions for the owner (defaults in bold)
1. Working title: **Pokémon Gilded Version**.
2. Faction and boss names as written: **President Rex Gaudy, Team MEGA, the Grindwell Brothers, the N.R.A. (National Rattata Association), the Heritage Order (Warden Pell), Barry Blaster, Sage Purely**.
3. Silver is the President's son: **yes**.
4. A New Game without an import is allowed, with a random "Lost Rift" trio: **yes**.
5. Keep HnS's wild encounter tables: **yes** (Sovereign's Gen 1–9 approach is not reapplied).
6. Keep HnS's gym/E4/Red teams and levels: **yes**.
7. RED CAP as a new key item: **yes** (cosmetic only).
8. Giratina catchable at the finale: **yes**. An Arceus battle as optional post-credits: **no** (later).
9. Pokédex carries over on import: **yes**.
10. Returning to Hoenn from Gilded: **no**. The Sovereign file stays playable on its own.
