#include "Level.h"
#include "Title.h"
#include "Util.h"
#include "CollisionEngine.h"
#include "GameOver.h"
#include "Engine.h"

Level::Level(MediaCache& mc, const int d) : State(mc), 
											font(mediaCache.getFont(60)),
											levelComplete(false), numberOfMovesTaken(0), difficulty(d),
											board(std::unique_ptr<Board>(new Board(20, 20, d)))
{
	buildMenu();
	buildColorChooser();
	createText();
}



Level::~Level()
{
}

void Level::enter(Engine*)
{
}

//only handle mouse clicked events
void Level::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

//if the level is complete, move to the gameover state
//if the level isn't complete check if the board has been completed and set the level as complete if needed
void Level::update(const double, Engine* engine)
{
	if(levelComplete)
	{
		engine->changeState(std::make_shared<GameOver>(mediaCache, numberOfMovesTaken, difficulty));
	}
	else
	{
		if(boardCompleted())
		{
			levelComplete = true;
		}
	}
}

//draw the board and the colour chooser squares, then the menus at the bottom
void Level::render()
{
	for(auto& sq : *board)
	{
		mediaCache.drawRectangle(sq->getRect(),  sq->getColor());
	}

	for(auto& sq : colorChooser)
	{
		mediaCache.drawRectangle(sq->getRect(),  sq->getColor());
	}

	for(auto& item : menu)
	{
		mediaCache.renderTexture(item, item->x(), item->y());
	}

	mediaCache.renderTexture(numMovesWords,			numMovesWords->x(),			numMovesWords->y());
	mediaCache.renderTexture(numMovesTex,			numMovesTex->x(),			numMovesTex->y());
	mediaCache.renderTexture(currentColourWords,	currentColourWords->x(),	currentColourWords->y());
	mediaCache.drawRectangle(currentColourRect->getRect(),  currentColor);
}

//when the level is complete, delay for a second so the user can see the board completed
void Level::exit(Engine*)
{
	if(levelComplete)
	{
		SDL_Delay(750);
	}
}

//===============
//===============

//create the menu for the bottom of the level
void Level::buildMenu()
{
	menu.push_back(mediaCache.getText("Menu", font, mediaCache.getTextColor()));
	menu.back()->setPosition(mediaCache.centreX(menu.back()->w()), mediaCache.scrHeight() - 2 * menu.back()->h());

	menu.push_back(mediaCache.getText("Exit", font, mediaCache.getTextColor()));
	menu.back()->setPosition(mediaCache.centreX(menu[1]->w()), mediaCache.scrHeight() - menu[1]->h());
}

//build the color choosing squares to the right of the board
void Level::buildColorChooser()
{
	auto colors = board->getColors();

	if (colors.size() == 4)
	{
		colorChooser.push_back(std::unique_ptr<Square>(new Square(525, 20, colors[0])));
		colorChooser.push_back(std::unique_ptr<Square>(new Square(525 + 80, 20, colors[2])));
		colorChooser.push_back(std::unique_ptr<Square>(new Square(525, 20 + 80, colors[3])));
		colorChooser.push_back(std::unique_ptr<Square>(new Square(525 + 80, 20 + 80, colors[1])));
	}
	else
	{
		for (unsigned i = 0; i < colors.size(); ++i)
		{
			colorChooser.push_back(std::unique_ptr<Square>(new Square(525 + (i % 3) * 80, 20 + (i % 2) * 80, colors[i])));
		}
	}
	currentColor = colors[0];
}

//create the text informing the player of their move count and current colour
void Level::createText()
{
	numMovesWords = mediaCache.getText("No. of moves:", font, mediaCache.getTextColor());
	numMovesWords->setPosition(mediaCache.scrWidth() - 305, 200);

	numMovesTex = mediaCache.getText(std::to_string(numberOfMovesTaken), font, mediaCache.getTextColor());
	numMovesTex->setPosition(mediaCache.scrWidth() - 55, 200);

	currentColourWords = mediaCache.getText("Current colour:", font, mediaCache.getTextColor());
	currentColourWords->setPosition(mediaCache.scrWidth() - 300, 300);

	currentColourRect = std::make_shared<Square>(610, 360, currentColor);
}

void Level::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		//if the user clicks a colour square at the side update the currentColour
		for (auto& sq : colorChooser)
		{
			if (CollisionEngine::checkCollision(sq->getRect(), x, y))
			{
				currentColor = sq->getColor();
			}
		}

		//if the user clicks in the liveSquares section and has selected a new colour to fill it in, floodFill the board
		SDL_Color topLeftColor = (*board)[0]->getColor();

		for (auto& sq : board->getLiveSquares())
		{
			if (CollisionEngine::checkCollision(sq->getRect(), x, y) && !(FloodFill::sameColor(currentColor, topLeftColor)))
			{
				board->floodFill((*board)[0], 0, sq->getColor(), currentColor);

				++numberOfMovesTaken;

				numMovesTex = mediaCache.getText(std::to_string(numberOfMovesTaken), font, mediaCache.getTextColor());
				numMovesTex->setPosition(mediaCache.scrWidth() - 55, 200);
			}
		}

		//if the user clicks menu or exit, change the state or exit the game
		if (CollisionEngine::checkCollision(menu[0]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
		else if (CollisionEngine::checkCollision(menu[1]->rect(), x, y))
		{
			engine->stopRunning();
		}
	}
}

//iterate through every square on the board checking it is the same colour as the top left square
const bool Level::boardCompleted()
{
	bool complete = true;
	SDL_Color topLeft = (*board)[0]->getColor();

	for (auto& sq : *board)
	{
		if (!(FloodFill::sameColor(sq->getColor(), topLeft)))
		{
			complete = false;
			break;
		}
	}

	return complete;
}