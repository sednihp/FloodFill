#ifndef COLLISIONENGINE_H_INCLUDED
#define COLLISIONENGINE_H_INCLUDED
#include "SDL.h"

namespace CollisionEngine
{
    const bool checkCollision(const SDL_Rect& firstBox, const SDL_Rect& secondBox);
	const bool checkCollision(const SDL_Rect& mBox, const int x, const int y);
}

#endif // COLLISIONENGINE_H_INCLUDED
