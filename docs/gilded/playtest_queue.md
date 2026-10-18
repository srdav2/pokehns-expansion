# Gilded playtest queue

All entries are queued until a ROM can be built. The overworld debug menu is opened by holding **R** and pressing **Start**.

1. **Title and new-game entry**
   - Boot the ROM; inspect the title branding, then start a fresh save and follow the HnS starter-selection flow.
   - Debug: from the overworld, **R + Start → ROM Info… → Expansion Version / ROM space**.
2. **Rift trio returns (GF1)**
   - Confirm each returned Pokémon has its expected level, original identity fields, and exactly-once behavior; fill the party and confirm the PC fallback.
   - Debug: use the three GF1 return actions once they are added; use **Utilities… → Warp to map warp…** to reach each return location.
3. **Team MEGA event flow**
   - Confirm the Slowpoke Well, Mahogany hideout, Radio Tower, and Underground events retain their HnS progression and use the planned replacement characters.
   - Debug: **R + Start → Utilities… → Warp to map warp…**; **Trainers… → Choose trainer from map → Try Battle**.
4. **Pressure Prompt choices**
   - For each prompt, select YES and NO on separate save copies and confirm neither choice blocks progression.
   - Debug: warp to the event map with **Utilities… → Warp to map warp…**; inspect state with **Flags & Vars… → Set Flag XYZ… / Set Var XYZ…**.
5. **Save/reload across an act**
   - Save and reload before and after an event; confirm event flags, returned Pokémon, and map state do not duplicate or reset.
   - Debug: use **Utilities… → Warp to map warp…** for the event map and **ROM Info… → Save Block space** for save-space inspection.
