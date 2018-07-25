#ifndef FONTCACHE_H
#define FONTCACHE_H

#include "SDL_ttf.h"
#include <map>

class FontCache
{
	private:
		SDL_Renderer*& ren;
		std::map<int, TTF_Font*> fonts;

		FontCache& operator=(const FontCache&);
		FontCache(const FontCache&);

	public:
		FontCache(SDL_Renderer*& ren);
		~FontCache();

		void flush();
		TTF_Font* getFont(const int size);
};

#endif