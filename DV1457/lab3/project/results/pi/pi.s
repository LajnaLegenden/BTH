.data
    format: .asciz "%d\n"
.text
    .global main
main:
    mov $60, %rax  
    xor %rdi, %rdi    
    syscall
