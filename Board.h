#pragma once
#include <vector>
#include "Tile.h"

using namespace std;

class Board {
private:
	vector<vector<Tile>> grid;

	bool canMerge(int row, int col, int newRow, int newCol) const;
	bool slideTile(int row, int col, int newRow, int newCol);
	void mergeTiles(int row, int col, int newRow, int newCol);
public:
	Board();

	void initialize();
	bool isFull() const;
	bool hasMoves() const;

	bool moveTilesUp();
	bool moveTilesDown();
	bool moveTilesLeft();
	bool moveTilesRight();

	void addRandomTile();
	bool hasWon() const;

	const Tile& getTile(int row, int col) const;
};