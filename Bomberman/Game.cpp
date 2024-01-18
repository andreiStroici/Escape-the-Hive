#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ESC.h"
#include "Components.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Collision.h"
#include <random>
#include <vector>
#include <algorithm>

Map* map;
SDL_Renderer* Game::renderer = nullptr;
//now I can acces this event from enywhere
SDL_Event Game::event;
std::vector<ColliderComponet*> Game::colliders;
//GameObject* player;
//SDL_Texture* playerTex;
//SDL_Rect* srcR, destR;
void level1(void);
void level2(void);
void level3(void);
char lvl = 1;
int Game::enemy_update = 0;
int Game::nrEnemies = 8;
//int Game::print = 0;

Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
//static AssetManager* assets = new AssetManager(&manager);
auto& newplayer(manager.addEntity());
//create a wall
auto& wall(manager.addEntity());
//auto& enemy(manager.addEntity());
//auto& tiles0(manager.addEntity());
//auto& tiles1(manager.addEntity());
//auto& tiles2(manager.addEntity());

// I will pass here all the tiles in the group
auto& tiles(manager.getgroup(groupMap));
//now I will do the same thing for all
auto& players(manager.getgroup(groupPlayers));
auto& enemies(manager.getgroup(groupEnemies));
auto& projectiles(manager.getgroup(groupProjectiles));



Game::Game(void)
{
	isRunning = 0;
	window = nullptr;
	renderer = nullptr;
}
Game::~Game(void)
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	//check if i want to be on the fulllscreen mode
	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//I succesfully initialized SDL subsystems
		std::cout << "Subusytsems initialized\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "The window was created\n";
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			std::cout << "The renderer was created\n";
		}
		isRunning = true;
	}
	map = new Map;

	//now i add the player texture
	//assets->addTexture("player", "assets/player_anims.png");

	Map::LoadMap("assets/Level1.map", 32, 18);


	/*tiles0.addComponent<TileComponent>(200,200,32,32,0);
	tiles1.addComponent<TileComponent>(250,250,32,32,1);
	tiles2.addComponent<TileComponent>(150,150,32,32,3);
	tiles1.addComponent<ColliderComponet>("dirt");
	tiles2.addComponent<ColliderComponet>("water");*/
	//player.addComponent<PositionComponent>();
	//player.addComponent<SpriteComponent>("assets/robot-preview.png");
	//playerTex = TextureManager::LoadTexture("assets/robot-preview.png", renderer);
	//player = new GameObject("assets/robot-preview.png", 0, 32);
	newplayer.addComponent<TransformComponent>(0,32);
	newplayer.addComponent<SpriteComponent>("assets/player1.png",false);
	newplayer.addComponent<KeyboardController>();
	newplayer.addComponent<ColliderComponet>("player");
	newplayer.addGroup(groupPlayers);
	//now I create a wall
	//wall.addComponent<TransformComponent>(96.0f, 384.0f, 96 ,96 , 1);
	//wall.addComponent<SpriteComponent>("assets/water.png");
	//wall.addComponent<ColliderComponet>("wall");
	//wall.addGroup(groupMap);
	level1();
}

