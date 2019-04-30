#include "FileManager.h"
#include "lexer.h"
#include "Parser.h"
#include <iostream>


int main(int argc, char** argv){
	if(argc != 3){
		std::cout << "You should use: \"input filename\" \"output filename\""<<std::endl;
		return 0;
	}
	std::string fin  = argv[1];
	std::string fout = argv[2];
	
	FileManager fileManager;
	try{
		fileManager.setInput(fin);
		fileManager.setOutput(fout);
	}
	catch(int e){
		if(e == IO_Exception){
			std::cout << "Cannot open input or output file!" << std::endl;
			return 1;
		}
	}
	
	
	
	std::string filest = fileManager.getStringFromFile();
	Lexer lex(filest);
	//lex.dumpTokArray();
	Parser parser(lex);
	filest = parser.parse();
	fileManager.saveStrToFile(filest);
	return 0; 
}