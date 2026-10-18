// Shared Rift logic for Pokémon Right and Pokémon Left.
// MUST be byte-identical in both repos (master copy: docs/rift/rift_shared.c; src/rift_shared.c is a copy).
// Game-specific behaviour (UI, scripts, text, Pokédex, de-evolving) lives in each game's own files.

#include "global.h"
#include "malloc.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "constants/items.h"
#include "constants/pokeball.h"
#include "config/rift_game.h"
#include "rift_shared.h"

// ---- Layout checks: if any of these fail, the two games no longer agree. Do NOT just change the number. ----
STATIC_ASSERT(sizeof(struct RiftRecord) == RIFT_RECORD_SIZE, RiftRecordSize);
STATIC_ASSERT(offsetof(struct RiftRecord, anchored) == 0x20, RiftAnchoredOffset);
STATIC_ASSERT(offsetof(struct RiftRecord, checksum) == 0x150, RiftChecksumOffset);
STATIC_ASSERT(offsetof(struct PokemonStorage, rift) == RIFT_RECORD_OFFSET, RiftRecordInStorage);
STATIC_ASSERT(sizeof(struct PokemonStorage) == RIFT_STORAGE_SIZE, RiftStorageSize);
STATIC_ASSERT(sizeof(struct PokemonStorage) <= (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START + 1) * SECTOR_DATA_SIZE, RiftStorageFitsSectors);
STATIC_ASSERT(sizeof(struct BoxPokemon) == 80, RiftBoxMonSize);
STATIC_ASSERT(TOTAL_BOXES_COUNT == 2 * RIFT_BOXES_PER_GAME, RiftBoxCount);
STATIC_ASSERT(IN_BOX_COUNT == 30, RiftInBoxCount);
STATIC_ASSERT(PLAYER_NAME_LENGTH + 1 == 8, RiftNameLength);
STATIC_ASSERT(TRAINER_ID_LENGTH == 4, RiftTrainerIdLength);
STATIC_ASSERT(BALL_CHERISH == RIFT_LAST_SHARED_BALL, RiftLastSharedBall);
STATIC_ASSERT(RIFT_THIS_GAME != RIFT_OTHER_GAME, RiftGameIds);

static const u8 sAnchorLevels[RIFT_ANCHOR_COUNT] = {RIFT_ANCHOR_LEVEL_1, RIFT_ANCHOR_LEVEL_2, RIFT_ANCHOR_LEVEL_3};

struct RiftRecord *Rift_GetRecord(void)
{
    return &gPokemonStoragePtr->rift;
}

u16 Rift_Crc16(const void *data, u32 size)
{
    const u8 *bytes = data;
    u16 crc = 0xFFFF;
    u32 i, bit;

    for (i = 0; i < size; i++)
    {
        crc ^= (u16)(bytes[i] << 8);
        for (bit = 0; bit < 8; bit++)
        {
            if (crc & 0x8000)
                crc = (u16)((crc << 1) ^ 0x1021);
            else
                crc = (u16)(crc << 1);
        }
    }
    return crc;
}

u16 Rift_ComputeChecksum(const struct RiftRecord *rec)
{
    return Rift_Crc16(rec, offsetof(struct RiftRecord, checksum));
}

bool32 Rift_IsRecordValid(const struct RiftRecord *rec)
{
    return rec->magic == RIFT_MAGIC
        && rec->version == RIFT_CONTRACT_VERSION
        && rec->checksum == Rift_ComputeChecksum(rec);
}

u8 Rift_GetProgress(const struct RiftRecord *rec, u8 game)
{
    if (game == RIFT_GAME_RIGHT)
        return rec->progressRight;
    if (game == RIFT_GAME_LEFT)
        return rec->progressLeft;
    return RIFT_PROGRESS_NONE;
}

void Rift_SetProgress(struct RiftRecord *rec, u8 game, u8 progress)
{
    if (game == RIFT_GAME_RIGHT)
        rec->progressRight = progress;
    else if (game == RIFT_GAME_LEFT)
        rec->progressLeft = progress;
}

static void CopyIdentityFromSave(struct RiftRecord *rec)
{
    memcpy(rec->playerName, gSaveBlock2Ptr->playerName, sizeof(rec->playerName));
    rec->playerGender = gSaveBlock2Ptr->playerGender;
    memcpy(rec->trainerId, gSaveBlock2Ptr->playerTrainerId, sizeof(rec->trainerId));
}

