#!/bin/bash

set -e

# Assemble the bootloader
nasm -f bin boot/boot.asm -o boot/boot.bin

# Compile the kernel
gcc -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

# Link the kernel
ld -o kernel/kernel.bin -Ttext 0x1000 --oformat binary kernel/kernel.o

# Create the OS image
cat boot/boot.bin kernel/kernel.bin > DemoOS.bin
