#include "kernel/sched.h"

void add_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset |= (1U << priority); 
    }
}

void remove_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset &= (0U << priority); 
    }
}

uint32_t get_highest_priority()
{
    if (ready_bitset == 0) {
        return -1; 
    }

    return 31 - __builtin_clz(ready_bitset);
}