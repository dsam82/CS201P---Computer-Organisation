

nasm -f elf32 -g  -F stabs sum_of_num.asm  -l sum_of_num.lst

ld  -m  elf_i386 -o sum_of_num sum_of_num.o  io.o 
