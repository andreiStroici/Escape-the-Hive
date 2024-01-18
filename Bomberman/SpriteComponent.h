#pragma once
#include "Components.h"
#include <SDL.h>
//#define ok
#include "TextureManager.h"
#include "Animation.h"
#include <map>


class SpriteComponent:public Component
{
private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	//Now i add some new information for animation
	bool animated = false;
	int frames = 0;
	int speed = 100;//delay between frames in ms

public:
	
	int animINdex = 0;

	//with this map I hold my animation
	std::map<const char*, Animation> animations;

	//now I need a flip flag for animations
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(void) = default;

	void setTex(const char* path)
	{
#ifdef ok
		std::cout << Game::renderer << "\n";
#endif // ok
		texture = TextureManager::LoadTexture(path);
	}
	SpriteComponent(const char* path)
	{
#ifdef ok
		std::cout << Game::renderer << "Sprite component\n";
#endif // ok
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
#ifdef ok
		std::cout << Game::renderer << "Sprite component\n";
#endif // ok
		animated = isAnimated;

		//crate an animation
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		//now I add animation to my map
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		//with this I initialize my values
		Play("Idle");

		setTex(path);
	}

	~SpriteComponent(void)
	{
		SDL_DestroyTexture(texture);
	}

	void init(void) override
	{
		//I get the reference to position component
		// and i have acces to position component
		transform = &entity->getComponent<TransformComponent>();


		//initialize the rectangles
		srcRect.x = srcRect.y = 0;
		srcRect.h = transform->width;
		srcRect.w = transform->height;

	}

	void update(void) override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		//if i don't animate  my sprite then the initial position shoud be 0
		srcRect.y = animINdex * transform->height;

		if (transform != nullptr)
		{
			destRect.x = static_cast<int>(transform->position.x);
			destRect.y = static_cast<int>(transform->position.y);
			destRect.w = transform->width * transform->scale;
			destRect.h = transform->height * transform->scale;
		}
	}

	void draw(void) override
	{
//#ifdef ok
//		std::cout << Game::renderer << "\n";
//#endif // ok
		TextureManager::Draw(texture, srcRect, destRect,spriteFlip);
	}

	void Play(const char* animName)
	{
		//I use this to chage the current frames and index we need
		if (animated)
		{
			frames = animations[animName].frames;
			animINdex = animations[animName].index;
			speed = animations[animName].speed;
		}
	}
};