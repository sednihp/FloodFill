#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "State.h"
#include <vector>

class GameOver : public State
{
	private:
		TTF_Font* font;
		std::shared_ptr<GameTexture> gameOver;
		std::shared_ptr<GameTexture> numMovesMsg;
		std::shared_ptr<GameTexture> newHSMsg;
		std::vector<std::shared_ptr<GameTexture>> menu;
		bool newHighScore;
		int difficulty;

		void mouseClicked(SDL_Event& e, Engine* engine);
		void loadHighScores(int numMovesTaken);

	public:
		GameOver(MediaCache& mc, int numberOfMovesTaken, int d);
		~GameOver();

		void enter(Engine* engine);
		void handleEvents(SDL_Event& e, Engine* engine);
		void update(const double dTime, Engine* engine);
		void render();
		void exit(Engine* engine);
};

#endif