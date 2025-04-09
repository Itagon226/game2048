#include "Board.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Board::Board() {
	srand(time(0));
	grid.resize(GRID_SIZE, vector<Tile>(GRID_SIZE));
}

void Board::initialize() {
	for (auto& row : grid) {
		for (auto& tile : row) {
			tile.setValue(0);
		}
	}
}

bool Board::moveUp() {
	
}

bool Board::moveDown() {

}

bool Board::moveLeft() {

	bool moved = false;

	for (int row = 0; row < GRID_SIZE; row++) {

		vector<Tile> newRow;

		for (int col = 0; col < GRID_SIZE; col++) {
			if (!grid[row][col].isEmpty()) {
				newRow.push_back(grid[row][col]);
			}
		}

		for (int i = 0; i < newRow.size(); i++) {
			if (i + 1 < newRow.size() && newRow[i].getValue() == newRow[i + 1].getValue()) {
				newRow[i].setValue(newRow[i].getValue() * 2);
				newRow.erase(newRow.begin() + i + 1);
			}
		}

		while (newRow.size() < GRID_SIZE) {
			newRow.push_back(Tile(0));
		}

		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].getValue() != newRow[col].getValue()) {
				moved = true;
			}
			grid[row][col] = newRow[col];
		}
	}

	return moved;
}

bool Board::moveRight() {

	bool moved = false;

	for (int row = 0; row < GRID_SIZE; row++) {

		vector<Tile> newRow;

		for (int col = GRID_SIZE-1; col >= 0 ; col--) {
			if (!grid[row][col].isEmpty()) {
				newRow.insert(newRow.begin(), grid[row][col]);
			}
		}

		for (int i = newRow.size() - 1; i > 0; i--) {
			if (newRow[i].getValue() == newRow[i - 1].getValue()) {
				newRow[i].setValue(newRow[i].getValue() * 2);
				newRow.erase(newRow.begin() + i - 1);
			}
		}

		while (newRow.size() < GRID_SIZE) {
			newRow.insert(newRow.begin(), Tile(0));
		}

		for (int col = 0; col < GRID_SIZE; col++) {
			int index = GRID_SIZE - col - 1;
			if (newRow[col].getValue() != grid[row][index].getValue()) {
				moved = true;
			}
			grid[row][index] = newRow[col];
		}
	}

	return moved;
}

void Board::addRandomTile() {

}

bool Board::hasMoves() const {

}

bool Board::hasWon() const {

}
