#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include "GameTexture.h"
#include <string>
#include <map>
#include <memory>

class ImageCache
{
	private:
		SDL_Renderer*& ren;
		std::map<std::string, std::shared_ptr<GameTexture>> images;

		ImageCache& operator=(const ImageCache&);
		ImageCache(const ImageCache&);

	public:
		ImageCache(SDL_Renderer*& renderer);
		~ImageCache();

		void flush();
		std::shared_ptr<GameTexture> getImage(const std::string file);
};

#endif