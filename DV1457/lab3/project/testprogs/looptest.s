.data
    format: .asciz "%d\n"
.text
    .global main
main:
	movq $100, %r11
L000:
	cmp $0, %r11
	jl	L001
	push %r11
	movq  %r11, %rsi 
	lea format(%rip), %rdi
	xor  %eax,%eax
	call printf
	pop %r11
	subq $1, %r11
	movq %r11, %r10
	movq %r10, %r11
	jmp	L000
L001:
    mov $60, %rax  
    xor %rdi, %rdi    
    syscall
