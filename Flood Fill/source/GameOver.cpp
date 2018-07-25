#include "GameOver.h"
#include <sstream>
#include "Difficulty.h"
#include "HighScore.h"
#include "Engine.h"
#include <fstream>
#include <algorithm>
#include <functional>
#include "CollisionEngine.h"
#include <iterator>

GameOver::GameOver(MediaCache& mc, int numberOfMovesTaken, int d) : State(mc),
																	font(mediaCache.getFont(80)),
																	newHighScore(false), difficulty(d)
{
	loadHighScores(numberOfMovesTaken);

	gameOver = mediaCache.getText("Game complete!", font, mediaCache.getTextColor());

	std::stringstream ss;
	ss << "You took " << numberOfMovesTaken << " moves";
	numMovesMsg = mediaCache.getText(ss.str(), font, mediaCache.getTextColor());

	gameOver->setPosition(mediaCache.centreX(gameOver->w()), mediaCache.centreY(numMovesMsg->h()) - 3*gameOver->h());
	numMovesMsg->setPosition(mediaCache.centreX(numMovesMsg->w()), mediaCache.centreY(numMovesMsg->h()) - 2*gameOver->h());

	newHSMsg = mediaCache.getText("New high score!", font, mediaCache.getTextColor());
	newHSMsg->setPosition(mediaCache.centreX(newHSMsg->w()), mediaCache.centreY(numMovesMsg->h()) - gameOver->h());

	menu.push_back(mediaCache.getText("Play Again", font, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("High Scores", font, mediaCache.getTextColor()));
	menu.push_back(mediaCache.getText("Exit", font, mediaCache.getTextColor()));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->w()), mediaCache.scrHeight() - (menu.size() - i)*menu[i]->h());
	}
}

GameOver::~GameOver()
{
}

void GameOver::enter(Engine*)
{
}

void GameOver::loadHighScores(int numMovesTaken)
{
	std::ifstream myfile("files/high scores.txt");

	if (!myfile)
	{
		throw("Could not open high scores");
	}

	std::vector<int> highScores;

	std::copy(std::istream_iterator<int>(myfile),
		std::istream_iterator<int>(),
		std::back_inserter(highScores));

	myfile.close();

	int difficultyLine = difficulty - 4;

	if (numMovesTaken < highScores[difficultyLine])
	{
		highScores[difficultyLine] = numMovesTaken;
		newHighScore = true;

		std::ofstream ofs("files/high scores.txt");

		if (!ofs)
		{
			throw("Could not open high scores");
		}

		for (auto &hiScore : highScores)
		{
			ofs << hiScore << std::endl;
		}

		ofs.close();
	}
}

void GameOver::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void GameOver::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
    {
		if(CollisionEngine::checkCollision(menu[0]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Difficulty>(mediaCache));
		}
		else if(CollisionEngine::checkCollision(menu[1]->rect(), x, y))
		{
			engine->changeState(std::make_shared<HighScore>(mediaCache));
		}
		else if(CollisionEngine::checkCollision(menu[2]->rect(), x, y))
		{
			engine->stopRunning();
		}
	}
}

void GameOver::update(const double, Engine*)
{
}

void GameOver::render()
{
	mediaCache.renderTexture(gameOver, gameOver->x(), gameOver->y());
	mediaCache.renderTexture(numMovesMsg, numMovesMsg->x(), numMovesMsg->y());

	if(newHighScore)
	{
		mediaCache.renderTexture(newHSMsg, newHSMsg->x(), newHSMsg->y());
	}
	
	for(auto& item : menu)
	{
		mediaCache.renderTexture(item, item->x(), item->y());
	}
}

void GameOver::exit(Engine*)
{
}