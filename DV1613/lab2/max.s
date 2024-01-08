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
/* Global variables */
PATTERN:
    .word 0x0F0F0F0F // pattern to show on the LED lights
LEDS_ROTATE_DIR: // rotating direction
    .word 0

/* Code section */
.text

/*****************************************************************************
    Interrupt Vector
*****************************************************************************/
.org INTERRUPT_VECTOR_BASE // Address of interrupt vector
// Write your Interrupt Vector here
//.section .vectors, "ax"
.org 0x00000000 // Similar to .section above
    B _start // reset vector
    B SERVICE_UND // undefined instruction vector
    B SERVICE_SVC // software interrrupt vector
    B SERVICE_ABT_INST // aborted prefetch vector
    B SERVICE_ABT_DATA // aborted data vector
    .word 0 // unused vector
    B SERVICE_IRQ // IRQ interrupt vector
    B SERVICE_FIQ // FIQ interrupt vector

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
_START:
    /* Set up stack pointers for IRQ and SVC processor modes */
//    MOV R1, #INT_DISABLE | IRQ_MODE
    MOV R1, #0b11010010 // interrupts masked, MODE = IRQ
    MSR CPSR_c, R1 // Change to IRQ mode. CPSR_c means only move the control bits [7:0]
//    LDR SP, =A9_ONCHIP_END - 3  // set IRQ stack to top of A9 onchip memory
    LDR SP, =0xFFFFFFFF-3 // set IRQ stack to A9 onchip memory

    /* Change to SVC (supervisor) mode with interrupts disabled */
//    MOV R1, #INT_DISABLE | SVC_MODE
    MOV R1, #0b11010011 // interrupts masked, MODE = SVC
    MSR CPSR_c, R1 // change to supervisor mode
//    LDR SP, =DDR_END - 3 // set SVC stack to top of DDR3 memory
    LDR SP, =0x3FFFFFFF-3 // set SVC stack to top of DDR3 memory

    BL CONFIG_GIC // configure the ARM generic interrupt controller

    BL CONFIG_INTERVAL_TIMER // configure the Altera interval timer

    /* enable IRQ interrupts in the processor */
//    MOV R1, #INT_ENABLE | SVC_MODE // IRQ unmasked, MODE = SVC
    MOV R1, #0b01010011 // IRQ unmasked, MODE = SVC
    MSR CPSR_c, R1

/*******************************************************************
 Main program
*******************************************************************/
// Write code for your main program here
LOOP:
    B LOOP

