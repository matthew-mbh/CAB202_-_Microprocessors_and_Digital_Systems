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
/**
//--------------------------------+---------------------------------------------//
// DEFINE FREQUENCY & PRESCALER:  |
//--------------------------------+
*/
#define FREQ (8000000.0)                        // Define appropriate frequency.
#define PRESCALER (64.0)                         // Define appropriate prescaler.
/**
//---------------------------+--------------------------------------------------//
// FUNCTION DECLARATION:     |
//---------------------------+
*/
void draw_double(uint8_t x, uint8_t y, double value, colour_t colour);
void draw_int(uint8_t x, uint8_t y, int value, colour_t colour);
/**
//---------------------+--------------------------------------------------------//
// SETUP FUNCTION:     |
//---------------------+
*/
void setup(void) {
	set_clock_speed(CPU_8MHz);
	lcd_init(LCD_DEFAULT_CONTRAST);
	lcd_clear();

	//	(a) Initialise Timer 3 in normal mode so that it overflows 
	//	with a period of approximately 0.5 seconds.
	//	Hint: use the table you completed in a previous exercise.
    //
    // Based on previous table we need a rough overflow period of 0.5 seconds.
    // If CS02:1 equals 1b010 equals 3, then our overflow period will occure
    // every 0.524288 seconds, which when rounded to one decimal places is 0.5
    // seconds
    TCCR1A = 0;                             // Set timer to normal mode.
    TCCR1B = 0;                             // Set overflow period to use.
    TCCR3B = 3;
    //
	//	(b) Enable timer overflow for Timer 3.
    TIMSK3 = 1;                             // Timer overflow interrupt Time 3.
    //
	//	(c) Turn on interrupts.
    sei();                                  // Turn on/enables interupts.
    //
	//	(d) Display your student number, "n8548625", with nominal top-left
	//	corner at screen location (15,23). Left-aligned 10
	//	pixels below that, display the pre-scale factor that corresponds
	//	to a timer overflow period of approximately 0.5 
	//	seconds.
    clear_screen();                         // Clears screen.
    draw_string(15, 23, "n8548625", FG_COLOUR); // Location of character string.
    draw_int(15, 33, PRESCALER, FG_COLOUR); // Location to print prescaler value.
    //
	// Keep the next instruction intact.
	show_screen();                          // Shows changes on screen.
}
/**
//------------------------------------------------------------------------------//
*/
//	(e) Create a volatile global variable called cycle_count.
//	The variable should be a 32-bit unsigned integer of type uint32_t. 
//	Initialise the variable to 0.
uint32_t cycle_count;                       // Create global uint32_t variable.
//
/**
//----------------------------+-------------------------------------------------//
// INTERUPT SERVICE ROUTINE:  |
//----------------------------+
*/
//	(f) Define an interrupt service routine to process timer overflow
//	interrupts for Timer 3. Every time the interrupt service
//	routine is called, cycle_count should increment by 1.
ISR(TIMER3_OVF_vect) {
    cycle_count ++;
}
//	(g) Define a function called now which has
//	no parameters, but returns a value of type double which contains
//	the total elapsed time measured up to the time at which it is called.
//	Use the method demonstrated in the Topic 9 lecture to compute the
//	elapsed time, taking into account the fact that the timer counter has 
//	16 bits rather than 8 bits.
/**
//-------------------+----------------------------------------------------------//
// NOW FUNCTION:     |
//-------------------+
*/
double now(void){
    double elapsed_time = ( cycle_count * 65536.0 + TCNT3 ) * PRESCALER  / FREQ;
    return elapsed_time;
}
/**
//--------------------+---------------------------------------------------------//
// HELPER FUNCTION:   |
//--------------------+
*/
char buffer[20];

void draw_double(uint8_t x, uint8_t y, double value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%f", value);
	draw_string(x, y, buffer, colour);
}

void draw_int(uint8_t x, uint8_t y, int value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%d", value);
	draw_string(x, y, buffer, colour);
}
/**
//--------------------+---------------------------------------------------------//
// OPERATION:         |
//--------------------+
*/
void process(void) {
	double time = now();
	draw_string(0, 0, "Time = ", FG_COLOUR);
	draw_string(10, 10, "           ", FG_COLOUR);
	draw_double(10, 10, time, FG_COLOUR);
	show_screen();
}

int main(void) {
	setup();

	for ( ;; ) {
		process();
	}
}
/**
//------------------------------------------------------------------------------//
*/
