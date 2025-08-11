#include "kernel/sched.h"
#include "util/list.h"
#include "kernel/clock.h"

// Bitset functions-- used to configure priority bitset
// Set any bit to 1
void add_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset |= (1U << priority); 
    }
}
// Set any bit to 0
void remove_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset &= (0U << priority); 
    }
}

// FInd the highest priority ready task
uint32_t get_highest_priority()
{
    if (ready_bitset == 0) {
        return -1; 
    }

    return __builtin_clz(ready_bitset);
}



// Triggers PendSV
void switch_context()
{
    SCB_ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

