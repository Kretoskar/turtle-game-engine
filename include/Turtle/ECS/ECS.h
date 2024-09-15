#pragma once

#include <queue>
#include <array>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <vector>
#include <set>

#include "Turtle/ECS/ECSTypes.h"
#include "Turtle/ECS/ComponentArray.h"
#include "Turtle/ECS/System.h"
#include "Turtle/ECS/Component.h"

#include "Turtle/Core/TurtleString.h"

namespace Turtle
{
	class ECS
	{
	public:
		ECS()
		{
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				AvailableEntities.push(entity);
			}
		}

		template <typename T>
		void RegisterComponent(TurtleString compName)
		{
			CompNameToType[compName] = CurrComponentType;
			CurrComponentType++;
			ComponentArrays.insert({ compName, std::make_shared<ComponentArray<T>>() });
		}

		Entity CreateEntity()
		{
			Entity id = AvailableEntities.front();
			AvailableEntities.pop();
			LivingEntityCount++;

			return id;
		}

		void DestroyEntity(Entity entity)
		{
			Signatures[entity].reset();
			AvailableEntities.push(entity);
			LivingEntityCount--;

			for (auto CompArrayPair : ComponentArrays)
			{
				CompArrayPair.second->EntityDestroyed(entity);
			}

			for (System* system : Systems)
			{
				system->_entities.erase(entity);
			}
		}

		template<typename T>
		T& GetComponent(Entity e, const Component& comp)
		{
			std::shared_ptr<ComponentArray<T>> compArray = GetComponentArray<T>(comp.TypeName());
			return compArray->GetData(e);
		}

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray(TurtleString name)
		{
			return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[name]);
		}

		template <typename T>
		void AddComponent(Entity entity, const T& component, TurtleString CompName)
		{
			ComponentType compType = CompNameToType[CompName];

			Signatures[entity].set(compType, true);

			GetComponentArray<T>(component.TypeName())->Insert(entity, component);

			for (System* system : Systems)
			{
				if ((system->_sig & Signatures[entity]) == system->_sig)
				{
					system->_entities.insert(entity);
				}
			}
		}

		void RegisterSystem(System* system)
		{
			Systems.push_back(system);

			// TODO: iterate over signatures
		}

		void RemoveComponent(Entity entity, ComponentType compType)
		{
			Signatures[entity].set(compType, false);

			for (System* system : Systems)
			{
				system->_entities.erase(entity);

				if ((system->_sig & Signatures[entity]) == Signatures[entity])
				{
					system->_entities.insert(entity);
				}
			}
		}

		void RegisterComponentInSystem(System& system, const Component& comp)
		{
			system._sig.set(CompNameToType[comp.TypeName()], true);
		}
		
		std::queue<Entity> AvailableEntities{};
		std::array<Signature, MAX_ENTITIES> Signatures {};
		std::vector<System*> Systems{};
		ComponentType CurrComponentType{};
		std::unordered_map<TurtleString, ComponentType, TurtleString::TurtleStringHasher> CompNameToType{};
		Entity LivingEntityCount{};
		std::unordered_map<TurtleString, std::shared_ptr<IComponentArray>, TurtleString::TurtleStringHasher> ComponentArrays{};
	};
}