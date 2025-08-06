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

#endif