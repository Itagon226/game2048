#pragma once
#include <SDL.h>

class Tile {
private:
	int value;
public: 
	Tile(int value = 0);

	int getValue() const;
	void setValue(int value);

	bool isEmpty() const;

	// M�u s?c d?a tr�n gi� tr? �
	SDL_Color getColor() const;
	SDL_Color getTextColor() const;
};