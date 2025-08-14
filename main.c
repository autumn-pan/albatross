#include "kernel/os.h"

uint8_t i = 0;
uint8_t j = 0;


void task_func1()
{
    while(1)
    {
        i++;
        yield();
    }
}

void task_func2()
{
    while (1)
    {
        j++;
        yield();
    }
}

int main()
{
    TBC* task1 = init_tbc(task_func1, 1);
    add_task(task1);
    TBC* task2 = init_tbc(task_func1, 1);
    add_task(task2);
    return 0;
}