static void ApplyIdentityToSave(const struct RiftRecord *rec)
{
    memcpy(gSaveBlock2Ptr->playerName, rec->playerName, sizeof(rec->playerName));
    gSaveBlock2Ptr->playerGender = rec->playerGender;
    memcpy(gSaveBlock2Ptr->playerTrainerId, rec->trainerId, sizeof(rec->trainerId));
}

void Rift_StampForSave(void)
{
    struct RiftRecord *rec = Rift_GetRecord();

    rec->magic = RIFT_MAGIC;
    rec->version = RIFT_CONTRACT_VERSION;
    rec->lastWrittenBy = RIFT_THIS_GAME;
    if (Rift_GetProgress(rec, RIFT_THIS_GAME) == RIFT_PROGRESS_NONE)
        Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_PLAYING);
    CopyIdentityFromSave(rec);
    rec->checksum = Rift_ComputeChecksum(rec);
}

void Rift_InitForNewGame(void)
{
    struct RiftRecord *rec = Rift_GetRecord();

    memset(rec, 0, sizeof(*rec));
    rec->magic = RIFT_MAGIC;
    rec->version = RIFT_CONTRACT_VERSION;
    rec->lastWrittenBy = RIFT_THIS_GAME;
    Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_PLAYING);
    CopyIdentityFromSave(rec);
    rec->checksum = Rift_ComputeChecksum(rec);
}

enum RiftSaveKind Rift_ClassifyLoadedSave(void)
{
    const struct RiftRecord *rec = Rift_GetRecord();
    u8 thisProgress, otherProgress;

    if (rec->magic != RIFT_MAGIC)
        return RIFT_SAVE_OWN_LEGACY;
    if (rec->version != RIFT_CONTRACT_VERSION)
        return RIFT_SAVE_UNREADABLE; // a future version must add a migration here
    if (rec->checksum != Rift_ComputeChecksum(rec))
        return (rec->lastWrittenBy == RIFT_THIS_GAME) ? RIFT_SAVE_OWN : RIFT_SAVE_UNREADABLE; // own: repaired by the next save
    if (rec->lastWrittenBy == RIFT_THIS_GAME)
        return RIFT_SAVE_OWN;

    thisProgress = Rift_GetProgress(rec, RIFT_THIS_GAME);
    otherProgress = Rift_GetProgress(rec, RIFT_OTHER_GAME);
    if (thisProgress != RIFT_PROGRESS_NONE || otherProgress == RIFT_PROGRESS_SECOND_FINISH)
        return RIFT_SAVE_FOREIGN_DONE;
    if (otherProgress == RIFT_PROGRESS_FIRST_FINISH)
        return RIFT_SAVE_FOREIGN_READY;
    return RIFT_SAVE_FOREIGN_UNFINISHED;
}

u8 Rift_FirstBoxOf(u8 game)
{
    return (game == RIFT_GAME_LEFT) ? RIFT_LEFT_FIRST_BOX : RIFT_RIGHT_FIRST_BOX;
}

bool32 Rift_IsBoxOwnedBy(u8 boxId, u8 game)
{
    u8 first = Rift_FirstBoxOf(game);
    return boxId >= first && boxId < first + RIFT_BOXES_PER_GAME;
}

bool32 Rift_IsBoxDepositable(u8 boxId)
{
    const struct RiftRecord *rec = Rift_GetRecord();

    if (boxId >= TOTAL_BOXES_COUNT)
        return FALSE;
    if (rec->magic != RIFT_MAGIC || rec->boxesUnsealed)
        return TRUE;
    return Rift_IsBoxOwnedBy(boxId, RIFT_THIS_GAME);
}

bool32 Rift_IsBoxViewable(u8 boxId)
{
    if (boxId >= TOTAL_BOXES_COUNT)
        return FALSE;
    if (Rift_IsBoxDepositable(boxId))
        return TRUE;
    return (Rift_GetRecord()->overflowBoxes & (1 << boxId)) != 0;
}

u8 Rift_FirstDepositableBox(void)
{
    u8 boxId;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        if (Rift_IsBoxDepositable(boxId))
            return boxId;
    }
    return Rift_FirstBoxOf(RIFT_THIS_GAME);
}

