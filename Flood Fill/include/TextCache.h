#ifndef TEXTCACHE_H
#define TEXTCACHE_H

#include "GameTexture.h"
#include <string>
#include <map>
#include "SDL_ttf.h"
#include <memory>

class TextCache
{
	private:
		SDL_Renderer*& ren;
		std::map<std::pair<TTF_Font*, std::string>, std::shared_ptr<GameTexture>> words;

		TextCache& operator=(const TextCache&);
		TextCache(const TextCache&);

	public:
		TextCache(SDL_Renderer*& renderer);
		~TextCache();

		void flush();
		std::shared_ptr<GameTexture> getText(const std::string message, TTF_Font* font, const SDL_Color color);
};

#endif