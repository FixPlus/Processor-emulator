in ax
call fib
jmp L1



fib:
push ax
push 1
pop bx
push bx
L0:
add bx
push bx
pop cx
pop bx
out bx
sub 1
cmp 0
push cx
jne L0
pop dx
pop dx
ret
L1: