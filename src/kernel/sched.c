#include "kernel/sched.h"
#include "util/list.h"

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

TBC* next_task()
{
    return ready_queue[get_highest_priority()]->head->value;
}

void update_scheduler()
{
    // Before anything, check if any sleeping tasks are ready to wake up and manage them
    update_sleep_handlers();

    uint8_t highest_priority = get_highest_priority();
    // Check if there are any ready tasks
    if(highest_priority == -1)
    {
        // If there is no running task either, do nothing
        if(!running)
        {
            __asm__ volatile("wfi");
        }    

        // In either case, return early
        return;
    }

    // If there is at least one ready task, this code will execute
    TBC* ready_task = ready_queue[highest_priority]->head->value;

    // If the ready task is the last of its priority, write that the priority is now empty in the bitset
    // This computes in O(n) time but can lead to signicant errors if the bitset is not correctly handled. The alternative is a safe, albeit O(n) algorithm.
    if(ready_queue[highest_priority]->size == 1)
    {
        remove_priority(highest_priority);
    }

    ready_task->state = RUNNING;
    list_pop_head(ready_queue[highest_priority]);

    // If there is currently a running task, move it to READY queue instead
    if(running)
    {
        running->state = READY; // Running TBC defaults to ready
        list_append(ready_queue[running->priority], running->node);

        if(ready_queue[running->priority]->size == 1)
        {
            add_priority(running->priority);
        }
    }

    // Mark the ready task as the current running task
    running = ready_task;
}

// Sleeping list is currently an unordered linked list
// Time complexity of O(n) is very inneficient and should be replace by a heap eventually
void update_sleep_handlers()
{
    ListNode* current = sleeping->head;

    while(1)
    {
        // If there is no task to check for whatever reason, return
        if(!current)
            return;
        // Update remaining time
        ((TBC*)current->value)->sleep_controller->remaining_time--;

        // If a task is ready to wake up, awake it
        if(task_is_awake(current->value))
        {
            wake_task(current->value);
        }

        // Get next task
        current = current->next;
    }
}

// Add a task to the Scheduler
void add_task(TBC* tbc)
{
    list_append(ready_queue[tbc->priority], tbc->node);

    if(ready_queue[tbc->priority]->size == 1)
    {
        add_priority(tbc->priority);
    }
}