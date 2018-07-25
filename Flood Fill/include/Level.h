#ifndef LEVEL_H
#define LEVEL_H

#include "State.h"
#include "Board.h"
#include <memory>

class Level : public State
{
	private:
		TTF_Font* font;
		std::vector<std::shared_ptr<GameTexture>> menu;
		std::unique_ptr<Board> board;
		std::vector<std::unique_ptr<Square>> colorChooser;
		SDL_Color currentColor;
		bool levelComplete;
		int numberOfMovesTaken, difficulty;
		std::shared_ptr<GameTexture> numMovesWords;
		std::shared_ptr<GameTexture> numMovesTex;
		std::shared_ptr<GameTexture> currentColourWords;
		std::shared_ptr<Square> currentColourRect;

		void buildMenu();
		void buildColorChooser();
		void createText();
		void mouseClicked(SDL_Event& e, Engine* engine);
		const bool boardCompleted();

	public:
		Level(MediaCache& mc, const int d);
		~Level();

		void enter(Engine* engine);
		void handleEvents(SDL_Event& e, Engine* engine);
		void update(const double dTime, Engine* engine);
		void render();
		void exit(Engine* engine);
};

#endif
