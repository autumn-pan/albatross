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


// Get the next ready task
TBC* scheduler_next_task()
{
    uint32_t highest_priority = get_highest_priority();
    if(highest_priority == -1)
        return NULL;

    // The corresponding list
    return ready_queue[highest_priority]->head;
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


void switch_task(TBC* next_task, enum TASK_STATE new_queue)
{
    set_state_queue(running, new_queue);

    // Save and change contexts
    switch_context(running, next_task);

    // If necessary, update ready bitset
    update_ready_bitset(next_task);
    running = next_task;
    current_context = next_task;
}

void yield()
{
    if(get_highest_priority() == -1)
        return;

    switch_task(scheduler_next_task, READY);
}

void sleep(uint32_t time)
{
    if(get_highest_priority() == -1)
    {
        is_running_task = false;
        running = NULL;
        return;
    }

    // Set up sleep controller
    running->sleep_controller->init_time = get_ticks();
    running->sleep_controller->sleep_time = time;
    running->sleep_controller->remaining_time = time;

    switch_task(scheduler_next_task(), SLEEPING);
}

void add_task(uint32_t priority, void (*task_func)(void))
{
    TBC* tbc = init_tbc(task_func, priority);
    
    if(ready_queue[get_highest_priority()] == -1)
    {
        list_append(ready_queue[tbc->priority], tbc);
        if(ready_queue[tbc->priority]->size == 1)
        {
            add_priority(tbc->priority);
        }
        return;
    }
}

void scheduler_loop()
{
    while(1)
    {
        if(!is_running_task)
        {
            if(get_highest_priority() != -1)
            {
                is_ready_task = true;
                switch_task(current_context, scheduler_next_task());       
            }
            else
            {
                __asm volatile("wfi");
            }
        }
    }
}