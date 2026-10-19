#include "global.h"
#include "config/rift_game.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "rift_shared.h"
#include "string_util.h"
#include "constants/party_menu.h"

static u16 sAnchorItemsToBag;
static u16 sAnchorItemsLost;

bool32 IsRiftSecondGame(void)
{
    return Rift_IsSecondGame();
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
