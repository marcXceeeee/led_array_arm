/*
===============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

#include <ucos_ii.h>
#include <string.h>
#include "common.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

extern int run(void);
extern stacks_t stack;
int main(void)
{

    OSInit();
    CREATE_TASK(run, 1, stack.run, STK_SIZE);
    OSStart();
    for (;;);
    return 0;
}
