#pragma once
#include <iostream>
#include <string>
#include <cassert>

/* TODO: delete from positions
	     insert at the beginning and location
*/

/*
	Pliskeviski Game Engine
*/
namespace pl {
	class string {
	public:
		/*
			@ new string
		*/
		string(const char* string);

		/*
			@ new empty string
		*/
		string();
		~string();
		/*
			@ get string size
		*/
		unsigned int size();
		char& operator[](unsigned int index);
		
		/*
			@ append another string
			@ at the end
		*/
		void append(const string& string);

		/*
			@ append a char*
			@ at the and
		*/
		void append(const char* string);

		/*
			@ returns in char* format
		*/
		const char* c_str();

		/*
			@ copy a new string to another
			@ new pointers and everything
		*/
		static void Copy(string& dest, const string& source);

		/*
			@ returns a string copy
		*/
		static pl::string Copy(const string& source);

	private:
		friend std::ostream& operator<<(std::ostream& stream, const pl::string& string);
		char* s_content;
		unsigned int s_size;
		unsigned char* inMemory;
	};
	
}
