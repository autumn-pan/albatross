#ifndef SCHED_H

#define SCHED_H
#define MAX_PRIORITIES 32

#define SCB_ICSR (*(volatile uint32_t *)0xE000ED04)
#define SCB_ICSR_PENDSVSET_Msk (1UL << 28)

#include <stddef.h>
#include "../util/list.h"
#include "task.h"
#include <stdint.h>


uint32_t ready_bitset;
List* ready_queue[MAX_PRIORITIES];
List* sleeping;
TBC* running;

TBC* current_context;

void *current_tcb;
void *next_tcb;

bool is_ready_task;
bool is_running_task;

// Bitset operations
void add_priority(uint32_t priority);

void remove_priority(uint32_t priority);

uint32_t get_highest_priority();

// Yields the running task's turn and sends it to the end of the READY queue, selecting a new task to take its place
void yield();
// Blocks the running task from running for a set amount of time before sending it back to the READY queue
void sleep(uint32_t time);

void switch_context();
TBC* next_task();
void update_scheduler();

#endif