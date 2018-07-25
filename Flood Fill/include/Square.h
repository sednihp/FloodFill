#ifndef SQUARE_H
#define SQUARE_H

#include "SDL_Rect.h"

class Square
{
	private:
		const int dimension;
		SDL_Color color;
		SDL_Rect sq;

		Square& operator=(const Square&);
		Square(const Square&);

	public:
		Square(const int x, const int y, const SDL_Color c);
		~Square();

		friend bool operator< (Square& sq1, Square& sq2);

		const SDL_Rect& getRect() const { return sq; }
		const SDL_Color& getColor() const { return color; }

		void changeColor(const SDL_Color& c) { color = c; }
};

#endif