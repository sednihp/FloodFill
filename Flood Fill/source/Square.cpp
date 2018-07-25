#include "Square.h"

Square::Square(int x, int y, SDL_Color c) : dimension(45), color(c)
{
	sq.x = x;
	sq.y = y;
	sq.w = dimension;
	sq.h = dimension;
}

Square::~Square()
{
}

bool operator< (Square& sq1, Square& sq2)
{
	return sq1.sq.x < sq2.sq.x 
		&& sq2.sq.y < sq2.sq.y;
}