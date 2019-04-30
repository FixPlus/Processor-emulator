#include "LabelTable.h"



int LabelTable::hashFunc(std::string name){
	unsigned id = 7;
	for(int i = 0; i < name.length(); i++)
		id += (1351*name[i] - 123)%599;
	
	return id%size;
}



LabelTable::LabelTable(int ini_size){
	table = new struct label_node_t*[ini_size];
	for(int i = 0; i < ini_size; i++)
		table[i] = NULL;
	size = ini_size;
}
LabelTable::~LabelTable(){
	struct label_node_t* temp, *new_next;
	for(int i = 0; i < size;i++){
		temp = table[i];
		while(temp){
			new_next = temp->next;
			delete temp;
			temp = new_next;
		}
	}
	delete[] table;
}

int LabelTable::addElement(std::string name, int data){
	int id = hashFunc(name);
	struct label_node_t* temp = table[id];
	if(!temp){
		temp = new struct label_node_t;
		temp->next = NULL;
		temp->name = name;
		temp->data = data;
		table[id] = temp;
		return 1;
	}
	
	
	while(temp->next){
		if(temp->name == name)
			return 0;
		temp = temp->next;
	}

	if(temp->name == name)
		return 0;
	
	temp->next = new struct label_node_t;
	temp = temp->next;
	temp->name = name;
	temp->data = data;
	
	return 1;
}
int LabelTable::getElement(std::string name){
	int id = hashFunc(name);
	struct label_node_t* temp = table[id];
	while(temp){
		if(temp->name == name)
			return temp->data;
		temp = temp->next;
	}
	return -1;
}