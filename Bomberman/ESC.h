#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
//#include "Components.h"
//#define ok
//#define ok

class Component;
class Entity;//contain a list of Components
class Manager;

//an ID to identify the components(position, input handling etc.)
using ComponentID = std::size_t;
//using Group = std::size_t;
using Group = std::size_t;

//generate the component ID
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	//every time I call this lastID will remember last value
	return lastID++;
}

//crate o template function to have a constant component ID
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

//tell my if an entity has a  component attached
constexpr std::size_t maxComponents = 32;
//maximum numbers of groups
//I can use groups for renderer layers and colision layers
//because each entity can be members of multiple groups
constexpr std::size_t maxGroups = 32;

//i can check if I have a component in the entity
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:

	bool collision;
	Entity* entity;//reference to it's owner

	//the functions are virtual to override them
	virtual void init(void) {}
	virtual void update(void) {}
	virtual void draw(void) {}
	virtual ~Component(void) {}
};

class Entity
{
private:
	Manager& manager;
	//tells me if the entity is active in the game
	//if it is not than i will remove it
	bool active = true;
	//list of all components that an entity has
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	//now i can check in witch group the entity belongs
	GroupBitset groupBitset;

public:

	//bool collision = false;//this tells me if I have a collision
	bool enemy = false;
	int number_enemy = 0;
	Entity(void) = default;
	Entity(Manager& mManager) : manager(mManager) {};

	void try_to_destroy(void)
	{
		components.resize(0);
		componentBitset.reset();
		componentArray.fill(0);
	}

	void update(void)
	{
		for (auto& c : components)
		{
			//c->entity->getComponent<ColliderComponet>().tag;
			//c->entity->
				c->update();
				//c->entity->getComponent<ColliderComponet>().tag;
		}
	}
	void draw(void)
	{
		for (auto& c : components)
		{
			c->draw();
		}
	}

	bool isActive(void) const 
	{ 
		return active; 
	}
	//i can delete an entity using this function
	void destroy(void)
	{ 
		active = false; 
	}

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	template <typename T> bool hasComponent(void) const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		//when i add a new Compoment type it will be allways  is the same position
		componentArray[getComponentTypeID<T>()] = c;
		//after i added to array then i mark that the entitiy has taht component(easy to check if it is active)
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent(void) const
	{
		// pointer to position in my array
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	//in this way i can write something like this
	//gameObject.getComponent<PositionComponent>().setXpos(25)
};

class Manager
{
private:
	//I keep a vector of entities that manager is looking after
	std::vector<std::unique_ptr<Entity>> entities;
	//I create a vector of arrays which baisicaly like my groups
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update(void)
	{
		//use Manager to update all entities
		for (auto& e : entities)
		{
			//if (e->getComponent<ColliderComponet>().tag != "enemy")
			//{
				e->update();
			//}
		}
	}
	void draw(void)
	{
		//draw entities
#ifdef ok
		std::cout << Game::renderer<<'\n';
#endif // ok
		for (auto& e : entities)
		{
			e->draw();
		}
	}
	//manager must be able to move through frame all entities
	void refresh(void)
	{
		//here I remove the entities from groups before update them
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		//remove the  entities if they are not active
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}
	
	//now I add a new entity to the group
	void addtogroup(Entity* mentity, Group mgroup)
	{
		groupedEntities[mgroup].emplace_back(mentity);
	}

	//here I get my entities as a list
	std::vector<Entity*>& getgroup(Group mgroup)
	{
		return groupedEntities[mgroup];
	}
	//add a new entitiy
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
//+ <T, TArgs...> addComponent(mArgs: TArgs&& ...): T&