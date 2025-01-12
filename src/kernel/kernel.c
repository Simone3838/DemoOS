// kernel/kernel.c
#include <stdint.h>
#include <stddef.h>

// VGA text mode buffer
#define VGA_ADDRESS 0xB8000
#define VGA_COLUMNS 80
#define VGA_ROWS 25

// Colors
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_BLACK 0

// Ports for keyboard input
#define KEYBOARD_DATA_PORT 0x60

volatile char *video_memory = (volatile char *)VGA_ADDRESS;
uint16_t cursor_position = 0;

void clear_screen() {
    for (size_t y = 0; y < VGA_ROWS; y++) {
        for (size_t x = 0; x < VGA_COLUMNS; x++) {
            size_t index = (y * VGA_COLUMNS + x) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = VGA_COLOR_GREEN;
        }
    }
}

void print_string(const char *str) {
    while (*str) {
        video_memory[cursor_position * 2] = *str++;
        video_memory[cursor_position * 2 + 1] = VGA_COLOR_GREEN;
        cursor_position++;
    }
}

void new_line() {
    cursor_position += VGA_COLUMNS - (cursor_position % VGA_COLUMNS);
}

char read_key() {
    char c = 0;
    while ((c = inb(KEYBOARD_DATA_PORT)) == 0);
    return c;
}

void shell() {
    char command[256];
    size_t command_length = 0;

    while (1) {
        print_string("DemoOS> ");
        command_length = 0;

        while (1) {
            char c = read_key();
            if (c == '\n') {
                break;
            } else if (c == '\b' && command_length > 0) {
                command_length--;
                cursor_position--;
                print_string(" ");
                cursor_position--;
            } else if (c >= 32 && c <= 126) {
                command[command_length++] = c;
                video_memory[cursor_position * 2] = c;
                video_memory[cursor_position * 2 + 1] = VGA_COLOR_GREEN;
                cursor_position++;
            }
        }

        command[command_length] = '\0';
        new_line();

        if (strcmp(command, "help") == 0) {
            print_string("Available commands: help, clear\n");
        } else if (strcmp(command, "clear") == 0) {
            clear_screen();
            cursor_position = 0;
        } else {
            print_string("Unknown command\n");
        }

        new_line();
    }
}

void main() {
    clear_screen();
    print_string("Hi, this is my OS\n\n");
    shell();
}
