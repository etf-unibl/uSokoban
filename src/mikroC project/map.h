/**
 * @file map.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a MAP module.
 */

#ifndef _MAP_H
#define _MAP_H

#include <stdint.h>

#define MAP_WIDTH				(16)
#define MAP_HEIGHT				(8)
#define NUMBER_OF_MAPS			(3)


/**
 * @brief Map abstraction with its matrix.
 *
 */
typedef struct map_t {
        uint8_t grid[MAP_HEIGHT][MAP_WIDTH];
} map_t;

/**
 * @brief Used to identify the area to be refreshed.
 *
 */
typedef struct refresh_area {
        uint8_t x;
        uint8_t y;
} refresh_area_t;

/**
 * @brief Used to identify what is present on the field.
 *
 */
typedef enum {
        FIELD_OUTSIDE,
        FIELD_EMPTY,
        FIELD_PLAYER,
        FIELD_PLAYER_DESTINATION,
        FIELD_BOX,
        FIELD_BOX_DESTINATION,
        FIELD_BOX_PLACED
} field_t;

extern map_t *map[NUMBER_OF_MAPS];

#endif