static bool32 BoxMonExists(struct BoxPokemon *mon)
{
    return GetBoxMonData(mon, MON_DATA_SANITY_HAS_SPECIES) != 0;
}

u16 Rift_CountMonsInBoxes(u8 firstBox, u8 count)
{
    u16 total = 0;
    u8 boxId, pos;

    for (boxId = firstBox; boxId < firstBox + count && boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            if (BoxMonExists(&gPokemonStoragePtr->boxes[boxId][pos]))
                total++;
        }
    }
    return total;
}

// Strips the held item (into this game's Bag when toBag is TRUE), clamps the ball, sets the met location.
static void SanitizeBoxMon(struct BoxPokemon *mon, bool32 toBag, struct RiftCrossingReport *report)
{
    u32 value;

    if (!BoxMonExists(mon))
        return;

    value = GetBoxMonData(mon, MON_DATA_HELD_ITEM);
    if (value != ITEM_NONE)
    {
        if (toBag && AddBagItem(value, 1))
        {
            if (report != NULL)
                report->itemsToBag++;
        }
        else if (report != NULL)
        {
            report->itemsLost++;
        }
        value = ITEM_NONE;
        SetBoxMonData(mon, MON_DATA_HELD_ITEM, &value);
    }

    value = GetBoxMonData(mon, MON_DATA_POKEBALL);
    if (value > RIFT_LAST_SHARED_BALL)
    {
        value = BALL_POKE;
        SetBoxMonData(mon, MON_DATA_POKEBALL, &value);
    }

    value = RIFT_CROSSING_MET_LOCATION;
    SetBoxMonData(mon, MON_DATA_MET_LOCATION, &value);
}

void Rift_MigrateLegacyStorage(void)
{
    struct RiftRecord *rec = Rift_GetRecord();
    u8 ownFirst = Rift_FirstBoxOf(RIFT_THIS_GAME);
    u8 boxId, pos, dstBox = ownFirst, dstPos = 0;

    // The bytes where the record now lives held other data in legacy saves: start clean.
    memset(rec, 0, sizeof(*rec));

    // Pack every Pokémon outside this game's half into free slots inside it.
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        if (Rift_IsBoxOwnedBy(boxId, RIFT_THIS_GAME))
            continue;
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            struct BoxPokemon *src = &gPokemonStoragePtr->boxes[boxId][pos];

            if (!BoxMonExists(src))
                continue;
            while (dstBox < ownFirst + RIFT_BOXES_PER_GAME
                && BoxMonExists(&gPokemonStoragePtr->boxes[dstBox][dstPos]))
            {
                if (++dstPos >= IN_BOX_COUNT)
                {
                    dstPos = 0;
                    dstBox++;
                }
            }
            if (dstBox >= ownFirst + RIFT_BOXES_PER_GAME)
            {
                rec->overflowBoxes |= (1 << boxId); // no room: stays put, withdraw-only
                continue;
            }
            gPokemonStoragePtr->boxes[dstBox][dstPos] = *src;
            ZeroBoxMonData(src);
        }
    }

    rec->magic = RIFT_MAGIC;
    rec->version = RIFT_CONTRACT_VERSION;
    rec->lastWrittenBy = RIFT_THIS_GAME;
    Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_PLAYING);
    CopyIdentityFromSave(rec);
    if (!Rift_IsBoxViewable(gPokemonStoragePtr->currentBox))
        gPokemonStoragePtr->currentBox = Rift_FirstDepositableBox();
    rec->checksum = Rift_ComputeChecksum(rec);
}

void *Rift_BackupStorage(void)
{
    void *backup = Alloc(sizeof(struct PokemonStorage));

    if (backup != NULL)
        memcpy(backup, gPokemonStoragePtr, sizeof(struct PokemonStorage));
    return backup;
}

