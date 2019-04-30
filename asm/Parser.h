#pragma once
#include "Lexer.h"
#include <string>


extern unsigned char op_codes[];
extern unsigned char rg_codes[];

enum expr_type { RG_ONLY, RG_NUM, LB_REF, NO_T};

class Parser{
	private:
	
	Lexer lex;
	bool isJmp(enum operation_t op);
	enum expr_type getTypeExpect(enum operation_t op); 
	
	public:
	
	Parser(Lexer ini_lex);
	~Parser();
	
	std::string parse();
	
	void setLex(Lexer new_lex);
	Lexer getLex();
	
};