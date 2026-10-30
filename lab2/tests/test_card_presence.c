#include "card_presence.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
int main(void) {
    CardPresence state={0};
    uint8_t a[5]={1,2,3,4,4},b[5]={5,6,7,8,12};
    assert(CardPresence_Update(&state,NULL)==CARD_UNCHANGED);
    assert(CardPresence_Update(&state,a)==CARD_PRESENTED && state.present);
    for (int i=0;i<50;i++) assert(CardPresence_Update(&state,a)==CARD_UNCHANGED);
    assert(CardPresence_Update(&state,NULL)==CARD_UNCHANGED && state.present);
    assert(CardPresence_Update(&state,NULL)==CARD_UNCHANGED && state.present);
    assert(CardPresence_Update(&state,a)==CARD_UNCHANGED && state.misses==0);
    assert(CardPresence_Update(&state,b)==CARD_PRESENTED && state.code[0]==5);
    CardPresence_Update(&state,NULL);CardPresence_Update(&state,NULL);
    assert(CardPresence_Update(&state,NULL)==CARD_REMOVED && !state.present);
    assert(CardPresence_Update(&state,b)==CARD_PRESENTED);
    puts("PASS: held card, transient misses, card replacement, removal and re-presentation");
}
