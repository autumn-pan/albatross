#include "kernel/os.h"

#define SIO_BASE           0xD0000000

#define GPIO_OE_SET        (*(volatile uint32_t *)(SIO_BASE + 0x024))
#define GPIO_OUT_SET        (*(volatile uint32_t *)(SIO_BASE + 0x014))
#define GPIO_OUT_CLR       (*(volatile uint32_t *)(SIO_BASE + 0x018))
#define GPIO25_CTRL         (*(volatile uint32_t *)0x400140cc)

uint8_t i = 0;
uint8_t j = 0;


void task_func1()
{
    while(1)
    {
        GPIO_OUT_SET = 1 << 25;
        yield();
    }
}

void task_func2()
{
    while (1)
    {
        GPIO_OUT_CLR = 1 << 25;
        j++;
        yield();
    }
}

int main()
{
    GPIO25_CTRL = 5;
    GPIO_OE_SET = 1 << 25;


    GPIO_OUT_SET = 1 << 25;

    for (volatile int i = 0; i < 1000000; ++i);
    return 0;
}