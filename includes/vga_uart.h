#ifndef _VGA_UART_H
#define _VGA_UART_H

#include "map.h"
#include <stdint.h>

#define BAUDRATE		9600
#define TAG_DIM			0xFF
#define TAG_MAP			0xFE

void vga_uart_init(map_t *);
void vga_uart_render(map_t *);

#endif
