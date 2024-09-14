#pragma once

#include <queue>
#include <array>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <vector>
#include <set>

#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	using Entity = uint32_t;
	constexpr Entity MAX_ENTITIES = 5000;
	
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 128;

	using Signature = std::bitset<MAX_COMPONENTS>;

	class System
	{
	public:
		void RegisterComponent(ComponentType compType)
		{
			_sig.set(compType, true);
		}

		Signature _sig{};
		std::set<Entity> _entities{};
	};

	class ECS
	{
		void AddEntity()
		{

		}

		void AddComponent(Entity entity, ComponentType compType)
		{
			Signatures[entity].set(compType, true);

			for (System& system : Systems)
			{
				if ((system._sig & Signatures[entity]) == Signatures[entity])
				{
					system._entities.insert(entity);
				}
			}
		}

		void RemoveComponent(Entity entity, ComponentType compType)
		{
			Signatures[entity].set(compType, false);

			for (System& system : Systems)
			{
				system._entities.erase(entity);

				if ((system._sig & Signatures[entity]) == Signatures[entity])
				{
					system._entities.insert(entity);
				}
			}
		}

		std::array<Signature, MAX_ENTITIES> Signatures {};
		std::vector<System> Systems{};
	};
}