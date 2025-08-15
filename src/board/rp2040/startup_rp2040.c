#include <stdint.h>
#include "kernel/os.h"
#include "kernel/sched.h"

extern uint32_t _start_idata; // Flash
extern uint32_t _start_data; // RAM
extern uint32_t _end_data; // RAN
extern uint32_t _start_bss;    
extern uint32_t _end_bss;     
extern uint32_t _initial_sp;   

extern void bss_zero(void);
extern void cp_flash(void);


int main(void);

void Reset_Handler(void)
{
    // Copy from Flash to RAM
    cp_flash();
    // Zero out .bss
    bss_zero();

    init_os();
    main();

    // Infinite loop is main returns for whatever reason
    while(1);
}


// Set all handlers as weak aliases for Default_Handler for now
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));

void TIMER_IRQ_0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void TIMER_IRQ_1_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void TIMER_IRQ_2_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void TIMER_IRQ_3_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PWM_IRQ_WRAP_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void USBCTRL_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void XIP_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PIO0_IRQ_0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PIO1_IRQ_0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PIO0_IRQ_1_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void PIO1_IRQ_1_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void DMA_IRQ_0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void DMA_IRQ_1_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void IO_IRQ_BANK0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void IO_IRQ_QSPI_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SIO_IRQ_PROC0_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void CLOCKS_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UART0_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UART1_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void ADC_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void I2C0_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void RTC_IRQ_Handler(void)    __attribute__((weak, alias("Default_Handler")));


void Default_Handler(void)
{
  for (;;);}

void HardFault_Handler(void)
{
  for (;;);
}

void SysTick_Handler(void)
{
  ticks++;

  void update_scheduler();
}