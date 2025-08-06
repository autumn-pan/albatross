.global save_context
.global restore_context

// Save the context of the current task
save_context:
    mrs r0, psp            // Save PSP into r0
 
    stmdb r0!, {r4-r11}    // Save registers R4-R11 into R0
    str r0, [r1]           // Save stack_ptr into r0
    bx lr                  // Return

// Restore the context of the next task
restore_context:
    ldr r0, [r1]           // Load stack_ptr
    ldmia r0!, {r4-r11}    // Load R4-R11 from R0
    msr psp, r0            // Update PSP
    bx lr                  // Return