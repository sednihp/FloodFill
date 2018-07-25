#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "State.h"
#include "GameTexture.h"
#include <vector>

class HighScore : public State
{
	private:
		TTF_Font* font;
		const int highScoreCount = 3;
		std::vector<int> highScores;
		std::shared_ptr<GameTexture> title;
		std::shared_ptr<GameTexture> mainMenu;
		std::shared_ptr<GameTexture> easy;
		std::shared_ptr<GameTexture> medium;
		std::shared_ptr<GameTexture> hard;

		void mouseClicked(SDL_Event& e, Engine* engine);
		void loadHighScores();

		HighScore& operator=(const HighScore&);
		HighScore(const HighScore&);

	public:
		HighScore(MediaCache& mc);
		~HighScore();

		void enter(Engine* engine);
		void handleEvents(SDL_Event& e, Engine* engine);
		void update(const double dTime, Engine* engine);
		void render();
		void exit(Engine* engine);
};

#endif