#include "Game.h"

int main()
{
	Game game;
	while(game.is_running()) {
			game.game_update();
			game.game_render();
	}

	return 0;
}