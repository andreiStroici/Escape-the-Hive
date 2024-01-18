#pragma once

#include "ESC.h"
#include "Collision.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component
{
private:

	TransformComponent* transform;

	Vector2D velocity;
	int range = 160;//the range of the projectile
	int speed = 2;//how fast the projectile go
	int distance = 0;//how far the projectile go

public:


	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp) , velocity(vel)
	{}
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			//std::cout << "Out of Range" << std::endl;
			entity->destroy();
		}/*
		else
		{
			if (transform->position.x > 1024 or transform->position.y > 576 or transform->position.x < 0 or transform->position.y < 0)
			{
				std::cout << "Out of bounds!" << std::endl;
				entity->destroy();
			}
		}*/
	}

};