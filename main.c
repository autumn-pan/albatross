#include <stdio.h>
#include <stdint.h>
#define MAX_TASKS 128

enum TASK_STATE 
{
    READY,
    RUNNING,
    BLOCKED,
    SUSPENDED
};

typedef struct
{
    void (*task_func)(void);
    uint8_t priority;
    enum TASK_STATE state;
} Task;

int current_task = 0;
Task task_list[MAX_TASKS];

// Prepares the next ready task to be run
void cycle_tasks(int num_tasks)
{
    int next_task = (current_task + 1) % num_tasks;
    while(task_list[next_task].state != READY || task_list[next_task].state == NULL)
    {
        int next_task = (next_task + 1) % num_tasks;
    }
    current_task = next_task;
}

void rtos()
{
    while(1)
    {
        task_list[current_task].task_func();
        cycle_tasks(5);
    }
}