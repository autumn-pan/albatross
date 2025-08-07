#include "kernel/sched.h"
#include "util/list.h"
#include "kernel/clock.h"

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

// Change the state of a task
// This switches its queue, updates the priority bitset, and changes its internal state
// This does not include handling for sleep or other utilities

void update_ready_bitset(TBC* tbc)
{
    if(tbc->state == READY)
    {
        if(ready_queue[tbc->priority]->size == 0)
        {
            remove_priority(tbc->priority);
        }
    }
}
void set_state_queue(TBC* tbc, enum TASK_STATE queue)
{
    uint8_t index = find_node_index(tbc->state, tbc);
    // Remove TBC from its current queue
    list_pop(tbc->state, index);

    // Update ready bitset if needed
    update_ready_bitset(tbc);

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

void sleep(uint32_t time)
{
    // Set up sleep controller
    running->sleep_controller->init_time = get_ticks();
    running->sleep_controller->sleep_time = time;
    running->sleep_controller->remaining_time = time;

    // Mark the running ask as asleep
    set_state_queue(running, SLEEPING);

    // Provisional solution; will eventually use linked lists to determine next task in advance
    TBC* next_task = scheduler_next_task();
    switch_context(running, next_task);
    // If necessary, update ready bitset
    update_ready_bitset(next_task);
    running = next_task;
}