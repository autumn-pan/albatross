#ifndef SCHED_H
#define SCHED_H
#define MAX_PRIORITIES 32
#include "../util/list.h"
#include "task.h"
#include <stdint.h>

uint32_t ready_bitset;
List* ready_queue[MAX_PRIORITIES];
List* sleeping;
TBC* running;

// Bitset operations
void add_priority(uint32_t priority);

void remove_priority(uint32_t priority);

uint32_t get_highest_priority();

// Updates the state of a task, as well as associated lists and queues
void set_state_queue(TBC* tbc, enum TASK_STATE queue);

// Used internally to select a new task to be run
void switch_task(TBC* next_task, enum TASK_STATE new_queue);

// Yields the running task's turn and sends it to the end of the READY queue, selecting a new task to take its place
void yield();
// Blocks the running task from running for a set amount of time before sending it back to the READY queue
void sleep(uint32_t time);

#endif