#include "Turtle/Core/Engine.h"
#include "Turtle/ResourceHandling/File.h"

#include <iostream>

int main()
{
	Turtle::File file("file.txt");
	std::cout << *file.GetFileContents();

	if (Turtle::Engine::Init())
	{
		Turtle::Engine::Loop();
		Turtle::Engine::ShutDown();
	}

	/*
	std::ifstream file(RESOURCES_PATH "EngineSettings.json");

	//read the file
	std::string str((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());


	*/
}