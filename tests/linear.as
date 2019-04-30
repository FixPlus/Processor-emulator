in ax
in bx
call linear
jmp exit



linear:
push 0
cmp ax
je L0
sub bx
div ax
pop cx
ret
L0:
pop cx
ret

exit:
out cx