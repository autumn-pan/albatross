#include "kernel/sched.h"
#include "util/list.h"

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

    return __builtin_clz(ready_bitset);
}

TBC* scheduler_next_task()
{
    return ready_queue[get_highest_priority()]->head;
}

void set_state_queue(TBC* tbc, enum TASK_STATE queue)
{
    uint8_t index = find_node_index(tbc->state, tbc);
    // Remove TBC from its current queue
    list_pop(tbc->state, index);

    // Update ready bitset if needed
    if(tbc->state == READY)
    {
        if(ready_queue[tbc->priority]->size == 0)
        {
            remove_priority(tbc->priority);
        }
    }
    tbc->state = queue;

    if(queue == READY)
    {
        list_append(ready_queue[tbc->priority], tbc);
        if(ready_queue[tbc->priority]->size == 1)
        {
            add_priority(tbc->priority);
        }
        return;
    }

    list_append(queue, tbc);
}

