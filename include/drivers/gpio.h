#ifndef GPIO_H
#define GPIO_H
#include <stddef.h>

enum GPIO_STATE {
    LOW = 0,
    HIGH = 1
};

void alba_gpio_write(size_t pin);
enum GPIO_STATE alba_gpio_read(size_t pin);
void alba_gpio_init();

#endif