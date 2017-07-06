#ifndef _CNTRL_H
#define _CNTRL_H

#define HIGH		(1)
#define PIN			PINA
#define RIGHT		PORTA7_bit
#define LEFT		PORTA5_bit
#define UPDOWN		PORTA6_bit
#define RST			PORTA4_bit

typedef enum {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_RST
} key_pressed_t;

typedef enum {
	KEY_OK,
	KEY_ERROR
} key_err_code_t;

key_err_code_t is_pressed(key_pressed_t *);

#endif
