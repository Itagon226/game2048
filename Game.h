#pragma once
#include "Board.h"
#include "Renderer.h"
#include <SDL_mixer.h>

struct Game {

	Game();
	~Game();

	Board board;
	Renderer renderer;
	bool running;
	bool gameOver;
	bool youWin;
	int score;

	// biến âm thanh
	
	bool initialize();
	void run();
	void restart();

	void handleEvents();
	void update();
	void render();

	void MergeSound();
	void WinSound();
	void LoseSound();

};