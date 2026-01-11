#ifndef GPIO_H
#define GPIO_H
#include <stddef.h>

typedef enum {
    LOW = 0,
    HIGH = 1
} GPIO_STATE;

void alba_gpio_write(size_t pin);
GPIO_STATE alba_gpio_read(size_t pin);
void alba_gpio_init();

#endif