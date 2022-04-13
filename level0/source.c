#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

int main(int argc, char **argv)
{
    int ret = atoi(argv[1]);
    char **sh;
    uid_t real_user;
    git_t group_user;
    char *arg[2];

    if (423 == ret)
    {
        sh = strdup("/bin/sh");

        // get group user
        group_user = getegid()
        // get real user ID of calling process
        real_user = geteuid()

        // setresuid, setresgid - set real, effective and saved user or group ID 
        setresgid(group_user, group_user, group_user);
        setresuid(real_user, real_user, real_user);

        // execve() executes the program pointed to by filename.
        execv(sh, NULL);
    }
    else
    {
        fwrite("No !\n", 1, 5, stderr);
    }
    return (0);
}