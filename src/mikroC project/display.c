#include "display.h"

void render(map_t *map, refresh_area_t *player)
{
	glcd_render(map, player);
	vga_uart_render(map);
}
