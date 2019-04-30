#pragma once

#include <cstddef>


struct node_t{
	struct node_t* next;
	int data;
};


class Stack{
	private:
	
	int size_int;
	struct node_t* top;
	
	public:
	
	Stack();
	~Stack();
	
	void clear();
	
	void push(int data);
	int pop();
	
	bool empty();
	int  size();

};