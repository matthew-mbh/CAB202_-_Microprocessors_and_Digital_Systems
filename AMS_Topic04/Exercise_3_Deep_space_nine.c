//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic04
//
//  COMPILE:
//  gcc Exercise_3_Deep_space_nine.c -o Exercise_3_Deep_space_nine -Wall -Werror -g -I ../ZDK -L ../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./Exercise_3_Deep_space_nine
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

bool game_over;
bool update_screen = true;

//  (a) Declare a global sprite_id called station, and two global integers
//      called x_star and y_star which will record the position of the star.
sprite_id station;                  // Declare sprite station.
//
int x_star;                         // declare global int for star x position.
int y_star;                         // declare global int for star y position.
//
void accelerate_station_towards_star(void);

void setup(void) {
    //  (b) Compute the position of the star, which should be placed at the 
    //      centre of the screen. Use integer arithmetic, make no attempt
    //      to round values, and make no assumptions about the screen size.
    //		Hint: screen width divided by 2, screen height divided by 2.
    x_star = round(((screen_width()/2)));        // Set star initial x position.
    y_star = round(((screen_height()/2)));       // Set star initial y position.
    //
    //  (c) Initialise the station to display a 1x1 image consisting of a string
    //      containing a single '9' character. The sprite should appear at an
    //      initial location which is displaced 5 units to the left and 
    //      8 units above the star.
    // STATION PARAMITERS:
    int sw = 1;                                         // Station width.
    int sh = 1;                                         // Station height.
    int x_displacement = 5;                             // Station x displacement.
    int y_displacement = 8;                             // Station y displacement.
    int x_station = (x_star - x_displacement);          // Station x position.
    int y_station = (y_star - y_displacement);      // Station y position.
    char * station_im = "9";                            // Station Character.
    //
    // INITIALISE STATION:
    station = sprite_create( x_station, y_station, sw, sh, station_im );
    //
    //  (d) Declare a double precision floating point variable called dx
    //      and set it equal to the difference between the x-coordinate of the 
    //      star and that of the station.
    double dx = (x_star - x_station);            // Difference x in position.
    //
    //  (e) Declare a double precision floating point variable called dy
    //      and set it equal to the difference between the y-coordinate of the 
    //      star and that of the station.
    double dy = (y_star - y_station);           // Difference y in position.
    //
    //  (f) Declare a double precision floating point value called dist
    //      and set it equal to the distance between the station and the star.
    //      The distance can be calculated using dx and dy, and applying the 
    //      Theorem of Pythagoras.
    double dist = sqrt(dx * dx + dy * dy);      // Distance between sprites.
    //
    //  (g) Normalise dx and dy by dividing them both by dist. 
    dx /= dist;                                 // Normalise dx value.
    dy /= dist;                                 // Normalise dy value.
    //
    //  (h) Multiply dx and dy by the velocity indicated in Table 1 corresponding
    //      to your particular x- and y- offset values. 
    double offset_value = 0.24;     // Define offset velocity value.
    dx = dx * offset_value;                     // Multiply dx by offset value.
    dy = dy * offset_value;                     // Multiply dy by offset value.
    //
    //  (i) Aim the station in towards the star by setting its step-size to (dx, dy). 
    sprite_turn_to(station, dx, dy);            // Turn station towards star/
    //
    //  (j) Turn the station +90 degrees to convert the flight path 
    //		from a suicide dive into an elliptical orbit.
    int angle = 90;                             // Create angle variable of +90.
    sprite_turn( station, angle );              // turn station +90 angle.
    //
    //  (k) Draw the station.
    sprite_draw(station);                       // Draw station at start position.
    //  (l) Draw the star at its designated location.
    //
    // STAR PARAMITERS:
    sprite_id star;                     // Declare sprite star.
    //
    int star_w = 1;                                     // Station width.
    int star_h = 1;                                     // Station height.
    char * star_im = "*";                               // Star Character.
    //
    // INITIALISE STAR:
    star = sprite_create( x_star, y_star, star_w, star_h, star_im );
    //
    // DRAW STAR:
    sprite_draw(star);                          // Draw star at start position.
    //
}

