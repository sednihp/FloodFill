#include "TextCache.h"
#include <iostream>
#include "Util.h"

TextCache::TextCache(SDL_Renderer*& renderer) : ren(renderer)
{
	if (TTF_Init() == -1)
	{
		std::cerr << TTF_GetError() << std::endl;
		exit(2);
	}
}

TextCache::~TextCache()
{
	flush();
}

void TextCache::flush()
{
	words.clear();
}

//make the font and message into a pair (so we can have the same message in different sizes and fonts)
//find the pair in the map
//if not there create an SDL_Surface, then an SDL_Texture and then a GameTexture
//pair the GT up with the original pair and add it to the map
std::shared_ptr<GameTexture> TextCache::getText(std::string message, TTF_Font* font, SDL_Color color)
{
	auto pair = std::make_pair(font, message);
	auto i = words.find(pair);

	if(i == words.end())
	{
		SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
		if(!texture) throw TTF_GetError();
		SDL_FreeSurface(surf);
		auto gt = std::make_shared<GameTexture>(texture);

		i = words.insert(i, std::make_pair(pair, gt));
	}

    return i->second;
}