#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void v(void)
{
    char    *format;
    int     m;
    
    fgets(&format, 0x200, _stdin);
    printf(&format);
    if (m == 0x40) {
        fwrite("Wait what?!\n", 1, 0xc, _stdout);
        system("/bin/sh");
    }
    return;
}

void main(void)
{
    v();
    return;
}