void Game::handleEvents(void)
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		//when i found the command quit i stop the game
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update(void)
{
	/*destR.h = 32;
	destR.w = 32;
	destR.x++;*/
	Vector2D playerPos = newplayer.getComponent<TransformComponent>().position;
	std::vector<int> ex;
	std::vector<int> ey;
	int i = 0;
	for (auto ee : enemies)
	{
		ex.push_back(ee->getComponent<ColliderComponet>().transform->position.x);
		ey.push_back(ee->getComponent<ColliderComponet>().transform->position.y);
		++i;
	}
	if (playerPos.x >= 994 and playerPos.x <= 1020 and playerPos.y >= 508 and playerPos.y <= 516)
	{
		playerPos.x = 0;
		playerPos.y = 32;
		newplayer.getComponent<TransformComponent>().position = playerPos;
		switch (lvl)
		{
		case 1:
			++lvl;
			level2();
			Map::LoadMap("assets/Level2.map", 32, 18);
			break;
		case 2:
			++lvl;
			level3();
			Map::LoadMap("assets/Level3.map", 32, 18);
			break;
		default:
			isRunning = false;
			std::cout << "You win\n";
			break;
		}
	}
	if (Game::enemy_update == 20)
	{
		for (auto ee : enemies)
		{
			std::vector<int> nums = { -1, 1, 0, -1 , 1 };
			//Seed random number generator
			std::random_device rd;
			std::mt19937 gen(rd());
			//std::cout << transform->entity->getComponent<ColliderComponet>().tag << '\n';
			// Shuffle the vector to get a random order
			std::shuffle(nums.begin(), nums.end(), gen);
			//srand(static_cast<unsigned int>(time(0))); //seed random number generator
			ee->getComponent<ColliderComponet>().transform->velocity.x = nums[0];
			ee->getComponent<ColliderComponet>().transform->velocity.y = nums[1];
		}
		Game::enemy_update = 0;
	}
	else
	{
		++Game::enemy_update;
	}
	manager.refresh();
	i = 0;
	//std::cout << '\n';
	manager.update();//update all entinties=> all components
	//std::cout << '\n';
#ifdef ok
	std::cout << Game::renderer << " Game update \n";
#endif // ok
	//chek for collison
	for (auto cc : colliders)
	{

		//Collision::AABB(newplayer.getComponent<ColliderComponet>(), *cc);
		//std::cout << " " << tag;
		if (Collision::AABB(newplayer.getComponent<ColliderComponet>(), *cc)
			or newplayer.getComponent<ColliderComponet>().transform->position.x < 0)
		{
			//ok = true;
			//colision = true;
			//std::cout << colision<< '\n';
			if (cc->tag == "enemy")
			{
				std::cout << "Game Over\n";
				isRunning = false;
				break;
			}
			newplayer.getComponent<TransformComponent>().position = playerPos;


		}
	}
	//enemy collision
	//std::cout<<enemy_update<<'\n';
	//if (enemy_update  == 20)
	{
		i = 0;
		for (auto ee : enemies)
		{
			if (ee->getComponent<ColliderComponet>().transform->position.x > 992 or 
				ee->getComponent<ColliderComponet>().transform->position.x < 0)
			{
				ee->getComponent<ColliderComponet>().transform->position = Vector2D(ex[i], ey[i]);
			}
			else
			{
				for (auto cc : colliders)
				{
					if (cc->tag == "wall")
					{
						if (Collision::AABB(ee->getComponent<ColliderComponet>(), *cc))
						{
							ee->getComponent<ColliderComponet>().transform->position = Vector2D(ex[i], ey[i]);
						}
					}
				}
			}
			++i;
		}
		//std::cout << '\n';
		//test = 0;
		//enemy_update = 0;
	}
	/*else
	{
		++enemy_update;
	}*/
	//std::cout << newplayer.getComponent<TransformComponent>().position.x << ',';
	//std::cout << newplayer.getComponent<TransformComponent>().position.y << '\n';
	//check if the projectile hit the player
	for (auto p : projectiles)
	{
		if (Collision::AABB(newplayer.getComponent<ColliderComponet>().collider, p->getComponent<ColliderComponet>().collider))
		{
			isRunning = false;
			std::cout << "Game Over\n";
			break;
		}
	}
	i = 0;
	//check if the projectile hit an wall
	for (auto p : projectiles)
	{
		for (auto cc : colliders)
		{
			if (Collision::AABB(p->getComponent<ColliderComponet>(), *cc))
			{
				std::string tag = cc->tag;
				tag.resize(tag.size() - 1);
				if (cc->tag == "enemy")
				{
					cc->entity->destroy();
				}
				p->destroy();
			}
		}
	}
	//std::cout << '\n';
}


void Game::render(void)
{
	//clar the renderer buffer
	SDL_RenderClear(renderer);
	//I will render all the groups
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	//this is were we add stuff to renderer
	SDL_RenderPresent(renderer);
}

void Game::clean(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game clean\n";
}

void Game::addTile(int id, int x, int y)
{
	//now i add a new tile
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);;
	//now I add a tile to the group
	tile.addGroup(groupMap);
}

