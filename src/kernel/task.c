#include "kernel/task.h"
#include "util/alloc.h"
#include <stdint.h>
#include <stddef.h>
#include "kernel/sched.h"

TaskControlBlock_t* init_tbc(void (*task_func)(void), uint32_t priority)
{
    TaskControlBlock_t* tcb = (TaskControlBlock_t*)(alloc(sizeof(TaskControlBlock_t)));

    if(!tcb)
        return NULL;

    tcb->task_func = task_func;
    tcb->priority = priority;
    tcb->node = create_node(tcb);

    // Init stack
    uint32_t* stack = (uint32_t*)alloc(STACK_SIZE * sizeof(uint32_t));
    if (!stack)
    {
        free(tcb); 
        return NULL;
    }

    // Clear stack
    memset(stack, 0, STACK_SIZE * sizeof(uint32_t));

    tcb->stack_ptr = init_stack(task_func, stack);

    // If init_stack fails, free everything
    if (!tcb->stack_ptr)
    {
        free(stack);
        free(tcb);
        return NULL;
    }

    tcb->stack_base = stack;

    tcb->sleep_controller = init_sleep_controller();
    
    return tcb;
}

uint32_t* init_stack(void (*task_func)(void), uint32_t* stack)
{
    uint32_t* sp = stack + STACK_SIZE;

    sp -= 8; // Make space for 8 Registers

    sp[0] = 0x00000000; // R0
    sp[1] = 0x01010101; // R1
    sp[2] = 0x02020202; // R2
    sp[3] = 0x03030303; // R3
    sp[4] = 0x12121212; // R12
    sp[5] = 0xFFFFFFFD; // LR
    sp[6] = (uint32_t)task_func; // PC
    sp[7] = 0x01000000; // PSR

    sp -= 8; // Make space for 8 GP Registers
    for (int i = 0; i < 8; i++)
    {
        sp[i + 8] = 0x00000000; // R4-R11
    }

    return sp;
}
SleepController_t* init_sleep_controller()
{
    SleepController_t* sleep_controller = (SleepController_t*)(alloc(sizeof(SleepController_t)));
    sleep_controller->asleep = false;
    return sleep_controller;
}


bool task_is_awake(TaskControlBlock_t* tcb)
{
    SleepController_t* controller = tcb->sleep_controller;

    if(controller->remaining_time <= 0)
    {
        return true;
    }

    return false;
}

void wake_task(TaskControlBlock_t* tcb)
{
    // Do nothing if task is already awake
    if(tcb->state != SLEEPING)
    {
        return;
    }

    SleepController_t* controller = tcb->sleep_controller;

    // Update sleep controller information
    controller->asleep = false;

    // Move TBC to ready queue
    tcb->state = READY;
    list_append(ready_queue[tcb->priority], tcb->node);

    if(ready_queue[tcb->priority]->size == 1)
    {
        add_priority(tcb->priority);
    }

    // Remove TBC from sleeping
    uint8_t index = find_node_index(sleeping, tcb->node);
    list_pop(sleeping, index);
}
