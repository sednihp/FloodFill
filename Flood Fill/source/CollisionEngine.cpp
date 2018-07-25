#include "CollisionEngine.h"

namespace CollisionEngine
{
    //if the firstBox is outside the secondBox there is no collision
    //otherwise they have collided
    const bool checkCollision(const SDL_Rect& firstBox, const SDL_Rect& secondBox)
    {
        if(firstBox.y >= secondBox.y + secondBox.h)
            return false;

        if(firstBox.y + firstBox.h <= secondBox.y)
            return false;

        if(firstBox.x >= secondBox.x + secondBox.w)
            return false;

        if(firstBox.x + firstBox.w <= secondBox.x)
            return false;

        return true;
    }

	//if x or y is outside the box return false, else return true
	const bool checkCollision(const SDL_Rect& mBox, const int x, const int y)
    {
        if(x < mBox.x)
        {
            return false;
        }

        if(x > mBox.x + mBox.w)
        {
            return false;
        }

        if(y < mBox.y)
        {
            return false;
        }

        if(y > mBox.y + mBox.h)
        {
            return false;
        }

        return true;
    }
}
