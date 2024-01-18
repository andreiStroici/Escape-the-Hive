#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	//create a surface
	SDL_Surface* tempSurface = IMG_Load(texture);
	//create the texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//clear the surface
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,SDL_RendererFlip flip)
{
//#ifdef ok
//	std::cout << "Call\n";
//#endif // ok

	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest,NULL, NULL, flip);
}
