# Processor-emulator

use "asm.exe tests\file.as tests\file.ex" to make bytecode file from assembler code
use "Executer.exe tests\file.ex" to execute bytecode.


Registers: ax bx cx dx

Commands:

add arg : pops element from stack, then adds       it by arg and push the result to stack
sub arg : pops element from stack, then subtracts  it by arg and push the result to stack
mul arg : pops element from stack, then multiplies it by arg and push the result to stack
div arg : pops element from stack, then divides    it by arg and push the result to stack

pop arg(only reg), push arg(reg or num const) - work with stack
cmp arg - compares the top stack element and arg (-1 - less; 0 - equal; 1 - more). Puts the result in FLAG_REG
jmp\je\jne\ja\jna\jb\jba arg - jumps using arg and FLAG_REG

in arg(reg only) - ask user to type in arg
out arg(reg or num) - print arg in stdout

call arg - calls function named as arg(it also push the ret address in stack)
ret - pops the ret address and jumps there
