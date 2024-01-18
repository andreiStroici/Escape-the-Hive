#include "Collision.h"
#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (
		recA.x + recA.w - 3 > recB.x &&
		recB.x + recB.w - 3 > recA.x &&
		recA.y + recA.h - 3 > recB.y &&
		recB.y + recB.h - 3 > recA.y
		)
	{
		// I have a collision
		return true;
	}
	//I don't have a collision
	return false;
}

bool Collision::AABB(const ColliderComponet& colA, const ColliderComponet& colB)
{
	if (AABB(colA.collider, colB.collider) && colA.tag != colB.tag)
	{
#ifdef ok
		std::cout << colA.tag << "hit: " << colB.tag << '\t';
		std::cout << colA.collider.x << ' ' << colA.collider.y << '\t';
		std::cout << colA.collider.w << ' ' << colA.collider.h << '\t';
		std::cout << colB.collider.x << ' ' << colB.collider.y << '\t';
		std::cout << colB.collider.w << ' ' << colA.collider.h << '\n';
#endif
		return true;
	}
	else
	{
		return false;
	}
}