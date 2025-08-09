.syntax unified
.cpu cortex-m0+
.thumb



.section isr_vtable, "a"
    .align  2
    .word   _stack_ptr

    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   0
    .word   0
    .word   0

    .word   0
    .word   0
    .word   0
    .word   0

    .word   SVC_Handler
    .word   DebugMon_Handler

    .word   0

    .word   PendSV_Handler
    .word   SysTick_Handler

    // Peripheral IQRs
    .word TIMER_IRQ_0_Handler
    .word TIMER_IRQ_1_Handler
    .word TIMER_IRQ_2_Handler
    .word TIMER_IRQ_3_Handler
    .word PWM_IRQ_WRAP_Handler
    .word USBCTRL_IRQ_Handler
    .word XIP_IRQ_Handler
    .word PIO0_IRQ_0_Handler
    .word PIO0_IRQ_1_Handler
    .word PIO1_IRQ_Handler
    .word PIO1_IRQ_1_Handler
    .word DMA_IRQ_0_Handler
    .word DMA_IRQ_1_Handler
    .word IO_IRQ_BANK0_Handler
    .word IO_IRQ_QSPI_Handler
    .word SIO_IRQ_PROC0_Handler
    .word CLOCKS_IRQ_Handler
    .word SPI0_IRQ_Handler
    .word SPI1_IRQ_Handler
    .word UART0_IRQ_Handler
    .word UART1_IRQ_Handler
    .word ADC_IRQ_Handler
    .word I2C0_IRQ_Handler
    .word I2C1_IRQ_Handler
    .word RTC_IRQ_Handler

    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0


.section .text
    .global Reset_Handler
    .global Default_Handler

    .word _sidata
    .word _sdata
    .word _edata
    .word _sbss
    .word _ebss

    .extern Reset_Handler
    .extern HardFault_Handler
    .extern SVC_Handler
    .extern DebugMon_Handler
    .extern PendSV_Handler
    .extern SysTick_Handler
    .extern Default_Handler

    .extern TIMER_IRQ_0_Handler
    .extern TIMER_IRQ_1_Handler
    .extern TIMER_IRQ_2_Handler
    .extern TIMER_IRQ_3_Handler
    .extern PWM_IRQ_WRAP_Handler
    .extern USBCTRL_IRQ_Handler
    .extern XIP_IRQ_Handler
    .extern PIO0_IRQ_0_Handler
    .extern PIO0_IRQ_1_Handler
    .extern PIO1_IRQ_Handler
    .extern PIO1_IRQ_1_Handler
    .extern DMA_IRQ_0_Handler
    .extern DMA_IRQ_1_Handler
    .extern IO_IRQ_BANK0_Handler
    .extern IO_IRQ_QSPI_Handler
    .extern SIO_IRQ_PROC0_Handler
    .extern CLOCKS_IRQ_Handler
    .extern SPI0_IRQ_Handler
    .extern SPI1_IRQ_Handler
    .extern UART0_IRQ_Handler
    .extern UART1_IRQ_Handler
    .extern ADC_IRQ_Handler
    .extern I2C0_IRQ_Handler
    .extern I2C1_IRQ_Handler
    .extern RTC_IRQ_Handler
