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

		Signature _sig{};
		std::set<Entity> _entities{};
	};

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void Insert(Entity entity, T component)
		{
			size_t idx = componentArray.size();
			entityToIndexMap[entity] = idx;
			indexToEntityMap[idx] = entity;
			componentArray.push_back(component);
		}

		void Remove(Entity entity)
		{
			if (entityToIndexMap.find(entity) == entityToIndexMap.end())
			{
				return;
			}

			size_t Idx = entityToIndexMap[entity];
			T LastComp = componentArray.back();
			Entity LastEntity = indexToEntityMap[componentArray.size() - 1];

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(Idx);

			componentArray[Idx] = LastComp;
			componentArray.pop_back();


			entityToIndexMap[LastEntity] = Idx;
			indexToEntityMap[Idx] = LastEntity;
		}

		void EntityDestroyed(Entity entity) override
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				Remove(entity);
			}
		}

		T& GetData(Entity entity)
		{
			return componentArray[entityToIndexMap[entity]];
		}

		std::unordered_map<Entity, size_t> entityToIndexMap;
		std::unordered_map<size_t, Entity> indexToEntityMap;

		std::vector<T> componentArray;
	};

	struct Component
	{
		// TODO: maybe avoid inheritance by using typeid instead?
		virtual TurtleString TypeName() const { return TurtleString::None; }
	};

	struct TransformComponent : public Component
	{
		float x{}, y{}, z{};
		virtual TurtleString TypeName() const { return TurtleString("Transform"); }
	};

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

	class TransformSystem : public System
	{
	public:
		void Update(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent& comp = ecs->GetComponent<TransformComponent>(e, TransformComponent());
				comp.x += 1;
			}
		}

		void Finish(ECS* ecs)
		{
			for (Entity e : _entities)
			{
				TransformComponent comp = ecs->GetComponent<TransformComponent>(e, TransformComponent());
				TURTLE_LOG_MESSAGE("X: %f", comp.x)
			}
		}
	};
}