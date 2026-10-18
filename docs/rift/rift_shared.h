#ifndef GUARD_RIFT_SHARED_H
#define GUARD_RIFT_SHARED_H

// Shared Rift logic for Pokémon Right and Pokémon Left.
// MUST be byte-identical in both repos (master copy: docs/rift/rift_shared.h).
// Each game provides include/config/rift_game.h defining RIFT_THIS_GAME and RIFT_OTHER_GAME.

#include "rift_contract.h"

// What the title screen should do with the save that was just loaded.
enum RiftSaveKind
{
    RIFT_SAVE_OWN,                // this game wrote it: Continue as normal
    RIFT_SAVE_OWN_LEGACY,         // no Rift record yet (pre-contract save of THIS game): migrate, then Continue
    RIFT_SAVE_FOREIGN_READY,      // the other game finished first: offer "Arrive through the Rift" or New Game
    RIFT_SAVE_FOREIGN_UNFINISHED, // the other game is still in progress: no Continue; New Game only after 2 warnings
    RIFT_SAVE_FOREIGN_DONE,       // this game was already played in this file (both worlds done): no Continue; warn
    RIFT_SAVE_UNREADABLE,         // newer contract version or corrupt record from the other game: no Continue; warn
};

// Reasons a first-finale crossing is blocked (bit flags)
#define RIFT_BLOCK_NONE            0
#define RIFT_BLOCK_FUSION_STORAGE  (1 << 0) // a fused Kyurem/Necrozma/Calyrex partner is in fusion storage: unfuse first
#define RIFT_BLOCK_OVERFLOW        (1 << 1) // legacy Pokémon still sit in the other game's boxes: move them first

struct RiftCrossingReport
{
    u16 monsCrossing;   // Pokémon in this game's half that will cross
    u16 itemsToBag;     // held items moved into this game's Bag
    u16 itemsLost;      // held items that didn't fit in the Bag (removed)
};

struct RiftRecord *Rift_GetRecord(void);
u16 Rift_Crc16(const void *data, u32 size);            // CRC-16/CCITT-FALSE: Rift_Crc16("123456789", 9) == 0x29B1
u16 Rift_ComputeChecksum(const struct RiftRecord *rec);
bool32 Rift_IsRecordValid(const struct RiftRecord *rec);
u8 Rift_GetProgress(const struct RiftRecord *rec, u8 game);
void Rift_SetProgress(struct RiftRecord *rec, u8 game, u8 progress);

// Saving / loading
void Rift_StampForSave(void);                          // call immediately before EVERY save is written
void Rift_InitForNewGame(void);                        // call at the end of NewGameInitData (after the trainer ID exists)
enum RiftSaveKind Rift_ClassifyLoadedSave(void);       // call right after the save is loaded, BEFORE anything reads SaveBlock1/2
void Rift_MigrateLegacyStorage(void);                  // for RIFT_SAVE_OWN_LEGACY, before Continue

// Arrival (second game). Order: Rift_BackupStorage -> normal new-game init (calls Rift_InitForNewGame) -> Rift_FinishArrival.
void *Rift_BackupStorage(void);                        // Alloc()s and copies the whole PokemonStorage; NULL if out of memory
void Rift_FinishArrival(void *backup);                 // restores storage + record, applies the saved identity, Free()s backup

// PC box rules
u8 Rift_FirstBoxOf(u8 game);
bool32 Rift_IsBoxOwnedBy(u8 boxId, u8 game);
bool32 Rift_IsBoxDepositable(u8 boxId);                // may this game put Pokémon into the box?
bool32 Rift_IsBoxViewable(u8 boxId);                   // may the player open it / withdraw from it?
u8 Rift_FirstDepositableBox(void);
u16 Rift_CountMonsInBoxes(u8 firstBox, u8 count);

// First finale (exporting game)
u8 Rift_CheckCrossingBlockers(void);                   // RIFT_BLOCK_* flags; 0 = OK to cross
bool32 Rift_StoreAnchor(u8 slot, struct BoxPokemon *src); // copies + sanitises (held item -> Bag); caller then removes the original
void Rift_PrepareCrossing(struct RiftCrossingReport *report); // sanitises every Pokémon in this game's half
void Rift_MarkFirstFinish(void);

// Second game
bool32 Rift_IsSecondGame(void);                        // TRUE if this game was started by arriving through the Rift
u8 Rift_GetAnchorCount(void);
u8 Rift_GetAnchorLevel(u8 slot);
bool32 Rift_TakeAnchor(u8 slot, struct BoxPokemon *dst); // FALSE if empty/already returned; caller resets level and gives it
void Rift_MarkSecondFinish(void);                      // unseals every box

#endif // GUARD_RIFT_SHARED_H
