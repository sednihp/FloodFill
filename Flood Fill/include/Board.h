#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#include <vector>
#include <set>
#include <memory>

class Board
{
	private:
		const short numSquaresWide;
		int difficulty;
		std::vector<std::shared_ptr<Square>> board;
		std::set<std::shared_ptr<Square>> liveSquares;
		std::vector<SDL_Color> colors;

		void generateColors();
		void createBoard(const int x, const int y);

		Board& operator=(const Board&);
		Board(const Board&);

	public:
		Board(const int topleftX, const int topleftY, const int d);
		~Board();

		void floodFill(std::shared_ptr<Square> sq, const int num, const SDL_Color& oldColor, const SDL_Color& newColor);

		std::vector<std::shared_ptr<Square>>::iterator begin() { return board.begin(); }
		std::vector<std::shared_ptr<Square>>::iterator end() { return board.end(); }
		std::shared_ptr<Square> operator[](const int index);

		const std::vector<SDL_Color>& getColors() { return colors; }
		std::set<std::shared_ptr<Square>>& getLiveSquares() { return liveSquares; }
};

#endif