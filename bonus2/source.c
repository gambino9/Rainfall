
int main(int argc, char **argv)
{
    char buffer[72];
    char *env;
    int language = 0;

    if (argc != 3)
        return 1;
    
    strncpy(buffer,argv[1],40);
    strncpy(&buffer[40],argv[2],32);

    env = getenv("LANG");
    if (memcmp(env, "fi", 2) == 0)
        language = 1;
    else if (memcmp(env, "nl", 2) == 0)
        language = 2;
    greetuser(buffer, language);
    return 0;
}

void greetuser(char* user, int language)
{
    char buffer[64];
    if (language == 1) 
        strcpy(buffer, "Hyvää päivää ");
    else if (language == 2)
        strcpy(buffer, "Goedemiddag! ");
    else
        strcpy(buffer, "Hello ");
    strcat(buffer, user);
    puts(buffer);
}