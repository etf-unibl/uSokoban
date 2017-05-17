#include "glcd.h"

#define CLEAR 0xFF

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define FIELD_WIDTH			(SCREEN_WIDTH / MAP_WIDTH)
#define FIELD_HEIGHT		(SCREEN_HEIGHT / MAP_HEIGHT)



/* Glcd module connections */
static char GLCD_DataPort at PORTC;
static char GLCD_DataPort_Direction at DDRC;

static sbit GLCD_CS1 at PORTB0_bit;
static sbit GLCD_CS2 at PORTB1_bit;
static sbit GLCD_RS  at PORTA2_bit;
static sbit GLCD_RW  at PORTA3_bit;
static sbit GLCD_EN  at PORTD6_bit;
static sbit GLCD_RST at PORTD7_bit;

static sbit GLCD_CS1_Direction at DDB0_bit;
static sbit GLCD_CS2_Direction at DDB1_bit;
static sbit GLCD_RS_Direction  at DDA2_bit;
static sbit GLCD_RW_Direction  at DDA3_bit;
static sbit GLCD_EN_Direction  at DDD6_bit;
static sbit GLCD_RST_Direction at DDD7_bit;
/* End Glcd module connection */

/* bitmaps */
static const code char box[8] = {
255, 195, 165, 153, 153, 165, 195, 255
};

static const code char box_destination[8] = {
  0,   0,   0,  24,  24,   0,   0,   0
};

static const code char box_placed[8] = {
255, 195, 189, 189, 189, 189, 195, 255
};

static const code char player[8] = {
  0,  60, 118,  94,  94, 118,  60,   0
};

void glcd_render(map_t *map)
{	
    Glcd_fill(CLEAR);
	unsigned char curr_height,curr_width;
	for(curr_height=0;curr_height<MAP_HEIGHT;curr_height++){
		for(curr_width=0;curr_width<MAP_WIDTH;curr_width++){
			draw(map->grid[curr_width][curr_height],curr_height,curr_width);
		}
	}
}

static void draw(field_t type,unsigned char height, unsigned char width){
	switch(type){
		case FIELD_EMPTY:
		    Glcd_Box(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,0);
			break;
		case FIELD_PLAYER:
			Glcd_PartialImage(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,FIELD_WIDTH,FIELD_HEIGHT,player);
			break;
		case FIELD_BOX:
			Glcd_PartialImage(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,FIELD_WIDTH,FIELD_HEIGHT,box);		
			break;
		case FIELD_BOX_DESTINATION:
			Glcd_PartialImage(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,FIELD_WIDTH,FIELD_HEIGHT,box_destination);		
			break;
		case FIELD_BOX_PLACED:
			Glcd_PartialImage(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,FIELD_WIDTH,FIELD_HEIGHT,box_placed);		
			break;
		default:
			Glcd_Box(width*FIELD_WIDTH,height*FIELD_HEIGHT,width*FIELD_WIDTH+FIELD_WIDTH,height*FIELD_HEIGHT+FIELD_HEIGHT,2);
			break;
	}
}