 In this level, we have a `setuid` file `level0`.

 >level0@RainFall:~$ ./level0  
 > Segmentation fault (core dumped)

 >level0@RainFall:~$ ./level0 abcdefg   
 > No !

When we `gdb` the file and we disass the main, we notice that a call to `atoi` function is made. The return value is probably put in `EAX` register.  
Then, this register is compared with the value 423 :    
` 0x08048ed9 <+25>:	cmp    $0x1a7,%eax`

We try to put 423 as an argument to the binary :
> level0@RainFall:~\$ ./level0 423 
> $ 

A prompt is now opened.

>$ whoami   
>level1

We are now user `level1`

>$ cat /home/user/level1/.pass   
>1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

This is the correct password for `su level1`