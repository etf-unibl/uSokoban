#include <stdint.h>
#include <string.h>
#include "symbols_tbl.h"

#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))

#define TRUE (1)
#define FALSE (0)

//Global definitions for VGA render
#define VGA_FIELD_LINE_COUNT (525) //standard VGA quantity lines
#define VGA_SYMBOLS_PER_ROW (20) //symbols quantity per horizontal
#define VGA_ROW_COUNT (20) //symbols quantity per vertical
#define VGA_SYMBOL_HEIGHT (24) //rendered symbol height

//Video
#define VIDEO_OFF DDRB = 0x90
#define VIDEO_ON DDRB = 0xB0
//HSYNC
#define HSYNC_OFF sbi(PORTB, 3)
#define HSYNC_ON cbi(PORTB, 3)
//VSYNC
#define VSYNC_OFF sbi(PORTB, 2)
#define VSYNC_ON cbi(PORTB, 2)

volatile uint8_t str_array[VGA_SYMBOLS_PER_ROW * VGA_ROW_COUNT + 1]; //Chars array for display buffer
volatile uint16_t current_symbol; //Current symbol number at terminal

volatile uint8_t video_enable_flg; //flag for enable render
volatile uint8_t raw_render; //Current row at display buffer for render
volatile uint16_t linecount; //Current line for render
volatile uint8_t y_line_render; //Current Y-line at symbol for render

const char str2[] = "Simple VGA terminal";
const char str3[] = "v1.2 UART-19200 bps";

static void avr_init(void);

//All VGA sincronize made here..
void Timer0Overflow_ISR() org IVT_ADDR_TIMER0_OVF
{
    TCNT0 = 0xC3;
    //Count number of lines
    if (++linecount >= VGA_FIELD_LINE_COUNT) {
        linecount = 0;
        raw_render = 0;
        y_line_render = 0;
    }

    //Make Vsync length 2 VGA lines
    if ((linecount == 10) || (linecount == 11)) {
        //Make here vertical syncronization & HSYNC syncro level on
        VSYNC_ON;
        cbi(PORTB, 3);
        //VSYNC_OFF;
    }
    else {
        //.. & HSYNC syncro level on
        //VSYNC_ON;
        VSYNC_OFF;
        cbi(PORTB, 3);
    }

    video_enable_flg = TRUE;

    if (linecount < 45) {
        video_enable_flg = FALSE;
        //Add to avoid flickering at top display
        asm {
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP
            NOP                 
            NOP
            NOP
            NOP
            NOP
        }
    }
    else {
        //Forming current string for rendering
        if (++y_line_render == VGA_SYMBOL_HEIGHT) {
            raw_render++;
            y_line_render = 0;
        }
        else {
            asm {
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
            }
        }
    }

    HSYNC_OFF;
}

void spi_init(void)
{
    sbi(DDRB, 7); //SCK
    cbi(DDRB, 6); //MISO
    sbi(DDRB, 5); //MOSI
    sbi(DDRB, 4); //SS
    SPSR = 1 << SPI2X;
    SPCR = (1 << SPE) | (1 << MSTR); //SPI enable as master ,FREQ = fclk/2
    //That's a great pity, that we can't work with SPI with FREQ = fclk,
    //because may be possible build terminal up 40 symbol per row!!!
}

void vga_render()
{
    unsigned char i;
    char* _ptr;
    char* _ptr1;

    //Initialize display buffer with StartUp strings
    strcpy(&str_array[VGA_SYMBOLS_PER_ROW * (VGA_ROW_COUNT - 2)], &str2[0]);
    strcpy(&str_array[VGA_SYMBOLS_PER_ROW * (VGA_ROW_COUNT - 1)], &str3[0]);

    for (;;) {
        //Check visible field
        if (video_enable_flg) {
            //OK, visible
            //Main render routine
            //Set pointer for render line (display bufffer)
            _ptr = &str_array[raw_render * VGA_SYMBOLS_PER_ROW];

            //Set pointer for render line (character generator)
            _ptr1 = &symbol[0][y_line_render >> 1];

            //Cycle for render line
            i = VGA_SYMBOLS_PER_ROW;
            while (i--) {
                SPDR = 0xFF; //*(_ptr1 + (* _ptr++)*VGA_SYMBOL_HEIGHT/2);
                //That's a great pity can't shift data faster (8Mhz at FOSC=16Mhz)!!
                asm {
                    NOP
                    NOP
                    NOP
                    NOP
                }
            }
            //Delay for draw last symbol
            asm {
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
            }
        }
    }
}

void main(void)
{
    avr_init();

    vga_render();
}

static void timer0_init(void)
{
    TCCR0 = 0x00; //stop
    TCNT0 = 0xC3; //set count, One VGA line 31.77us
    TCCR0 = 1 << CS01; //start timer with prescaler select 1/8
    TOIE0_bit = 1;
    SREG_I_bit = 1;
}

static void avr_init(void)
{
    //Enable SPI
    spi_init();
    timer0_init();

    //init VGA SYNC ports
    //HSYNC
    sbi(PORTB, 3);
    sbi(DDRB, 3);
    //VSYNC
    sbi(PORTB, 2);
    sbi(DDRB, 2);
}