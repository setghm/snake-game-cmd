#include "game/game.h"
#include <stdio.h>

int main(void) {
	Game* game = GameCreate("Snake Game");
	
	if (!game) {
		fputs("Can't initialize the game", stderr);
		return -1;
	}
	
	while (game->running) {
		GameUpdate(game);
	}
	
	GameCleanup(game);
	
	return 0;
}