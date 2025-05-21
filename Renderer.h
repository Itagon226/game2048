#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"
#include <string>

struct Button {
	SDL_Rect rect;
	std::string text;
};

struct Renderer {

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	Renderer();
	~Renderer();

	bool initialize();
	void render(const Board& board, int score, int highScore);
	void renderLose();
	void renderWin();

	void renderTile(int x, int y, const Tile& tile);
	bool isPointInButton(int x, int y, const Button& button);

	Button PlayAgain;
	Button Exit;
};