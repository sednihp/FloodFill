#include "HighScore.h"
#include "Title.h"
#include "Engine.h"
#include <fstream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "CollisionEngine.h"
#include <iterator>

HighScore::HighScore(MediaCache& mc) : State(mc),
										font(mediaCache.getFont(80))
{
	title = mediaCache.getText("High Scores", font, mediaCache.getTextColor());
	title->setPosition(mediaCache.centreX(title->w()), 0);
	
	mainMenu = mediaCache.getText("Main Menu", font, mediaCache.getTextColor());
	mainMenu->setPosition(mediaCache.centreX(mainMenu->w()), mediaCache.scrHeight() - mainMenu->h());

	loadHighScores();
}

HighScore::~HighScore()
{
}

void HighScore::enter(Engine*)
{

}

void HighScore::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void HighScore::update(const double, Engine*)
{
}

void HighScore::render()
{
	mediaCache.renderTexture(title, title->x(), title->y());

	mediaCache.renderTexture(easy, easy->x(), easy->y());
	mediaCache.renderTexture(medium, medium->x(), medium->y());
	mediaCache.renderTexture(hard, hard->x(), hard->y());

	mediaCache.renderTexture(mainMenu, mainMenu->x(), mainMenu->y());
}

void HighScore::exit(Engine*)
{
}

//===============
//===============

void HighScore::loadHighScores()
{
	std::ifstream inf("files/high scores.txt");

	if (!inf)
	{
		printf("Can't open high scores.txt");
		return;
	}

	//read the scores in from the file and put them in the hiScore vector
	std::copy(std::istream_iterator<int>(inf),
		std::istream_iterator<int>(),
		std::back_inserter(highScores));

	inf.close();

	easy = mediaCache.getText("Easy: " + std::to_string(highScores[0]), font, mediaCache.getTextColor());
	easy->setPosition(mediaCache.centreX(easy->w()), title->h() + 10);

	medium = mediaCache.getText("Medium: " + std::to_string(highScores[1]), font, mediaCache.getTextColor());
	medium->setPosition(mediaCache.centreX(medium->w()), easy->y() + easy->h() + 10);

	hard = mediaCache.getText("Hard: " + std::to_string(highScores[2]), font, mediaCache.getTextColor());
	hard->setPosition(mediaCache.centreX(hard->w()), medium->y() + medium->h() + 10);
}

void HighScore::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(mainMenu->rect(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
	}
}