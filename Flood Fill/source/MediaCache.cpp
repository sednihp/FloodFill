#include "MediaCache.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"

MediaCache::MediaCache() :	mScrWidth(800), mScrHeight(600),
							window(nullptr), ren(nullptr), 
							imgCache(ren), fontCache(ren), txtCache(ren), textColor({255,0,0})
{
	window = SDL_CreateWindow("Flood Fill", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mScrWidth, mScrHeight, SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(2);
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
	{
		std::cout << SDL_GetError() << std::endl;
		exit(3);
	}
}

MediaCache::~MediaCache()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);

    SDL_Quit();
}

std::shared_ptr<GameTexture> MediaCache::getImage(std::string file)
{
	return imgCache.getImage(file);
}

TTF_Font* MediaCache::getFont(int size)
{
	return fontCache.getFont(size);
}

std::shared_ptr<GameTexture> MediaCache::getText(std::string message, TTF_Font* font, SDL_Color color)
{
	return txtCache.getText(message, font, color);
}

#include "Util.h"

void MediaCache::renderTexture(std::shared_ptr<GameTexture> tex, const int x, const int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
	pos.w = tex->w();
	pos.h = tex->h();
 
	SDL_RenderCopy(ren, tex->texture(), NULL, &pos);
}

void MediaCache::drawRectangle(SDL_Rect rect, SDL_Color c)
{
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &rect);
}

void MediaCache::clearScreen()
{ 
	SDL_SetRenderDrawColor(ren, 253, 253, 150, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(ren); 
}

int MediaCache::centreX(int gtWidth) const
{
	return (mScrWidth - gtWidth) / 2;
}

int MediaCache::centreY(int gtHeight) const
{
	return (mScrHeight - gtHeight) / 2;
}

const SDL_Color& MediaCache::getTextColor()
{
	return textColor;
}