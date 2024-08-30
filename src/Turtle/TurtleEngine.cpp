#include "Turtle/Core/Engine.h"

int main()
{
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

	json json = json::parse(str);

	std::cout << json["window"]["height"];
	*/
}