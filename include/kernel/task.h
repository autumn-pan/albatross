#ifndef TASK_H
#define TASK_H
#include <stdio.h>
#include <stdint.h>

enum TASK_STATE
{
    RUNNING,
    BLOCKED,
    SUSPENDED,
    READY
};

typedef struct tbc
{
    struct tbc* next;
    uint32_t priority;
    void (*task_func)(void);

    uint32_t stack_ptr;
    uint32_t stack_base;

    uint32_t delay;
    uint8_t id;
} TBC;


#endif