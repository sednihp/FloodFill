#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "SDL_pixels.h"

namespace FloodFill
{
	//compares two SDL_Colors to see if they're equivalent
	inline const bool sameColor(SDL_Color const& lhs, SDL_Color const& rhs)
	{
		if(lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b)
		{
			return true;
		}

		return false;
	}
}

#endif