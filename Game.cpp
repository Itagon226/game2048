#include "Game.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>

using namespace std;

Game::Game() : running(false), gameOver(false), youWin(false), bgMusic(nullptr), winSound(nullptr), loseSound(nullptr), musicPlaying(false), score(0), highScore(0) {}

Game::~Game() {
	
	Mix_FreeMusic(bgMusic);
	Mix_FreeChunk(winSound);
	Mix_FreeChunk(loseSound);
	bgMusic = nullptr;
	winSound = nullptr;
	loseSound = nullptr;

	Mix_CloseAudio();
	Mix_Quit();
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
	if (Mix_Init(MIX_INIT_MP3) == 0) {
		cerr << "SDL_mixer could not init required support for mp3. Error: " << Mix_GetError() << std::endl;
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	// Khởi tạo renderer
	if (!renderer.initialize()) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Renderer initialize: %s", SDL_GetError());
		return false;
	}

	// Load âm thanh
	bgMusic = Mix_LoadMUS("assets/sound/nhacnen.mp3");
	winSound = Mix_LoadWAV("assets/sound/win.wav");
	loseSound = Mix_LoadWAV("assets/sound/lose.wav");

	if (!bgMusic || !winSound || !loseSound) {
		cerr << "Failed to load sound! Error: " << Mix_GetError() << std::endl;
	}

	// Khởi tạo game
	restart();
	running = true;
	loadHighScore();
	return true;
}

void Game::run() {

	unsigned int frameStart, frameTime;
	const unsigned int frameDelay = 1000 / 60;

	while (running) {
		frameStart = SDL_GetTicks();

		if (!musicPlaying && !Mix_PlayingMusic()) {
			Mix_PlayMusic(bgMusic, -1); 
			musicPlaying = true;
		}

		handleEvents();
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
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				running = false;
				break;
			case SDLK_F5:
				restart();
				break;
			default:
				if (!gameOver && !youWin) {
					int currentscore = 0;
					switch (event.key.keysym.sym) {
					case SDLK_UP:
						if (board.moveUp(currentscore)) {
							score += currentscore;
							board.addRandomTile();
						}
						break;
					case SDLK_DOWN:
						if (board.moveDown(currentscore)) {
							score += currentscore;
							board.addRandomTile();
						}
						break;
					case SDLK_LEFT:
						if (board.moveLeft(currentscore)) {
							score += currentscore;
							board.addRandomTile();
						}
						break;
					case SDLK_RIGHT:
						if (board.moveRight(currentscore)) {
							score += currentscore;
							board.addRandomTile();
						}
						break;
					}
				}
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN && gameOver) {
			int x = event.button.x;
			int y = event.button.y;
			if (renderer.isPointInButton(x, y, renderer.PlayAgain)) {
				restart();
			}
			else if (renderer.isPointInButton(x, y, renderer.Exit)) {
				running = false;
			}
		}
	}
}


void Game::update() {
	if (!board.canMove()) {
		gameOver = true;
		Mix_PlayChannel(-1, loseSound, 0);
	}
	else if (board.Win() && !youWin) {
		youWin = true;
		Mix_PlayChannel(-1, winSound, 0);
	}
	if (score > highScore) {
		highScore = score;
		saveHighScore();
	}
}

void Game::render() {
	renderer.render(board, score, highScore);
	
	if (gameOver)
		renderer.renderLose();
	else if (youWin)
		renderer.renderWin();
}

void Game::restart() {
	board.initialize();
	gameOver = false;
	youWin = false;
	score = 0;
	board.addRandomTile();
	board.addRandomTile();
}

void Game::loadHighScore() {
	ifstream file("highscore.txt");
	if (file.is_open()) {
		file >> highScore;
		file.close();
	}
}

void Game::saveHighScore() {
	ofstream file("highscore.txt");
	if (file.is_open()) {
		file << highScore;
		file.close();
	}
}