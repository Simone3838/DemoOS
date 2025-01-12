#!/bin/bash

set -e

# Directories
BOOT_DIR="boot"
KERNEL_DIR="kernel"
ISO_DIR="isodir"

# Assemble the bootloader
nasm -f bin $BOOT_DIR/boot.asm -o $BOOT_DIR/boot.bin

# Compile the kernel
gcc -ffreestanding -c $KERNEL_DIR/kernel.c -o $KERNEL_DIR/kernel.o

# Link the kernel
ld -o $KERNEL_DIR/kernel.bin -Ttext 0x1000 --oformat binary $KERNEL_DIR/kernel.o

# Create the ISO directory structure
mkdir -p $ISO_DIR/boot/grub
cp $BOOT_DIR/boot.bin $ISO_DIR/boot/boot.bin
cp $KERNEL_DIR/kernel.bin $ISO_DIR/boot/kernel.bin
cp grub.cfg $ISO_DIR/boot/grub/grub.cfg

# Create the bootable ISO image
grub-mkrescue -o DemoOS.iso $ISO_DIR

# Clean up
rm -rf $ISO_DIR
