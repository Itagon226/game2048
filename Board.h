#pragma once
#include <vector>
#include "Tile.h"



struct Board {

	std::vector<std::vector<Tile>> grid;

	Board();
	void initialize();

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	void addRandomTile();
	bool hasWon() const;
	bool hasMoves() const;

	bool canMerge(int row, int col, int newRow, int newCol) const;
	bool slideTile(int row, int col, int newRow, int newCol);
	void mergeTiles(int row, int col, int newRow, int newCol);
	
	bool isFull() const;

	const Tile& getTile(int row, int col) const;
};