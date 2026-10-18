#ifndef GUARD_PERFECT_PLAYER_MONS_H
#define GUARD_PERFECT_PLAYER_MONS_H

struct BoxPokemon;
struct Pokemon;

void MaxPlayerBoxMonStats(struct BoxPokemon *boxMon);
void MaxPlayerMonStats(struct Pokemon *mon);
void MaxAllPlayerMonStats(void);

#endif // GUARD_PERFECT_PLAYER_MONS_H
