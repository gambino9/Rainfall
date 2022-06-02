
// WARNING: Variable defined which should be unmapped: var_8h

undefined4 main(char **argv, char **envp)
{
    undefined4 uVar1;
    int32_t iVar2;
    undefined4 *puVar3;
    uint8_t uVar4;
    undefined4 auStack152 [16];
    undefined uStack87;
    undefined auStack86 [66];
    int32_t iStack20;
    int32_t var_8h;
    
    uVar4 = 0;
    iStack20 = fopen("/home/user/end/.pass", 0x80486f0);
    puVar3 = auStack152;
    for (iVar2 = 0x21; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + (uint32_t)uVar4 * -2 + 1;
    }
    if ((iStack20 == 0) || (argv != (char **)0x2)) {
        uVar1 = 0xffffffff;
    } else {
        fread(auStack152, 1, 0x42, iStack20);
        uStack87 = 0;
        iVar2 = atoi(envp[1]);
        *(undefined *)((int32_t)auStack152 + iVar2) = 0;
        fread(auStack86, 1, 0x41, iStack20);
        fclose(iStack20);
        iVar2 = strcmp(auStack152, envp[1]);
        if (iVar2 == 0) {
            execl("/bin/sh", 0x8048707, 0);
        } else {
            puts(auStack86);
        }
        uVar1 = 0;
    }
    return uVar1;
}



/* jsdec pseudo code output */
/* /home/lamia/bonus3 @ 0x80484f4 */
#include <stdint.h>
 
int32_t main (char ** argv, char ** envp) {
    int32_t var_8h;
    const char * size;
    size_t nmemb;
    FILE * stream;
    const char * ptr;
    int32_t var_59h;
    FILE * var_9ch;
    edx = 0x80486f0;
    eax = "/home/user/end/.pass";
    eax = fopen (eax, edx);
    *((esp + 0x9c)) = eax;
    ebx = esp + 0x18;
    eax = 0;
    edx = 0x21;
    edi = ebx;
    ecx = edx;
    memset (edi, eax, ecx);
    if (*((esp + 0x9c)) != 0) {
        if (*((ebp + 8)) == 2) {
            goto label_0;
        }
    }
    eax = 0xffffffff;
    goto label_1;
label_0:
    eax = esp + 0x18;
    edx = *((esp + 0x9c));
    fread (edx, 1, 0x42);
    eax = *((ebp + 0xc));
    eax += 4;
    eax = *(eax);
    atoi (0);
    *((esp + eax + 0x18)) = 0;
    eax = esp + 0x18;
    edx = eax + 0x42;
    eax = *((esp + 0x9c));
    fread (eax, 1, 0x41);
    eax = *((esp + 0x9c));
    fclose (eax);
    eax = *((ebp + 0xc));
    eax += 4;
    eax = *(eax);
    eax = esp + 0x18;
    eax = strcmp (eax, eax);
    if (eax == 0) {
        execl ("/bin/sh", 0x8048707, 0);
    } else {
        eax = esp + 0x18;
        eax += 0x42;
        puts (eax);
    }
    eax = 0;
label_1:
    esp = ebp - 8;
    return eax;
}
