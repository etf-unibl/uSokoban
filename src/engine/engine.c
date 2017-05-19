#include "engine.h"

uint8_t temp[MAP_HEIGHT][MAP_WIDTH] = {
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, 		  FIELD_OUTSIDE, FIELD_OUTSIDE,    FIELD_OUTSIDE, 		  FIELD_OUTSIDE, 		 FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, 		  FIELD_OUTSIDE, FIELD_EMPTY,	   FIELD_EMPTY,   		  FIELD_EMPTY,   		 FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_BOX_DESTINATION, FIELD_PLAYER,  FIELD_BOX, 	   FIELD_EMPTY, 		  FIELD_EMPTY,  		 FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, 		  FIELD_OUTSIDE, FIELD_EMPTY, 	   FIELD_BOX, 			  FIELD_BOX_DESTINATION, FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_BOX_DESTINATION, FIELD_OUTSIDE, FIELD_OUTSIDE,    FIELD_BOX, 			  FIELD_EMPTY, 			 FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_EMPTY, 		  FIELD_OUTSIDE, FIELD_EMPTY, 	   FIELD_BOX_DESTINATION, FIELD_EMPTY, 			 FIELD_OUTSIDE, 		FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_BOX, 			  FIELD_EMPTY,   FIELD_BOX_PLACED, FIELD_BOX, 			  FIELD_BOX, 			 FIELD_BOX_DESTINATION, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE,
	FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_EMPTY, 		  FIELD_EMPTY,   FIELD_EMPTY, 	   FIELD_BOX_DESTINATION, FIELD_EMPTY, 			 FIELD_EMPTY, 			FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE, FIELD_OUTSIDE
};

void get_move_coords(uint8_t *x, uint8_t *y, direction_t dir)
{
	switch (dir) {
		case DIR_LEFT:
			(*x)--;
			break;
		case DIR_RIGHT:
			(*x)++;
			break;
		case DIR_UP:
			(*y)--;
			break;
		case DIR_DOWN:
			(*y)++;
			break;
	}
}

engine_err_code_t init(game_t *game)
{
	int i, j;

	game->map = malloc(sizeof(map_t));
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			game->map->grid[i][j] = temp[i][j];
			if (temp[i][j] == FIELD_PLAYER) {
				game->player.x = j;
				game->player.y = i;
			}
		}
	}
	return ENGINE_OK;
}

engine_err_code_t can_move(game_t *game, direction_t dir)
{
	uint8_t x = game->player.x, y = game->player.y;
	uint8_t field, next_field;
	engine_err_code_t ret = ENGINE_OK;

	get_move_coords(&x, &y, dir);
	field = game->map->grid[y][x];
	get_move_coords(&x, &y, dir);
	next_field = game->map->grid[y][x];
	if (field == FIELD_OUTSIDE) {
		ret = ENGINE_ERROR;
	}
	if ((field == FIELD_BOX || field == FIELD_BOX_PLACED) && (next_field == FIELD_OUTSIDE || next_field == FIELD_BOX || next_field == FIELD_BOX_PLACED)) {
		ret = ENGINE_ERROR;
	}
	return ret;
}

engine_err_code_t move(game_t *game, direction_t dir)
{
	uint8_t x = game->player.x, y = game->player.y;
	engine_err_code_t ret = ENGINE_ERROR;
	if (can_move(game, dir) != ENGINE_ERROR) {
		if (game->map->grid[game->player.y][game->player.x] == FIELD_PLAYER_DESTINATION) {
			game->map->grid[game->player.y][game->player.x] = FIELD_BOX_DESTINATION;
		}
		else {
			game->map->grid[game->player.y][game->player.x] = FIELD_EMPTY;
		}
		get_move_coords(&x, &y, dir);
		game->player.x = x;
		game->player.y = y;

		if (game->map->grid[game->player.y][game->player.x] == FIELD_BOX || game->map->grid[game->player.y][game->player.x] == FIELD_BOX_PLACED) {
			get_move_coords(&x, &y, dir);
			if (game->map->grid[y][x] == FIELD_EMPTY) {
				game->map->grid[y][x] = FIELD_BOX;
			}
			else if (game->map->grid[y][x] == FIELD_BOX_DESTINATION) {
				game->map->grid[y][x] = FIELD_BOX_PLACED;
			}

			if (game->map->grid[game->player.y][game->player.x] == FIELD_BOX) {
				game->map->grid[game->player.y][game->player.x] = FIELD_PLAYER;
			}
			else if (game->map->grid[game->player.y][game->player.x] == FIELD_BOX_PLACED) {
				game->map->grid[game->player.y][game->player.x] = FIELD_PLAYER_DESTINATION;
			}
		}
		else if (game->map->grid[game->player.y][game->player.x] == FIELD_EMPTY) {
			game->map->grid[game->player.y][game->player.x] = FIELD_PLAYER;
		}
		else if (game->map->grid[game->player.y][game->player.x] == FIELD_BOX_DESTINATION) {
			game->map->grid[game->player.y][game->player.x] = FIELD_PLAYER_DESTINATION;
		}
		render(game->map, NULL);
		ret = ENGINE_OK;
	}
	return ret;
}
