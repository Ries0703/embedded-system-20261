#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H
#include "ds1307.h"
#define AC_MAX_ALLOWED 10
#define AC_MAX_LOGS 100
typedef struct { uint32_t sequence; Time time; uint8_t code[5]; } AccessLog;
typedef struct {
    uint8_t allowed[AC_MAX_ALLOWED][5], allowed_count;
    AccessLog logs[AC_MAX_LOGS];
    uint16_t log_head, log_count;
    uint32_t next_sequence;
} AccessControl;
typedef enum { AC_OK, AC_DUPLICATE, AC_FULL, AC_NOT_FOUND, AC_INVALID } AccessResult;
typedef enum { ACCESS_REJECTED, ACCESS_GRANTED, ACCESS_CLOCK_ERROR } AccessDecision;
AccessDecision Access_Authorize(AccessControl *access,const uint8_t code[5],const Time *time);
int Access_ParseCode(const char *text,uint8_t code[5]);
int Access_IsAllowed(const AccessControl *access,const uint8_t code[5]);
AccessResult Access_Add(AccessControl *access,const uint8_t code[5]);
AccessResult Access_Delete(AccessControl *access,const uint8_t code[5]);
void Access_AppendLog(AccessControl *access,const Time *time,const uint8_t code[5]);
const AccessLog *Access_GetLog(const AccessControl *access,unsigned index);
void Access_ClearLogs(AccessControl *access);
#endif
