#include "FileHandler.h"

using std::string;

void FileHandler::ReadFile()
{
	std::fstream reader;

	reader.open(file_name, std::ios::in);

	if ( reader.is_open() )
	{
		// getline 10 times and set the values
		string line;
		getline(reader, line);
	}
}