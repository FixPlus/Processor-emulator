#include "Executer.h"

const char* rgs_arr[] = {"ax", "bx", "cx", "dx"};

//                            NOP   ADD   SUB   MUL   DIV  PUSH	 POP    JMP    IN   OUT    JZ   JNZ    JE   JNE  CALL   RET	  CMP   JBE   JNA    JB    JA
unsigned char op_codes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x20, 0x21, 0x22, 0x23, 0x24};
//                            AX    BX    CX    DX
unsigned char rg_codes[] = {0x10, 0x11, 0x12, 0x13};



Executer::Executer() : cursor(0){
}
Executer::~Executer(){
	stack.clear();
}

int Executer::getReg(unsigned char code){
	for(int i = 0; i < REG_COUNT; i++)
		if(code == rg_codes[i])
			return i;
		
	return -1;	
}

int Executer::isNum(unsigned char code){
	return code & (1u << 7) ? 1:0;
}
int Executer::getNum(unsigned char code){
	return code & 0x7F;
}

void Executer::printStackError(){
	std::cout << "Stack failed!" << std::endl;
}

void Executer::printWrongArgumentErr(){
	std::cout << "Wrong argument!" << std::endl;
}


int Executer::iter_stack(unsigned char arg, enum operation_t op){
	switch(op){
		case PUSH:{
			int num = getReg(arg);
			if(num != -1)
				num = reg[num];
			else
				if(isNum(arg))
					num = getNum(arg);
				else{
					printWrongArgumentErr();
					return FAILED;
				}
			stack.push(num);
			break;
		}
		case POP:{
			if(stack.empty()){
				printStackError();
				return FAILED;
			}
			int id = getReg(arg);
			if(id == -1)
				return FAILED;
			reg[id] = stack.pop();
			break;
		}
		default: return FAILED;
	}
	return SUCCES;
}

int Executer::cmp(unsigned char arg){
	if(stack.empty()){
		printStackError();
		return FAILED;
	}
	
	int num1 = getReg(arg);
	if(num1 != -1)
		num1 = reg[num1];
	else
		if(isNum(arg))
			num1 = getNum(arg);
		else{
			printWrongArgumentErr();
			return FAILED;
		}
	
	int num2 = stack.pop();
	
	reg[FLAG_REG] = (num1 == num2) ? 0: (num1 > num2) ? 1 : -1;
	stack.push(num2);
	return SUCCES;
}


int Executer::calc(unsigned char arg, enum operation_t op){
	if(stack.empty())
		return FAILED;
	
	int num = getReg(arg);
	if(num != -1)
		num = reg[num];
	else
		if(isNum(arg))
			num = getNum(arg);
		else{
			printWrongArgumentErr();
			return FAILED;
		}
	
	int temp;
	temp = stack.pop();
	
	switch(op){
		case ADD: temp = temp + num; break;
		case SUB: temp = temp - num; break;
		case MUL: temp = temp * num; break;
		case DIV:{
			if(num == 0)
				return FAILED;
			temp = temp / num; 
			break;
		}
		default: return FAILED;
	}
	stack.push(temp);
	return SUCCES;
}

int Executer::call(unsigned char arg){
	cursor++;
	stack.push(cursor);
	cursor = arg;
	return SUCCES;
}
int Executer::ret(){
	if(stack.empty()){
		printStackError();
		return FAILED;
	}
	cursor = stack.pop();
	return SUCCES;
}


