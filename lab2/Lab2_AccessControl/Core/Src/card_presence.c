#include "card_presence.h"
#include <string.h>
CardEvent CardPresence_Update(CardPresence *state,const uint8_t *code) {
    if (code) {
        CardEvent event=(!state->present || memcmp(state->code,code,5)) ? CARD_PRESENTED : CARD_UNCHANGED;
        memcpy(state->code,code,5);state->present=1;state->misses=0;
        return event;
    }
    if (state->present && ++state->misses >= 3) {
        state->present=0;state->misses=0;return CARD_REMOVED;
    }
    return CARD_UNCHANGED;
}
