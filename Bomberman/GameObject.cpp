#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);
	xpos = x;
	ypos = y;
}


void GameObject::update()
{
	xpos++;
	ypos++;
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 32;
	destRect.h = 32;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, nullptr, &destRect);
}