#include "game.h"

// C:\Users\admin\source\repos\2048GAME\2048\2048
int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
	if (TTF_Init() != 0) return -1;

	Game game;

	if (!game.initialize()) {
		return -1;
	}

	game.run();

	TTF_Quit();
	SDL_Quit();
	return 0;
}
