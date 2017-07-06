/**
 * @file display.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a DISPLAY module.
 */
 
#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "vga_uart.h"
#include "glcd.h"

/**
 * @brief Function used for triggering the render process on the display
 * devices.
 *
 * @return @c Returns nothing.
 */
void render(map_t *, refresh_area_t *);

#endif
