//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_6_Angry_bird.c -o Exercise_6_Angry_bird -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_6_Angry_bird
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
#include <cab202_sprites.h>
#include <cab202_timers.h>
//
//--------------------+
// Initialise:        |
//--------------------+
// Millisecond delay between game updates
#define DELAY (10)
//
// Is the game over?
bool game_over = false;                     // When false, game continues.
//
// String containing sprite bitmap
char * bird_img =
"   _  "
"__(0)<"
"\\___) ";
//
// (a) Declare global variable of type sprite_id called angry_bird.
sprite_id angry_bird;                       // Define Sprite_id angry_bird.
//
//--------------------+
// Setup:             |
//--------------------+
void setup( void ) {
	// (b) Set the value of angry_bird: create a sprite which displays the
    //     bird-like bitmap which is provided for you. The width of the bitmap
    //     is 6 units and the height is 3 units. The sprite should be placed
    //     so it is sitting on the bottom row of the terminal window, flush
    //     with the left side of the window.
    //
    // Initial Sprite Parameters:
    int w = screen_width();                 // Define Screen Width.
    int h = screen_height();                // Define Screen Height.
    int ab_w = 6;                           // Define angry bird sprite Width.
    int ab_h = 3;                           // Define angry bird sprite Height.
    int ab_x = (w - w);                     // Define sprite start x position.
    int ab_y = (h - ab_h);                  // Define sprite start y position.
    //
    angry_bird = sprite_create( ab_x, ab_y, ab_w, ab_h, bird_img );
    //
	// (c) Call sprite_turn_to(...) to set angry_bird moving with
	//     initial horizontal step-size of 0.45 units and vertical step-size
	//     -0.46 units.
    double ws_size = 0.45;                  // Define horizontal step-size.
    double hs_size = -0.46;                 // Define vertical step-size.
    //
    sprite_turn_to( angry_bird, ws_size, hs_size ); // set sprite motion x & y.
    //
	// (d) Call sprite_draw(...) to make angry_bird visible at the start of the
    //     game.
    sprite_draw( angry_bird );              // Draws sprite at start coordinates.
}
//
//--------------------+
// Process:           |
//--------------------+
void process(void) {
	// (e) Call sprite_step(...) to move angry_bird one step in the current 
	//     direction determined by its internal (dx,dy) step values.
    sprite_step( angry_bird );              // Move sprite one step.
    //
	// (f) Declare floating point variable called dx, of type double.
	//     Assign a value to dx by calling sprite_dx(...) to find the current 
	//     horizontal step size of angry_bird.
    double dx = sprite_dx( angry_bird );    // Find current step size in x direc.
    //
	// (g) Declare floating point variable called dy, of type double.
	//     Assign a value to  dy by calling sprite_dy(...) to find the current 
	//     vertical step size of angry_bird.
    double dy = sprite_dy( angry_bird );    // Find current step size in y direc.
    //
	// (h) Add constant gravitational acceleration of 0.0028 to dy.
    dy = (dy + 0.0028);                     // Add grav. acceleration to dy.
    //
	// (i) Call sprite_turn_to(...) to update angry_bird's internal step values:
	//     dx does not change, but dy does.
    sprite_turn_to( angry_bird, dx, dy ); // Update stored sprite step values.
    //
	// (j) Call sprite_draw(...) to show angry_bird in its new position.
    sprite_draw( angry_bird );              // Draws sprite at new coordinates.
    //
	// Don’t mess with the following statement. It detects when angry_bird 
	// falls off the bottom of the terminal and terminates the game.
	if ( sprite_y(angry_bird) >= screen_height() ) {
		game_over = true;                   // When true, game terminates.
	}
}
//
//--------------------+
// Clean up Game:     |
//--------------------+
// Clean up game
void cleanup(void) {
	// No change is required here.
}
//
//--------------------+
// Operation:         |
//--------------------+
// Program entry point.
int main( void ) {
	setup_screen();                         // Screen setup, run once.
	setup();                                // Calls function 'setup()', run once.
	show_screen();                          // Displays 'setup()' content.
    //
    // while loop contents:
    // Will continue to repeat while game over is not true, due to the angry
    // bird sprite not yet exceeding the screen height dimensions.
    // (1) Clears screen, so the new positions can be updated and displayed,
    //     minus the old sprite position.
    // (2) Calls and runs the process function, which updates the angry birds
    //     position and step size.
    // (3) Displays the changes on screen.
    // (4) Timer dellay of 10 milliseconds, before repeating the while loop.
	while ( !game_over ) {
		clear_screen();
		process();
		show_screen();
		timer_pause( DELAY );
	}
    //
	cleanup();                              // cleanup run once while loop exited.
	return 0;
}
//
//==============================================================================//
