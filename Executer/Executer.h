#pragma once
#include "stack.h"
#include <string>
#include <iostream>


//block from lexer

enum operation_t { NOP, ADD, SUB, MUL, DIV, PUSH, POP, JMP, IN, OUT, JZ, JNZ, JE, JNE, CALL, RET, CMP, JBE, JAE, JB, JA, LASTOP, UNKNOWN_OP};

enum {INIT_SIZE = 10};
enum {REG_COUNT = 4};


extern const char* rgs_arr[];


enum {SUCCES = 0};
enum {FAILED = 1};
enum {FLAG_REG = REG_COUNT + 2};



class Executer{
	private:
	
	int reg[REG_COUNT + 3];
	Stack stack;
	int cursor;
	
	void printStackError();
	void printWrongArgumentErr();
	
	int calc(unsigned char arg, enum operation_t op);
	int iter_stack(unsigned char arg, enum operation_t op);
	int jump(unsigned char arg, enum operation_t op);
	int iter_io(unsigned char arg, enum operation_t op);
	int cmp(unsigned char arg);
	int call(unsigned char arg);
	int ret();
	
	enum operation_t opFromCode(unsigned char code);
	int getReg(unsigned char code);
	int isNum(unsigned char code);
	int getNum(unsigned char code);
	
	public:
	
	Executer();
	~Executer();
	
	void execute(std::string code);


};