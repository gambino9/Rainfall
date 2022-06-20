void m(void)
{
    printf("%s - %d\n", flag, time(0));
    return;
}

int main(int argc,char **argv)
{
    str1 = (char *)malloc(8);
    str2 = (char *)malloc(8);
    strcpy(str1, argv[1]);
    strcpy(str2, argv[2]);
    file = fopen("/home/user/level8/.pass");
    fgets(flag, 68, file);
    puts("~~");
    return 0;
}