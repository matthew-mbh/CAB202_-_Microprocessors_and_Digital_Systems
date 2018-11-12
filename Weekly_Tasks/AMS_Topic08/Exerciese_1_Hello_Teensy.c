/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic08
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
#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <lcd.h>
/**
//---------------------+--------------------------------------------------------//
// SETUP FUNCTION:     |
//---------------------+
*/
void setup( void ) {
	set_clock_speed(CPU_8MHz);       // Set 8MHz for CPU speed.
    //
	//	(a) Initialise the LCD display using the default contrast setting
    lcd_init(LCD_DEFAULT_CONTRAST);  // Set LCD to default contrast.
    //
	//	(b) Use one of the functions declared in "graphics.h" to display 
	//	your student number, n8548625, using the foreground colour, 
	//	positioning the left edge of the image at 13 and the nominal top 
	//	of the text at 35.
    clear_screen();                  // Clears LCD screen
    char * S_number = "n8548625";   // Define Character type for student number.
    draw_string(13, 35, S_number, FG_COLOUR); // Set string position and colour.
    //
	//	(c) Use one of the functions declared in "graphics.h" to copy the contents 
	//	of the screen buffer to the LCD.
    show_screen();                   // Shows on LCD screen
    //
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main(void) {
	setup();

	for ( ;; ) {
		_delay_ms(10);
	}

	return 0;
}
/**
//------------------------------------------------------------------------------//
*/
