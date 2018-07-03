#include <iostream>

#include <fstream>

#include "stringLoader.hpp"

#include "..\\Pliskeviski\String.h"

pl::string load(const char* path) {
	std::fstream stream(path, std::fstream::in);
	if (!stream) {
		std::cerr << "Failed to load the filepath " << path << "." << std::endl;
		getchar();
	}

	std::string finalString;
	
	std::getline(stream, finalString, '\0');

	stream.close();
	return pl::string(finalString.c_str());
}