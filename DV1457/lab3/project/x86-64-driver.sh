#!/bin/bash
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
.data
    format: .asciz "%d\n"
.text
    .global main
main:
EOL

echo "Prologue written to: $output_file"
echo pwd = $(pwd)
# Append the output of the compiler to the .s file
./bin/calc3i.exe < "$input_file" >> "$output_file"

echo "Compiler output written to: $output_file"
# Append the epilogue
cat >> "$output_file" <<EOL
    mov \$60, %rax  
    xor %rdi, %rdi    
    syscall
EOL

echo "Assembly file created at: $output_file"


gcc -o program $output_file -no-pie