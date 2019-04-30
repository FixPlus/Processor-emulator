#include "lexer.h"
#include <iostream>

const char* ops_arr[] = {"nop", "add", "sub", "mul", "div", "push", "pop", "jmp", "in", "out", "jz", "jnz", "je", "jne", "call", "ret", "cmp", "jbe", "jae", "jb", "ja"};
const char* rgs_arr[] = {"ax", "bx", "cx", "dx"};


token_t::token_t(){
	type = NUM_T;
	num = 0;
}
token_t::~token_t(){
	switch(type){
		case LABEL_REF_T:{
		}
		case LABEL_T:{
			name.~basic_string();
			break;
		}
	}
}
token_t::token_t(const struct token_t& t ){
  type = t.type;
  switch(type){
		case OP_T:{
			op = t.op;
			break;
		}
		case RG_T:{
		}
		case NUM_T:{
			num = t.num;
			break;
		}
		case LABEL_T:{
		}
		case LABEL_REF_T:{
			new (&name) auto(t.name);
		}
  }
}

struct token_t& token_t::operator=(const struct token_t& t ){
	type = t.type;
    switch(type){
		case OP_T:{
			op = t.op;
			break;
		}
		case RG_T:{
		}
		case NUM_T:{
			num = t.num;
			break;
		}
		case LABEL_T:{
		}
		case LABEL_REF_T:{
			new (&name) auto(t.name);
		}
    }
	return *this;
}




int Lexer::isSpaceSymbol(char c){
	return (c == ' ' || c == '\n' || c == '\t') ? 1:0; 
}

int Lexer::isLabelTok(std::string str){
	return (str.back() == ':') ? 1:0;
}

int Lexer::isLabelRefTok(std::string str){
	//TODO (отфильтровать русские буквы. В общем какая-то жопа)
	return 1;
}





enum token_type_t Lexer::getStrTokType(std::string str){
	if(getTokReg(str) != -1)
		return RG_T;
	if(isdigit(str[0]))
		return NUM_T;
	if(getStrTokOp(str) != UNKNOWN_OP)
		return OP_T;
	if(isLabelTok(str))
		return LABEL_T;
	if(isLabelRefTok(str))
		return LABEL_REF_T;
	
	return UNKNOWN_T;
}	

int Lexer::getTokReg(std::string str){
	for(int i = 0; i < REG_COUNT; i++)
		if(str == rgs_arr[i])
			return i;
		
	return -1;
}


enum operation_t Lexer::getStrTokOp(std::string str){
	for(int i = 0; i < LASTOP; i++)
		if(!strcmp(str.c_str(), ops_arr[i]))
			return (enum operation_t)i;		
	return UNKNOWN_OP;
}

int Lexer::onlyDigits(std::string str){
	for(int i = 0; i < str.length(); i++)
		if(!isdigit(str[i]))
			return 0;
	
	return 1;	
}


void Lexer::cancelParse(){
	tokArray.clear();
	std::cout << "Lexer stopped!" << std::endl;
}





Lexer::Lexer(std::string source): tokArray(10){
	
	char* buf = (char*)calloc(source.length() + 1, sizeof(char));
	buf = strcpy(buf, source.c_str());
	tokArray.clear();
	
	for(int i = 0; i < source.length(); i++)
		if(isSpaceSymbol(buf[i]))
			buf[i] = '\0';
		else
			if(buf[i] == '#'){
				for(;buf[i] != '\n' && i < source.length();i++)
					buf[i] = '\0';
				
				if(i < source.length())
					buf[i] = '\0';
			}
	
	std::string tmp = "";
	char* ptr = buf;
	while(ptr - buf < source.length()){
		tmp = ptr;
		if(tmp.length() == 0){
			ptr++;
			continue;
		}
		
		struct token_t temp_tok;
		temp_tok.type  = getStrTokType(tmp);
		switch(temp_tok.type){
			case OP_T:{
				temp_tok.op = getStrTokOp(tmp);
				break;
			}
			case RG_T:{
				temp_tok.num = getTokReg(tmp);
				break;
			}
			case NUM_T:{
				if(!onlyDigits(tmp)){
					std::cout << "Wrong numeral constant: " << tmp << std::endl;
					free(buf);
					cancelParse();
					return;
				}
				temp_tok.num = stoi(tmp);
				break;
			}
			case LABEL_T:{
				tmp.pop_back();
				new (&temp_tok.name) auto(tmp);
				break;
			}
			case LABEL_REF_T:{
				new (&temp_tok.name) auto(tmp);
				break;
			}
			case UNKNOWN_T:{
				std::cout << "Unknown token: " << tmp << std::endl;
				free(buf);
				cancelParse();
				return;
			}
		}
		
		ptr = strchr(ptr,'\0') + 1;
		tokArray.push_back(temp_tok);
	}
	
	free(buf);
}


Lexer::~Lexer(){



}


std::vector<struct token_t> Lexer::getTokArray(){
	return tokArray;
}

void Lexer::printToken(struct token_t token){
	switch(token.type){
		case OP_T:{
			std::cout << ops_arr[(int)token.op];
			break;
		}
		case LABEL_T:{
			std::cout << token.name << " (label) ";
			break;
		}
		case LABEL_REF_T:{
			std::cout << token.name << " (label reference)";
			break;
		}
		case NUM_T:{
			std::cout << token.num << " (numeric constant)"; 
			break;
		}
		case RG_T:{
			std::cout << rgs_arr[token.num] << " (register)";
			break;
		}
	}
}

void Lexer::dumpTokArray(){
	
	for(int i = 0; i < tokArray.size(); i++)
		switch(tokArray[i].type){
			case OP_T:{
				switch(tokArray[i].op){
					case NOP: std::cout << "NOP "; break;
					case ADD: std::cout << "ADD "; break;
					case SUB: std::cout << "SUB "; break;
					case MUL: std::cout << "MUL "; break;
					case DIV: std::cout << "DIV "; break;
					case PUSH: std::cout << "PUSH "; break;
					case POP: std::cout << "POP "; break;
					case JMP: std::cout << "JMP "; break;
					case IN: std::cout << "IN "; break;
					case OUT: std::cout << "OUT "; break;
					default: std::cout << "**Unknown op** "; break;
				}
				break;
			}
			case RG_T:{
				std::cout << rgs_arr[tokArray[i].num] << " ";
				break;
			}
			case NUM_T:{
				std::cout << "NCONST:" << tokArray[i].num << " ";
				break;
			}
			case LABEL_T:{
				std::cout << "LABEL:" << tokArray[i].name << " ";
				break;
			}
			case LABEL_REF_T:{
				std::cout << "LABEL_REF:" << tokArray[i].name << " ";
				break;
			}
			default:{
				std::cout << "**unknown token** ";
				break;
			}
		}
}

