#include "Map.h"
#include "Game.h"
#include <fstream>
//#include "TextureManager.h"

//int lvl1[18][32]
//= {
//	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
//	{2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2},
//	{2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2},
//	{2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,2},
//	{2,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
//};

Map::Map(void)
{
	//set textures for map
	//dirt = TextureManager::LoadTexture("assets/dirt.png");
	//grass = TextureManager::LoadTexture("assets/grass.png");
	//wall = TextureManager::LoadTexture("assets/wall.png");
	//water = TextureManager::LoadTexture("assets/water.png");
	//
	////load the map
	//LoadMap(lvl1);

	//src.x = src.y = 0;
	//src.h = dest.h = 64;
	//dest.w = src.w = 64;
	//

	//dest.x = dest.y = 0;
}

Map::~Map(void)
{
	/*SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(water);*/
}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	/*for (int row = 0; row < 18; ++row)
	{
		for (int col = 0; col < 32; ++col)
		{
			map[row][col] = arr[row][col];
		}
	}*/
	//when i read the file i will take in character buy character
	char tile;
	std::fstream mapfile;
	// now i open the file
	mapfile.open(path);
	//now i need some for loops to move through the file
	// and make a tile for all character
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			mapfile.get(tile);
			Game::addTile(atoi(&tile), x * 32, y * 32);
			mapfile.ignore();
			//std::cout << x << ' ' << y << ' ' << tile << '\n';
		}
	}
	//now i clode the file
	mapfile.close();
}

//void Map::DrawMap(void)
//{
//	int type = 0;
//	for (int row = 0; row < 18; ++row)
//	{
//		for (int col = 0; col < 32; ++col)
//		{
//			type = map[row][col];
//			dest.y = row * 32;
//			dest.x = col * 32;
//			switch (type)
//			{
//				//case 0 = grass
//				//case 1 = dirt
//				//case 2 = wall
//				//case 3 = water
//			case 0:
//				TextureManager::Draw(grass, src, dest);
//				break;
//			case 1:
//				TextureManager::Draw(dirt, src, dest);
//				break;
//			case 2:
//				TextureManager::Draw(wall, src, dest);
//				break;
//			case 3:
//				TextureManager::Draw(water, src, dest);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}