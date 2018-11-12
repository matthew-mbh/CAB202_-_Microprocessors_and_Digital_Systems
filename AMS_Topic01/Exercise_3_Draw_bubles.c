//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_3_Draw_bubles.c -o Exercise_3_Draw_bubles -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_3_Draw_bubles
//
//------------------------------------------------------------------------------//
//==============================================================================//
//------------------------------------------------------------------------------//
// C SECIFIC CODE:
//------------------------------------------------------------------------------//
//
//--------------------+
// Define Directories:|
//--------------------+
#include "cab202_graphics.h"
//
//--------------------+
// Setup:             |
//--------------------+
void draw_bubbles(void){
	// (a) Draw a bubble at (31,12)
    draw_char(31,12,'O');           // Draws buble at coordinates 31(x) & 12(y).
    //
	// (b) Draw a bubble at (52,0)
    draw_char(52,0,'O');            // Draws buble at coordinates 52(x) & 0(y).
    //
	// (c) Draw a bubble at (39,18)
    draw_char(39,18,'O');           // Draws buble at coordinates 39(x) & 18(y).
    //
	// (d) Draw a bubble at (40,2)
    draw_char(40,2,'O');            // Draws buble at coordinates 40(x) & 2(y).
    //
	// Keep the following line without change.
	show_screen();                  // Executing command shows all four bubles.
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	setup_screen();                 // Screen Setup.
    //
	draw_bubbles();                 // Calls function, displaying the four bubles.
    //
    // Exit Display of function:
        // (1) String displayed after bubles, calling for any key to be pressed
        //     to exit 'draw_bubbles' function.
        // (2) Waits for any character to be pressed.
        // (3) After any character key pressed, code continues on and executes
        //     the 'cleanup_screen()' command.
	draw_string( 0, screen_height() - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}
//
//==============================================================================//
