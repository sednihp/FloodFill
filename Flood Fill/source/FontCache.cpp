#include "FontCache.h"
#include "Util.h"

FontCache::FontCache(SDL_Renderer*& renderer) : ren(renderer)
{
}

FontCache::~FontCache()
{
	flush();

	TTF_Quit();
}

void FontCache::flush()
{
	for(auto& f : fonts)
	{
		TTF_CloseFont(f.second);
	}
	fonts.clear();
}

//look to see if that size font is already open
//if it isn't then open it and add it to the map
TTF_Font* FontCache::getFont(int size)
{
	auto i = fonts.find(size);

    if(i == fonts.end())
    {
		TTF_Font* font = TTF_OpenFont("files/seriously.ttf", size);
		if(!font) throw TTF_GetError();
		i = fonts.insert(i, std::make_pair(size, font));
}

    return i->second;
}