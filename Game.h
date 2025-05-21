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
	int highScore;

	// biến âm thanh
	bool musicPlaying = false;
	Mix_Music* bgMusic = nullptr;
	Mix_Chunk* winSound = nullptr;
	Mix_Chunk* loseSound = nullptr;
	
	bool initialize();
	void run();
	void restart();
	void loadHighScore();
	void saveHighScore();

	void handleEvents();
	void update();
	void render();

};