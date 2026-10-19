#include "global.h"
#include "config/rift_game.h"
#include "credits.h"
#include "main.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "pokedex.h"
#include "rift_left.h"
#include "rift_shared.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/party_menu.h"

static void *sRiftArrivalBackup;
static bool8 sSkipSavedChallengeSettings;
static u16 sAnchorItemsToBag;
static u16 sAnchorItemsLost;

#if IS_HNS
static const u16 sReturnFlags[] =
{
    FLAG_GILDED_RETURN_1_SEEN,
    FLAG_GILDED_RETURN_2_SEEN,
    FLAG_GILDED_RETURN_3_SEEN,
};
#endif

bool32 IsRiftSecondGame(void)
{
    return Rift_IsSecondGame();
}

bool32 Rift_BeginArrival(void)
{
    if (sRiftArrivalBackup != NULL)
        return FALSE;

    sRiftArrivalBackup = Rift_BackupStorage();
    if (sRiftArrivalBackup == NULL)
        return FALSE;

    sSkipSavedChallengeSettings = TRUE;
    return TRUE;
}

void Rift_MarkForeignSaveOverwrite(void)
{
    sSkipSavedChallengeSettings = TRUE;
}

bool32 Rift_ShouldPreserveChallengeSettings(void)
{
    return !sSkipSavedChallengeSettings;
}

void Rift_FinishPendingArrival(void)
{
#if IS_HNS
    if (sRiftArrivalBackup != NULL)
    {
        void *backup = sRiftArrivalBackup;

        sRiftArrivalBackup = NULL;
        Rift_FinishArrival(backup);
    }
#endif
    sSkipSavedChallengeSettings = FALSE;
    Rift_UpdateReturnFlags();
}

void Rift_UpdateReturnFlags(void)
{
#if IS_HNS
    const struct RiftRecord *record = Rift_GetRecord();
    bool32 secondGame = Rift_IsRecordValid(record) && Rift_IsSecondGame();
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sReturnFlags); i++)
    {
        bool32 anchorAvailable = secondGame
            && i < record->anchoredCount
            && !(record->anchoredReturned & (1 << i));

        if (anchorAvailable)
            FlagClear(sReturnFlags[i]);
        else
            FlagSet(sReturnFlags[i]);
    }
#endif
}

bool32 Rift_AreOtherBoxesSealed(void)
{
    const struct RiftRecord *record = Rift_GetRecord();

    return Rift_IsRecordValid(record) && Rift_IsSecondGame() && !record->boxesUnsealed;
}

void Rift_MarkSecondFinishForScript(void)
{
    u8 boxId, pos;

    Rift_MarkSecondFinish();
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        if (!Rift_IsBoxOwnedBy(boxId, RIFT_OTHER_GAME))
            continue;

        for (pos = 0; pos < IN_BOX_COUNT; pos++)
        {
            struct BoxPokemon *boxMon = &gPokemonStoragePtr->boxes[boxId][pos];
            u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);

            if (species == SPECIES_NONE
             || GetBoxMonData(boxMon, MON_DATA_IS_EGG)
             || !IsSpeciesEnabled(species))
                continue;

            GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_SEEN);
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
        }
    }
}

bool32 Rift_IsCurrentGameFinished(void)
{
    const struct RiftRecord *record = Rift_GetRecord();

    if (!Rift_IsRecordValid(record))
        return FALSE;
    return Rift_GetProgress(record, RIFT_THIS_GAME) >= RIFT_PROGRESS_FIRST_FINISH;
}

bool32 Rift_HasFusionBlocker(void)
{
    return (Rift_CheckCrossingBlockers() & RIFT_BLOCK_FUSION_STORAGE) != 0;
}

bool32 Rift_HasOverflowBlocker(void)
{
    return (Rift_CheckCrossingBlockers() & RIFT_BLOCK_OVERFLOW) != 0;
}

void Rift_ResetCrossingState(void)
{
    sAnchorItemsToBag = 0;
    sAnchorItemsLost = 0;
}

bool32 Rift_CanPickAnotherAnchor(void)
{
    return gSpecialVar_0x8005 < RIFT_ANCHOR_COUNT
        && CalculatePlayerPartyCount() > 1;
}

bool32 Rift_StoreSelectedAnchor(void)
{
    u8 slot = gSpecialVar_0x8004;
    u8 rank = gSpecialVar_0x8005;
    struct Pokemon *mon;
    enum Item heldItem;
    u16 quantityBefore = 0;

    if (slot >= PARTY_SIZE || rank >= RIFT_ANCHOR_COUNT || CalculatePlayerPartyCount() <= 1)
        return FALSE;

    mon = &gPlayerParty[slot];
    if (!GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES) || GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (heldItem != ITEM_NONE)
        quantityBefore = CountTotalItemQuantityInBag(heldItem);

    if (!Rift_StoreAnchor(rank, &mon->box))
        return FALSE;

    if (heldItem != ITEM_NONE)
    {
        if (CountTotalItemQuantityInBag(heldItem) > quantityBefore)
            sAnchorItemsToBag++;
        else
            sAnchorItemsLost++;
    }

    ZeroMonData(mon);
    CompactPartySlots();
    CalculatePlayerPartyCount();
    return TRUE;
}

bool32 Rift_PrepareCrossingForScript(void)
{
    struct RiftCrossingReport report;

    Rift_PrepareCrossing(&report);
    report.itemsToBag += sAnchorItemsToBag;
    report.itemsLost += sAnchorItemsLost;
    ConvertIntToDecimalStringN(gStringVar1, report.monsCrossing, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, report.itemsToBag, STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, report.itemsLost, STR_CONV_MODE_LEFT_ALIGN, 3);
    return report.itemsLost != 0;
}

// First finish: hand over to the credits from a clean callback (they end in a soft reset).
// Calling CB2_StartCreditsSequence directly from a script resets tasks and the heap while the overworld is still running.
void Rift_StartFirstFinishCredits(void)
{
    SetMainCallback2(CB2_StartCreditsSequence);
}
