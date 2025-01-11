// kernel/kernel.c
void main() {
    char *video_memory = (char *)0xB8000;
    const char *message = "Hi, this is my OS";
    int i = 0;
    
    // Green text on black background (color code: 0x02)
    while (message[i] != 0) {
        video_memory[i * 2] = message[i];
        video_memory[i * 2 + 1] = 0x02; // Green on black background
        i++;
    }

    while (1) {}
}
