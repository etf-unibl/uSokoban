#include "vga_uart.h"

static void send_map(map_t *map) {
	uint8_t i, j;

	UART1_Write(TAG_DIM);
    UART1_Write(MAP_WIDTH);
    UART1_Write(MAP_HEIGHT);
    UART1_Write(TAG_MAP);
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			UART1_Write(map->grid[i][j]);
		}
	}
}

void vga_uart_init(map_t *map)
{
	UART1_Init(BAUDRATE);
	send_map(map);
}

void vga_uart_render(map_t *map)
{
	send_map(map);
}
