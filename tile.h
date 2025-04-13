#pragma once
#include <SDL.h>

struct Tile {

	int value;

	Tile(int value = 0);

	void setValue(int value);
	int getValue() const;

	bool isEmpty() const;

	// Màu sắc dựa trên giá trị của ô
	SDL_Color getColor() const;
	SDL_Color getTextColor() const;
};