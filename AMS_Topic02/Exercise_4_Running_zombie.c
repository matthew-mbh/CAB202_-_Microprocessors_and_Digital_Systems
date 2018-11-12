//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic02
//
//  COMPILE:
//  gcc Exercise_4_Running_zombie.c -o Exercise_4_Running_zombie -Wall -Werror -g -I ../ZDK -L ../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./Exercise_4_Running_zombie
//
//  COMPILE & EXECUTE - SIMULTANIOUSLY
//  gcc Exercise_4_Running_zombie.c -o Exercise_4_Running_zombie -Wall -Werror -g -I ../ZDK -L ../ZDK -lzdk -lncurses -lm    && ./Exercise_4_Running_zombie
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
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
//
//--------------------+
// Initialise:        |
//--------------------+
// Configuration
#define DELAY (10) /* Millisecond delay between game updates */
//
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)
//
// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */
//
char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";
//
//	(a) Declare a sprite_id called zombie
sprite_id zombie;                       // Define Sprite_id zombie.
//
//--------------------+
// Setup:             |
//--------------------+
// Setup game.
void setup(void) {
    //  (b) Assign a value to zombie by creating a sprite at integer 
    //      coordinates (x,y). Use integer arithmetic to calculate 
    //      the location relative to the screen dimensions:
    //      x = 40% of available horizontal space on the screen.
    //      y = 50% of available vertical space on the screen.
    //      Use the formula set out in the statement of the problem.
    //
    // Initial Sprite Parameters:
    int w = screen_width();                 // Define Screen Width.
    int h = screen_height();                // Define Screen Height.
    int pw = 40;                            // Percentage of horizontal space.
    int ph = 50;                            // Percentage of vertical space.
    int zb_w = 5;                           // Define zombie sprite Width.
    int zb_h = 5;                           // Define zombie sprite Height.
    int zb_x = ((w-zb_w)*pw/100);           // Define sprite start x position.
    int zb_y = ((h-zb_h)*ph/100);           // Define sprite start y position.
    //
    zombie = sprite_create( zb_x, zb_y, zb_w, zb_h, zombie_image );
    //
    //	(c) Draw the zombie.
    sprite_draw( zombie );                  // Draws sprite at start coordinates.
}
//
//--------------------+
// Process:           |
//--------------------+
// Play one turn of game.
void process(void) {
    //	(d) Get a character code from standard input without waiting.
    int key = get_char();                  // checking for input character.
    //
    //  (e) Get the current screen coordinates of the zombie in integer variables 
    //      by rounding the actual coordinates. Store the coordinates in a pair of
    //      variables called x and y, both of type int.
    int x = round((sprite_x( zombie )));  // Used to locate x position of zombie.
    int y = round((sprite_y( zombie )));  // Used to locate y position of zombie.
    //
    //	(f) Move zombie left, ensuring that it always remains within the screen.
    sprite_step( zombie );                  // Zombie takes a step.
    if (key == '4'){
        if ( x == 0 ) {
            sprite_move( zombie, +1, 0 );   // Prevent passing left edge.
        }
        else {
            sprite_move( zombie, -1, 0 );   // Posative step left.
        }
    }
    //
    //	(g) Move zombie right, ensuring that it always remains within the screen.
    if (key == '6'){
        if ( x == (screen_width() - 5)) {
            sprite_move( zombie, -1, 0 );   // Prevent passing right edge.
        }
        else {
            sprite_move( zombie, +1, 0 );   // Posative step right.
        }
    }
    //
    //	(h) Move zombie up, ensuring that it always remains within the screen.
    if (key == '8'){
        if ( y == 0) {
            sprite_move( zombie, 0, +1 );   // Prevent passing upper edge.
        }    else {
            sprite_move( zombie, 0, -1 );   // Posative step up.
        }
    }
    //
    //	(i) Move zombie down according to specification.
    if (key == '2'){
        if ( y == (screen_height() - 5)) {
            sprite_move( zombie, 0, -1 );   // Prevent passing bottom edge.
        }
        else {
            sprite_move( zombie, 0, +1 );   // Posative step downwards.
        }
    }
    //
    //	(j) If the key is 'q', set game_over to true.
    if ( key == 'q' ) {
        game_over = true;
    }
    //
    // Leave next line intact.
    clear_screen();

    //	(k)	Draw the zombie.
    sprite_draw( zombie );              // Draws sprite at new coordinates.
}
//
//--------------------+
// Operation:         |
//--------------------+
// Program entry point.
int main(void) {
	setup_screen();                    // Screen setup, run once.
	setup();                           // Calls function 'setup()', run once.
	show_screen();                     // Displays 'setup()' content.
    //
    // while loop contents:
    // Will continue to repeat while game over is not true.
    // (1) Calls and runs the process function, which updates the zombies
    //     position and step size.
    // (2) if update screen true, then:
    //     (2a) Displays the changes on screen.
    //
    // (3) Timer dellay of 10 milliseconds, before repeating the while loop.
	while ( !game_over ) {
		process();
        //
		if ( update_screen ) {
			show_screen();
		}
        //
		timer_pause(DELAY);
	}
    //
	return 0;
}
//
//==============================================================================//