void Rift_FinishArrival(void *backup)
{
    struct RiftRecord *rec;
    u8 boxId, pos, i;

    if (backup == NULL)
        return;
    memcpy(gPokemonStoragePtr, backup, sizeof(struct PokemonStorage));
    Free(backup);

    rec = Rift_GetRecord();
    ApplyIdentityToSave(rec);
    Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_PLAYING);
    rec->lastWrittenBy = RIFT_THIS_GAME;

    // Defensive: the exporting game already sanitised, but never trust data from another ROM.
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        if (Rift_IsBoxOwnedBy(boxId, RIFT_THIS_GAME))
            continue;
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
            SanitizeBoxMon(&gPokemonStoragePtr->boxes[boxId][pos], FALSE, NULL);
    }
    for (i = 0; i < RIFT_ANCHOR_COUNT; i++)
        SanitizeBoxMon(&rec->anchored[i], FALSE, NULL);
    for (i = 0; i < MAX_FUSION_STORAGE; i++)
        ZeroMonData(&gPokemonStoragePtr->fusions[i]);

    gPokemonStoragePtr->currentBox = Rift_FirstBoxOf(RIFT_THIS_GAME);
    rec->checksum = Rift_ComputeChecksum(rec);
}

u8 Rift_CheckCrossingBlockers(void)
{
    u8 blockers = RIFT_BLOCK_NONE;
    u8 i;

    for (i = 0; i < MAX_FUSION_STORAGE; i++)
    {
        if (GetMonData(&gPokemonStoragePtr->fusions[i], MON_DATA_SPECIES) != SPECIES_NONE)
            blockers |= RIFT_BLOCK_FUSION_STORAGE;
    }
    if (Rift_GetRecord()->overflowBoxes != 0)
        blockers |= RIFT_BLOCK_OVERFLOW;
    return blockers;
}

bool32 Rift_StoreAnchor(u8 slot, struct BoxPokemon *src)
{
    struct RiftRecord *rec = Rift_GetRecord();

    if (slot >= RIFT_ANCHOR_COUNT || !BoxMonExists(src))
        return FALSE;
    rec->anchored[slot] = *src;
    SanitizeBoxMon(&rec->anchored[slot], TRUE, NULL);
    rec->anchoredLevel[slot] = sAnchorLevels[slot];
    if (rec->anchoredCount < slot + 1)
        rec->anchoredCount = slot + 1;
    rec->anchoredReturned &= ~(1 << slot);
    return TRUE;
}

void Rift_PrepareCrossing(struct RiftCrossingReport *report)
{
    u8 ownFirst = Rift_FirstBoxOf(RIFT_THIS_GAME);
    u8 boxId, pos;

    memset(report, 0, sizeof(*report));
    for (boxId = ownFirst; boxId < ownFirst + RIFT_BOXES_PER_GAME; boxId++)
    {
        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            struct BoxPokemon *mon = &gPokemonStoragePtr->boxes[boxId][pos];

            if (!BoxMonExists(mon))
                continue;
            report->monsCrossing++;
            SanitizeBoxMon(mon, TRUE, report);
        }
    }
}

void Rift_MarkFirstFinish(void)
{
    struct RiftRecord *rec = Rift_GetRecord();

    Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_FIRST_FINISH);
    if (rec->firstGame == RIFT_GAME_NONE)
        rec->firstGame = RIFT_THIS_GAME;
    rec->checksum = Rift_ComputeChecksum(rec);
}

bool32 Rift_IsSecondGame(void)
{
    const struct RiftRecord *rec = Rift_GetRecord();
    return rec->magic == RIFT_MAGIC && rec->firstGame == RIFT_OTHER_GAME;
}

u8 Rift_GetAnchorCount(void)
{
    return Rift_GetRecord()->anchoredCount;
}

u8 Rift_GetAnchorLevel(u8 slot)
{
    if (slot >= RIFT_ANCHOR_COUNT)
        return 0;
    return Rift_GetRecord()->anchoredLevel[slot];
}

bool32 Rift_TakeAnchor(u8 slot, struct BoxPokemon *dst)
{
    struct RiftRecord *rec = Rift_GetRecord();

    if (slot >= rec->anchoredCount || (rec->anchoredReturned & (1 << slot)))
        return FALSE;
    if (!BoxMonExists(&rec->anchored[slot]))
        return FALSE;
    *dst = rec->anchored[slot];
    rec->anchoredReturned |= (1 << slot);
    rec->checksum = Rift_ComputeChecksum(rec);
    return TRUE;
}

void Rift_MarkSecondFinish(void)
{
    struct RiftRecord *rec = Rift_GetRecord();

    Rift_SetProgress(rec, RIFT_THIS_GAME, RIFT_PROGRESS_SECOND_FINISH);
    rec->boxesUnsealed = 1;
    rec->overflowBoxes = 0;
    rec->checksum = Rift_ComputeChecksum(rec);
}
