#include <stdint.h>
 
void n(void)
{
    char *format;
    
    fgets(&format, 0x200, _stdin);
    printf(&format);
    exit(1);
    n(&stack0xfffffffc);
    return;
}

void o (void) {
    system ("/bin/sh");
    return exit (1);
}

void main(void)
{
    n();
    return;
}