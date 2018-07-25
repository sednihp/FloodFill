#include "GameTexture.h"
#include <stdio.h>

//initialize tex, then query it to find it's width and height
GameTexture::GameTexture(SDL_Texture* texture) : tex(texture)
{
	box.x = box.y = box.w = box.h = 0;
	SDL_QueryTexture(tex, NULL, NULL, &box.w, &box.h);
}

GameTexture::~GameTexture()
{
	SDL_DestroyTexture(tex);
}

void GameTexture::setPosition(const int x, const int y)
{
	box.x = x;
	box.y = y;
}