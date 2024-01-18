#pragma once
#include "ESC.h"
#include "TransformComponent.h"
#include <SDL.h>

class TileComponent:public Component
{
public:

	TransformComponent *transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	//automaticly set the texture for me
	int tileID;

	char* path;

	//the constructor
	TileComponent(void) = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		// I set my path
		switch (tileID)
		{
		case 0:
			path = (char*)"assets/grass.png";
			break;
		case 1:
			path = (char*)"assets/dirt.png";
			break;
		case 2:
			path = (char*)"assets/wall.png";
			break;
		case 3:
			path = (char*)"assets/water.png";
			break;
		default:
			break;
		}
	}

	void init(void) override
	{
		//now i initialize the rest members
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};