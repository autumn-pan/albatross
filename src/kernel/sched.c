#include "kernel/sched.h"
#include "util/list.h"

uint32_t ready_bitset;
List* ready_queue[MAX_PRIORITIES];
List* sleeping;
TBC* running;

TBC* current_context;

void *current_tcb;
void *next_tcb;

bool is_ready_task;
bool is_running_task;

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

uint32_t count_leading_zeros(uint32_t n)
{
    if(n == 0)
        return 32;
    uint32_t count = 0;

    while(1)
    {
        if(n & 0x80000000)
            break;
        count++;
        n <<= 1;
    }

    return count;
}

// FInd the highest priority ready task
int8_t get_highest_priority()
{
    if (ready_bitset == 0) {
        return -1; 
    }

    return count_leading_zeros(ready_bitset);
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

    int8_t highest_priority = get_highest_priority();
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
    next_tcb = ready_task;
    
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
    current_tcb = ready_task;
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

void sleep(uint32_t time)
{
    if(!running)
    {
        return;
    }

    SleepController* controller = running->sleep_controller;

    controller->asleep = true;
    controller->init_time = ticks;
    controller->sleep_time = time;
    controller->remaining_time = time;
    running->state = SLEEPING;

    list_push(sleeping, running->node);
    running = NULL;
}

void yield()
{
    list_append(ready_queue[running->priority], running->node);
    running->state = READY;

    if(ready_queue[running->priority]->size == 1)
    {
        add_priority(running->priority);
    }
    running = NULL;


    __asm__ volatile("wfi");
}
