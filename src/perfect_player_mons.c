#include "global.h"
#include "daycare.h"
#include "perfect_player_mons.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "rift_shared.h"

static bool32 ShouldSweepBox(u8 boxId)
{
    return Rift_IsBoxDepositable(boxId);
}

void MaxPlayerBoxMonStats(struct BoxPokemon *boxMon)
{
    u32 value;

    if (!P_PLAYER_MONS_PERFECT
     || !GetBoxMonData(boxMon, MON_DATA_SANITY_HAS_SPECIES))
        return;

    value = P_PLAYER_MONS_IV_VALUE;
    SetBoxMonData(boxMon, MON_DATA_HP_IV, &value);
    SetBoxMonData(boxMon, MON_DATA_ATK_IV, &value);
    SetBoxMonData(boxMon, MON_DATA_DEF_IV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPEED_IV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPATK_IV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPDEF_IV, &value);

    value = P_PLAYER_MONS_EV_VALUE;
    SetBoxMonData(boxMon, MON_DATA_HP_EV, &value);
    SetBoxMonData(boxMon, MON_DATA_ATK_EV, &value);
    SetBoxMonData(boxMon, MON_DATA_DEF_EV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPEED_EV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPATK_EV, &value);
    SetBoxMonData(boxMon, MON_DATA_SPDEF_EV, &value);
}

void MaxPlayerMonStats(struct Pokemon *mon)
{
    if (mon == NULL || !GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES))
        return;

    MaxPlayerBoxMonStats(&mon->box);
    CalculateMonStats(mon);
}

void MaxAllPlayerMonStats(void)
{
    u8 i, box, pos;

    for (i = 0; i < PARTY_SIZE; i++)
        MaxPlayerMonStats(&gPlayerParty[i]);

    for (box = 0; box < TOTAL_BOXES_COUNT; box++)
    {
        if (!ShouldSweepBox(box))
            continue;

        for (pos = 0; pos < IN_BOX_COUNT; pos++)
            MaxPlayerBoxMonStats(&gPokemonStoragePtr->boxes[box][pos]);
    }

    for (i = 0; i < DAYCARE_MON_COUNT; i++)
        MaxPlayerBoxMonStats(&gSaveBlock1Ptr->daycare.mons[i].mon);
}
