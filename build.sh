#!/bin/bash 

reset
mkdir -p build_dir

clang   $(cat compile_flags.txt) -c src/boot/arch/x86/boot.s -o build_dir/bootstrap.o
clang++ $(cat compile_flags.txt) -c src/kernel.cpp -o build_dir/kernel.o
clang++ $(cat compile_flags.txt) -c src/terminal.cpp -o build_dir/terminal.o

ld.lld -m elf_i386 -T src/boot/arch/x86/linker.ld -o build_dir/kernel.elf build_dir/bootstrap.o build_dir/kernel.o build_dir/terminal.o


cp -rv  build_dir/kernel.elf iso/boot/kernel
grub-mkrescue -o kernel.iso iso

qemu-system-i386 -d int,cpu_reset -no-reboot -no-shutdown -cdrom kernel.iso -s
