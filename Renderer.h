#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"

struct Renderer {

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	void renderTile(int x, int y, const Tile& tile);

	Renderer();
	~Renderer();

	bool initialize();
	void render(const Board& board);
	void renderGameOver();
	void renderYouWin();
	void renderScore(int score);
};