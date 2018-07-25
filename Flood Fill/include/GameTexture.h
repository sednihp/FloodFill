#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

#include "SDL_render.h"

class GameTexture 
{
	private:
		SDL_Rect box;
		SDL_Texture* tex;

	public:
		GameTexture(SDL_Texture*);
		~GameTexture();

		const int w() const { return box.w; };
		const int h() const { return box.h; }
		const int x() const { return box.x; }
		const int y() const { return box.y; }
		const SDL_Rect rect() const { return box; }
		SDL_Texture* texture() const { return tex; }

		void setPosition(const int x, const int y);
};

#endif