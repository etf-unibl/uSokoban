#ifndef _ENGINE_H
#define _ENGINE_H

#include "display.h"
#include "cntrl.h"

typedef enum {
	ENGINE_OK,
	ENGINE_ERROR
} engine_err_code_t;

typedef enum {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
} direction_t;

typedef struct player {
	uint8_t x;
	uint8_t y;
} player_t;

typedef struct game {
	map_t *map;
	player_t player;
} game_t;

engine_err_code_t init(game_t *);
engine_err_code_t move(game_t *, direction_t dir);

#endif
