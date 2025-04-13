#include "Renderer.h"
#include "Constants.h"
#include <SDL_ttf.h>
#include <string>

Renderer::Renderer() : window(nullptr), renderer(nullptr), font(nullptr) {}

Renderer::~Renderer() {
	if (font) TTF_CloseFont;
	if (renderer) SDL_DestroyRenderer;
	if (window) SDL_DestroyWindow;
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
