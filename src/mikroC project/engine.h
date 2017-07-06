/**
 * @file engine.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a ENGINE module.
 */
 
#ifndef _ENGINE_H
#define _ENGINE_H

#include "display.h"
#include "cntrl.h"
#include <stddef.h>

/**
 * @brief Used for IDing is everything OK with the ENGINE module.
 *
 */
typedef enum {
	ENGINE_OK,
	ENGINE_ERROR
} engine_err_code_t;

/**
 * @brief Introducing "boolean" data.
 *
 */
typedef enum {
	ENGINE_FALSE,
	ENGINE_TRUE
} engine_bool_t;

/**
 * @brief Used for applying player movement.
 *
 */
typedef enum {
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
} direction_t;

/**
 * @brief Player abstraction with its coordinates.
 *
 */
typedef struct player {
	uint8_t x;
	uint8_t y;
} player_t;

/**
 * @brief All data regarding game, including map state, player position
 * and level being played.
 *
 */
typedef struct game {
	map_t *map;
	player_t player;
	uint8_t level;
} game_t;

/**
 * @brief Initializes ENGINE module. Should be called before using any of the
 * functions belonging to this module.
 * @param game_t Pointer to game structure.
 * @return Returns ENGINE_OK.
 */
engine_err_code_t engine_init(game_t *);

/**
 * @brief Changes current level. Should be called before using any of the
 * functions belonging to this module.
 * @param game_t Pointer to the game structure.
 * @return Returns nothing.
 */
void change_level(game_t *);

/**
 * @brief Changes current level.
 * @param game_t Pointer to the game structure.
 * @param direction_t Direction where player wants to move.
 * @return Returns error if player cannot go that way, else OK.
 */
engine_err_code_t move(game_t *, direction_t);

/**
 * @brief Changes current level.
 * @param map_t Pointer to the map structure.
 * @return Returns ENGINE_TRUE if all boxes are at right spot, else ENGINE_FALSE.
 */
engine_bool_t is_finished(map_t *);

#endif
