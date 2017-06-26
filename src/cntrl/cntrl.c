#include "cntrl.h"

#define HIGH (1)
#define PIN			PINA
#define RIGHT		PORTA7_bit
#define LEFT		PORTA5_bit
#define UPDOWN		PORTA6_bit

key_err_code_t is_pressed(key_pressed_t *key){

	key_err_code_t ret_value = KEY_ERROR;

	DDRA |= 0xE0;
	DDRA &= 0xFC;
	LEFT=HIGH;
	if(Button(&PIN, 0, 1, HIGH) ){
		*key = KEY_LEFT;
		ret_value = KEY_OK;
	}
	LEFT=!HIGH;

	UPDOWN=HIGH;
	if(Button(&PIN, 0, 1, HIGH) ){
		*key = KEY_DOWN;
		ret_value = KEY_OK;
	}
	if(Button(&PIN, 1, 1, HIGH)){
		*key = KEY_UP;
		ret_value = KEY_OK;
	}
	UPDOWN=!HIGH;

	RIGHT=HIGH;
	if(Button(&PIN, 0, 1, HIGH) ){
		*key = KEY_RIGHT;
		ret_value = KEY_OK;
	}
	RIGHT=!HIGH;

	return ret_value;
}
