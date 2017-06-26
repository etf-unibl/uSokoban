#include "glcd.h"

#define CLEAR 0xFF

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define FIELD_WIDTH                 (SCREEN_WIDTH / MAP_WIDTH)
#define FIELD_HEIGHT                (SCREEN_HEIGHT / MAP_HEIGHT)

/* Glcd module connections */
uint8_t GLCD_DataPort at PORTC;
uint8_t GLCD_DataPort_Direction at DDRC;

sbit GLCD_CS1 at PORTB0_bit;
sbit GLCD_CS2 at PORTB1_bit;
sbit GLCD_RS  at PORTA2_bit;
sbit GLCD_RW  at PORTA3_bit;
sbit GLCD_EN  at PORTD6_bit;
sbit GLCD_RST at PORTD7_bit;

sbit GLCD_CS1_Direction at DDB0_bit;
sbit GLCD_CS2_Direction at DDB1_bit;
sbit GLCD_RS_Direction  at DDA2_bit;
sbit GLCD_RW_Direction  at DDA3_bit;
sbit GLCD_EN_Direction  at DDD6_bit;
sbit GLCD_RST_Direction at DDD7_bit;
/* End Glcd module connection */

/* bitmaps */
static const code uint8_t box[8] = {
0, 60, 90, 102, 102, 90, 60, 0
};

static const code uint8_t box_destination[8] = {
  0,   0,   0,  24,  24,   0,   0,   0
};

static const code uint8_t box_placed[8] = {
0, 60, 66, 66, 66, 66, 60, 0
};

static const code uint8_t player[8] = {
  0,  60, 118,  94,  94, 118,  60,   0
};
/* End bitmaps */

static void draw(field_t type, uint8_t height, uint8_t width);

void glcd_initialization(map_t *map) {
        uint8_t curr_height, curr_width;

        Glcd_init();
        Glcd_fill(CLEAR);

        for(curr_height = 0; curr_height < MAP_HEIGHT; curr_height++){
                for(curr_width = 0; curr_width < MAP_WIDTH; curr_width++){
                        draw(map->grid[curr_height][curr_width], curr_height, curr_width);
                }
        }
}

void glcd_render(map_t *map, refresh_area_t *area){
        uint8_t curr_height, curr_width;
        uint8_t min_height, min_width;
        uint8_t max_height, max_width;

        min_height = (area->y == 0 ? area->y : (area->y) - 1);
        min_width = (area->x == 0 ? area->x : (area->x) - 1);
        max_height = (area->y + 1 == MAP_HEIGHT ? area->y + 1 : (area->y) + 2);
        max_width = (area->x  + 1 == MAP_WIDTH ? area->x + 1 : (area->x) + 2);

		// UART1_Write(min_height + 0x30);
		// UART1_Write(min_width + 0x30);
		// UART1_Write(max_height + 0x30);
		// UART1_Write(max_width + 0x30);
		// UART1_Write(area->y + 0x30);
		// UART1_Write(area->x + 0x30);
		// UART1_Write(10);
		// UART1_Write(13);
        for(curr_height = min_height; curr_height < max_height; curr_height++){
                for(curr_width = min_width; curr_width < max_width; curr_width++){
                        draw(map->grid[curr_height][curr_width], curr_height, curr_width);
						// UART1_Write(map->grid[curr_height][curr_width] + 0x30);
                }
				// UART1_Write(10);
				// UART1_Write(13);
        }
}

static void draw(field_t type, uint8_t height, uint8_t width){
        switch(type){
                case FIELD_EMPTY:
                        Glcd_Box(width * FIELD_WIDTH, height * FIELD_HEIGHT, width * FIELD_WIDTH + FIELD_WIDTH - 1, height * FIELD_HEIGHT + FIELD_HEIGHT - 1, 0);
                        break;
                case FIELD_PLAYER:
						Glcd_PartialImage(width * FIELD_WIDTH, height * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, 8, 8, player);
						break;
				case FIELD_PLAYER_DESTINATION:
                        Glcd_PartialImage(width * FIELD_WIDTH, height * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, 8, 8, player);
                        break;
                case FIELD_BOX:
                        Glcd_PartialImage(width * FIELD_WIDTH, height * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, 8, 8, box);
                        break;
                case FIELD_BOX_DESTINATION:
                        Glcd_PartialImage(width * FIELD_WIDTH, height * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, 8, 8, box_destination);
                        break;
                case FIELD_BOX_PLACED:
                        Glcd_PartialImage(width * FIELD_WIDTH, height * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, 8, 8, box_placed);
                        break;
                default:
                        Glcd_Box(width * FIELD_WIDTH, height * FIELD_HEIGHT, width * FIELD_WIDTH + FIELD_WIDTH - 1, height * FIELD_HEIGHT + FIELD_HEIGHT - 1, 1);
                        break;
        }
}
