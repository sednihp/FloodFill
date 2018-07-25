#include "ImageCache.h"
#include "SDL_image.h"
#include <iostream>
#include "Util.h"

ImageCache::ImageCache(SDL_Renderer*& renderer) : ren(renderer)
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cerr << SDL_GetError() << std::endl;
		exit(1);
	}
}

ImageCache::~ImageCache()
{
	flush();
}

void ImageCache::flush()
{
	images.clear();
}

//look for the file in the map
//if not there, load the SDL_Texture then create a GameTexture and add it to the map
std::shared_ptr<GameTexture> ImageCache::getImage(std::string file)
{
	auto i = images.find(file);

    if(i == images.end())
    {
		SDL_Texture* tex = IMG_LoadTexture(ren, file.c_str());
		if(!tex) throw IMG_GetError();
		auto gt = std::make_shared<GameTexture>(tex);
		i = images.insert(i, std::make_pair(file, gt));
    }

    return i->second;
}