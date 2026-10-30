#ifndef CARD_PRESENCE_H
#define CARD_PRESENCE_H
#include <stdint.h>
typedef struct { uint8_t code[5], present, misses; } CardPresence;
typedef enum { CARD_UNCHANGED, CARD_PRESENTED, CARD_REMOVED } CardEvent;
CardEvent CardPresence_Update(CardPresence *state, const uint8_t *code);
#endif
