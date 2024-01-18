#pragma once
#include "Game.h"

class GameObject
{
private:

	//positions on the screen
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	//SDL_Renderer* renderer;

public:

	//GameObject(void) = default;
	GameObject(const char* textureSheet, int x, int y);
	~GameObject(void) = default;

	void update(void);
	void render(void);
};