/******************************************************************************
    Define symbols
******************************************************************************/
// Proposed interrupt vector base address
    .equ INTERRUPT_VECTOR_BASE, 0x00000000

// Proposed stack base addresses
    .equ SVC_MODE_STACK_BASE, 0x3FFFFFFF-3 // set SVC stack to top of DDR3 memory
    .equ IRQ_MODE_STACK_BASE, 0xFFFFFFFF-3 // set IRQ stack to A9 onchip memory

// GIC Base addresses
    .equ GIC_CPU_INTERFACE_BASE, 0xFFFEC100
    .equ GIC_DISTRIBUTOR_BASE, 0xFFFED000

// Other I/O device base addresses

/* Data section, for global data/variables if needed. */
.data

/* Code section */
.text

/*****************************************************************************
    Interrupt Vector
*****************************************************************************/
.org INTERRUPT_VECTOR_BASE // Address of interrupt vector
// Write your Interrupt Vector here

    B _start // reset vector
    B service_und // undefined instruction vector
    B service_svc // software interrrupt vector
    B service_abt_inst // aborted prefetch vector
    B service_abt_data // aborted data vector
    .word 0 // unused vector
    B service_irq // IRQ interrupt vector
    B service_fiq // FIQ interrupt vector

.global _start
/*****************************************************************************************************
    System startup.
    ---------------
On system startup some basic configuration is needed, in this case:
    1. Setup stack pointers for each used processor mode
    2. Configure the Generic Interrupt Controller (GIC). Use the given help function CONFIG_GIC!
    3. Configure the used I/O devices and enable them for interrupt
    4. Change to the processor mode for the main program loop (for example supervisor mode)
    5. Enable the processor interrupts (IRQ in our case)
    6. Start running the main program loop
 Your program will use two different processor modes when running:
 -Supervisor mode (SVC) when running the main program loop. Also default mode on reset.
 -IRQ mode when handling IRQ interrupts
 Changing processor mode and/or enabling/disabling interrupts control bits
 is done by updating the program status register (CPSR) control bits [7:0]
 The CPSR register holds the processor mode control bits [4:0]:
   10011 - Supervisor mode (SVC)
   10010 - IRQ mode
 The CPSR register also holds the following interrupt control bits:
   bit [7] IRQ enable/disable. 0 means IRQ enabled, 1 means IRQ disabled
   bit [6] FIQ enable/disable. 0 means FIQ enabled, 1 means FIQ disabled
 Bit [5] of the CPSR register should always be 0 in this case!
 The instruction "MSR CPSR_c, #0b___" can be used to modify the CPSR control bits.
 Example: "MSR CPSR_c #0b11011111" diables both interrupts and sets processor mode to "system mode".
 The instruction "MRS CPSR_c, R__" can be used to read the CPSR control bits into a register.
 Example: "MRS CPSR_c R0" reads CPSR control bits for interrupts and processor mode into register R0.
*****************************************************************************************************/
// Write your system startup code here. Follow the steps in the description above!
// System startup code
_start:

    /* Set up stack pointers for IRQ and SVC processor modes */
    MOV R1, #0b11010010             // interrupts masked, MODE = IRQ
    MSR CPSR_c, R1                  // change to IRQ mode
    LDR SP, =0xFFFFFFFF-3           // set IRQ stack to A9 onchip memory
    /* Change to SVC (supervisor) mode with interrupts disabled */
    MOV R1, #0b11010011             // interrupts masked, MODE = SVC
    MSR CPSR, R1                    // change to supervisor mode
    LDR SP, =0x3FFFFFFF-3
    MOV R0, #73 // set SVC stack to top of DDR3 memory
    BL config_gic // configure the ARM GIC
    // To DO: write to the pushbutton KEY interrupt mask register
    // Or, you can call enable_PB_INT_ASM subroutine from previous task
    // to enable interrupt for ARM A9 private timer, use ARM_TIM_config_ASM subroutine

    LDR R0, =0xFF200050             // pushbutton KEY base address
    MOV R1, #0xF                    // set interrupt mask bits
    STR R1, [R0, #0x8]              // interrupt mask register (base + 8)

    LDR A1, =#2000000 // Initial count value of 1 second
    MOV A2, #6 // bit I = 1 sets turns on timer interrupts; E = 1 starts timer; bit A = 1 loops timer

    // enable IRQ interrupts in the processor
    MOV R0, #0b01010011 // IRQ unmasked, MODE = SVC
    MSR CPSR_c, R0

/*******************************************************************
 Main program
*******************************************************************/
// Write code for your main program here

// Main program loop
main_loop:
    // Write your main program here
    B main_loop // Infinite loop
/*******************************************************************
    IRQ Interrupt Service Routine (ISR)
    -----------------------------------
The ISR  should:
    1. Read and acknowledge the interrupt at the GIC.The GIC returns the interrupt ID.
    2. Check which device raised the interrupt
    3. Handle the specific device interrupt
    4. Acknowledge the specific device interrupt
    5. Inform the GIC that the interrupt is handled
    6. Return from interrupt
The following GIC CPU interface registers should be used (both v2/v1 alternative names showed below):
    -Interrupt Acknowledge Register (GICC_IAR/ICCIAR)
        Reading this register returns the interrupt ID corresponding to the I/O device.
        This read acts as an acknowledge for the interrupt.
    -End of Interrupt Register (GICC_EOIR/ICCEOIR)
        Writing the corresponding interrupt ID to this register informs the GIC that
        the interrupt is handled and clears the interrupt from the GIC CPU interface.
How to handle a specific interrupt depends on the I/O device generating the interrupt.
Read the documentation for your I/O device carefully!
Every I/O device has a base address. Usually the I/O device has several registers
(32 bit words on a 32 bit architecture) starting from the base address. Each register, and
often every bit in these registers, have a certain function and meaning. Look out for
how to read and/write to your device and also how to enable/disable interrupts from the device.
Returning from an interrupt is done by using a special system level instruction:
    SUBS PC, LR, #CONSTANT
    where the CONSTANT depends on the specific interrupt (4 for IRQ).
Finally, don't forget to push/pop registers used by this interrupt routine!
*******************************************************************/
// Write code for your IRQ interrupt service routine here
service_irq:
    PUSH {R0-R7, LR}
    /* Read and acknowledge the interrupt at the GIC */
    LDR R0, =0xFFFEC100 // base address of CPU Interface, 0xFFFEC100
    LDR R5, [R0, #0x0C] // read the Interrupt Acknowledge Register (GICC_IAR/ICCIAR)
    /* Check which device raised the interrupt */
    CMP R5, #73 // compare interrupt ID with push buttons
    BNE unexpected

    /* Handle the specific device interrupt */

    MOV R2, #0xF
    STR R2, [R0, #0xC]// clear the interrupt
    /* Acknowledge the specific device interrupt */
    LDR R0, =0xFFFEC100 // base address of CPU Interface, 0xFFFEC100
    STR R5, [R0, #0x10] // write the interrupt ID to the End of Interrupt Register (GICC_EOIR/ICCEOIR)
    // CLEAR INTERRUPT

    MOV R2, #0xF
    STR R2, [R0, #0xC]// clear the interrupt

/* Write to the End of Interrupt Register (ICCEOIR) */
//    STR R5, [R4, #ICCEOIR]
# STR R5, [R4, #0x10]// write to ICCEOIR

    // Restore registers and return from interrupt.
    POP {R0-R7, LR}
    SUBS PC, LR, #4 // Atomically restores CPSR from SPSR and returns to interrupted instruction.

unexpected:
    B unexpected // if not recognized, stop here

push:
    B push

/****************************************************************************
    Other Interrupt Service Routines (except for IRQ)
    -------------------------------------------------
Other interrupts are unused in this program, but should at least be defined.
These interrupt routines can just "idle" if ever called...
****************************************************************************/
// Write code for your other interrupt service routines here

// Undefined instruction ISR
service_und:
    B service_und

// Software interrupt ISR
service_svc:
    B service_svc

// Aborted prefetch ISR
service_abt_inst:
    B service_abt_inst

// Aborted data ISR
service_abt_data:
    B service_abt_data

// FIQ ISR
service_fiq:
    B service_fiq

/*******************************************************************
    HELP FUNCTION!
    --------------
Configures the Generic Interrupt Controller (GIC)
    Arguments:  R0: Interrupt ID
*******************************************************************/
config_gic:
    PUSH {LR}
    /* To configure a specific interrupt ID:
    * 1. set the target to cpu0 in the ICDIPTRn register
    * 2. enable the interrupt in the ICDISERn register */
    /* CONFIG_INTERRUPT (int_ID (R0), CPU_target (R1)); */
    MOV R1, #1 // this field is a bit-mask; bit 0 targets cpu0
    BL config_interrupt
    /* configure the GIC CPU Interface */
    LDR R0, =0xFFFEC100 // base address of CPU Interface, 0xFFFEC100
    /* Set Interrupt Priority Mask Register (ICCPMR) */
    LDR R1, =0xFFFF // enable interrupts of all priorities levels
    STR R1, [R0, #0x04]
    /* Set the enable bit in the CPU Interface Control Register (ICCICR).
    * This allows interrupts to be forwarded to the CPU(s) */
    MOV R1, #1
    STR R1, [R0]
    /* Set the enable bit in the Distributor Control Register (ICDDCR).
    * This enables forwarding of interrupts to the CPU Interface(s) */
    LDR R0, =0xFFFED000 // 0xFFFED000
    STR R1, [R0]
    POP {PC}

    /*********************************************************************
        HELP FUNCTION!
        --------------
    Configure registers in the GIC for an individual Interrupt ID.
    We configure only the Interrupt Set Enable Registers (ICDISERn) and
    Interrupt Processor Target Registers (ICDIPTRn). The default (reset)
    values are used for other registers in the GIC.
    Arguments:  R0 = Interrupt ID, N
                R1 = CPU target
    *********************************************************************/
config_interrupt:
    PUSH {R4-R5, LR}
    /* Configure Interrupt Set-Enable Registers (ICDISERn).
    * reg_offset = (integer_div(N / 32) * 4
    * value = 1 << (N mod 32) */
    LSR R4, R0, #3 // calculate reg_offset
    BIC R4, R4, #3 // R4 = reg_offset
    LDR R2, =0xFFFED100 // Base address of ICDISERn
    ADD R4, R2, R4 // R4 = address of ICDISER
    AND R2, R0, #0x1F // N mod 32
    MOV R5, #1 // enable
    LSL R2, R5, R2 // R2 = value
    /* Using the register address in R4 and the value in R2 set the
    * correct bit in the GIC register */
    LDR R3, [R4]// read current register value
    ORR R3, R3, R2 // set the enable bit
    STR R3, [R4]// store the new register value
    /* Configure Interrupt Processor Targets Register (ICDIPTRn)
    * reg_offset = integer_div(N / 4) * 4
    * index = N mod 4 */
    BIC R4, R0, #3 // R4 = reg_offset
    LDR R2, =0xFFFED800 // Base address of ICDIPTRn
    ADD R4, R2, R4 // R4 = word address of ICDIPTR
    AND R2, R0, #0x3 // N mod 4
    ADD R4, R2, R4 // R4 = byte address in ICDIPTR
    /* Using register address in R4 and the value in R2 write to
    * (only) the appropriate byte */
    STRB R1, [R4]
    POP {R4-R5, PC}

.end
