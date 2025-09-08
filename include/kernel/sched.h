#ifndef SCHED_H

#define SCHED_H
#define MAX_PRIORITIES 32

#define SCB_ICSR (*(volatile uint32_t *)0xE000ED04)
#define SCB_ICSR_PENDSVSET_Msk (1UL << 28)

#include <stddef.h>
#include "../util/list.h"
#include "task.h"
#include <stdint.h>
#include "clock.h"

extern uint32_t ready_bitset;
extern List_t* ready_queue[MAX_PRIORITIES];
extern List_t* sleeping;
extern TaskControlBlock_t* running;

extern TaskControlBlock_t* current_context;

extern void *current_tcb;
extern void *next_tcb;

extern bool is_ready_task;
extern bool is_running_task;

// Bitset operations
void add_priority(uint32_t priority);

void remove_priority(uint32_t priority);

int8_t get_highest_priority();

// Yields the running task's turn and sends it to the end of the READY queue, selecting a new task to take its place
void yield();
// Blocks the running task from running for a set amount of time before sending it back to the READY queue
void sleep(uint32_t time);

void switch_context();
TaskControlBlock_t* next_task();
void update_scheduler();
void update_sleep_handlers();
void add_task(TaskControlBlock_t* tcb);

#endif