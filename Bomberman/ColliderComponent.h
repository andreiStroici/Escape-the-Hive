#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"

class ColliderComponet : public Component
{
private:

public:

	//I define an area that is collideble
	SDL_Rect collider;
	//detect the object that have a colision
	std::string tag;
	TransformComponent* transform;

	ColliderComponet(std::string t)
	{
		tag = t;
	}

	ColliderComponet(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init(void) override
	{
		//i make sure that i have TransformComponent at the entity
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		Game::colliders.push_back(this);
	}

	void update(void) override
	{
		//std::cout << "ColliderComponent " << collision << '\n';
		if (!collision)
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	}

};