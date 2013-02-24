/*
 * common.h
 *
 *  Created on: Feb 4, 2013
 *      Author: mcarino
 */

#ifndef COMMON_H_
#define COMMON_H_

#define STK_SIZE 64
#define SCAN_STACK_SIZE 64
#define ANIMATE_STACK_SIZE 128
#define CONSOLE_STACK_SIZE 64

typedef struct
{
    uint32_t run[STK_SIZE];
    uint32_t scan[SCAN_STACK_SIZE];
    uint32_t animate[ANIMATE_STACK_SIZE];
    uint32_t console[CONSOLE_STACK_SIZE];
} stacks_t;

#define CREATE_TASK(func, id, stack, stack_size) \
        OSTaskCreateExt((void *)&(func), 0, &(stack)[(stack_size) - 1], \
        (id), (id), (stack), (stack_size), 0, 0)

#define BIT(x) (1 << (x))
enum
{
    FLAG_SUPERVISOR         = 0x1,
    FLAG_PENDING_STATE_CHG  = 0x2,
    FLAG_UART               = 0x4,
};

extern int32_t task_scan_hz;
extern int32_t task_animate_hz;
extern OS_FLAG_GRP *grp;

int32_t init_uart_setup(void);

#endif /* COMMON_H_ */
