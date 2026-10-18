# Gilded decisions log

| Date | Mission | Decision | Why |
| --- | --- | --- | --- |
| 2026-10-17 | GF0 | Keep the documented working title “Pokémon Gilded Version”. | This is the default in `docs/GILDED_STORY_BIBLE.md` §9. |
| 2026-10-17 | GF1 | Store the three anchors and their return state in named fields appended to `PokemonStorage`; select distinct enabled base species that are not restricted legendaries, sub-legendaries, Mythicals, or Ultra Beasts. | SaveBlock1 had insufficient sector space for the trio. PokemonStorage has room in its allocated save sectors, and this keeps the anchors out of the player's visible party until a return scene or debug action requests them. |
| 2026-10-18 | GF2 | Set the existing Running Shoes flags during HnS New Game initialization and skip Mom's later handoff; give Elm's Gen 6 Exp. Share immediately after the starter and enable its existing toggle. | This makes both requested quality-of-life features available at the beginning while avoiding a duplicate Running Shoes handoff. |
