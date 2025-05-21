#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>

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


vector<Tile> Board::mergeTile(const vector<Tile>& tiles, int& currentScore) {
	vector<Tile> merged;
	currentScore = 0;
	int i = 0;
	while (i < tiles.size()) {
		if (i + 1 < tiles.size() && tiles[i].getValue() == tiles[i + 1].getValue()) {
			int newValue = tiles[i].getValue() * 2;
			merged.push_back(Tile(newValue));
			currentScore += newValue;
			i += 2;
		}
		else {
			merged.push_back(tiles[i]);
			i++;
		}
	}
	while (merged.size() < GRID_SIZE) {
		merged.push_back(Tile(0));
	}
	return merged;
}

bool Board::moveUp(int& currentScore) {
	bool moved = false;
	currentScore = 0;
	int localScore = 0;
	for (int col = 0; col < GRID_SIZE; col++) {
		vector<Tile> column;
		for (int row = 0; row < GRID_SIZE; row++) {
			if (!grid[row][col].isEmpty()) {
				column.push_back(grid[row][col]);
			}
		}

		vector<Tile> merged = mergeTile(column, localScore);
		currentScore += localScore;

		for (int row = 0; row < GRID_SIZE; row++) {
			if (grid[row][col].getValue() != merged[row].getValue()) {
				moved = true;
			}
			grid[row][col] = merged[row];
		}
	}

	return moved;
}

bool Board::moveDown(int& currentScore) {
	bool moved = false;
	currentScore = 0;
	int localScore = 0;

	for (int col = 0; col < GRID_SIZE; col++) {
		vector<Tile> column;
		for (int row = GRID_SIZE - 1; row >= 0; row--) {
			if (!grid[row][col].isEmpty()) {
				column.push_back(grid[row][col]);
			}
		}

		vector<Tile> merged = mergeTile(column, localScore);
		currentScore += localScore;

		for (int row = 0; row < GRID_SIZE; row++) {
			int index = GRID_SIZE - 1 - row;
			if (grid[index][col].getValue() != merged[row].getValue()) {
				moved = true;
			}
			grid[index][col] = merged[row];
		}
	}

	return moved;
}

bool Board::moveLeft(int& currentScore) {
	bool moved = false;
	currentScore = 0;
	int localScore = 0;

	for (int row = 0; row < GRID_SIZE; row++) {
		vector<Tile> line;
		for (int col = 0; col < GRID_SIZE; col++) {
			if (!grid[row][col].isEmpty()) {
				line.push_back(grid[row][col]);
			}
		}

		vector<Tile> merged = mergeTile(line, localScore);
		currentScore += localScore;

		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].getValue() != merged[col].getValue()) {
				moved = true;
			}
			grid[row][col] = merged[col];
		}
	}

	return moved;
}

bool Board::moveRight(int& currentScore) {
	bool moved = false;
	currentScore = 0;
	int localScore = 0;

	for (int row = 0; row < GRID_SIZE; row++) {
		vector<Tile> line;
		for (int col = GRID_SIZE - 1; col >= 0; col--) {
			if (!grid[row][col].isEmpty()) {
				line.push_back(grid[row][col]);
			}
		}

		vector<Tile> merged = mergeTile(line, localScore);
		currentScore += localScore;

		for (int col = 0; col < GRID_SIZE; col++) {
			int index = GRID_SIZE - 1 - col;
			if (grid[row][index].getValue() != merged[col].getValue()) {
				moved = true;
			}
			grid[row][index] = merged[col];
		}
	}

	return moved;
}



void Board::addRandomTile() {
	vector<pair<int, int>> emptyCell;

	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].isEmpty()) {
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

bool Board::canMerge(int row, int col, int newRow, int newCol) const {

	if (newRow < 0 || newRow >= GRID_SIZE || newCol < 0 || newCol >= GRID_SIZE) {
		return false;
	}

	return (grid[newRow][newCol].isEmpty() || grid[newRow][newCol].getValue() == grid[row][col].getValue());
}

bool Board::slideTile(int row, int col, int newRow, int newCol) {

	if (!canMerge(row, col, newRow, newCol)) {
		return false;
	}

	if (grid[newRow][newCol].isEmpty()) {
		grid[newRow][newCol] = grid[row][col];
		grid[row][col] = Tile(0);
		return true;
	}

	return false;
}

void Board::mergeTiles(int row, int col, int newRow, int newCol) {
	if (grid[newRow][newCol].getValue() == grid[row][col].getValue()) {
		grid[newRow][newCol].setValue(grid[row][col].getValue() * 2);
		grid[row][col] = Tile(0);
	}
}

bool Board::isFull() const {
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			if (grid[row][col].isEmpty())
				return false;
		}
	}
	return true;
}


#include <stdexcept>

const Tile& Board::getTile(int row, int col) const {
	if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
		return grid[row][col];
	}
	throw std::out_of_range("Invalid tile position");
}
