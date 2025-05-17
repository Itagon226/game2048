#pragma once
#include <SDL.h>
#include <iostream>
struct Tile {

	int value;

	Tile(int value = 0);

	void setValue(int value);
	int getValue() const;

	bool isEmpty() const;

	// Màu sắc dựa trên giá trị của ô
	SDL_Color getColor() const;
	SDL_Color getTextColor() const;

	std::vector<Animation> animations;
	void addAnimation(const Animation& anim);
	void updateAnimation(float time);
	SDL_Point getRenderPosition() const;
	
};

struct Animation {
	SDL_Point from;
	SDL_Point to;
	float progress = 0.0f;
	bool active = false;
};