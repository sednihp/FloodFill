#include "Board.h"
#include "Util.h"
#include "CollisionEngine.h"
#include <iostream>
#include <fstream>

Board::Board(const int topleftX, const int topleftY, const int d) : numSquaresWide(10), difficulty(d)
{
	generateColors();

	createBoard(topleftX, topleftY);

	liveSquares.insert(board[0]);
}

void Board::generateColors()
{
	//standard 4 colours
	SDL_Color c = {255,0,128};		//pink
	colors.push_back(c);
	c.r = 0; c.g = 160; c.b = 0;	//green
	colors.push_back(c);
	c.r = 255; c.g = 160; c.b = 0;	//orange
	colors.push_back(c);
	c.r = 128; c.g = 0; c.b = 128;	//purple
	colors.push_back(c);
	
	if (difficulty > 4)
	{
		c.r = 0; c.g = 0; c.b = 255;	//blue
		colors.push_back(c);

		if (difficulty > 5)
		{
			c.r = 0; c.g = 192; c.b = 192;	//dark teal
			colors.push_back(c);
		}
	}
}

//create a board of 100 squares, 10 squares wide
//give the squares a random color
//move x across by the width of the square
//if we get to the 10th square, reset x back to the left and move y down
void Board::createBoard(int topleftX, int topleftY)
{
	int x = topleftX;
	int y = topleftY;

	for(int i=0; i<100; ++i)
	{
		SDL_Color c = colors[rand() % colors.size()];
		board.push_back(std::make_shared<Square>(x, y, c));
		
		int dimension = board.back()->getRect().w;
		x += dimension;
		if(x >= topleftX + numSquaresWide*dimension)
		{
			x = topleftX;
			y += dimension;
		}
	}
}

Board::~Board()
{
	
}

std::shared_ptr<Square> Board::operator[](const int index)
{
	return board[index];
}

//check that we're not trying to change to the same color
//if the current square's colour is different from the oldColor we're changing from, then the squares weren't the same to begin with
//otherwise, change the color of the square to the new color and add the square to liveSquares
void Board::floodFill(std::shared_ptr<Square> sq, int index, SDL_Color oldColor, SDL_Color newColor)
{
	if(FloodFill::sameColor(oldColor, newColor) ||  !(FloodFill::sameColor(sq->getColor(), oldColor)))
	{
		return;
	}

	sq->changeColor(newColor);
	liveSquares.insert(sq);

	//one square to the left as long as we're not in the far left column
	if(index % 10 != 0 && index - 1 >= 0)
	{
		floodFill(board[index - 1], index - 1, oldColor, newColor);
	}

	//one square to the right as long as we're not in the far right column or the topleft square (which has index 0 and 0 % 9 == 0)
	if((index % 9 != 0 && index + 1 < 100) || index == 0)
	{
		floodFill(board[index + 1], index + 1, oldColor, newColor);
	}

	//one square above as long as we're not in the top row
	if(index > 9)
	{
		floodFill(board[index - 10], index - 10, oldColor, newColor);
	}

	//one square below as long as we're not in the bottom row
	if(index < 90)
	{
		floodFill(board[index + 10], index + 10, oldColor, newColor);
	}
}