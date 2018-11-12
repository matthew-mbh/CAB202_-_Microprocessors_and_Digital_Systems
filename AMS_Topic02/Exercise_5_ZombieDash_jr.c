//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic02
//
//  COMPILE:
//  gcc Exercise_5_ZombieDash_jr.c -o Exercise_5_ZombieDash_jr -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_5_ZombieDash_jr
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

// ADD INCLUDES HERE
//
//--------------------+
// Initialise:        |
//--------------------+
// Configuration
#define DELAY (10) /* Millisecond delay between game updates */
//
#define HERO_WIDTH (5)
#define HERO_HEIGHT (5)
#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)
//
// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */
//
char * hero_image =
/**/    "H   H"
/**/    "H   H"
/**/    "HHHHH"
/**/    "H   H"
/**/    "H   H";
//
char * zombie_image =
/**/    "ZZZZZ"
/**/    "   Z "
/**/    "  Z  "
/**/    " Z   "
/**/    "ZZZZZ";
//
char * msg_image =
/**/    "Goodbye and thank-you for playing ZombieDash Jr."
/**/    "            Press any key to exit...            ";
//
// (c) Declare a sprite_id called hero.
sprite_id hero;                       // Define Sprite_id hero.
//
// (m) Declare a sprite_id called zombie.
sprite_id zombie;                    // Define Sprite_id zombie.
//
//--------------------+
// Setup:             |
//--------------------+
// Setup game.
void setup(void) {
    // (a) Draw the border (setup).
    // Initialise Border Coordinates:
    int left = 0;                       // Set x value for left boarder side.
    int top = 0;                        // Set y value for top boarder side.
    int right = screen_width() - 1;     // Set x value for right boarder side.
    int bottom = screen_height() - 1;   // Set y value for bottom boarder side.
    //
    // Draw Border:
    draw_line( left, top, right, top, '*' );            // Top edge border.
    draw_line( right, top, right, bottom, '*' );        // Right edge border.
    draw_line( left, bottom, right, bottom, '*' );      // Bottom edge border.
    draw_line( left, top, left, bottom, '*' );          // Left edge border.
    //
    // Keep the next line intact.
    show_screen();
    //
    // (d) Set up the hero at the centre of the screen.
    int hb_w = 5;                       // Hero sprite width.
    int hb_h = 5;                       // Hero sprite height.
    int hb_x = (screen_width()-hb_w)/2; // Set starting x coordinate.
    int hb_y = (screen_height()-hb_h)/2;// Set starting y coordinate.
    //
    hero = sprite_create( hb_x, hb_y, hb_w, hb_h, hero_image );
    //
    // (e) Draw the hero.
    sprite_draw( hero );                // Draws sprite at start coordinates.
    //
    // Keep the next line intact.
    show_screen();
    //
    // (n)    Set up the zombie at a random location on the screen.
    srand(3197208);                    // Specific randomiser key used.
    int x_limits = screen_width() - hb_w - 2;   // Prevents boarder overlap.
    int y_limits = screen_height() - hb_h - 1;  // Prevents boarder overlap.
    int zb_x = 1 + rand() % x_limits;  // randomise x coordinate.
    int zb_y = 1 + rand() % y_limits;  // randomise y coordinate.
    int zb_w = 5;                      // Zombie sprite width.
    int zb_h = 5;                      // Zombie sprite height.
    //
    zombie = sprite_create( zb_x, zb_y, zb_w, zb_h, zombie_image );
    //
    // (o) Draw the zombie.
    sprite_draw( zombie );            // Draws sprite at start coordinates.
    //
    // (p) Set the zombie in motion.
    double dx = 0.1;                     // Limit motion to the x direction.
    double dy = 0.0;                     // No motion in the y.
    //
    sprite_turn_to( zombie, dx, dy ); // Initial movement.
    int angle = rand() % 360;         // randomise angle, bound by limit of 360.
    sprite_turn( zombie, angle );     // turn zombie by randomised angle.
    //
    // Keep the next line intact.
    show_screen();                    // Displays all features currently setup.
}
//
//--------------------+
// Process:           |
//--------------------+
// Play one turn of game.
void process(void) {
    // Initialise Border Coordinates:
    int left = 0;                       // Set x value for left boarder side.
    int top = 0;                        // Set y value for top boarder side.
    int right = screen_width() - 1;     // Set x value for right boarder side.
    int bottom = screen_height() - 1;   // Set y value for bottom boarder side.
    //
    // (f) Get a character code from standard input without waiting.
    int key = get_char();                  // checking for input character.
    //
    // (y) Test for end of game.
    if ( key == 'q' ) {
        sprite_id message;
        message = sprite_create( ((right/2) - 24), (bottom/2), 48, 2, msg_image );
        clear_screen();
        sprite_draw( message );
        show_screen();
        game_over = true;
        wait_char();
        return;
    }
    //
    // (g)    Get the current screen coordinates of the hero in integer variables
    //        by rounding the actual coordinates.
    int hx = round(sprite_x( hero ));  // Used to locate x position of hero.
    int hy = round(sprite_y( hero ));  // Used to locate y position of hero.
    
    // (h) Move hero left according to specification.
    if (key == 'a') {
        if (hx > 1) {
            sprite_move(hero, -1, 0);           // moves hero left by one.
        }
    }
    //
    // (i) Move hero right according to specification.
    if (key == 'd') {
        if (hx < screen_width() - 1 - 5) {
            sprite_move(hero, +1, 0);           // moves hero right by one.
        }
    }
    //
    // (j) Move hero up according to specification.
    if (key == 'w') {
        if (hy > 1) {
            sprite_move(hero, 0, -1);           // moves hero up by one.
        }
    }
    //
    // (k) Move hero down according to specification.
    if (key == 's') {
        if (hy < screen_height() - 1 - 5) {
            sprite_move(hero, 0, +1);           // moves hero down by one.
        }
    }
    //
    // (q.a) Test to move the zombie if key is 'z' or negative.
    if (key == 'z') {
        // (r) Zombie takes one step.
        sprite_step( zombie );                  // Zombie takes a step.
        //
        // (s) Get screen location of zombie.
        int zx = round(sprite_x( zombie ));  // Locate x position of zombie.
        int zy = round(sprite_y( zombie ));  // Locate y position of zombie.
        //
        // (t) Get the displacement vector of the zombie.
        double z_dx = sprite_dx( zombie );     // Displacement in the x direction.
        double z_dy = sprite_dy( zombie );     // Displacement in the y direction.
        int angle = rand() % 360;              // Randomise angle, within limits.
        //
        // (u) Test to see if the zombie hit the left or right border.
        if ( zx == 0 || zx== screen_width() - 1 - 5 ) {
            if (zx == 0) {
                sprite_move(zombie, +1, 0);         // +x if hits left border.
            }
            if (zx == screen_width() - 1 - 5) {
                sprite_move(zombie, -1, 0);         // -x if hits right border.
            }
        }
        //
        // (v) Test to see if the zombie hit the top or bottom border.
        if ( zy == 0 || zy == screen_height() - 1 - 5 ) {
            if (zy == 0) {
                sprite_move(zombie, 0, +1);         // +y if hits top border.
            }
            if (zy == screen_height() - 1 - 5) {
                sprite_move(zombie, 0, -1);         // -y if hits bottom border.
            }
        }
        //
        // (w) Test to see if the zombie needs to step back and change direction.
        if ( zx == 0 || zx == screen_width() - 1 - 5 || zy == 0 || zy == screen_height() - 1 - 5 ){
            sprite_turn_to( zombie, z_dx, z_dy );   // Current movement.
            sprite_turn( zombie, angle );           // turn zombie random angle.
        }
        //
        // (q.b) End else-if test to move the zombie if key is 'z' or negative.
    }
    // Leave next line intact
    clear_screen();                                     // clears screen.
    
    // (b) Draw the border (process).
    draw_line( left, top, right, top, '*' );            // Top edge border.
    draw_line( right, top, right, bottom, '*' );        // Right edge border.
    draw_line( left, bottom, right, bottom, '*' );      // Bottom edge border.
    draw_line( left, top, left, bottom, '*' );          // Left edge border.
    //
    // (l)    Draw the hero.
    sprite_draw( hero );                 // Draws sprite at new coordinates.
    //
    // (x)    Draw the zombie.
    sprite_draw( zombie );              // Draws sprite at new coordinates.
}
//
//--------------------+
// Clean up Game:     |
//--------------------+
// Clean up game
void cleanup(void) {
    // STATEMENTS
}
//
//--------------------+
// Operation:         |
//--------------------+
// Program entry point.
int main(void) {
    setup_screen();                    // Screen setup, run once.
    setup();                        // Calls function 'setup()', run once.
    show_screen();                    // Displays 'setup()' content.
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
    cleanup();                        // cleanup run once while loop exited.
    //
    return 0;
}
//
//==============================================================================//

