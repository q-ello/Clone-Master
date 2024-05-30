#include "Game.h"

int main()
{
	srand(time(NULL));
	Game* game = new Game();
	game->play();
	delete game;
	return 0;
}