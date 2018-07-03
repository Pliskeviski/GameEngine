#include "String.h"

pl::string::string(const char* string) : s_size(0) {
	inMemory = new unsigned char;
	*inMemory = 1;
	s_size = strlen(string);
	s_content = new char[s_size + 1];
	
	memcpy(s_content, string, s_size + 1);
	s_content[s_size] = '\0';
}

pl::string::string() : s_size(0) {
	inMemory = new unsigned char;
	s_content = NULL;
}

pl::string::~string() {
	if (*inMemory)
		delete[] s_content;
	
	*inMemory = 0;
}

char& pl::string::operator[](unsigned int index) {
	assert(*inMemory);
	return s_content[index];
}

void pl::string::append(const string& string) {
	assert(*inMemory);
	char* str = new char[this->s_size + string.s_size + 1];
	memcpy(str, s_content, this->s_size);

	for (unsigned int i = 0; i < string.s_size; i++)
		str[this->s_size + i] = string.s_content[i];
	str[this->s_size + string.s_size] = '\0';
	delete[] s_content;
	this->s_content = str;
	this->s_size = this->s_size + string.s_size;
}

void pl::string::append(const char* string) {
	assert(*inMemory);
	char* str = new char[this->s_size + strlen(string) + 1];
	memcpy(str, this->s_content, this->s_size);

	for (unsigned int i = 0; i < strlen(string); i++)
		str[this->s_size + i] = string[i];
	str[this->s_size + strlen(string)] = '\0';
	delete[] s_content;
	this->s_content = str;
	this->s_size = this->s_size + strlen(string);
}

const char* pl::string::c_str() {
	return (const char*)this->s_content;
}

unsigned int pl::string::size() {
	return this->s_size;
}


std::ostream& pl::operator<<(std::ostream& stream, const pl::string& string) {
	stream << string.s_content;
	return stream;
}

void pl::string::Copy(string& dest, const string& source) {
	dest = pl::string();
	dest.s_content = new char[source.s_size + 1];
	dest.s_size = source.s_size;
	memcpy(dest.s_content, source.s_content, source.s_size);
	dest.s_content[dest.s_size] = '\0';
	*dest.inMemory = 1;
}

pl::string pl::string::Copy(const string& source) {
	char* str = new char[source.s_size + 1];
	memcpy(str, source.s_content, source.s_size);
	str[source.s_size] = '\0';
	return pl::string(str);
}
