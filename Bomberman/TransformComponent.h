#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "Game.h"
//this class will hold out positions and rotations
class TransformComponent :public Component
{

public:

	Vector2D position;
	//a velocity vector
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 2;

	
	TransformComponent(void)
	{
		position.zero();
		velocity.zero();
	}

	TransformComponent(int s)
	{
		position.zero();
		velocity.zero();
		scale = s;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	//I make sure that automaticly my velocity vector has null componets
	void init(void) override 
	{
		velocity.zero();
	}
	
	void update(void) override
	{
		//collision = colision;
		if (!collision)
		{
			// i will use it to move my player
			//std::cout << colision <<"*\n";
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
	}

};