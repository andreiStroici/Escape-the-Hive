#pragma once
#include <SDL.h>
#include "ColliderComponent.h"

class Collision
{
public:

	// I create the function that detect the collision
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponet& colA, const ColliderComponet& colB);
};