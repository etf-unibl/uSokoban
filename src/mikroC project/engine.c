#include "engine.h"

map_t current_map;

static void get_move_coords(uint8_t *x, uint8_t *y, direction_t dir)
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

static void copy_map(game_t *game)
{
	uint8_t i, j;
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			current_map.grid[i][j] = map[game->level]->grid[i][j];
			if (current_map.grid[i][j] == FIELD_PLAYER) {
				game->player.x = j;
				game->player.y = i;
			}
		}
	}
}

engine_err_code_t engine_init(game_t *game)
{
	game->map = &current_map;
	copy_map(game);
	return ENGINE_OK;
}

void change_level(game_t *game)
{
	copy_map(game);
}

static engine_bool_t can_move(game_t *game, direction_t dir)
{
	uint8_t x = game->player.x, y = game->player.y;
	uint8_t field, next_field;
	engine_err_code_t ret = ENGINE_TRUE;

	get_move_coords(&x, &y, dir);
	if (x >= MAP_WIDTH || y >= MAP_HEIGHT) {
		ret = ENGINE_FALSE;
	}
	else {
		field = game->map->grid[y][x];
		get_move_coords(&x, &y, dir);
		next_field = game->map->grid[y][x];
		if (field == FIELD_OUTSIDE) {
			ret = ENGINE_FALSE;
		}
		if ((field == FIELD_BOX || field == FIELD_BOX_PLACED) && (next_field == FIELD_OUTSIDE || next_field == FIELD_BOX || next_field == FIELD_BOX_PLACED)) {
			ret = ENGINE_FALSE;
		}
		if ((field == FIELD_BOX || field == FIELD_BOX_PLACED) && (x < 0 || y < 0 || x == MAP_WIDTH || y == MAP_HEIGHT)) {
			ret = ENGINE_FALSE;
		}
	}
	return ret;
}

engine_err_code_t move(game_t *game, direction_t dir)
{
	int i, j;
	uint8_t x = game->player.x, y = game->player.y;
	engine_err_code_t ret = ENGINE_ERROR;
	refresh_area_t area;
	if (can_move(game, dir) != ENGINE_FALSE) {
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
		area.x = game->player.x;
		area.y = game->player.y;
		render(game->map, &area);
		ret = ENGINE_OK;
	}
	return ret;
}

engine_bool_t is_finished(map_t *map)
{
	uint8_t count = 0;
	uint8_t i, j;
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (map->grid[i][j] == FIELD_BOX)
				count++;
		}
	}
	return !count;
}
