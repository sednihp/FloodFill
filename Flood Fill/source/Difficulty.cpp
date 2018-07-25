#include "Difficulty.h"
#include "Title.h"
#include "Level.h"
#include "Engine.h"
#include "HighScore.h"
#include "CollisionEngine.h"
#include <iostream>
#include <fstream>

Difficulty::Difficulty(MediaCache& mc) : State(mc), 
								font(mediaCache.getFont(200)),
								menuFont(mediaCache.getFont(100))
{
	title = mediaCache.getText("Flood Fill", font, mediaCache.getTextColor());
	title->setPosition(mediaCache.centreX(title->w()), 0);

	menu.push_back(mediaCache.getText("Easy", menuFont, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("Medium", menuFont, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("Hard", menuFont, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("Main Menu", menuFont, mediaCache.getTextColor()));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->w()), mediaCache.centreY(menu[i]->h()) + i*menu[i]->h() - menu[i]->h()/2);
	}
}

Difficulty::~Difficulty()
{
}

void Difficulty::enter(Engine*)
{
}

void Difficulty::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Difficulty::update(const double, Engine*)
{
}

void Difficulty::render()
{
	mediaCache.renderTexture(title, title->x(), title->y());

	for(auto& item : menu)
	{
		mediaCache.renderTexture(item, item->x(), item->y());
	}
}

void Difficulty::exit(Engine* )
{

}

//===============
//===============

void Difficulty::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu[0]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Level>(mediaCache, 4));
		}
		else if (CollisionEngine::checkCollision(menu[1]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Level>(mediaCache, 5));
		}
		else if (CollisionEngine::checkCollision(menu[2]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Level>(mediaCache, 6));
		}
		else if (CollisionEngine::checkCollision(menu[3]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
	}
}