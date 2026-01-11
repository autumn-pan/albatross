#include "drivers/gpio.h"
#include "config.c"
#include <stddef.h>
#include "error.h"

#ifdef RP2040
// rp2040 has 30 GPIO pins
#define NUM_GPIO 30
#define MIN_GPIO 0

// IO_BANK is used to GPIO Function selection
// (IO_BANK_BASE + 12*n) controls the function of GPIO n
#define IO_BANK_BASE *(uint32_t *) (0x40014000)
#define GPIO_OE_SET *(uint32_t *) (0xd0000024)
#define SIO_BASE *(uint32_t *) (0xd0000000)
#define GPIO_OUT_SET *(uint32_t *) (0xd0000014)
#define GPIO_IN *(uint32_t *) (0xd0000004)

Status_t alba_gpio_init_pin(size_t pin) {
    if(pin > NUM_GPIO || pin < MIN_GPIO) {
        fprintf(stderr, "Error: Yo")
        return RET_ERR_PARAMS;
    }

    // Set the pin function to SIO
    uint32_t *GPIO_CTRL = IO_BANK_BASE + 12*pin;
    GPIO_CTRL = 5;

    // Enable SIO outputs for the pin
    GPIO_OE_SET |= 1 << pin;
}

Status_t alba_gpio_set_pin(size_t pin, GPIO_STATE state) {
    if (pin < MIN_GPIO || pin > NUM_GPIO) {
        return RET_ERR_PARAMS
    }

    if(state == HIGH)
        GPIO_OE_SET |= 1 << pin;
    else if(state == LOW)
        GPIO_OE_SET &= ~(1 << pin);
    else 
        return RET_ERR_PARAMS;

    return RET_SUCCESS
}

GPIO_STATE alba_gpio_read_pin(size_t pin) {
    if (pin < MIN_GPIO || pin > NUM_GPIO) {
        return RET_ERR_PARAMS
    }

    return (GPIO_IN >> pin) & 1U;
}

#endif