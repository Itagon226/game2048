#include "Board.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Board::Board() {
	srand(static_cast<unsigned int>(time(0)));
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
	bool moved = false;

	for (int col = 0; col < GRID_SIZE; col++) {
		vector<Tile> newCol;

		for (int row = 0; row < GRID_SIZE; row++) {
			if (!grid[row][col].isEmpty()) {
				newCol.push_back(grid[row][col]);
			}
		}

		for (int i = 0; i < newCol.size(); i++) {
			if (i + 1 < newCol.size() && newCol[i].getValue() == newCol[i + 1].getValue()) {
				newCol[i].setValue(newCol[i].getValue() * 2);
				newCol.erase(newCol.begin() + i + 1);
			}
		}
		
		while (newCol.size() < GRID_SIZE) {
			newCol.push_back(Tile(0));
		}

		for (int row = 0; row < GRID_SIZE; row++) {
			if (grid[row][col].getValue() != newCol[row].getValue()) {
				moved = true;
			}
			grid[row][col] = newCol[row];
		}
	}

	return moved;
}

bool Board::moveDown() {
	bool moved = false;
	
	for (int col = 0; col < GRID_SIZE; col++) {
		vector<Tile> newCol;

		for (int row = GRID_SIZE - 1; row >= 0; row--) {
			if (!grid[row][col].isEmpty()) {
				newCol.insert(newCol.begin(), grid[row][col]);
			}
		}

		reverse(newCol.begin(), newCol.end());
		for (int i = 0; i < newCol.size() - 1; i++) {
			if (newCol[i].getValue() == newCol[i + 1].getValue()) {
				newCol[i].setValue(newCol[i].getValue() * 2);
				newCol.erase(newCol.begin() + i + 1);
			}
		}
		reverse(newCol.begin(), newCol.end());

		while (newCol.size() < GRID_SIZE) {
			newCol.insert(newCol.begin(), Tile(0));
		}

		for (int row = 0; row < GRID_SIZE; row++) {
			int index = GRID_SIZE - row - 1;
			if (grid[index][col].getValue() != newCol[row].getValue()) {
				moved = true;
			}
			grid[index][col] = newCol[row];
		}
	}
	return moved;
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

		reverse(newRow.begin(), newRow.end());
		for (int i = 0; i < newRow.size() - 1; i++) {
			if (newRow[i].getValue() == newRow[i + 1].getValue()) {
				newRow[i].setValue(newRow[i].getValue() * 2);
				newRow.erase(newRow.begin() + i + 1);
			}
		}
		reverse(newRow.begin(), newRow.end());

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
	vector<pair<int, int>> emptyCell;

	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].isEmpty()) {
				pair<int, int> cell;
				emptyCell.push_back(make_pair(row, col));
			}
		}
	}

	if (!emptyCell.empty()) {
		int randomCell = rand() % emptyCell.size();
		int randomRow = emptyCell[randomCell].first;
		int randomCol = emptyCell[randomCell].second;

		int value;
		int randomNum = rand() % 10;
		if (randomNum == 0) {
			value = 4;
		}
		else value = 2;
		grid[randomRow][randomCol].setValue(value);
	}
}

bool Board::canMove() const {
	
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].isEmpty())
				return true;

			if (row < GRID_SIZE - 1 && grid[row][col].getValue() == grid[row + 1][col].getValue())
				return true;

			if (col < GRID_SIZE - 1 && grid[row][col].getValue() == grid[row][col + 1].getValue())
				return true;
		}
	}

	return false;
}

bool Board::Win() const {

	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].getValue() == 2048)
				return true;
		}
	}

	return false;
}
