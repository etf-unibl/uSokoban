#include "vga.h"
#include <stdint.h>

static uint16_t ticks;
static uint16_t intervals;

static void init(void);
static void init_timer1_ctc(void);

static void init_vga(void)
{
     /* PORTB as output and set to LOW. */
     DDRB   = 0xFF;
     PORTB  = 0;
     init_timer1_ctc();
}

static void init_timer1_ctc(void)
{
     /* TOP value. This should generate interrupt every
        0.25us */
     OCR1AH = 0x00;
     OCR1AL = 0x00;
     /* Choose CTC mode with no prescaling and
        start timer. */
     TCCR1B = 0x05;
     TCCR1A = 0x00;
     /* Global interrupt enable. */
     SREG_I_bit = 1;
     /* Timer 1 output compare match interrupt enable. */
     OCIE1A_bit  = 1;
}

void timer1_ctc_ISR() org IVT_ADDR_TIMER1_COMPA
{
    /* This should generate 2MHz clock. */
    PORTB0_bit = ~PORTB0_bit;
    if (++ticks == 0)
    {
       /* 16ms elapsed. */
       if (intervals++ > 63)
       {
          /* This should be one second interval. */
          PORTB1_bit = ~PORTB1_bit;
       }
    }
}

void vga_render(map_t *)
{

}
