void m(void)
{
    printf("%s - %d\n", pass, time(0));
    return;
}

int main(int argc,char **argv)
{
    undefined4 *puVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    
    str1 = (char *)malloc(8);
    *str1 = 1;
    str2 = (char *)malloc(8);
    *str2 = 2;
    strcpy(str1[1], argv[1]);
    strcpy(str2[1], argv[2]);
    file = fopen("/home/user/level8/.pass");
    fgets(pass, 68, file);
    puts("~~");
    return 0;
}