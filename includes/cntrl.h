#ifndef _CNTRL_H
#define _CNTRL_H

typedef enum {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN
} key_pressed_t;

typedef enum {
	KEY_OK,
	KEY_ERROR
} key_err_code_t;


key_err_code_t is_pressed(key_pressed_t *);

#endif