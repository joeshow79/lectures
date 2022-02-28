pushq $0xabcdef  # push value onto stack
addq $17, %rax   # Add 17 to $rax
movl %eax, %edx   # Copy lower 32 bits to %edx
