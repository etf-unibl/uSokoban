/**
 * @file vga_uart.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a VGA_UART module.
 */

#ifndef _VGA_UART_H
#define _VGA_UART_H

#include "map.h"
#include <stdint.h>

#define BAUDRATE		9600
#define TAG_DIM			0xFF
#define TAG_MAP			0xFE

/**
 * @brief Initializes VGA_UART module. Should be called before using any of the
 * functions belonging to this module.
 * @param map_t Pointer to map structure that should initialize GLCD.
 * @return Returns nothing.
 */
void vga_uart_init(map_t *);

/**
 * @brief Displays the map on the VGA_UART(on PC that runs uSokoban app) module.
 * @param map_t Pointer to map structure that should be replicated on GLCD.
 * @param refresh_area_t Pointer to the area that needs to be refreshed.
 * @return Returns nothing.
 */
void vga_uart_render(map_t *);

#endif
