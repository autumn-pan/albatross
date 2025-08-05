#include "kernel/clock.h"

void init_systick(uint32_t ticks) 
{
    SYSTICK_LOAD = ticks - 1; // Set reload value
    SYSTICK_VAL = 0;          // Clear current value
    SYSTICK_CTRL = SYSTICK_ENABLE | SYSTICK_TICKINT | SYSTICK_CLKSOURCE; // Enable SysTick
}

void update_systick() 
{
    ticks++;
}

uint64_t get_ticks()
{
    return ticks;
}