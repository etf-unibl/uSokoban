#include "cntrl.h"
#include "engine.h"
#include "display.h"

game_t game;
key_pressed_t key;

void main()
{
	int i, j;
	game.level = 0;
    engine_init(&game);
    glcd_initialization(game.map);

/*
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			UART1_Write(game.map->grid[i][j] + 0x30);
		}
		UART1_Write(13);
	    UART1_Write(10);
	}*/
	while (1) {
		if (is_pressed(&key) == KEY_OK) {
			move(&game, key);
			while(is_pressed(&key) == KEY_OK)
				;
			if (is_finished(game.map) && game.level < 2) {
				game.level++;
				engine_init(&game);
				glcd_initialization(game.map);
			}
		}
	}
}
