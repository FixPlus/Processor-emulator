#include "Parser.h"
#include "LabelTable.h"
#include <iostream>

//                            NOP   ADD   SUB   MUL   DIV  PUSH	 POP    JMP    IN   OUT    JZ   JNZ    JE   JNE  CALL   RET  CMP    JBE   JAE    JB    JA
unsigned char op_codes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x20, 0x21, 0x22, 0x23, 0x24};
//                            AX    BX    CX    DX
unsigned char rg_codes[] = {0x10, 0x11, 0x12, 0x13};

bool Parser::isJmp(enum operation_t op){
	return (op == JMP || op == JZ || op == JNZ || op == JE || op == JNE || op == JBE || op == JAE || op == JB || op == JA) ? 1 : 0;
}

enum expr_type Parser::getTypeExpect(enum operation_t op){
	return (isJmp(op) || op == CALL) ? LB_REF : (op == NOP || op == RET) ? NO_T : (op == POP) ? RG_ONLY : RG_NUM;
}	

Parser::Parser(Lexer ini_lex): lex(ini_lex){
}
Parser::~Parser(){

}

std::string Parser::parse(){
	std::string ret = "";
	LabelTable table(100);
	std::vector<struct token_t> tokArr = lex.getTokArray();
	if(tokArr.empty())
		return ret;
	int shift = 0;
	for(int i = 0; i < tokArr.size(); i++)
		if(tokArr[i].type == LABEL_T){
			shift--;
			int succes = table.addElement(tokArr[i].name, i + 1 + shift);
			if(!succes){
				std::cout << "Label \"" << tokArr[i].name << "\" appeared twice!" << std::endl;
				return ret;
			}
		}
	
	int i = 0;
	while(i < tokArr.size()){
		switch(tokArr[i].type){
			case OP_T:{
				ret += op_codes[(int)(tokArr[i].op)];
				switch(getTypeExpect(tokArr[i].op)){
					case RG_NUM:{
						i++;
						switch(tokArr[i].type){
							case RG_T:{
								ret += rg_codes[tokArr[i].num];
								i++;
								break;
							}
							case NUM_T:{
								if(tokArr[i].num > 127 || tokArr[i].num < 0){
									std::cout << "Numeric constant " << tokArr[i].num << " is out of boundaries (0 to 127)" << std::endl;
									ret = "";
									return ret;
								}
								unsigned char mask_code = 0x80;
								mask_code += tokArr[i].num;
								ret += mask_code;
								i++;
								break;
							}
							default:{
								std::cout << "Unexpected token: "; lex.printToken(tokArr[i]);
								std::cout << ". Expected register or numeric constant!" << std::endl;
								ret = "";
								return ret;
							}
						}
						break;
					}
					case RG_ONLY:{
						i++;
						if(tokArr[i].type != RG_T){
							std::cout << "Unexpected token: "; lex.printToken(tokArr[i]);
							std::cout << ". Expected register!" << std::endl;
							ret = "";
							return ret;
						}
						ret += rg_codes[tokArr[i].num];
						i++;
						break;
					}
					case LB_REF:{
						i++;
						if(tokArr[i].type != LABEL_REF_T){
							std::cout << "Unexpected token: "; lex.printToken(tokArr[i]);
							std::cout << ". Expected label reference!" << std::endl;
							ret = "";
							return ret;
						}
						int label_ref = table.getElement(tokArr[i].name);
						if(label_ref == -1){
							std::cout << "Undefined reference to \"" << tokArr[i].name << "\"!\n";
							ret = "";
							return ret;
						}
						if(label_ref > 255){
							std::cout << "Address reference is too big: " << label_ref << " > 255\n";
							ret = "";
							return ret;
						}
						unsigned char code_ref = (unsigned char)label_ref;
						ret += code_ref;
						i++;
						break;
					}
					case NO_T:{
						i++; break;
					}
				}
				break;
			}
			case LABEL_T: i++; break;
			default:{
				std::cout << "Unexpected token: "; lex.printToken(tokArr[i]); std::cout<< "!" << std::endl;
				ret = "";
				return ret;
			}
		}
	}
	
	
	std::cout << "Parsed succesful!" << std::endl;
	return ret;
}

void Parser::setLex(Lexer new_lex){
	lex = new_lex;
}
Lexer Parser::getLex(){
	return lex;
}
