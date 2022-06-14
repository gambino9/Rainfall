void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return;
}

void m(void)
{
    puts("Nope");
    return;
}


int main(int argc, char **argv)
{
    string = malloc(0x40);
    func = (code **)malloc(4);
    *func = m;
    strcpy(string, argv[1]);
    func();
    return 0;
}