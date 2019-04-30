#include "LabelTable.h"
#include <iostream>

using namespace std;

int main(){
	
	LabelTable table(100);
	
	string str1 = "Lol yep ;)";
	string str2 = "MEM";
	table.addElement(str1, 45);
	table.addElement(str2, 56);
	
	cout << str1 << " : " << table.getElement(str1) << endl << str2 << " : " << table.getElement(str2) << endl;
	

}