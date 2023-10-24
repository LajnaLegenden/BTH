section .data
; Add data declarations here if needed.

section .text
    global _start
_start:
	mov	rax, 100
	mov	[rbp-36], rax
L000:
	mov	rax, [rbp-36]
	push	rax
	mov	rax, 0
	pop	rbx
	cmp	rax, rbx
	setge	al
	movzx	rax, al
	test	rax, rax
	jz	L001
	mov	rax, [rbp-36]
	mov	rsi, rax
	mov	rdi, 1
	mov	rsi, rsp
	mov	dl, 4
	mov	rax, 0x2000004
	syscall
	add	rsp, 8
	push	rax
	mov	rax, [rbp-36]
	push	rax
	mov	rax, 1
	pop	rbx
	sub	rax, rbx
	mov	[rbp-36], rax
	pop	rbx
	jmp	L000
L001:
    ; Exit system call.
    mov rax, 60       ; syscall: exit
    xor rdi, rdi      ; status: 0
    syscall
