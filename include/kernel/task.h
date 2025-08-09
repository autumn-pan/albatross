#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Task ID is initially set to -1 such that the first task will have ID 0. Task IDs will increment linearly in O(1) time.
int max_id = -1;

enum TASK_STATE
{
    RUNNING,
    BLOCKED,
    SLEEPING,
    READY
};

typedef struct
{
    bool asleep; // Whether or not a task is sleep

    uint32_t init_time; // The time in ms that the task was put to sleep
    uint32_t sleep_time; // The total time that the task is meant to sleep for
    uint32_t remaining_time; // The remaining time it is supposed to sleep for
} SleepController;

typedef struct tbc
{
    struct tbc* next;
    uint32_t priority;
    void (*task_func)(void);

    uint32_t stack_ptr;
    uint32_t stack_base;
    enum TASK_STATE state;

    uint32_t delay;
    uint8_t id;

    SleepController* sleep_controller;
} TBC;



uint32_t* init_stack(void (*task_func)(void), uint32_t* stack);

#endif