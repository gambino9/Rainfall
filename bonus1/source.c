
int main(int argc, char **argv)
{
    char buffer [40];
    int number;
    int returnValue;
    number = atoi(argv[1]);
    if (number < 10) {
        memcpy(buffer, argv[2], number * 4);
        if (number == 1464814662) {
            execl("/bin/sh", "sh", 0);
        }
        returnValue = 0;
    } else {
        returnValue = 1;
    }
    return returnValue;
}
