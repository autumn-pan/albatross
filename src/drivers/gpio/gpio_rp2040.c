#include "drivers/gpio.h"
#include "config.c"
#include <stddef.h>

#ifdef RP2040
// rp2040 has 30 GPIO pins
#define NUM_GPIO 30

// IO_BANK is used to GPIO Function selection
// (IO_BANK_BASE + 12*n) controls the function of GPIO n
#define IO_BANK_BASE *(uint32_t *) (0x40014000)
#define GPIO_OE_SET *(uint32_t *) (0xd0000024)
#define SIO_BASE *(uint32_t *) (0xd0000000)

void alba_gpio_init_pin(size_t pin) {
    if(pin > NUM_GPIO) {
        return;
    }

    // Set the pin function to SIO
    uint32_t *GPIO_CTRL = IO_BANK_BASE + 12*pin;
    GPIO_CTRL = 5;

    // Enable SIO outputs for the pin
    GPIO_OE_SET |= 1 << pin;
}

#endif