int Executer::jump(unsigned char arg, enum operation_t op){
	bool flag = false;
	switch(op){
		case JZ:{
			break;
		}
		case JNZ:{
			break;
		}
		case JBE:{
			if(reg[FLAG_REG] <= 0)
				flag = true;
			break;
		}
		case JAE:{
			if(reg[FLAG_REG] >= 0)
				flag = true;
			break;
		}
		case JB:{
			if(reg[FLAG_REG] < 0)
				flag = true;
			break;
		}
		case JA:{
			if(reg[FLAG_REG] > 0)
				flag = true;
			break;
		}
		case JE:{
			if(reg[FLAG_REG] == 0)
				flag = true;
			break;
		}
		case JNE:{
			if(reg[FLAG_REG] != 0)
				flag = true;
			break;
		}
		case JMP:{
			flag = true;
			break;
		}
		default: return FAILED;
	}
	if(flag)
		cursor = arg;
	else
		cursor++;
	return SUCCES;
}

int Executer::iter_io(unsigned char arg, enum operation_t op){
	int id = getReg(arg);
	if(id == -1)
		return FAILED;
	switch(op){
		case IN:{
			std::cout << "Enter " << rgs_arr[id] << ":" << std::endl; 
			std::cin >> reg[id];
			std::cin.clear();
			break;
		}
		case OUT:{
			std::cout << "Out: "<< reg[id] << std::endl;
			break;
		}
		default: return FAILED;
	}
	return SUCCES;
}



enum operation_t Executer::opFromCode(unsigned char code){
	for(int i = 0; i < LASTOP; i++)
		if(code == op_codes[i])
			return (enum operation_t)i;
		
	return UNKNOWN_OP;
}


void Executer::execute(std::string code){
	cursor = 0;
	while(cursor < code.length() - 1){
		unsigned char op = code[cursor];
		int stat = SUCCES;
		switch(opFromCode(op)){
			case NOP: cursor++; break;
			case ADD:{
				cursor++;
				stat = calc(code[cursor], ADD);
				cursor++;
				break;
			}
			case SUB:{
				cursor++;
				stat = calc(code[cursor], SUB);
				cursor++;
				break;
			}
			case MUL:{
				cursor++;
				stat = calc(code[cursor], MUL);
				cursor++;
				break;
			}
			case DIV:{
				cursor++;
				stat = calc(code[cursor], DIV);
				cursor++;
				break;
			}
			case CALL:{
				cursor++;
				stat = call(code[cursor]);
				break;
			}
			case RET:{
				stat = ret();
				break;
			}
			case PUSH:{
				cursor++;
				stat = iter_stack(code[cursor], PUSH);
				cursor++;
				break;
			}
			case POP:{
				cursor++;
				stat = iter_stack(code[cursor], POP);
				cursor++;
				break;
			}
			case JMP:{
				cursor++;
				stat = jump(code[cursor], JMP);
				break;
			}
			case CMP:{
				cursor++;
				stat = cmp(code[cursor]);
				cursor++;
				break;
			}
			case IN:{
				cursor++;
				stat = iter_io(code[cursor], IN);
				cursor++;
				break;
			}
			case OUT:{
				cursor++;
				stat = iter_io(code[cursor], OUT);
				cursor++;
				break;
			}
			case JZ:{
				cursor++;
				stat = jump(code[cursor], JZ);
				break;
			}
			case JNZ:{
				cursor++;
				stat = jump(code[cursor], JNZ);
				break;
			}
			case JE:{
				cursor++;
				stat = jump(code[cursor], JE);
				break;
			}
			case JNE:{
				cursor++;
				stat = jump(code[cursor], JNE);
				break;
			}
			case JBE:{
				cursor++;
				stat = jump(code[cursor], JBE);
				break;
			}	
			case JAE:{
				cursor++;
				stat = jump(code[cursor], JAE);
				break;
			}	
			case JB:{
				cursor++;
				stat = jump(code[cursor], JB);
				break;
			}	
			case JA:{
				cursor++;
				stat = jump(code[cursor], JA);
				break;
			}	
			default:{
				stat = FAILED;
			}
		}
		if(stat == FAILED){
			std::cout << "Procces stopped at " << cursor << "!" << std::endl;
			stack.clear();
			return;
		}
	}
	std::cout << "Done!" << std::endl;
	stack.clear();
}