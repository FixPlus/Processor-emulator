in ax
in bx
in cx
call quad
jmp exit


#solves the ax2 + bx + c = 0 eq. ax for a, bx for b, cx for c. Answer returns using cx and dx

quad:
push ax
mul 4
mul cx
pop dx
push bx
mul bx
sub dx
pop dx
push 0
cmp dx
jb L2
push ax
push bx
push cx
call sq_root
pop cx
pop bx
pop ax
push bx
sub bx
sub bx
pop cx
push cx
add dx
push cx
sub dx
div 2
div ax
pop cx
div 2
div ax
pop dx
pop ax
jmp L3
L2:
push 0
pop cx
pop dx
L3:
ret


#calculate a sqrt of dx. returns answer in dx

sq_root:
push 0
cmp dx
je L1
L0:
add 1
pop bx
push bx
mul bx
cmp dx
pop cx
push bx
ja L0
L1:
pop dx
ret


exit:
out cx
out dx