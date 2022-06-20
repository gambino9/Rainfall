
char* p(char *dest, char *s)
{
    char *buffer;
    
    puts(s);
    read(0, &buffer, 4096);
    *strchr(&buffer, '\n') = 0;
    return strncpy(dest, buffer, 20);
}


void pp(char *dest)
{
    char str1[20];
    char str2[20];
    int len = 0;

    p(str1, " - ");
    p(str2, " - ");
    strcpy(dest, str1);
    len = strlen(dest);
    dest[len] = ' ';
    dest[len + 1] = 0;
    
    return strcat(dest,str2);
}


int main(int argc, char **argv)
{
    char buffer [42];
    pp(buffer);
    puts(buffer);
    return 0;
}