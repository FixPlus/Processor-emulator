#pragma once
#include <string>


struct label_node_t{
	struct label_node_t* next;
	int data;
	std::string name;
};

class LabelTable{
	private:
	
	struct label_node_t** table;
	int size;
	int hashFunc(std::string name);
	
	public:
	
	LabelTable(int ini_size);
	~LabelTable();
	
	int addElement(std::string name, int data);
	int getElement(std::string name);
	
};