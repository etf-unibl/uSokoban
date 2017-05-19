#include "cntrl.h"

#define HIGH (1)

key_err_code_t is_pressed(key_pressed_t *key){
	
	key_err_code_t ret_value = KEY_ERROR;	
	
	DDRD |= 0xC7;
	DDRD &= 0xCF;
	PORTD0_bit=HIGH;
	if(Button(&PIND, 5, 1, HIGH) ){
		*key = KEY_LEFT;
		ret_value = KEY_OK;
	}
	PORTD0_bit=!HIGH;
	
	PORTD1_bit=HIGH;
	if(Button(&PIND, 5, 1, HIGH) ){
		*key = KEY_DOWN;
		ret_value = KEY_OK;
	}
	if(Button(&PIND, 4, 1, HIGH)){
		*key = KEY_UP;
		ret_value = KEY_OK;
	}
	PORTD1_bit=!HIGH;
	
	PORTD2_bit=HIGH;
	if(Button(&PIND, 5, 1, HIGH) ){
		*key = KEY_RIGHT;
		ret_value = KEY_OK;
	}
	PORTD2_bit=!HIGH;

	return ret_value;
}
