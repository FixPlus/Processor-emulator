#include "stack.h"


Stack::Stack() :top(NULL), size_int(0){
}
Stack::~Stack(){
	clear();
}

void Stack::clear(){
	while(!empty())
		pop();	
}


void Stack::push(int data){
	struct node_t* temp = top;
	top = new struct node_t;
	top->data = data;
	if(size_int != 0)
		top->next = temp;
	else 
		top->next = NULL;
	size_int++;
}

int  Stack::pop(){
	if(size_int == 0)
		return 0;
	
	struct node_t* temp = top->next;
	int ret = top->data;
	delete top;
	top = temp;
	size_int--;
	return ret;
}

bool Stack::empty(){
	return size_int == 0 ? 1:0;
}

int  Stack::size(){
	return size_int;
}
