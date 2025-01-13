// kernel/reboot.c
#include <stdint.h>

// Port for the keyboard controller
#define KEYBOARD_CTRL_PORT 0x64

void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void reboot() {
    // Send the reset command to the keyboard controller
    while (1) {
        outb(KEYBOARD_CTRL_PORT, 0xFE);
    }
}
