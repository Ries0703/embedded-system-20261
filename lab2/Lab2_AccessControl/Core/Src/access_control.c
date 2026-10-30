#include "access_control.h"
#include <string.h>
static int valid_code(const uint8_t code[5]) {
    return code && (uint8_t)(code[0]^code[1]^code[2]^code[3])==code[4];
}
static int hex(char c) {
    if(c>='0' && c<='9') return c-'0';
    if(c>='A' && c<='F') return c-'A'+10;
    if(c>='a' && c<='f') return c-'a'+10;
    return -1;
}
int Access_ParseCode(const char *text,uint8_t code[5]) {
    if(!text || !code || strlen(text)!=10) return 0;
    uint8_t result[5];
    for(unsigned i=0;i<5;i++) {
        int hi=hex(text[i*2]),lo=hex(text[i*2+1]);
        if(hi<0 || lo<0) return 0;
        result[i]=(uint8_t)((hi<<4)|lo);
    }
    if(!valid_code(result)) return 0;
    memcpy(code,result,5);return 1;
}
int Access_IsAllowed(const AccessControl *access,const uint8_t code[5]) {
    if(!access || !valid_code(code)) return 0;
    for(unsigned i=0;i<access->allowed_count;i++) if(!memcmp(access->allowed[i],code,5)) return 1;
    return 0;
}
AccessResult Access_Add(AccessControl *access,const uint8_t code[5]) {
    if(!access || !valid_code(code)) return AC_INVALID;
    if(Access_IsAllowed(access,code)) return AC_DUPLICATE;
    if(access->allowed_count==AC_MAX_ALLOWED) return AC_FULL;
    memcpy(access->allowed[access->allowed_count++],code,5);return AC_OK;
}
AccessResult Access_Delete(AccessControl *access,const uint8_t code[5]) {
    if(!access || !valid_code(code)) return AC_INVALID;
    for(unsigned i=0;i<access->allowed_count;i++) {
        if(!memcmp(access->allowed[i],code,5)) {
            --access->allowed_count;
            if(i<access->allowed_count) memmove(access->allowed[i],access->allowed[i+1],(access->allowed_count-i)*5);
            return AC_OK;
        }
    }
    return AC_NOT_FOUND;
}
void Access_AppendLog(AccessControl *access,const Time *time,const uint8_t code[5]) {
    unsigned index;
    if(access->log_count<AC_MAX_LOGS) {
        index=(access->log_head+access->log_count)%AC_MAX_LOGS;access->log_count++;
    } else {
        index=access->log_head;access->log_head=(access->log_head+1)%AC_MAX_LOGS;
    }
    AccessLog *log=&access->logs[index];
    log->sequence=++access->next_sequence;log->time=*time;memcpy(log->code,code,5);
}
const AccessLog *Access_GetLog(const AccessControl *access,unsigned index) {
    if(!access || index>=access->log_count) return NULL;
    return &access->logs[(access->log_head+index)%AC_MAX_LOGS];
}
void Access_ClearLogs(AccessControl *access) {
    access->log_head=0;access->log_count=0;access->next_sequence=0;
}
AccessDecision Access_Authorize(AccessControl *access,const uint8_t code[5],const Time *time) {
    if(!Access_IsAllowed(access,code)) return ACCESS_REJECTED;
    if(!time) return ACCESS_CLOCK_ERROR;
    Access_AppendLog(access,time,code);
    return ACCESS_GRANTED;
}
