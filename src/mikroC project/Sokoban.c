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
	glcd_init1(game.map);
	vga_uart_init(game.map);

	while (1) {
		if (is_pressed(&key) == KEY_OK) {
			if (key != KEY_RST) {
				move(&game, key);
				while(is_pressed(&key) == KEY_OK)
					;
			}
			else {
				change_level(&game);
				glcd_init1(game.map);
				vga_uart_render(game.map);
				key = KEY_UP;
			}
			if (is_finished(game.map) && game.level < 2) {
				game.level++;
				change_level(&game);
				glcd_init1(game.map);
				vga_uart_render(game.map);
			}
		}
	}
}
