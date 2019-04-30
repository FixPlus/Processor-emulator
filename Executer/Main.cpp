#include "FileManager.h"
#include "Executer.h"
#include <iostream>

//Executer of asm compiled files 
//                 v 1.0.0
//Coded by BUSHEV DMITRY April 2019

using namespace std;


int main(int argc, char** argv){
	if(argc != 2){
		cout << "Usage: <filename>" << endl;
		return 0;
	}
	
	std::string fin  = argv[1];
	
	FileManager fileManager;
	
	try{
		fileManager.setInput(fin);
	}
	catch(int e){
		if(e == IO_Exception){
			std::cout << "Cannot open input file!" << std::endl;
			return 1;
		}
	}
	
	std::string code = fileManager.getStringFromFile();
	
	Executer executer;
	executer.execute(code);
	
	std::cout << "Press enter to quit...\n";
	std::cin.clear();
	std::cin.get();
	
}