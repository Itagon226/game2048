#include "game.h"

// C:\Users\admin\source\repos\2048GAME\2048\2048
int main(int argc, char* argv[]) {
	Game game;

	if (!game.initialize()) {
		return -1;
	}

	game.run();

	return 0;
}
