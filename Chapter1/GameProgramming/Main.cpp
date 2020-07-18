#include"Game.h"

int main(int argc, char** argv) {
	Game game;

	if (game.Initialize())
		game.Update();

	game.ShutDown();

	return 0;
}