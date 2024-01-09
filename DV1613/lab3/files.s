.data
inputbuffer:    .space 128
outputbuffer:   .space 128
oindex:         .quad 0
iindex:         .quad 0
asciibuffer:
                .fill 64, 1, 0 # Allocate 64 bytes, initialized to 0

.text

.global inimage
inimage:
    movq $inputBuffer, %rdi
    movq $128, %rsi
    movq stdin, %rdx
    call fgets
    movq $0, iIndex
    ret

# ___________________________________
.global getint
getint:
# Implementation for getInt

    movq $0, %rax # Set return value to 0
    mov $0, %r8 # Initialize isMinus flag to 0
    movq $inputBuffer, %rdi # Load inputBuffer address into %rdi
    movq iIndex, %r10 # Load iIndex value into %r10
    cmp $0, inputBuffer # Check if input is empty
    jne handleSpace
    call inImage

# handle " "

handlespace:
    movzbq (%rdi, %r10), %r9 # load current into register
    cmp $' ', %r9            # Compare r9 with ASCII value of space character
    jne handleMinus          # Jump to handleMinus if not equal
    incq %r10                # Increment the value of register r10
    jmp handleSpace          # Jump to handleSpace

# handle -
handleminus:
    movzbq (%rdi, %r10), %r9 # load current into register
    cmp $'-', %r9
    jne handlePlus
    incq %r10
    movq $1, %r8 # set isMinus to true
    jmp processNumber

# handle +
handleplus:
    movzbq (%rdi, %r10), %r9 # load current into register
    cmp $'+', %r9
    jne processNumber
    incq %r10
    jmp processNumber

processnumber:
    movzbq (%rdi, %r10), %r9 # load current into register
    cmp $'0', %r9 # Compare r9 with ASCII value of 0
    jl invlidNumber
    cmp $'9', %r9 # Compare r9 with ASCII value of 9
    jg invlidNumber
    subq $'0', %r9 # Subtract the ASCII value of 0 from the value in register r9
    imulq $10, %rax
    addq %r9, %rax
    incq %r10
    jmp processNumber

invlidnumber:
    cmpq $1, %r8 # check if isMinus is true
    jne returnInt # jump to returnInt if isMinus is false
    negq %rax # negate the value in register rax

returnint:
    movq %r10, iIndex # save iIndex back
    ret
# ___________________________________
.global gettext
gettext:
    movq $inputBuffer, %r13
    movq iIndex, %r14
    cmp $0, inputBuffer
    jg proceedGetText
    call inImage
    cmp $128, iIndex
    jg proceedGetText
    call inImage

proceedgettext:
# buffer address %rdi
# n bytes : %rsi
    movq $0, %r11
    movq iIndex, %r10

loopgettext:
# check rsi != r11
    cmp %rsi, %r11
    je finnishGetText
    movzbq (%r13, %r14), %r9 # load current into register
    movq %r9, (%rdi, %r11)# put in buffer and step
    incq %r11
    incq %r14
    jmp loopGetText

finnishgettext:
    movq %r8, %rax
    movq %r14, iIndex

    ret
# ___________________________________
.global getchar
getchar:
    movq $inputBuffer, %r13 # load inputBuffer address
    movq iIndex, %r14 # load iIndex
    cmp $0, inputBuffer # check if inputBuffer is empty
    jg proceedGetChar
    call inImage
    cmp $128, iIndex # check if iIndex is greater than 128
    jg proceedGetChar
    call inImage

proceedgetchar:
    movzbq (%r13, %r14), %rax
    incq %r14
    movq %r14, iIndex
    ret
# ___________________________________
.global getinpos
getinpos:
    movq iIndex, %rax # return iIndex
    ret
# ___________________________________
.global setinpos
setinpos:
    cmp $128, %rdi            # Compare the value in register %rdi with 128
    jge setPosMax             # Jump to setPosMax if %rdi is greater than or equal to 128
    cmp $0, %rdi              # Compare the value in register %rdi with 0
    jle setPosMin             # Jump to setPosMin if %rdi is less than or equal to 0
    movq %rdi, iIndex         # Move the value in register %rdi to the memory location iIndex
    jmp endSetPos             # Jump to endSetPos
setposmax:                    # Label for setPosMax
    movq $128, iIndex         # Move the value 128 to the memory location iIndex
    jmp endSetPos             # Jump to endSetPos
setposmin:                    # Label for setPosMin
    movq $0, iIndex           # Move the value 0 to the memory location iIndex
    jmp endSetPos
# Jump to endSetPos
endsetpos: # Label for endSetPos
    ret # Return from the function

# ___________________________________
.global outimage
outimage:
    movq $outputBuffer, %rdi # load outputBuffer address
    call puts # call puts
    movq $0, oIndex # reset oIndex
    ret
# ___________________________________
.global putint
putint:
    movq %rdi, %rax
    push $0 # push 0 to indicate end of number
    leaq outputBuffer, %rcx
    movq oIndex, %rdi

    cmpq $0, %rax
    jge putIntDivision

    movq $1, %r11
    movq $45, %r9
    movq %r9, (%rcx, %rdi)# put in outputBuffer and step
    incq %rdi
    negq %rax

putintdivision:
    movq $10, %rbx # divide with 10
    xor %rdx, %rdx # set rdx to 0
    divq %rbx
    addq $48, %rdx # convert to ascii
    pushq %rdx
    cmpq $0, %rax # check if is last place digit
    je putIntOrdering
    jmp putIntDivision

putintordering:
    xor %r10, %r10 # reset r10
    popq %r10 # Pop into register r10
    cmpq $0, %r10
    jle putIntRestore          # Jump to the "end" label if the value in r10 is less than or equal to 0
    movq %r10, (%rcx, %rdi)    # put in outputBuffer and step
    incq %rdi # increment outputBuffer index
    jmp putIntOrdering

putintrestore:
    movq %rdi, oIndex # saves oIndex back
    ret

# ___________________________________
.global puttext
puttext:
    leaq outputBuffer, %r10 # load output buffer address
    movq oIndex, %r11 # load output buffer index
    movq $0, %r12 # outbuf index

puttextouter:
    cmp $128, %r11 # check full buffer
    jl readBuffer
    call outImage

readbuffer:
    movzbq (%rdi, %r12), %r13 # read char from arg buf
    incq %r12 # increment arg buf index
    movq %r13, (%r10, %r11)# write char to out buf
    incq %r11 # increment out buf index
    cmp $0, %r13 # check for null terminator
    je putTextEnd
    jmp putTextOuter

puttextend:
    decq %r11
    movq %r11, oIndex
    ret
# ___________________________________
.global putchar
putchar:
    cmp $128, oIndex
    jl putCharMain
    call outImage

putcharmain:
    leaq outputBuffer, %r10
    movq oIndex, %r11
    movq %rdi, (%r10, %r11)
    incq %r11
    movq %r11, oIndex
    ret
# ___________________________________
.global getoutpos
getoutpos:
    movq oIndex, %rax # return oIndex
    ret
# ___________________________________
.global setoutpos
setoutpos:
    cmp $128, %rdi # check if greater than 128
    jge setOutPosMax
    cmp $0, %rdi # check if less than 0
    jle setOutPosMin
    movq %rdi, oIndex # load oIndex
    jmp endSetOutPos
setoutposmax:
    movq $128, oIndex # set 128 to the memory location oIndex
    jmp endSetOutPos
setoutposmin:
    movq $0, oIndex # set 0 to the memory location oIndex
endsetoutpos:
    ret

# ___________________________________
