.syntax unified
.cpu cortex-m0plus
.thumb


.global _initial_sp

.section .isr_vector, "a"
    .align  2

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
    .word PIO1_IRQ_0_Handler
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

    .word _start_idata
    .word _start_data
    .word _end_data
    .word _start_bss
    .word _end_bss
    .word _initial_sp

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
    .extern PIO1_IRQ_0_Handler
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

.global bss_zero
bss_zero:
    ldr R0, =_start_bss
    ldr R1, =_end_bss
    movs R2, #0
    bl bss_zero_loop

bss_zero_loop:
    cmp R0, R1
    bge bss_zero_end

    str R2, [R0]
    adds R0, R0, #4
    b bss_zero_loop

bss_zero_end:   
    bx lr


.global cp_flash
cp_flash:
    ldr R0, =_start_data
    ldr R1, =_end_data
    ldr R2, =_start_idata

cp_flash_loop:
    cmp R0, R1
    bge cp_flash_end

    ldr R3, [R2]
    str R3, [R0]
    adds R0, R0, #4
    adds R2, R2, #4

    b cp_flash_loop

cp_flash_end:
    bx lr

.global save_context
.global restore_context



// stack_ptr exists in r1

// Save the context of the current task
save_context:
    mrs r0, psp            // Save PSP into r0
 
    push {r4-r7}    // Save registers R4-R11 into R0
    str r0, [r1]           // Save stack_ptr into r0
    bx lr                  // Return

// Restore the context of the next task
restore_context:
    ldr r0, [r1]           // Load stack_ptr
    pop {r4-r7}    // Load R4-R11 from R0
    msr psp, r0            // Update PSP
    bx lr                  // Return


.global PendSV_Handler

.extern current_tcb
.extern next_tcb

PendSV_Handler:
    cpsid i

    ldr r1, =current_tcb
    ldr r1, [r1]
    bl save_context

    ldr r1, =next_tcb    
    ldr r1, [r1]                 
    bl restore_context

    ldr r2, =next_tcb
    ldr r2, [r2]
    ldr r3, =current_tcb
    str r2, [r3]

    cpsie i
    bx lr