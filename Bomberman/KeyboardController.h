#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "ESC.h"
#include "Game.h"
#include "ColliderComponent.h"
#include "Components.h"

//static int trying = 0;
static SDL_Keycode key = 0;

class KeyboardController : public Component
{
public:
	//this is going to need acces to TransformComponent
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	//now i chek what key the player press
	void update() override
	{
		//Bomb* b;
		//I make sure that I have a key event
		if (!entity->enemy)
		{
			//test = 1;
			if (Game::event.type == SDL_KEYDOWN)
			{
				Vector2D temp(transform->position.x, transform->position.y);
				//i move through statemet depending what key is press
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					key = SDLK_w;
					transform->velocity.y = -1;
					//lastKeyDown = 0;
					//set the animation type
					sprite->Play("Walk");
					break;
				case SDLK_a:
					key = SDLK_a;
					//lastKeyDown = 1;
					transform->velocity.x = -1;
					sprite->Play("Walk");
					//set a type of flip to chage directions
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:
					key = SDLK_d;
					//lastKeyDown = 2;
					transform->velocity.x = 1;
					sprite->Play("Walk");
					break;
				case SDLK_s:
					key = SDLK_s;
					//lastKeyDown = 3;
					transform->velocity.y = 1;
					sprite->Play("Walk");
					break;
				case SDLK_UP:
					key = SDLK_UP;
					//lastKeyDown = 0;
					transform->velocity.y = -1;
					sprite->Play("Walk");
					break;
				case SDLK_LEFT:
					key = SDLK_LEFT;
					//lastKeyDown = 1;
					transform->velocity.x = -1;
					sprite->Play("Walk");
					//set a type of flip to chage directions
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_RIGHT:
					key = SDLK_RIGHT;
					//lastKeyDown = 2;
					transform->velocity.x = 1;
					sprite->Play("Walk");
					break;
				case SDLK_DOWN:
					key = SDLK_DOWN;
					//lastKeyDown = 3;
					transform->velocity.y = 1;
					sprite->Play("Walk");
					break;
				case SDLK_SPACE:
					//AssetManager* assets->addTexture("projectile", "assets/fire.png");
					Game::assets->addTexture("projectile", "assets/fire.png");
					if (key == SDLK_w || key == SDLK_UP)
					{
						temp.y -= 32;
						Game::assets->CreateProjectile(temp, Vector2D(0, -2), 160, 2, "projectile");
					}
					if (key == SDLK_a || key == SDLK_LEFT)
					{
						temp.x -= 32;
						Game::assets->CreateProjectile(temp, Vector2D(-2, 0), 160, 2, "projectile");
					}
					if (key == SDLK_d || key == SDLK_RIGHT || !key)
					{
						temp.x += 32;
						Game::assets->CreateProjectile(temp, Vector2D(2, 0), 160, 2, "projectile");
					}
					if (key == SDLK_s || key == SDLK_DOWN)
					{
						temp.y += 32;
						Game::assets->CreateProjectile(temp, Vector2D(0, 2), 160, 2, "projectile");
					}
					break;
				default:
					break;
				}
			}

			//I see  when the key is released
			if (Game::event.type == SDL_KEYUP)
			{
				//when the key is released I set the velocity vector to 0
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					transform->velocity.y = 0;
					//set the animation type
					sprite->Play("Idle");
					break;
				case SDLK_a:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_d:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					break;
				case SDLK_s:
					transform->velocity.y = 0;
					sprite->Play("Idle");
					break;
				case SDLK_UP:
					transform->velocity.y = 0;
					sprite->Play("Idle");
					break;
				case SDLK_LEFT:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_RIGHT:
					transform->velocity.x = 0;
					sprite->Play("Idle");
					break;
				case SDLK_DOWN:
					transform->velocity.y = 0;
					sprite->Play("Idle");
					break;
					//case SDLK_ESCAPE:
						//Game::isRunning = false;
				default:
					break;
				}
			}
		}
		else
		{
			//std::cout << Game::enemy_update << '\n';
			//if (Game::enemy_update == 20)
			//{
			//	std::vector<int> nums = { -1, 0, 1, -1, 1 };

			//	// Seed random number generator
			//	std::random_device rd;
			//	std::mt19937 gen(rd());
			//	//std::cout << transform->entity->getComponent<ColliderComponet>().tag << '\n';
			//	// Shuffle the vector to get a random order
			//	std::shuffle(nums.begin(), nums.end(), gen);
			//	//srand(static_cast<unsigned int>(time(0))); //seed random number generator
			//	transform->velocity.x =  nums[0];
			//	transform->velocity.y = nums[1];
			//	std::cout << transform->velocity.x << ' ' << transform->velocity.x << '\n';
			//	Game::enemy_update = 0;
			//}
			//else
			//{
			//	Game::enemy_update++;
			//}
		}
		//else
		//{
		//	srand(static_cast<unsigned int>(time(0))); //seed random number generator
		//	transform->velocity.x = (rand() % 3) - 1;
		//	transform->velocity.y = (rand() % 3) - 1;
		//}
	}
};