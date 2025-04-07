#include "Game.h"
#include "Constants.h"
#include <SDL.h>

Game::Game() : running(false), gameOver(false), youWin(false), score(0) {}

Game::~Game() {
	// Các hàm hủy âm thanh

	// Hủy font chữ

	SDL_Quit();
}

bool Game::initialize() {

	// Khởi tạo SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize: %s", SDL_GetError());
		return false;
	}

	// Khởi tạo ttf

	// Khởi tạo mixer

	// Khởi tạo renderer
	if (!renderer.initialize()) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Renderer initialize: %s", SDL_GetError());
		return false;
	}

	// Load âm thanh

	// Khởi tạo game
	restart();
	running = true;

	return true;
}

void Game::run() {

	unsigned int frameStart, frameTime;
	const unsigned int frameDelay = 1000 / 60;

	while (running) {
		frameStart = SDL_GetTicks();

		handleEvents;
		update();
		render();

		// Delay thời gian để đồng bộ là 60FPS
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}