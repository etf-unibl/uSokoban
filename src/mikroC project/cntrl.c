#include "cntrl.h"

key_pressed_code_t is_pressed(key_pressed_t *key) {
	key_pressed_code_t ret_value = KEY_NOT_PRESSED;

	DDRA |= 0xF0;
	DDRA &= 0xFC;
	LEFT=HIGH;
	if(Button(&PIN, 0, 1, HIGH)) {
		*key = KEY_LEFT;
		ret_value = KEY_PRESSED;
	}
	LEFT=!HIGH;

	UPDOWN=HIGH;
	if(Button(&PIN, 0, 1, HIGH) ){
		*key = KEY_DOWN;
		ret_value = KEY_PRESSED;
	}
	if(Button(&PIN, 1, 1, HIGH)){
		*key = KEY_UP;
		ret_value = KEY_PRESSED;
	}
	UPDOWN=!HIGH;

	RIGHT=HIGH;
	if(Button(&PIN, 0, 1, HIGH)) {
		*key = KEY_RIGHT;
		ret_value = KEY_PRESSED;
	}
	RIGHT=!HIGH;

	RST = HIGH;
	if (Button(&PIN, 1, 1, HIGH)) {
		*key = KEY_RST;
		ret_value = KEY_PRESSED;
	}
	RST=!HIGH;

	return ret_value;
}
