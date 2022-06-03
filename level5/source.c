#include <stdint.h>
 
void n(void)
{
    char *buf;
    
    fgets(&buf, 512, _stdin);
    printf(&buf);
    exit(1);
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