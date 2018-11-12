//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic02
//
//  COMPILE:
//  gcc Exercise_3_Draw_border.c -o Exercise_3_Draw_border -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_3_Draw_border
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
#include <cab202_graphics.h>
//
//--------------------+
// Setup:             |
//--------------------+
void draw_border( void ) {
	// (a) Declare an integer variable called left, with an initial value of 3.
    int left = 3;                                       // Set left to 3.
	// (b) Declare an integer variable called top, with an initial value of 4.
    int top = 4;                                        // Set top to 4.
	// (c) Declare an integer variable called right, with an initial value 2 
	//     less than the largest visible horizontal location in the terminal window.
    int right = (screen_width() - 1 - 2);  // Subtract norm of 1 plus subtract 2.
    //
	// (d) Declare an integer variable called bottom, with an initial value 2 
	//     less than the maximum visible vertical location in the terminal window.
    int bottom = (screen_height() - 1 - 2);// Subtract norm of 1 plus subtract 2.
    // (e) Draw a line from (left, top) to (right, top), using the '^' symbol.
    draw_line( left, top, right, top, '^' );            // Parameters for line 1.
    //
    // (f) Draw a line from (right, top) to (right, bottom), using the '^' symbol.
    draw_line( right, top, right, bottom, '^' );        // Parameters for line 2.
    //
    // (g) Draw a line from (left, bottom) to (right, bottom), using the '^' symbol.
    draw_line( left, bottom, right, bottom, '^' );      // Parameters for line 3.
    //
    // (h) Draw a line from (left, top) to (left, bottom), using the '^' symbol.
    draw_line( left, top, left, bottom, '^' );          // Parameters for line 4.
    // Do not touch the following line.
    show_screen();			// Executing command shows border on screen.
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	setup_screen();			// Screen Setup.
	//
	draw_border(); 			// Calls function 'draw_border()', run once.
    //
    // Exit Display of function:
    // (1) Waits for any character to be pressed.
    // (2) After any character key pressed, code continues on and executes
    //     the 'cleanup_screen()' command.
	wait_char();
	cleanup_screen();
	return 0;
}
//
//==============================================================================//