// Play one turn of game.
void process(void) {
    // Keep the next line intact.
    clear_screen();

    //  (m) Call accelerate_station_towards_star to accelerate the station toward the star.
    accelerate_station_towards_star();          // Call function.
    //
    //  (n) Move the station forward one step.
    sprite_step(station);                       // 'station' takes one step.
    //
    //  (o) Draw the station.
    sprite_draw(station);                       // Draw station at new location.
    //
    //  (p) Draw the star at its designated location, (x_star, y_star).
    sprite_id star;                     // Declare sprite star.
    //
    int star_w = 1;                                     // Station width.
    int star_h = 1;                                     // Station height.
    char * star_im = "*";                               // Star Character.
    //
    // INITIALISE STAR:
    star = sprite_create( x_star, y_star, star_w, star_h, star_im );
    //
    // DRAW STAR:
    sprite_draw(star);                          // Draw star at start position.
    //
    //
}

void accelerate_station_towards_star(void) {
    //  (aa) Get the difference between the x-coordinate of the star and that 
    //      of the station (without rounding) and store it in a double 
    //      precision floating point variable called x_diff. Do the same for
    //      the y-coordinate, and store the result in a variable called y_diff.
    double stat_x = (sprite_x(station));      // Current station x Position.
    double stat_y = (sprite_y(station));      // Current station y Position.
    //
    double x_diff = (x_star - stat_x);             // Station x displacement.;
    double y_diff = (y_star - stat_y);             // Station y displacement.;
    //
    //
    //  (ab) Use x_diff and y_diff together with the Theorem of Pythagoras to 
    //      calculate the _square of the distance_ from the station to the star. 
    //      Save this value in a double precision floating point variable, 
    //		dist_squared. (_DO NOT_ take the square root in this step.)
    double dist_squared = (x_diff * x_diff + y_diff * y_diff); // Dist. squared.
    //
    //  (ac) Guard against possible division by zero in later calculations. If
    //      dist_squared is less than 1e-10, set it to 1e-10. In a "practical" 
    //		setting the space station would have vaporised before this point 
    //		could be reached. In this simulation, we will allow the station to 
    //		fly past the star (very close).
    if (dist_squared < 1e-10){                  // Aerforms check to see size.
        dist_squared = 1e-10;                   // Assigns new value if too small.
    }
    //
    //  (ad) Compute the square root of dist_squared and store it in a double precision
    //      floating point variable called dist. 
    double dist = sqrt(dist_squared);           // Distance between sprites.
    //
    //  (ae) Get the current horizontal and vertical step sizes of the station 
    //      and store them in double precision floating point variables called 
    //      dx and dy.
    double dx = (sprite_dx(station));          // station x direction step size.
    double dy = (sprite_dy(station));          // station y direction step size.
    //
    //  (af) Calculate the magnitude of the acceleration due to the gravity of
    //      the star. This is given by the formula a = GM/dist_squared, where G is the 
    //      universal gravitational constant, M is the mass of the star, and
    //      dist_squared is the square of the distance from the station to the star.
    //      Due to the laws of physics in the simulation, and by amazing coincidence,
    //      it turns out that GM = 1.
    int GM = 1;                                 // Define value of Gravity * Mass.
    //
    double a = GM/dist_squared;                 // Magnitude station acceleration.
    //
    //    //  (ag) The acceleration must be split between the x and y direction and
    //      added to the horizontal and vertical step sizes. To do this, add 
    //      (a * x_diff / dist) to dx, and add (a * y_diff / dist) to dy.
    dx = dx + (a * x_diff / dist);              // Acceleration in x direction.
    dy = dy + (a * y_diff / dist);              // Acceleration in y direction.
    //
    //  (ah) Now check the speed of the station. It must never exceed the 
    //      speed of light, which we define to be one screen unit per time 
    //      step. Use the Theorem of Pythagoras to find the speed of
    //      station, v, which is calculated from dx and dy.
    //      (_DEFINITELY_ take the square root this time.)  
    double v = sqrt(dx * dx + dy * dy);         // Speed of station.
    //
    //  (ai) If the speed of the station is greater than 1, divide both dx
    //      and dy by the speed. This will limit the a maximum velocity of
    //		1 screen unit per time slice. Think of it as retro-rockets being
    //		used to prevent the station from breaking up.
    if (v > 1){                                 // Check see if v greater than 1.
        dx /= v;                                // Divide dx by v
        dy /= v;                                // Divide dy by v
    }
    //
    //  (aj) Turn the station to move with the new dx and dy values.
    sprite_turn_to(station, dx, dy);           // Turn station towards dx and dy.
    //
}

// Clean up game
void cleanup(void) {
    // STATEMENTS
}

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

