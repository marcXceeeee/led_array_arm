#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include <NXP/crp.h>
#include <ucos_ii.h>
#include <string.h>
#include "common.h"

#include "console.h"

static int32_t console_printstr(const char *str)
{
    if (str)
    {
        char c;
        while ((c = *str++) != '\0')
        {
            if (c == '\n')
            {
                LPC_UART0->THR = '\r';
                while (!(LPC_UART0->LSR & (1 << 5)))
                    ;
            }

            LPC_UART0->THR = c;
            while (!(LPC_UART0->LSR & (1 << 5)))
                ;
        }
    }

    return 0;
}

#if (0)
static int32_t console_getstr(char *str, int32_t len)
{
    return -1;
}
#endif

static uint32_t console_touint32(const char *str)
{
    uint32_t val = 0;
    int32_t mul = 1;
    const char *p = str;

    if (*p == '\0')
    {
        return 0;
    }
    else
    {
        while (*p != '\0')
        {
            p++;
        }
        p--;
    }

    do
    {
        // bla
        val += (mul * (*p - '0'));
        mul *= 10;
    }
    while (p-- != str);

    return val;
}

static char tmpstr[64];
static char last_ok_cmd[64];
static int32_t console_getcmd(console_cmd_t *cmd)
{
    int32_t status = -1;
    int32_t idx = 0;
    char c = '\0';
    int32_t done = 0;
    int32_t escape = 0;

    /* Read string from staged UART buffer */
    memset(tmpstr, 0, sizeof(tmpstr));
    do
    {
        while (!(LPC_UART0->LSR & 0x1))
            ;
        c = (char) LPC_UART0->RBR;

        if (escape)
        {
            if (escape == 1)
            {
                if (c == '[')
                {
                    escape = 2;
                }
                else
                {
                    escape = 0;
                }
            }
            else
            {
                if (c == 'A')
                {
                    while (idx != 0)
                    {
                        LPC_UART0->THR = '\b';
                        idx--;
                    }
                    memcpy(tmpstr, last_ok_cmd, sizeof(last_ok_cmd));
                    idx = strlen(last_ok_cmd);
                    console_printstr(last_ok_cmd);
                    escape = 0;
                }
            }
        }
        else
        {
            switch (c)
            {
                case '\e':
                    escape = 1;
                    break;
                case '\r':
                case '\n':
                    tmpstr[idx] = '\0';
                    done = 1;
                    break;
                case '\b':
                case 127:
                    if (idx > 0)
                    {
                        idx--;
                        tmpstr[idx] = '\0';
                        LPC_UART0->THR = '\b';
                    }
                    break;
                default:
                    LPC_UART0->THR = c;
                    if (idx < 32)
                    {
                        tmpstr[idx++] = c;
                    }
                    break;
            }
        }
    }
    while (!done);

    LPC_UART0->THR = '\r';
    LPC_UART0->THR = '\n';

    if (idx > 0)
    {
        char *tok = strtok(tmpstr, " ");
        if (strcmp(tok, "enable") == 0)
        {
            if (cmd)
            {
                cmd->cmd = CONS_ENABLE;
                status = 0;
            }
        }
        else if (strcmp(tok, "disable") == 0)
        {
            if (cmd)
            {
                cmd->cmd = CONS_DISABLE;
                status = 0;
            }
        }
        else if (strncmp(tok, "set-task-freq", 13) == 0)
        {
            if (cmd)
            {
                cmd->cmd = CONS_SET_TASK_FREQ;
                tok = strtok(NULL, " ");
                if (tok)
                {
                    cmd->param1 = console_touint32(tok);
                    tok = strtok(NULL, " ");
                    if (tok)
                    {
                        cmd->param2 = console_touint32(tok);
                        status = 0;
                    }
                }
            }
        }

        if (status == 0)
        {
            memcpy(last_ok_cmd, tmpstr, sizeof(tmpstr));
        }
    }

    return status;
}

void task_console(void)
{
    //uint8_t os_status;
    int32_t status;
    init_uart_setup();

    console_printstr("Marc's LED Array, v0.1\n");
    for (;;)
    {
        console_cmd_t cmd;

        console_printstr("prompt> ");

        //OSFlagPend(grp, FLAG_UART, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME, 0, &os_status);

        status = console_getcmd(&cmd);

        if (!status)
        {
            switch (cmd.cmd)
            {
                case CONS_ENABLE:
                {
                    task_animate_hz = 15;
                    OSTimeDlyResume(3);
                    break;
                }
                case CONS_DISABLE:
                {
                    task_animate_hz = 0xFFFFFFFF;
                    break;
                }
                case CONS_SET_TASK_FREQ:
                {
                    switch (cmd.param1)
                    {
                        case 2:
                        {
                            task_scan_hz = cmd.param2;
                            break;
                        }
                        case 3:
                        {
                            task_animate_hz = cmd.param2;
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }

        }
    }
}
