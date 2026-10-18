#ifndef GUARD_RIFT_CONTRACT_H
#define GUARD_RIFT_CONTRACT_H

// =====================================================================
// THE RIFT CONTRACT (version 2)
// Shared by Pokémon Right (srdav2/pokeemerald-custom) and
// Pokémon Left (srdav2/pokehns-expansion).
//
// This file MUST be byte-identical in both repos. The master copy is
// docs/rift/rift_contract.h; include/rift_contract.h is a copy of it.
// Never edit one repo's copy alone. Read docs/rift/RIFT_CONTRACT.md.
//
// No #includes: include this after pokemon.h (needs struct BoxPokemon).
// =====================================================================

#define RIFT_CONTRACT_VERSION   2
#define RIFT_MAGIC              0x54464952  // bytes 'R','I','F','T' (little-endian u32)

// Games
#define RIFT_GAME_NONE          0
#define RIFT_GAME_RIGHT         1   // Pokémon Right (was Sovereign), Hoenn
#define RIFT_GAME_LEFT          2   // Pokémon Left (was Gilded), Johto + Kanto

// Per-game progress
#define RIFT_PROGRESS_NONE          0   // never started in this save file
#define RIFT_PROGRESS_PLAYING       1   // started, not finished
#define RIFT_PROGRESS_FIRST_FINISH  2   // finished as the FIRST game; Arceus trio exported
#define RIFT_PROGRESS_SECOND_FINISH 3   // finished as the SECOND game; all boxes unsealed

// PC box ownership (box indices are 0-based; players see 1-14)
#define RIFT_BOXES_PER_GAME     7
#define RIFT_RIGHT_FIRST_BOX    0   // boxes 1-7 belong to Right
#define RIFT_LEFT_FIRST_BOX     7   // boxes 8-14 belong to Left

// Arceus trio
#define RIFT_ANCHOR_COUNT       3
#define RIFT_ANCHOR_LEVEL_1     5
#define RIFT_ANCHOR_LEVEL_2     10
#define RIFT_ANCHOR_LEVEL_3     15

// Crossing sanitisation
#define RIFT_LAST_SHARED_BALL   27      // BALL_CHERISH in both games. Higher balls (e.g. Left's BALL_GS) become BALL_POKE.
#define RIFT_CROSSING_MET_LOCATION 0xFF // METLOC_FATEFUL_ENCOUNTER in both games

// Layout checks (asserted in src/rift_shared.c)
#define RIFT_RECORD_SIZE        340
#define RIFT_RECORD_OFFSET      34144   // offsetof(struct PokemonStorage, rift)
#define RIFT_STORAGE_SIZE       34484   // sizeof(struct PokemonStorage)

// Lives as the LAST member of struct PokemonStorage, directly after `fusions`,
// so it is saved in flash sectors 5-13 with the boxes (and in the backup slot).
struct RiftRecord
{
    /*0x000*/ u32 magic;                // RIFT_MAGIC
    /*0x004*/ u16 version;              // RIFT_CONTRACT_VERSION
    /*0x006*/ u8 lastWrittenBy;         // RIFT_GAME_*: stamped on every save
    /*0x007*/ u8 firstGame;             // RIFT_GAME_* finished first; RIFT_GAME_NONE until a first finale
    /*0x008*/ u8 progressRight;         // RIFT_PROGRESS_*
    /*0x009*/ u8 progressLeft;          // RIFT_PROGRESS_*
    /*0x00A*/ u8 boxesUnsealed;         // 1 = every box usable in every game (set by the second finale)
    /*0x00B*/ u8 playerGender;          // MALE 0 / FEMALE 1
    /*0x00C*/ u8 playerName[8];         // PLAYER_NAME_LENGTH + 1, EOS-terminated, game charmap
    /*0x014*/ u8 trainerId[4];          // same bytes as SaveBlock2.playerTrainerId
    /*0x018*/ u8 anchoredCount;         // 0..3 Pokémon chosen at the first finale
    /*0x019*/ u8 anchoredReturned;      // bit n set = anchored[n] already given back by the second game
    /*0x01A*/ u8 anchoredLevel[3];      // RIFT_ANCHOR_LEVEL_1..3
    /*0x01D*/ u8 padding1[3];           // zero
    /*0x020*/ struct BoxPokemon anchored[3]; // snapshots, already sanitised; reset/de-evolve happens on return
    /*0x110*/ u16 overflowBoxes;        // bit n = box n is in the OTHER game's half but still holds this save's
                                        // legacy Pokémon (from migrating a pre-contract save). Withdraw-only.
                                        // The file cannot cross while this is non-zero.
    /*0x112*/ u16 padding2;             // zero
    /*0x114*/ u32 reserved[15];         // zero; for future versions
    /*0x150*/ u16 checksum;             // CRC-16/CCITT-FALSE over bytes 0x000-0x14F
    /*0x152*/ u16 padding3;             // zero
}; // 0x154 = 340 bytes

#endif // GUARD_RIFT_CONTRACT_H
