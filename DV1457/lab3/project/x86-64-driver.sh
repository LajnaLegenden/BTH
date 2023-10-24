#!/bin/bash
set -x
# Check if an argument is given
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file.calc>"
    exit 1
fi

input_file="$1"
if [ "${input_file: -5}" != ".calc" ]; then
    echo "Error: Input file should have a '.calc' extension."
    exit 1
fi

# Create the .s file corresponding to the .calc file
output_file="${input_file%.calc}.s"

# Write the prologue
cat > "$output_file" <<EOL
section .data
; Add data declarations here if needed.

section .text
    global _start
_start:
EOL

echo "Prologue written to: $output_file"
echo pwd = $(pwd)
# Append the output of the compiler to the .s file
./lexyacc-code/calc3i.exe < "$input_file" >> "$output_file"

echo "Compiler output written to: $output_file"
# Append the epilogue
cat >> "$output_file" <<EOL
    ; Exit system call.
    mov rax, 60       ; syscall: exit
    xor rdi, rdi      ; status: 0
    syscall
EOL

echo "Assembly file created at: $output_file"
