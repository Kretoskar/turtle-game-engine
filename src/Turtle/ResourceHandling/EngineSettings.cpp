#include "Turtle/ResourceHandling/EngineSettings.h"
#include "Turtle/ResourceHandling/File.h"
#include "Turtle/Core/Logger.h"
#include "json/json.hpp"

using Json = nlohmann::json;

Turtle::EngineSettings::EngineSettings(const char* jsonPath)
{
	File file(jsonPath);
	if (!file.IsValid())
	{
		TURTLE_LOG_ERROR("Invalid path for EngineSettings.json provided")
		return;
	}

	Json json = Json::parse(*file.GetFileContents());
	
	_windowSettings.Name = TurtleString(json["window"]["name"]);

	_windowSettings.Width = json["window"]["width"];
	_windowSettings.Height = json["window"]["height"];

	_windowSettings.BgColor = 
	{ 
		json["window"]["bgColorR"], 
		json["window"]["bgColorG"], 
		json["window"]["bgColorB"] 
	};
}