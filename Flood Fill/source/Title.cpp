#include "Title.h"
#include "Level.h"
#include "Engine.h"
#include "HighScore.h"
#include "CollisionEngine.h"
#include "Difficulty.h"

Title::Title(MediaCache& mc) : State(mc), 
								font(mediaCache.getFont(200)),
								menuFont(mediaCache.getFont(100))
{
	title = mediaCache.getText("Flood Fill", font, mediaCache.getTextColor());
	title->setPosition(mediaCache.centreX(title->w()), 0);

	menu.push_back(mediaCache.getText("Play", menuFont, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("High Scores", menuFont, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("Exit", menuFont, mediaCache.getTextColor()));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->w()), mediaCache.centreY(menu[i]->h()) + i*menu[i]->h());
	}
}

Title::~Title()
{
}

void Title::enter(Engine*)
{
}

void Title::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Title::update(const double, Engine*)
{
}

void Title::render()
{
	mediaCache.renderTexture(title, title->x(), title->y());

	for(auto& item : menu)
	{
		mediaCache.renderTexture(item, item->x(), item->y());
	}
}

void Title::exit(Engine* )
{

}

//===============
//===============

void Title::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(menu[0]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Difficulty>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[1]->rect(), x, y))
		{
			engine->changeState(std::make_shared<HighScore>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[2]->rect(), x, y))
		{
			engine->stopRunning();
		}
	}
}