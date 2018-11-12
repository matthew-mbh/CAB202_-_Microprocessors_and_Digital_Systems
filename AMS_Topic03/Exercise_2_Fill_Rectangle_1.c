//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic03
//
//  COMPILE:
//  gcc Exercise_2_Fill_Rectangle_1.c -o Exercise_2_Fill_Rectangle_1 -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_2_Fill_Rectangle_1
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
#include <cab202_timers.h>
#include <cab202_graphics.h>

//  (a) Declare four global integer variables, as follows:
//      left - the horizontal location of the left edge of the rectangle
//      top - the vertical location of the top edge of the rectangle 
//      width - the width of the rectangle.
//      height - the height of the rectangle.
int left;   // Creates global variable for left, waiting on value assignment.
int top;    // Creates global variable for top, waiting on value assignment.
int width;  // Creates global variable for width, waiting on value assignment.
int height; // Creates global variable for height, waiting on value assignment.
//
//	(b) Declare a global variable of type char called ch.
//      This is the character that is to be used to render the outline of the
//      rectangle.
char ch;   // Creates global variable for ch, waiting on character assignment.
//
//--------------------+
// fill_rect:         |
//--------------------+
void fill_rect(void) {
    //  (c) Test to see if either of width or height is less than 1.
    //      If so, the function should stop immediately and draw nothing.
    if (width <= 0 || height <= 0){
        return;
    }
    //
    //  (d) Calculate the x-coordinate of the right-hand side of the rectangle.
    //      Store the value in an integer variable called rect_right.
    int rect_right = left + width - 1;               // Define right coordinate.
    //  (e) Calculate the y coordinate of the bottom edge of the rectangle.
    //      Store the result in an integer variable called rect_base.
    int rect_base = top + height -1;                // Define bottom coordinate.
    //
    //  (f.a) Set up for loop that uses an integer variable called y_ctr to 
    //      iterate from the top of the rectangle to the bottom of the rectangle.
    //      Initially y_ctr should be equal to top.
    //      The loop body should run while y_ctr is less than or equal to rect_base.
    for ( int y_ctr = top; y_ctr <= rect_base; y_ctr++ ) {
        //  (g) Draw a horizontal line from left to rect_right, with 
        //      y-coordinate equal to y_ctr, using the character specified by 
        //      ch.
        draw_line(left, y_ctr, rect_right, y_ctr, ch);       // Creates line.
    //  (f.b) End the loop.
    }
}
//
//--------------------+
// Opperation:        |
//--------------------+
// The bellow code was supplied to use as a test driver within terminal. For AMS
// this code is removed and replaced with additional examples, to test the
// viability of the above progrgram.
int main(void) {
    setup_screen();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '@';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '&';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box with zero width.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 0;
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '*';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '#';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box with negative width.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = -rand() % screen_width();
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '!';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '+';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box with zero height.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 0;
    ch = 'a';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = 'b';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box with negative width.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - top - 1);
    height = -rand() % screen_height();
    ch = 'c';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    // draw a box.
    left = 1 + rand() % (screen_width() - 1) / 2;
    top = 1 + rand() % (screen_height() - 1) / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = 'd';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        left, top, width, height
        );
    fill_rect();
    show_screen();
    wait_char();
    //
    timer_pause(5000);
    cleanup_screen();
    return 0;
}
//
//==============================================================================//
