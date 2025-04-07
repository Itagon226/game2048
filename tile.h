#pragma once
#include <SDL.h>

struct Tile {

	int value;

	Tile(int value = 0);

	int getValue() const;
	void setValue(int value);

	bool isEmpty() const;

	// M�u s?c d?a tr�n gi� tr? �
	SDL_Color getColor() const;
	SDL_Color getTextColor() const;
};