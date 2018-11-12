//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_4_Draw_lines.c -o Exercise_4_Draw_lines -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_4_Draw_lines
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
void draw_lines(void){
	// (a) Draw a line from (18,23) to (56,10).
    draw_line( 18, 23, 56, 10, '^' ); // Defines start & end  positions for line.
    //
	// (b) Draw a line from (56,10) to (40,7).
    draw_line( 56, 10, 40, 7, '^' );  // Defines start & end  positions for line.
    //
	// (c) Draw a line from (40,7) to (78,4).
    draw_line( 40, 7, 78, 4, '^' );   // Defines start & end  positions for line.
    //
	// (d) Draw a line from (78,4) to (18,23).
    draw_line( 78, 4, 18, 23, '^' );  // Defines start & end  positions for line.
    //
	// Leave the following instruction unchanged.
	show_screen();                  // Executing command shows all four lines.
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	setup_screen( );                // Screen Setup.
    //
	draw_lines();                   // Calls function, displaying the four lines.
    //
    // Exit Display of function:
    // (1) String displayed after lines, calling for any key to be pressed
    //     to exit 'draw_lines' function.
    // (2) Waits for any character to be pressed.
    // (3) After any character key pressed, code continues on and executes
    //     the 'cleanup_screen()' command.
	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char( );
	cleanup_screen( );
	return 0;
}
//
//==============================================================================//
