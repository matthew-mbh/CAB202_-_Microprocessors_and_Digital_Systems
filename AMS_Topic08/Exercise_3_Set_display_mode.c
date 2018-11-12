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
#include <graphics.h>
#include <lcd.h>
#include <macros.h>
#include "lcd_model.h"
/**
//---------------------+--------------------------------------------------------//
// SETUP FUNCTION:     |
//---------------------+
*/
void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the Left, Right, Up, and Down switches
	//	of the joystick.
    CLEAR_BIT(DDRB, 1);            // Set input for Pin 1 (Left Switch).
    CLEAR_BIT(DDRB, 7);            // Set input for Pin 7 (Down Switch).
    CLEAR_BIT(DDRD, 0);            // Set input for Pin 0 (Right Switch).
    CLEAR_BIT(DDRD, 1);            // Set input for Pin 1 (Up Switch).
	//	(b) Initialise the LCD display using the default contrast setting.
    lcd_init(LCD_DEFAULT_CONTRAST);  // Set LCD to default contrast.
	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n8548625", using the background colour, 
	//	positioning the left edge of the text at 11 and the nominal top 
	//	of the text at 11.
    clear_screen();                  // Clears LCD screen.
    char * S_number = "n8548625";   // Define Character type for student number.
    draw_string(11, 11, S_number, BG_COLOUR); // Set string position and colour.
	//	(d) Use one of the functions declared in "graphics.h" to copy 
	//	the contents of the screen buffer to the LCD.
    show_screen();                   // Shows on LCD screen.
}
/**
//---------------------+--------------------------------------------------------//
// SETUP FUNCTION:     |
//---------------------+
*/
void process( void ) {
	//  (e) Determine if the Up joystick switch is closed. 
	//	If it is, set the LCD display to enter normal video mode.
    if(BIT_IS_SET(PIND, 1)){         // Checks status of up switch.
        LCD_CMD(lcd_set_display_mode, lcd_display_normal);
    }

	//  (f) OTHERWISE, determine if the Down joystick switch 
	//	is closed. If it is, set the LCD display to switch to inverse video mode.
    else if(BIT_IS_SET(PINB, 7)){      // Checks status of down switch.
        LCD_CMD(lcd_set_display_mode, lcd_display_inverse);
    }

	//  (g) OTHERWISE, determine if the Left joystick switch 
	//	is closed. If it is, set the LCD display to turn off all pixels.
    else if(BIT_IS_SET(PINB, 1)){      // Checks status of Left Switch.
        LCD_CMD(lcd_set_display_mode, lcd_display_all_off);
    }
	//  (h) OTHERWISE, determine if the Right joystick switch 
	//	is closed. If it is, set the LCD display to turn on all pixels.
    else if(BIT_VALUE(PIND, 0)){      // Checks status of Right Switch.
        LCD_CMD(lcd_set_display_mode, lcd_display_all_on);
    }
	//	If none of the joystick switches are closed, do nothing.
	//	(Hint: do not insert any more instructions.)
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main(void) {
	setup();

	for ( ;; ) {
		process();
		_delay_ms(100);
	}

	return 0;
}
/**
//------------------------------------------------------------------------------//
*/
