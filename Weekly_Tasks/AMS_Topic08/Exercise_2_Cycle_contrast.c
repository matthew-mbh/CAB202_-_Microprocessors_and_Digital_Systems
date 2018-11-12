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
#include "lcd_model.h"
/**
//---------------------+--------------------------------------------------------//
// SETUP FUNCTION:     |
//---------------------+
*/void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the left button and right button.
    
    CLEAR_BIT(PORTF, 0);            // Set input for pin 0 low.
    CLEAR_BIT(PORTF, 1);            // Set input for pin 1 low.
    CLEAR_BIT(PORTF, 2);            // Set input for pin 2 low.
    CLEAR_BIT(PORTF, 3);            // Set input for pin 3 low.
    CLEAR_BIT(PORTF, 4);            // Set input for pin 4 low.
    CLEAR_BIT(PORTF, 5);            // Set input for pin 5 low.
    CLEAR_BIT(PORTF, 6);            // Set input for pin 6 low.
    CLEAR_BIT(PORTF, 7);            // Set input for pin 7 low.
    
    CLEAR_BIT(PORTB, 0);            // Set input for pin 0 low.
    CLEAR_BIT(PORTB, 1);            // Set input for pin 1 low.
    CLEAR_BIT(PORTB, 2);            // Set input for pin 2 low.
    CLEAR_BIT(PORTB, 3);            // Set input for pin 3 low.
    CLEAR_BIT(PORTB, 4);            // Set input for pin 4 low.
    CLEAR_BIT(PORTB, 5);            // Set input for pin 5 low.
    CLEAR_BIT(PORTB, 6);            // Set input for pin 6 low.
    CLEAR_BIT(PORTB, 7);            // Set input for pin 7 low.
    
    CLEAR_BIT(PORTD, 0);            // Set input for pin 0 low.
    CLEAR_BIT(PORTD, 1);            // Set input for pin 1 low.
    CLEAR_BIT(PORTD, 2);            // Set input for pin 2 low.
    CLEAR_BIT(PORTD, 3);            // Set input for pin 3 low.
    CLEAR_BIT(PORTD, 4);            // Set input for pin 4 low.
    CLEAR_BIT(PORTD, 5);            // Set input for pin 5 low.
    CLEAR_BIT(PORTD, 6);            // Set input for pin 6 low.
    CLEAR_BIT(PORTD, 7);            // Set input for pin 7 low.
    
    CLEAR_BIT(PINF, 0);            // Set input for pin 0 low.
    CLEAR_BIT(PINF, 1);            // Set input for pin 1 low.
    CLEAR_BIT(PINF, 2);            // Set input for pin 2 low.
    CLEAR_BIT(PINF, 3);            // Set input for pin 3 low.
    CLEAR_BIT(PINF, 4);            // Set input for pin 4 low.
    CLEAR_BIT(PINF, 5);            // Set input for pin 5 low.
    CLEAR_BIT(PINF, 6);            // Set input for pin 6 low.
    CLEAR_BIT(PINF, 7);            // Set input for pin 7 low.
    
    CLEAR_BIT(DDRF, 0);            // Set input for pin 0 low.
    CLEAR_BIT(DDRF, 1);            // Set input for pin 1 low.
    CLEAR_BIT(DDRF, 2);            // Set input for pin 2 low.
    CLEAR_BIT(DDRF, 3);            // Set input for pin 3 low.
    CLEAR_BIT(DDRF, 4);            // Set input for pin 4 low.
    CLEAR_BIT(DDRF, 5);            // Set input for pin 5 low.
    CLEAR_BIT(DDRF, 6);            // Set input for pin 6 low.
    CLEAR_BIT(DDRF, 7);            // Set input for pin 7 low.

    //CLEAR_BIT(DDRF, 5);              // Set input for Pin 5 (SW2).
    //CLEAR_BIT(DDRF, 6);              // Set input for Pin 6 (SW1).
    //
	//	(b) Initialise the LCD display using the default contrast setting.
    lcd_init(LCD_DEFAULT_CONTRAST); // Set LCD to default contrast.
	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n8548625", using the foreground colour, 
	//	positioning the left edge of the text at 17 and the nominal top 
	//	of the text at 11.
    char * S_number = "n8548625";   // Define Character type for student number.
    draw_string(17, 11, S_number, FG_COLOUR); // Set string position and colour.
    //
	//	(d) Use one of the functions declared in "graphics.h" to copy the contents 
	//	of the screen buffer to the LCD.
    show_screen();                   // Shows on LCD screen
}

//	(e) Declare a global variable of type int named Lcd_Contrast and 
//	initialise it to the default LCD contrast.
int Lcd_Contrast = LCD_DEFAULT_CONTRAST; // Integer lcd contrast global variable.
//
/**
//---------------------+--------------------------------------------------------//
// Process FUNCTION:   |
//---------------------+
*/
void process(void) {
	//	(f) Test pin corresponding to right button. If closed,
	//	decrement Lcd_Contrast by 9. If the result is less than zero,
	//	set Lcd_Contrast to the maximum permitted LCD contrast value.
    if(BIT_VALUE(PINF, 6)){    // Checks status of SW1.
        if (Lcd_Contrast < 0){ // Checks if LCD contrast smaller than zero.
            Lcd_Contrast = 0b01111111; // Set LCD contrast to max.
        }
        else if (Lcd_Contrast >= 0){
            Lcd_Contrast = Lcd_Contrast - 9; // Otherwise keep subtracting by 9.
        }
    }
	//	(g) Test pin corresponding to left button. If closed,
	//	increment Lcd_Contrast by 9. If the result is greater
	//	then the maximum permitted LCD contrast value, set Lcd_Contrast 
	//	to zero.
    if(BIT_VALUE(PINF, 5)){    // Checks status of SW2.
        if (Lcd_Contrast > 0b01111111){ // checks if greater than max.
            Lcd_Contrast = 0;  // Set LCD contrast to 0.
        }
        else if (Lcd_Contrast<= 0b01111111){
            Lcd_Contrast = Lcd_Contrast + 9; // Otherwise keep adding by 9.
        }
    }
	//	(h) Send a sequence of commands to the LCD to enable extended
	//	instructions, set contrast to the current value of Lcd_Contrast, 
	//	and finally retore the LCD to basic instruction mode.
    LCD_CMD(lcd_set_function, lcd_instr_extended);
    LCD_CMD(lcd_set_contrast, Lcd_Contrast);
    LCD_CMD(lcd_set_display_mode, lcd_display_all_on);
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
