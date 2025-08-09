.syntax unified
.cpu cortex-m0+
.thumb



.section isr_vtable
    .align  2
    .word   _stack_ptr

    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   MemManage_Handler
    .word   BusFault_Handler
    .word   UsageFault_Handler

    .word   0
    .word   0
    .word   0
    .word   0

    .word   SVC_Handler
    .word   DebugMon_Handler

    .word   0

    .word   PendSV_Handler
    .word   SysTick_Handler


.section .text
    .global Reset_Handler
    .global Default_Handler

    .word _sidata
    .word _sdata
    .word _edata
    .word _sbss
    .word _ebss

    .weak NMI_Handler
    .weak HardFault_Handler
    .weak MemManage_Handler
    .weak BusFault_Handler
    .weak UsageFault_Handler
    .weak SVC_Handler
    .weak DebugMon_Handler
    .weak PendSV_Handler
    .weak SysTick_Handler

    .set NMI_Handler, Default_Handler
    .set HardFault_Handler, Default_Handler
    .set MemManage_Handler, Default_Handler
    .set BusFault_Handler, Default_Handler
    .set UsageFault_Handler, Default_Handler
    .set SVC_Handler, Default_Handler
    .set DebugMon_Handler, Default_Handler
    .set PendSV_Handler, Default_Handler
    .set SysTick_Handler, Default_Handler


