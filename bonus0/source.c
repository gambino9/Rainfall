
void p(char *dest, char *s)
{
    undefined *puVar1;
    char *var_1008h;
    
    puts(s);
    read(0, &var_1008h, 0x1000);
    puVar1 = (undefined *)strchr(&var_1008h, 10);
    *puVar1 = 0;
    strncpy(dest, &var_1008h, 0x14);
    return;
}


void pp(char *dest)
{
    char cVar1;
    uint32_t uVar2;
    char *pcVar3;
    uint8_t uVar4;
    int32_t var_3ch;
    int32_t var_30h;
    int32_t var_1ch;
    
    uVar4 = 0;
    p((char *)&var_30h, " - ");
    p((char *)&var_1ch, " - ");
    strcpy(dest, &var_30h);
    uVar2 = 0xffffffff;
    pcVar3 = dest;
    do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + (uint32_t)uVar4 * -2 + 1;
    } while (cVar1 != '\0');
    *(undefined2 *)(dest + (~uVar2 - 1)) = *(undefined2 *)0x80486a4;
    strcat(dest, &var_1ch);
    return;
}


undefined4 main(void)
{
    char acStack58 [54];
    
    pp(acStack58);
    puts(acStack58);
    return 0;
}