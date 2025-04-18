#include "Renderer.h"
#include <string>

using namespace std;

Renderer::Renderer() : window(nullptr), renderer(nullptr), font(nullptr) {}

Renderer::~Renderer() {
	if (font != nullptr) TTF_CloseFont(font);
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);
	if (window != nullptr) SDL_DestroyWindow(window);
}

bool Renderer::initialize() {
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) return false;

	font = TTF_OpenFont("assets/font/ClearSans-Medium.ttf", 36);
	if (font == nullptr) return false;

	SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
	return true;
}

void Renderer::render(const Board& board) {
	SDL_RenderClear(renderer);

	// draw board
	SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
	SDL_RenderFillRect(renderer, nullptr); 

	// draw tile
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			renderTile(col * (TILE_SIZE + TILE_MARGIN) + BOARD_PADDING,
				row * (TILE_SIZE + TILE_MARGIN) + BOARD_PADDING ,
				board.getTile(row,col));
		}
	}

	SDL_RenderPresent(renderer);
}

void Renderer::renderTile(int x, int y, const Tile& tile) {

	SDL_Color color = tile.getColor();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect tileRect = { x,y,TILE_SIZE, TILE_SIZE };
	SDL_RenderFillRect(renderer, &tileRect);

	if (!tile.isEmpty()) {
		SDL_Color textColor = tile.getTextColor();
		string valueStr = to_string(tile.getValue());

		SDL_Surface* surface = TTF_RenderText_Solid(font, valueStr.c_str(), textColor);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_Rect textRect = {
			x + (TILE_SIZE - surface->w) / 2,
			y + (TILE_SIZE - surface->h) / 2,
			surface->w,
			surface->h
		};

		SDL_RenderCopy(renderer, texture, nullptr, &textRect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void Renderer::renderLose() {
	SDL_Color color = { 255,0,0,200 };
	SDL_Color textColor = { 255,255,255,255 };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect background = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderFillRect(renderer, &background);

	SDL_Surface* surface = TTF_RenderText_Solid(font, "GAME OVER!", textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textRect = {
		(SCREEN_WIDTH - surface->w) / 2,
		(SCREEN_HEIGHT - surface->h) / 2,
		surface->w,
		surface->h
	};
	SDL_RenderCopy(renderer, texture, nullptr, &textRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Renderer::renderWin() {
	SDL_Color color = { 144, 238, 144, 180 };
	SDL_Color textColor = { 0, 100, 0, 255 };

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect background = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderFillRect(renderer, &background);

	SDL_Surface* surface = TTF_RenderText_Solid(font, "YOU WIN!", textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textRect = {
		(SCREEN_WIDTH - surface->w) / 2,
		(SCREEN_HEIGHT - surface->h) / 2,
		surface->w,
		surface->h,
	};
	SDL_RenderCopy(renderer, texture, nullptr, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Renderer::renderScore(int score) {
	string scoreText = "Score: " + to_string(score);
	SDL_Color color = { 255,255,255,255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect textRect = { 20,20,surface->w, surface->h };

	SDL_RenderCopy(renderer, texture, nullptr, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
