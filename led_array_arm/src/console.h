#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "common.h"

typedef enum
{
    CONS_ENABLE,
    CONS_DISABLE,
    CONS_SET_TASK_FREQ
} cons_cmd_t;

typedef struct
{
    cons_cmd_t cmd;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
} console_cmd_t;

void task_console(void);

#endif /* __CONSOLE_H__ */
