#include "Helpers.h"

std::string get_file_contents(const char* filename) {

	std::ifstream in(filename, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}

	std::cout << "Error reading " << std::string(filename) << std::endl;
	throw(errno);
}