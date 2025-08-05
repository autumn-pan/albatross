#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

// Reference: ARM Cortex-m0plus docs
// SysTick Register addresses should be consistent between m7 and m0plus
// In future versions, clock may be arch specific

#define SYSTICK_CTRL   (*(volatile uint32_t *)0xE000E010)
#define SYSTICK_LOAD   (*(volatile uint32_t *)0xE000E014)
#define SYSTICK_VAL    (*(volatile uint32_t *)0xE000E018)
#define SYSTICK_CALIB  (*(volatile uint32_t *)0xE000E01C)

#define SYSTICK_ENABLE     (1 << 0) // Bit 0
#define SYSTICK_TICKINT    (1 << 1) // Bit 1
#define SYSTICK_CLKSOURCE  (1 << 2) // Bit 2

// Global tick counter
volatile uint64_t ticks = 0;

// To be called on startup-- enables SysTick
void init_systick(uint32_t ticks);

// To be called every tick
void update_systick();

// Returns the global tick count
uint64_t get_ticks();

#endif