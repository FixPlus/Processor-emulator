#pragma once

#include <string>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "FileManager.h"

enum token_type_t { OP_T, RG_T, NUM_T, LABEL_T, LABEL_REF_T, UNKNOWN_T};

enum operation_t { NOP, ADD, SUB, MUL, DIV, PUSH, POP, JMP, IN, OUT, JZ, JNZ, JE, JNE, CALL, RET, CMP, JBE, JAE, JB, JA, LASTOP, UNKNOWN_OP};

enum {INIT_SIZE = 10};
enum {REG_COUNT = 4};


extern const char* ops_arr[];
extern const char* rgs_arr[];

struct token_t {
  enum token_type_t type;
  union {
    enum operation_t op;
	std::string name;  
	int num;
  };
  token_t();
  ~token_t();
  token_t(const struct token_t& t );
  struct token_t& operator=(const struct token_t& t);
}; 

class Lexer{
	private:
	std::vector<struct token_t> tokArray;
	
	int isSpaceSymbol(char c);
	int getTokReg(std::string str);
	int onlyDigits(std::string str);
	int isLabelTok(std::string str);
	int isLabelRefTok(std::string str);
	enum token_type_t getStrTokType(std::string str); 
	enum operation_t getStrTokOp(std::string str);
	void cancelParse();
	public:
	
	Lexer(std::string source);
	~Lexer();
	
	std::vector<struct token_t> getTokArray();
	
	void printToken(struct token_t token);
	void dumpTokArray();

};