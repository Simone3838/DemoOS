; boot/boot.asm
BITS 16
ORG 0x7C00

start:
    ; Set up stack
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Load the kernel
    mov si, hello_msg
    call print_string

    ; Hang
    jmp $

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

hello_msg db 'Loading DemoOS...', 0

times 510-($-$$) db 0
dw 0xAA55
