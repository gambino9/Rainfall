
// WARNING: Variable defined which should be unmapped: var_8h

int main(int argc, char **argv)
{
    char* buffer1;
    char* buffer2;
    int nb;

    file = fopen("/home/user/end/.pass", "r");
    bzero(buffer1);
    if ((!file) || (argc != 2))
        return -1
    fread(buffer1, 1, 66, file);
    int nb = atoi(argv[1]);
    buffer1[nb] = 0;
    fread(buffer2[66], 1, 65, file);
    fclose(file);
    int isSame = strcmp(buffer1, argv[1]);
    if (isSame == 0) 
        execl("/bin/sh", "sh", 0);
    else 
        puts(buffer2);

    return 0;
}
