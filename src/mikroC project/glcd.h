/**
 * @file glcd.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a GLCD module.
 */

#ifndef _GLCD_H
#define _GLCD_H

#include "map.h"

/**
 * @brief Initializes GLCD module. Should be called before using any of the
 * functions belonging to this module.
 * @param map_t Pointer to map structure that should initialize GLCD.
 * @return Returns nothing.
 */
void glcd_init1(map_t *);

/**
 * @brief Displays the map on the GLCD module.
 * @param map_t Pointer to map structure that should be replicated on GLCD.
 * @param refresh_area_t Pointer to the area that needs to be refreshed.
 * @return Returns nothing.
 */
void glcd_render(map_t *, refresh_area_t *);

#endif
