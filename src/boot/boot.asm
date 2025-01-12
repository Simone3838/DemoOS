; boot/boot.asm
BITS 32
ORG 0x100000

; Multiboot header
multiboot_header:
    dd 0x1BADB002   ; magic number
    dd 0x00010003   ; flags
    dd - (0x1BADB002 + 0x00010003) ; checksum

; Entry point for the bootloader
start:
    ; Set up the stack
    mov esp, 0x9C000

    ; Clear the screen
    call clear_screen

    ; Print a message
    mov si, welcome_msg
    call print_string

    ; Jump to the kernel's entry point
    call kernel_main

hang:
    hlt
    jmp hang

clear_screen:
    mov edi, 0xB8000
    mov ecx, 2000
    mov eax, 0x07200720
    rep stosd
    ret

print_string:
    mov ah, 0x0E
.repeat:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .repeat
.done:
    ret

welcome_msg db 'Welcome to DemoOS', 0

times 510-($-$$) db 0
dw 0xAA55