void level1(void)
{
	//auto enemies1((manager.getgroup(groupEnemies)));
	int x[] = { 32 * 8, 20 * 32, 32 * 9, 30 * 32 };
	int y[] = { 32 * 4, 7 * 32, 32 * 14, 16 * 32 };
	//int x[] = { 32 * 4, 19 * 32, 32 * 30, 1 * 32, 32 * 30, 12 * 32 };
	//int y[] = { 32 * 4, 4 * 32, 32 * 3, 16 * 32, 13 * 32, 320 };
	Game::nrEnemies = 4;
	for (int i = 0; i < 4; ++i)
	{
		auto& enemy(manager.addEntity());
		//std::cout << &enemy << '\n';
		enemy.enemy = true;
		enemy.number_enemy = i;
		enemy.addComponent<TransformComponent>(x[i], y[i]);
		enemy.addComponent<SpriteComponent>("assets/newenemy.png", false);
		enemy.addComponent<KeyboardController>();
		enemy.addComponent<ColliderComponet>("enemy");
		enemy.addGroup(groupEnemies);
		enemies.push_back(&enemy);
		enemies.pop_back();
	}
	std::cout << enemies.size() << '\n';
	wall.addComponent<TransformComponent>(96.0f, 384.0f, 96, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(576.0f, 64.0f, 96, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(768.0f, 128.0f, 64, 128, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(768.0f, 384.0f, 64, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(192.0f, 128.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 224.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(384.0f, 288.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(512.0f, 384.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 448.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(896.0f, 448.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 256.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(320.0f, 480.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 64.0f, 480, 32, 1);//left line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(992.0f, 32.0f, 480, 32, 1);//right line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 0.0f, 32, 1024, 1);//up line ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 544.0f, 32, 1024, 1);//down line = ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
}

void level2(void)
{
	for (auto ee : enemies)
	{
		//std::cout << ee->getComponent<ColliderComponet>().transform->position.x << '\n';
		ee->try_to_destroy();
	}
	enemies.resize(0);
	int x[] = { 32 * 4, 19 * 32, 32 * 30, 1 * 32, 32 * 30, 12 * 32  };
	int y[] = { 32 * 4, 4 * 32, 32 * 3, 16 * 32, 13 * 32, 320 };
	Game::nrEnemies = 6;
	for (int i = 0; i < 6; ++i)
	{
		auto& enemy(manager.addEntity());
		//std::cout << &enemy << '\n';
		enemy.enemy = true;
		enemy.number_enemy = i;
		enemy.addComponent<TransformComponent>(x[i], y[i]);
		enemy.addComponent<SpriteComponent>("assets/newenemy.png", false);
		enemy.addComponent<KeyboardController>();
		enemy.addComponent<ColliderComponet>("enemy");
		enemy.addGroup(groupEnemies);
		enemies.push_back(&enemy);
		enemies.pop_back();
	}
	std::cout << enemies.size() << '\n';
	wall.try_to_destroy();
	wall.addComponent<TransformComponent>(0.0f, 64.0f, 480, 32, 1);//left line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(992.0f, 32.0f, 480, 32, 1);//right line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 0.0f, 32, 1024, 1);//up line ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 544.0f, 32, 1024, 1);//down line = ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(128.0f, 96.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(64.0f, 256.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 288.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(128.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 352.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(512.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(640.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 128.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(448.0f, 192.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 288.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 384.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 448.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(512.0f, 320.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(640.0f, 256.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 256.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 160.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(896.0f, 128.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 32.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 480.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(896.0f, 448.0f, 64, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(640.0f, 384.0f, 32, 128, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 448.0f, 32, 128, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
}


void level3(void)
{
	for (auto ee : enemies)
	{
		//std::cout << ee->getComponent<ColliderComponet>().transform->position.x << '\n';
		ee->try_to_destroy();
	}
	enemies.resize(0);
	int x[] = { 29 * 32, 18 * 32, 4 * 32, 11 * 32, 32, 16 * 32, 28 * 32 };
	int y[] = { 2 * 32, 5 * 32, 6 * 32, 9 * 32, 16 * 32, 15*32, 15 * 32 };
	Game::nrEnemies = 7;
	for (int i = 0; i < 7; ++i)
	{
		auto& enemy(manager.addEntity());
		//std::cout << &enemy << '\n';
		enemy.enemy = true;
		enemy.number_enemy = i;
		enemy.addComponent<TransformComponent>(x[i], y[i]);
		enemy.addComponent<SpriteComponent>("assets/newenemy.png", false);
		enemy.addComponent<KeyboardController>();
		enemy.addComponent<ColliderComponet>("enemy");
		enemy.addGroup(groupEnemies);
		enemies.push_back(&enemy);
		enemies.pop_back();
	}
	std::cout << enemies.size() << '\n';
	wall.try_to_destroy();
	wall.addComponent<TransformComponent>(0.0f, 64.0f, 480, 32, 1);//left line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(992.0f, 32.0f, 480, 32, 1);//right line
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 0.0f, 32, 1024, 1);//up line ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(0.0f, 544.0f, 32, 1024, 1);//down line = ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(160.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(352.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(416.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(544.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(672.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(736.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(864.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 32.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(768.0f, 64.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 96.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(160.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(352.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(416.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(544.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(672.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(736.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 128.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(192.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(320.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(832.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(736.0f, 224.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(64.0f, 256.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(128.0f, 256.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(160.0f, 288.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 288.0f, 64, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(128.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(384.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(640.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(736.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(832.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(896.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(960.0f, 320.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 320.0f, 32, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(160.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(352.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(416.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(544.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(672.0f, 416.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(32.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(96.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(160.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(288.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(352.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(416.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(480.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(544.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(608.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(672.0f, 480.0f, 32, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(224.0f, 352.0f, 96, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(448.0f, 224.0f, 32, 224, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(544.0f, 256.0f, 96, 32, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 128.0f, 32, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(736.0f, 384.0f, 160, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(800.0f, 480.0f, 64, 96, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(832.0f, 384.0f, 64, 128, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
	wall.addComponent<TransformComponent>(928.0f, 448.0f, 64, 64, 1);//ok
	wall.addComponent<ColliderComponet>("wall");
	wall.addGroup(groupMap);
}