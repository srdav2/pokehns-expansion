#ifndef GUARD_RIFT_LEFT_H
#define GUARD_RIFT_LEFT_H

bool32 Rift_BeginArrival(void);
void Rift_MarkForeignSaveOverwrite(void);
bool32 Rift_ShouldPreserveChallengeSettings(void);
void Rift_FinishPendingArrival(void);
void Rift_UpdateReturnFlags(void);
bool32 Rift_AreOtherBoxesSealed(void);
void Rift_MarkSecondFinishForScript(void);

void Rift_StartFirstFinishCredits(void);

#endif // GUARD_RIFT_LEFT_H
