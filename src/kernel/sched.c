#include "kernel/sched.h"
#include "util/list.h"

uint32_t ready_bitset = 0;
List_t* ready_queue[MAX_PRIORITIES];
List_t* sleeping;
TaskControlBlock_t* running;

TaskControlBlock_t* current_context;

void *current_tcb;
void *next_tcb;

bool is_ready_task;
bool is_running_task;

// Bitset functions-- used to configure priority bitset
// Set any bit to 1

uint8_t __clz(uint32_t x)
{
    if (x == 0) return 32;
    int n = 0;
    if (x <= 0x0000FFFF) { n += 16; x <<= 16; }
    if (x <= 0x00FFFFFF) { n += 8; x <<= 8; }
    if (x <= 0x0FFFFFFF) { n += 4; x <<= 4; }
    if (x <= 0x3FFFFFFF) { n += 2; x <<= 2; }
    if (x <= 0x7FFFFFFF) { n += 1; }
    return n;
}

void add_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset |= (1U << (31 - priority)); 
    }
}

// Set any bit to 0
void remove_priority(uint32_t priority) {
    if (priority < 32) {
        ready_bitset &= ~(1U << (31 - priority)); 
    }
}

// FInd the highest priority ready task
int8_t get_highest_priority()
{
    if (ready_bitset == 0) {
        return -1; 
    }

    return __clz(ready_bitset);
}

// Triggers PendSV
void switch_context()
{
    SCB_ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void init_scheduler()
{
    for(int i = 0; i < MAX_PRIORITIES; i++)
    {
        ready_queue[i] = (List_t*)(malloc(sizeof(List_t)));
        init_list(ready_queue[i]);
    }
}

void update_scheduler()
{
    // Before anything, check if any sleeping tasks are ready to wake up and manage them
    int8_t highest_priority = get_highest_priority();

    if(highest_priority == -1)
    {
        return;
    }

    List_t* list = ready_queue[highest_priority];

    TaskControlBlock_t* ready_task = (TaskControlBlock_t*)list->head->value;
    next_tcb = ready_task;

    ready_task->state = RUNNING;

    list_pop_head(list);
    
    if(!list->head)
        remove_priority(highest_priority);



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


    running->task_func();
    current_tcb = ready_task;
}

// Sleeping list is currently an unordered linked list
// Time complexity of O(n) is very inneficient and should be replace by a heap eventually
void update_sleep_handlers()
{
    ListNode_t* current = sleeping->head;

    while(current)
    {
        // Update remaining time
        ((TaskControlBlock_t*)current->value)->sleep_controller->remaining_time--;

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
void add_task(TaskControlBlock_t* tcb)
{
    list_append(ready_queue[tcb->priority], tcb->node);


    add_priority(tcb->priority);
}

void sleep(uint32_t time)
{
    if(!running)
    {
        return;
    }

    SleepController_t* controller = running->sleep_controller;

    controller->asleep = true;
    controller->init_time = 0;
    controller->sleep_time = time;
    controller->remaining_time = time;
    running->state = SLEEPING;

    list_push(sleeping, running->node);
    running = NULL;
}

void yield()
{
    list_append(ready_queue[running->priority], running->node);
    add_priority(running->priority);

    running = NULL;
    // wfi
}
