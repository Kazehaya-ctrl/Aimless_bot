#include "Game.h"

int main()
{
	srand(time(NULL));
	Game game;
	while(game.is_running()) {
		game.game_update();
		game.game_render();
	}

	return 0;
}