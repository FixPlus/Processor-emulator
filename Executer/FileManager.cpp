#include "FileManager.h"
#include <iostream>

FileManager::FileManager(){
	
}

FileManager::FileManager(std::string infn, std::string outfn) : in(infn, std::ios::in), out(outfn, std::ios::out){
	if(!in.good() || !out.good())
		throw IO_Exception;
}
FileManager::~FileManager(){
	in.close();
	out.close();
}


void FileManager::setInput(std::string newIn){
	in.open(newIn, std::ios::in);
	if(!in.good())
		throw IO_Exception;
}
void FileManager::setOutput(std::string newOut){
	out.open(newOut, std::ios::out);
	if(!out.good())
		throw IO_Exception;
}

std::string FileManager::getStringFromFile(){
	std::string ret;
	std::string tmp;
	while(!in.eof()){
		getline(in, tmp);
		if(tmp.length() != 0)
			ret = ret + tmp + "\n";
	}
	return ret;
}

void FileManager::saveStrToFile(std::string str){
	out.write(str.c_str(), str.length());
}

