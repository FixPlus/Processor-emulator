#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>


enum {IO_Exception = 4};

class FileManager{
	private:
	
	std::ifstream in;
	std::ofstream out;
	
	public:
	
	FileManager();
	FileManager(std::string infn, std::string outfn);
	~FileManager();
	
		
	void setInput(std::string newIn);
	void setOutput(std::string newOut);
	
	std::string getStringFromFile();
	void saveStrToFile(std::string str);
	
};