#include "Turtle/ECS/Systems/EditorUISystem.h"
#include "Turtle/ECS/Components/NameComponent.h"
#include "Turtle/ECS/ECS.h"
#include "Turtle/Core/Engine.h"
#include "Turtle/Rendering/UserInterface.h"
#include "Turtle/Core/Logger.h"

#include <unordered_map>

void Turtle::EditorUISystem::Update()
{
	// TODO: run this only when entity destroyed/created

	UserInterface* ui = Engine::UserInterface;

	if (!ui)
	{
		TURTLE_LOG_ERROR("UI system is running, but user interface is missing")
			return;
	}

	std::unordered_map<Entity, TurtleString> entityMap;


	for (Entity entity : _entities)
	{
		NameComponent& name = _ecs->GetComponent<NameComponent>(entity);

		entityMap.insert({entity, name.Name});
	}

	// TODO: don't copy
	ui->UpdateEntityMap(entityMap);
}