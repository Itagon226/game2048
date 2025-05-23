#pragma once
#include <vector>
#include "Tile.h"
#include "Constants.h"



struct Board {

	std::vector<std::vector<Tile>> grid;

	Board();
	void initialize();

	std::vector<Tile> mergeTile(const std::vector<Tile>& tiles, int& currentScore);
	bool moveUp(int& currentScore);
	bool moveDown(int& currentScore);
	bool moveLeft(int& currentScore);
	bool moveRight(int& currentScore);

	void addRandomTile();
	bool Win() const;
	bool canMove() const;

	bool canMerge(int row, int col, int newRow, int newCol) const;
	bool slideTile(int row, int col, int newRow, int newCol);
	void mergeTiles(int row, int col, int newRow, int newCol);
	
	bool isFull() const;
	const Tile& getTile(int row, int col) const ;
	
};