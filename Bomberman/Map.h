#pragma once
#include <string>
//#include "Game.h"

class Map
{
private:

	////source and destination for rendeering
	//SDL_Rect src, dest;

	////the textures for map
	//SDL_Texture* dirt;
	//SDL_Texture* grass;
	//SDL_Texture* wall;
	//SDL_Texture* water;

	////the matrix that holds the map
	//int map[18][32];

public:

	Map(void);//constructor
	~Map(void);//destructor

	static void LoadMap(std::string path, int sizeX, int sizeY);;
};