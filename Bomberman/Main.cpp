#include "SDL.h"
#include "Game.h"
#undef main

Game* game = nullptr;

int main(void)
{
	/*
		game loop
		while(game is running)
		{
			handle any user input
			update all object eg. positions etc
			renderer changes to the display

		}
	*/
	const int fps = 120;
	//how long will take a frame(max time between frames)
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;//how long the game is running
	int frameTime;
	
	game = new Game;
	//initialize the game
	game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, false);
	//game loop
	while (game->running())
	{
		//curent running time in ms
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		//how long it takes in ms to handle events update ojects and render
		frameTime = SDL_GetTicks() - frameStart;
		
		//check if i need to delay frame
		if (frameDelay > frameTime)
		{
			//we need to delay
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}