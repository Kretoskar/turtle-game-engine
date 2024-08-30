#include <fstream>
#include <iostream>

#include "Turtle/ResourceHandling/File.h"

Turtle::File::File(const char* path)
{
	char result[100];

	strcpy(result, RESOURCES_PATH);
	strcat(result, path);

	std::ifstream file(result);

	if (file.good())
	{
		_fileContents = new std::string((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		_isValid = true;
	}
	else 
	{
		_fileContents = new std::string("");
		_isValid = false;
	}
}

Turtle::File::~File()
{
	delete _fileContents;
}
