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

	struct Component
	{
		virtual TurtleString TypeName() const { return TurtleString::None; }
	};

	class ECS
	{
		void RegisterComponent(Component comp)
		{
			CompNameToType[comp.TypeName()] = CurrComponentType;
			CurrComponentType++;
		}

		void AddEntity()
		{

		}

		void AddComponent(Entity entity, const Component& component)
		{
			ComponentType compType = CompNameToType[component.TypeName()];

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
		// TODO: available entities
		std::array<Signature, MAX_ENTITIES> Signatures {};
		std::vector<System> Systems{};
		ComponentType CurrComponentType{};
		std::unordered_map<TurtleString, ComponentType, TurtleString::TurtleStringHasher> CompNameToType{};
	};
}