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

	// Màu s?c d?a trên giá tr? ô
	SDL_Color getColor() const;
	SDL_Color getTextColor() const;
};