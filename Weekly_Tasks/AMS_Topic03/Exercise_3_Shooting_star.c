//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic03
//
//  COMPILE:
//  gcc Exercise_3_Shooting_star.c -o Exercise_3_Shooting_star -Wall -I../ZDK -L../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./Exercise_3_Shooting_star
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
#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#define DELAY 10 /* milliseconds */

// MAKE SURE bool game_over = false; IF IT IS KEPT AS A GLOBAL LOOKING LIKE THIS:
// bool game_over;, IT WILL CAUSE AN ERROR AND FAIL TO  RUN IN AMS.
bool game_over = false;             // Make sure set to false!!!!!.
bool update_screen = true;

//  (a) Declare a global sprite_id called bomb;
sprite_id bomb;                     // Global Variable for bomb.
//
sprite_id star;                     // Global Variable for Star.
//
//--------------------+
// Setup:             |
//--------------------+
void setup(void) {
    //  (b) Initialise the bomb to display a 1x1 image consisting of a string
    //      containing a single '@' character. The sprite should appear at 
    //      initial location (7,17).
    //Initialise Bomb Parameters:
    int b_w = 1;                    // Bomb sprite width.
    int b_h = 1;                    // Bomb sprite height.
    int init_bx = 7;                // Initial x position of bomb.
    int init_by = 17;               // Initial y position of bomb.
    char * bomb_image = "@";        // Character used to represent bomb.
    //
    //Initialise the Bomb:
    bomb = sprite_create( init_bx, init_by, b_w, b_h, bomb_image );
    //
    //  (c) Declare a double precision floating point variable called dx
    //      and set it equal to the difference between the x-coordinate of the 
    //      star and that of the bomb.
    int init_sx = 69;               // Initial x position of star.
    double dx = init_sx - init_bx;  // Difference between x of star and bomb.
    //
    //  (d) Declare a double precision floating point variable called dy
    //      and set it equal to the difference between the y-coordinate of the 
    //      star and that of the bomb.
    int init_sy = 5;                // Initial y position of star.
    double dy = init_sy - init_by;  // Difference between y of star and bomb.
    //
    //  (e) Declare a double precision floating point value called dist
    //      and set it equal to the distance between the bomb and the star.
    //      The distance can be calculated using dx and dy, and applying the 
    //      Theorem of Pythagoras.
    //      Hint: the right-hand side of the assignment statement should look
    //      like this: sqrt( dx * dx + dy * dy );
    double dist = sqrt( dx * dx + dy * dy );    // Distance between bomb and star.
    //
    //  (f) Multiply dx by the desired speed, then divide it by the distance.
    double bomb_speed = 0.25;
    dx = (bomb_speed * dx)/dist;
    //
    //  (g) Do the same to dy. 
    dy = (bomb_speed * dy)/dist;
    //
    //  (h) Turn the bomb to move towards the star. This involves dx and dy. 
    sprite_turn_to( bomb, dx, dy ); // Initial movement.
    //
    //  (i) Draw the bomb.
    sprite_draw( bomb );            // Draws sprite at start coordinates.
    //
    //  (j) Draw the star at its designated location, (69,5).
    int s_w = 1;                    // Star sprite width.
    int s_h = 1;                    // Star sprite height.
    char * star_image = "*";        // Character used to represent star.
    //
    //Initialise the Star:
    star = sprite_create( init_sx, init_sy, s_w, s_h, star_image );
    //
    sprite_draw(star);            // Draws sprite at start coordinates.
    //
}
//
//--------------------+
// process:         |
//--------------------+
// Play one turn of game.
void process(void) {
    // Keep the next line intact.
    clear_screen();

    //  (k) Move the bomb forward one step.
    sprite_step( bomb );                    // bomb takes a step.
    //
    //  (l) Draw the bomb.
    sprite_draw( bomb );                    // Draws sprite at new coordinates.
    //
    //  (m) Draw the star at its designated location, (69,5).
    sprite_draw(star);                      // Draws sprite at same coordinates.
    //
    //  (n) Get the position of the bomb on the screen, and compare it to the 
    //      location of the star. If they are both the same, set game_over true.
    // Location of bomb:
    int bx = round(sprite_x( bomb ));       // Locate x position of bomb.
    int by = round(sprite_y( bomb ));       // Locate y position of bomb.
    //
    // Location of star:
    int sx = round(sprite_x( star ));       // Locate x position of star.
    int sy = round(sprite_y( star ));       // Locate y position of star.
    //
    // Test for colision:
    // If x and y positions do not match, then game over state continues to
    // be false.
    if ((bx > sx) || (sx > bx) || (by > sy) || (sy > by)){
        if (bx > sx){                       // Checks for difference in bx and sx.
            game_over = false;              // if no match, game over state false.
        }
        //
        if (sx > bx){                       // Checks for difference in sx and bx.
            game_over = false;              // if no match, game over state false.
        }
        //
        if(by > sy){                        // Checks for difference in by and sy.
            game_over = false;              // if no match, game over state false.
        }
        //
        if (sy > by){                       // Checks for difference in sy and by.
            game_over = false;              // if no match, game over state false.
        }
    }
    //
    // If this point reached, implys that the positions must now match as they are
    // no longer different. as case has been met, terminate program by returning
    // game over is equal to true.
    else {
        game_over = true;                   // When match, game over state true.
    }
}
//
//--------------------+
// cleanup:           |
//--------------------+
// Clean up game
void cleanup(void) {
    // STATEMENTS
}
//
//--------------------+
// Opperation:        |
//--------------------+
// Program entry point.
int main(void) {
    setup_screen();

#if defined(AUTO_SAVE_SCREEN)
    auto_save_screen(true);
#endif

    setup();
    show_screen();

    while ( !game_over ) {
        process();

        if ( update_screen ) {
            show_screen();
        }

        timer_pause(DELAY);
    }

    cleanup();

    return 0;
}
//
//==============================================================================//
