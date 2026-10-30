#include "access_control.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
int main(void) {
    static AccessControl access;
    uint8_t card[5],bad[5]={1,2,3,4,0};
    assert(Access_ParseCode("B3C08F34C8",card));
    assert(card[0]==0xB3 && card[4]==0xC8);
    assert(Access_ParseCode("b3c08f34c8",card));
    assert(!Access_ParseCode("B3C08F34C9",bad));
    assert(!Access_ParseCode("B3C08F34C8X",bad));
    assert(!Access_ParseCode("B3C08F34",bad));
    assert(!Access_ParseCode("ZZC08F34C8",bad));
    assert(!Access_IsAllowed(&access,card));
    Time current={.sec=20,.min=52,.hour=14,.weekday=6,.day=30,.month=10,.year=26};
    assert(Access_Authorize(&access,card,&current)==ACCESS_REJECTED && !access.log_count);
    assert(Access_Add(&access,card)==AC_OK);
    assert(Access_Authorize(&access,card,NULL)==ACCESS_CLOCK_ERROR && !access.log_count);
    assert(Access_Authorize(&access,card,&current)==ACCESS_GRANTED && access.log_count==1);
    Access_ClearLogs(&access);
    assert(Access_Add(&access,card)==AC_DUPLICATE && access.allowed_count==1);
    assert(Access_IsAllowed(&access,card));
    assert(Access_Delete(&access,card)==AC_OK && !Access_IsAllowed(&access,card));
    assert(Access_Delete(&access,card)==AC_NOT_FOUND);
    for(unsigned i=0;i<AC_MAX_ALLOWED;i++) {
        uint8_t code[5]={(uint8_t)i,0,0,0,(uint8_t)i};
        assert(Access_Add(&access,code)==AC_OK);
    }
    assert(Access_Add(&access,card)==AC_FULL && access.allowed_count==10);
    uint8_t invalid[5]={1,2,3,4,0};
    assert(Access_Add(&access,invalid)==AC_INVALID && access.allowed_count==10);
    Time time={.sec=20,.min=52,.hour=14,.weekday=6,.day=30,.month=10,.year=26};
    for(unsigned i=0;i<101;i++) Access_AppendLog(&access,&time,card);
    assert(access.log_count==100);
    assert(Access_GetLog(&access,0)->sequence==2);
    assert(Access_GetLog(&access,99)->sequence==101);
    assert(Access_GetLog(&access,99)->time.hour==14);
    assert(!memcmp(Access_GetLog(&access,99)->code,card,5));
    assert(Access_GetLog(&access,100)==NULL);
    Access_ClearLogs(&access);
    assert(!access.log_count && Access_GetLog(&access,0)==NULL);
    assert(access.allowed_count==10);
    Access_AppendLog(&access,&time,card);
    assert(Access_GetLog(&access,0)->sequence==1);
    puts("PASS: whitelist, duplicate/full/invalid/delete, hex/BCC parser, 101-entry RAM ring and clear");
}
