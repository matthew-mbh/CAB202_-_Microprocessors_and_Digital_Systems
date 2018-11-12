/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic09
//
//  EXECUTE:
//  make
//
//------------------------------------------------------------------------------//
//==============================================================================//
//------------------------------------------------------------------------------//
// C SECIFIC CODE:
//------------------------------------------------------------------------------//
//--------------------+---------------------------------------------------------//
// DEFINE DIRECTORIES:|
//--------------------+
*/
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"

void setup(void) {
	set_clock_speed(CPU_8MHz);
	lcd_init(LCD_DEFAULT_CONTRAST);
	lcd_clear();

	//	(a) Initialise Timer 0 in normal mode so that it overflows 
	//	with a period of approximately 0.008 seconds.
	//	Hint: use the table you completed in a previous exercise.
    TCCR1A = 0;                             // Set timer to normal mode.
    TCCR0B = 4;                             // Set overflow period to use.
    TCCR1B = 0;
    //
	//	(b) Enable timer overflow interrupt for Timer 0.
    TIMSK0 = 1;                             // Timer overflow interrupt Time 0.
    //
	//	(c) Turn on interrupts.
    sei();                                  // Turn on/enables interupts.
    //
	//	(d) Enable the joystick right switch for digital input.
    CLEAR_BIT(DDRD, 0);            // Set input for Pin 0 (Right Switch).
    //
	//	(e) Display your student number, "n8548625", with nominal
	//	top-left corner at screen location (22,30).
    clear_screen();                         // Clears screen.
    draw_string(22, 30, "n8548625", FG_COLOUR); // Location of character string.
    //
	// Keep the next instruction intact.
	show_screen();
}

//	(f) Create a volatile global variable called bit_count.
//	The variable should be an 8-bit unsigned integer. 
//	Initialise the variable to 0.
uint8_t bit_count = 0;

//	(g) Define a volatile global 8-bit unsigned global variable 
//	called switch_closed which will store the current state of the switch.
uint8_t switch_closed;
//	(h) Define an interrupt service routine to process timer overflow
//	interrupts for Timer 0. Every time the interrupt service
//	routine is called, bit_count should:
uint8_t history = 0;
uint8_t bit_mask = 0b00011111;
uint8_t debounced_state = 0;

ISR(TIMER0_OVF_vect) {
//	(h.a) Left-shift bit_count one place;
    bit_count = (bit_count << 1);
    //
//	(h.b) Bitwise AND with a mask in which the 5 bits on the right
//		  are 1 and the others are 0.
    bit_count = bit_count | BIT_VALUE(PIND, 0);
    bit_count = (bit_count & bit_mask);
    //
//	(h.c) Use bitwise OR to add the current open/closed value of the
//		  joystick right switch to the history.
    history = (history & bit_mask) | BIT_IS_SET(PIND, 0);
    //
//	(h.d) If bit_count is equal to the bit mask, then the switch has been
//		  observed 5 times in a row to be closed. Assign the value 1 to
//		  switch_closed, indicating that the switch should now be considered to
//        be officially "closed".
    if (bit_count == bit_mask){
        switch_closed = 1;
    }
    //
//		(h.e) If bit_count is equal to 0, then the switch has been observed 
//			to be open at least 5 in a row, so store 0 in switch_closed, 
//			indicating that the switch should now be considered to be officially
//          "closed".
    if (bit_count == 0){
        switch_closed = 0;
    }
    //
}

// -------------------------------------------------
// Test driver.
// -------------------------------------------------

void process(void) {
	static uint8_t prevState = 0;
	if ( switch_closed != prevState ) {
		prevState = switch_closed;
		draw_string( 30, 40, prevState ? "closed" : "open  ", FG_COLOUR);
		show_screen();
	}
}

int main(void) {
	setup();

	for ( ;; ) {
		process();
	}
}
