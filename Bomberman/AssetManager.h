#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ESC.h"
//#include "Components.h"

class AssetManager
{
private:
	
	//first is the key to identify the element and the second is the value of the element
	std::map<std::string, SDL_Texture*> textures;
	//now i add a local manager
	Manager* manager;


public:

	AssetManager(Manager* man);
	
	~AssetManager(void);

	//game objects

	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	//manage textures
	void addTexture(std::string id, const char* path);

	SDL_Texture* getTexture(std::string id);

};