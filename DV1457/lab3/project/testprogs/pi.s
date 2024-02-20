.data
    format: .asciz "%d\n"
.text
    .global main
main:
	movq $1000001, %r11
	movq $100000000, %r12
	movq $0, %r13
	movq $0, %r14
L000:
	cmp $0, %r11
	jle	L001
	cmp $0, %r14
	jnz	L002
	movq %r11, %r15
	movq $1, %r14
	jmp	L003
L002:
	movq %r11, %r8
	neg %r8
	movq %r8, %r10
	movq %r10, %r15
	movq $0, %r14
L003:
	movq $0, %rdx 
	movq %r12, %rax
	idivq %r15
	movq %rax, %r10
	add %r13, %r10
	movq %r10, %r13
	subq $2, %r11
	movq %r11, %r10
	movq %r10, %r11
	jmp	L000
L001:
	movq $0, %rdx 
	movq $100000, %rbx
	movq %r12, %rax
	idivq %rbx
	movq %rax, %r10
	movq $0, %rdx 
	movq %r13, %rax
	idivq %r10
	movq %rax, %r10
	imul $4, %r10
	movq %r10, %r10
	push %r10
	movq  %r10, %rsi 
	lea format(%rip), %rdi
	xor  %eax,%eax
	call printf
	pop %r10
    mov $60, %rax  
    xor %rdi, %rdi    
    syscall
