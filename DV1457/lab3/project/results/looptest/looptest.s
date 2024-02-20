.data
    format: .asciz "%d\n"
.text
    .global main
main:
	movq $100, %r8
L000:
	cmp $0, %r8
	jl	L001
	push %r8
	movq  %r8, %rsi 
	lea format(%rip), %rdi
	xor  %eax,%eax
	call printf
	pop %r8
	sub $1, %r8
	movq %r8, %r14
	movq %r14, %r8
	jmp	L000
L001:
    mov $60, %rax  
    xor %rdi, %rdi    
    syscall
