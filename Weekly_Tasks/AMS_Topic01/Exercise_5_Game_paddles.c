//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_5_Game_paddles.c -o Exercise_5_Game_paddles -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_5_Game_paddles
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
void draw_paddles( void ) {
    // DEFINE BOUNDARIES:
    int H = screen_height();        // Height of screen from bottom to top.
    int L = 0;                      // Left hand side starts at 0.
    int R = screen_width() - 1;     // Right hand side is the screen width - 1.
    //
    // PADDLE PARAMETERS:
    int p = 7;                      // Paddles should be 7 char units in length.
    int LD = 3;                     // Left Paddle offset 3 units below H.
    int RD = 4;                     // Right Paddle offset 4 units above H.
    //
    // LEFT PADDLE X & Y:
    int LX = L + 3;                 // Define X position of Left Paddle.
    int LYt = ((H - p) / 2 + LD);   // Define Y top position of Left Paddle.
    int LYb = (LYt + p - 1);        // Define Y bottom position of Left Paddle.
    //
    // RIGHT PADDLE X & Y:
    int RX = R - 2;                 // Define X position of Right Paddle.
    int RYt = ((H - p) / 2 - RD);   // Define Y top position of Right Paddle.
    int RYb = (RYt + p - 1);        // Define Y bottom position of Right Paddle.
    //
    // DRAW PADDLES:
    draw_line( LX, LYt, LX, LYb, '~' );   // X & Y positions for Left Paddle.
    draw_line( RX, RYt, RX, RYb, '~' );   // X & Y positions for Right Paddle.
    //
	show_screen( );                 // Executing command shows paddle lines.
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	setup_screen();                 // Screen Setup.
    //
	draw_paddles();                 // Calls function, displaying paddle lines.
    //
    // Exit Display of function:
    // (1) String displayed after paddles, calling for any key to be pressed
    //     to exit 'draw_paddles' function.
    // (2) Waits for any character to be pressed.
    // (3) After any character key pressed, code continues on and executes
    //     the 'cleanup_screen()' command.
	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}
//
//==============================================================================//
