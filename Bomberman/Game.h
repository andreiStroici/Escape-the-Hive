#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "AssetManager.h"
//#define ok

class AssetManager;
class ColliderComponet;
class Game
{
private:
	bool isRunning;//tells me if the game is running
	int count = 0;
	SDL_Window* window;//the game window
	
public:

	//this member gives me an delay to update the enemies
	static int enemy_update;
	static int nrEnemies;
	//static int print;

	static void addTile(int id, int x, int y);

	static SDL_Renderer* renderer;

	static AssetManager* assets;
	
	//I will have one instance of this type to
	//check in my controler class
	static SDL_Event event;
	//I keep a list of colliders
	//when i create an object i had a colider addet to this list
	static std::vector<ColliderComponet*> colliders;
	Game(void);//constructor
	~Game(void);//destructor

	//initalizez game-ul
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	//funtion to handle events
	void handleEvents(void);
	//function that update the game
	void update(void);
	//function for render
	void render(void);
	//function to clean the game
	void clean(void);
	//let the main that game is still running
	bool running(void)
	{
		return isRunning;
	}
};

//I need a clearly way to define my grops so I use tihis enum because I use int
enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupProjectiles,
	test
};