/**
 * @file cntrl.h
 * @author ANS
 * @date 6 July 2017
 * @brief File containing headers of a CNTRL module.
 */
 
#ifndef _CNTRL_H
#define _CNTRL_H

#define HIGH		(1)
#define PIN			PINA
#define RIGHT		PORTA7_bit
#define LEFT		PORTA5_bit
#define UPDOWN		PORTA6_bit
#define RST			PORTA4_bit


/**
 * @brief Used for IDing what is pressed.
 *
 */
typedef enum {
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_RST
} key_pressed_t;

/**
 * @brief Used for detecting the event of pressed button.
 *
 */
typedef enum {
	KEY_PRESSED,
	KEY_NOT_PRESSED
} key_pressed_code_t;

/**
 * @brief Simple function for detecting is some key pressed.
 *
 * @return @c Returns what is pressed.
 */
key_pressed_code_t is_pressed(key_pressed_t *);

#endif
