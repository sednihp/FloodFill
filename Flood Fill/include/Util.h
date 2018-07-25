#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "SDL_pixels.h"

namespace FloodFill
{
	//compares two SDL_Colors to see if they're equivalent
	inline const bool sameColor(const SDL_Color& lhs, const SDL_Color& rhs)
	{
		if(lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b)
		{
			return true;
		}

		return false;
	}
}

#endif