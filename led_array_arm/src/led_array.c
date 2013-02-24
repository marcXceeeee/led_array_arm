#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

#include <ucos_ii.h>
#include <string.h>
#include "common.h"

#include "console.h"
#include "scan.h"

stacks_t stack __attribute__ ((aligned(16)));
OS_FLAG_GRP *grp;

int32_t task_scan_hz = 1;
int32_t task_animate_hz = 15;

static void init_pin_setup(void)
{
    port_t tmp = { .all = 0xFFFFFFFF };

    tmp.bits.rs9 = 0;
    tmp.bits.rsvd13_31 = 0;

    LPC_GPIO2->FIODIR = tmp.all;
}

static void init(void)
{
    memset(&stack, 0x11, sizeof(stack));
    OS_CPU_SysTickInit(SystemCoreClock / 1000);
    init_pin_setup();
    init_scan();
}

int32_t init_uart_setup(void)
{
    /*                       PCLK
     * UART_baud = --------------------------
     *             16 x (256 x UnDLM + UnDLL)
     *
     * PCLK = 74.25 MHz
     */

    uint32_t baud = 115200;
    uint32_t pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x3;
    uint32_t pclk;
    uint32_t dll;

    switch (pclkdiv)
    {
        case 0:
            pclk = SystemCoreClock / 4;
            break;
        case 1:
            pclk = SystemCoreClock;
            break;
        case 2:
            pclk = SystemCoreClock / 2;
            break;
        case 3:
            pclk = SystemCoreClock / 8;
            break;
    }

    dll = (pclk / 16) / baud;

    //LPC_SC->PCONP |= (1 << 3);

    LPC_PINCON->PINSEL0 &= ~0x000000F0;
    LPC_PINCON->PINSEL0 |= (1 << 4) | (1 << 6); /* tx enable, rx enable */

    LPC_PINCON->PINMODE0 |= (2 << 6);

    LPC_PINCON->PINMODE_OD0 |= (1 << 2); /* tx open drain */

    //LPC_SC->PCLKSEL0 |= (0 << 6); /* CLK / 4 */
    LPC_UART0->LCR |= (1 << 7);
    LPC_UART0->DLL = dll & 0xFF;
    LPC_UART0->DLM = (dll >> 8) & 0xFF;
    LPC_UART0->LCR &= ~(1 << 7);

    LPC_UART0->LCR |= (0x3 << 0) | (0x0 << 2) | (0x0 << 3); /* 8-bit char, 1 stop bit, no parity */

    /* Reset and enable FIFOs */
    LPC_UART0->FCR = 0x7;

    //LPC_UART0->IER |= 0x1;
    LPC_UART0->IER &= ~0x1;
    //NVIC_EnableIRQ(UART0_IRQn);

    return 0;
}

int32_t run(void)
{
    uint8_t status;

    init();

    CREATE_TASK(task_console, 4, stack.console, CONSOLE_STACK_SIZE);
    CREATE_TASK(task_animate, 3, stack.animate, ANIMATE_STACK_SIZE);
    CREATE_TASK(task_scan, 2, stack.scan, SCAN_STACK_SIZE);

    grp = OSFlagCreate(0xFFFFFFFF, &status);
    if (!grp)
        for (;;);

    for (;;)
        OSFlagPend(grp, FLAG_SUPERVISOR, OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                   0, &status);

    return 0;
}