CONFIG_INTERVAL_TIMER:
//    LDR R0, =TIMER_BASE
    LDR R0, =0xFF202000
    /* set the interval timer period for scrolling the LED displays */
    LDR R1, =5000000 // 1/(100 MHz) x 5x10^6 = 50 msec
    STR R1, [R0, #0x8]// store the low half word of counter
    // start value
    LSR R1, R1, #16
    STR R1, [R0, #0xC]// high half word of counter start value
    // start the interval timer, enable its interrupts
    MOV R1, #0x7 // START = 1, CONT = 1, ITO = 1
    STR R1, [R0, #0x4]
    BX LR
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

SERVICE_IRQ:
    PUSH {R0-R7, LR}

    /* Read the Interrupt Acknowledge Register (ICCIAR) from the CPU interface */
//   LDR R4, =MPCORE_GIC_CPUIF
    LDR R4, =0xFFFEC100
//   LDR R5, [R4, #ICCIAR] // read the interrupt ID
    LDR R5, [R4, #0x0C]// read from ICCIAR

INTERVAL_TIMER_CHECK:
//    CMP R5, #INTERVAL_TIMER_IRQ // check for interval timer interrupt
    CMP R5, #72 // check for interval timer interrupt
    BNE UNEXPECTED
    BL TIMER_ISR
    B EXIT_IRQ

UNEXPECTED:
    B UNEXPECTED // if not recognized, stop here

EXIT_IRQ:
    /* Write to the End of Interrupt Register (ICCEOIR) */
//    STR R5, [R4, #ICCEOIR]
    STR R5, [R4, #0x10]// write to ICCEOIR

    // Restore registers and return from interrupt.
    POP {R0-R7, LR}
    SUBS PC, LR, #4 // Atomically restores CPSR from SPSR and returns to interrupted instruction.

/*--- Undefined instructions --------------------------------------------------*/
SERVICE_UND:
    B SERVICE_UND
/*--- Software interrupts -----------------------------------------------------*/
SERVICE_SVC:
    B SERVICE_SVC
/*--- Aborted data reads ------------------------------------------------------*/
SERVICE_ABT_DATA:
    B SERVICE_ABT_DATA

/*--- Aborted instruction fetch -----------------------------------------------*/
SERVICE_ABT_INST:
    B SERVICE_ABT_INST
/*--- FIQ ---------------------------------------------------------------------*/
SERVICE_FIQ:
    B SERVICE_FIQ

/****************************************************************************
    Other Interrupt Service Routines (except for IRQ)
    -------------------------------------------------

Other interrupts are unused in this program, but should at least be defined.
These interrupt routines can just "idle" if ever called...
****************************************************************************/
// Write code for your other interrupt service routines here

TIMER_ISR:
    PUSH {R4-R7}
//    LDR R1, =TIMER_BASE // interval timer base address
    LDR R1, =0xFF202000 // interval timer base address
    MOVS R0, #0
    STR R0, [R1]// clear the interrupt

//    LDR R1, =LED_BASE // LED base address
    LDR R1, =0xFF200000 // LED base address
    LDR R2, =PATTERN // set up a pointer to the pattern for LED displays
    LDR R7, =LEDS_ROTATE_DIR // set up a pointer to the shift direction variable

    LDR R6, [R2] // load pattern for LED displays
    STR R6, [R1] // store to LEDs

SHIFT:
    LDR R5, [R7]// get shift direction
//    CMP R5, #RIGHT
    CMP R5, #1
    BNE SHIFT_L
    MOVS R5, #1 // used to rotate right by 1 position
    RORS R6, R5 // rotate right
    B END_TIMER_ISR
SHIFT_L:
    MOVS R5, #31 // used to rotate left by 1 position
    RORS R6, R5
END_TIMER_ISR:
    STR R6, [R2]// store LED display pattern
    POP {R4-R7}
    BX LR

/*******************************************************************
    HELP FUNCTION!
    --------------
Configures the Generic Interrupt Controller (GIC)
    Arguments:  R0: Interrupt ID
*******************************************************************/
CONFIG_GIC:
    PUSH {LR}
    /* To configure a specific interrupt ID:
    * 1. set the target to cpu0 in the ICDIPTRn register
    * 2. enable the interrupt in the ICDISERn register */
    /* CONFIG_INTERRUPT (int_ID (R0), CPU_target (R1)); */
    MOV R1, #1 // this field is a bit-mask; bit 0 targets cpu0
    BL CONFIG_INTERRUPT
    /* configure the GIC CPU Interface */
    LDR R0, =GIC_CPU_INTERFACE_BASE // base address of CPU Interface, 0xFFFEC100
    /* Set Interrupt Priority Mask Register (ICCPMR) */
    LDR R1, =0xFFFF // enable interrupts of all priorities levels
    STR R1, [R0, #0x04]
    /* Set the enable bit in the CPU Interface Control Register (ICCICR).
    * This allows interrupts to be forwarded to the CPU(s) */
    MOV R1, #1
    STR R1, [R0]
    /* Set the enable bit in the Distributor Control Register (ICDDCR).
    * This enables forwarding of interrupts to the CPU Interface(s) */
    LDR R0, =GIC_DISTRIBUTOR_BASE // 0xFFFED000
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
CONFIG_INTERRUPT:
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
