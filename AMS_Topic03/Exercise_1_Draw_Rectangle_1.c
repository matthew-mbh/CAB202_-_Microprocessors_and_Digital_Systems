//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic03
//
//  COMPILE:
//  gcc Exercise_1_Draw_Rectangle_1.c -o Exercise_1_Draw_Rectangle_1 -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_1_Draw_Rectangle_1
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
#include <cab202_graphics.h>
#include <cab202_timers.h>
//
//--------------------+
// Declare Variables: |
//--------------------+
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
//  (b) Declare a global variable of type char called ch.
//      This is the character that is to be used to render the rectangle.
char ch;   // Creates global variable for ch, waiting on character assignment.
//
//--------------------+
// draw_rect:         |
//--------------------+
void draw_rect(void) {
    //  (c) Insert code to draw the outline of the rectangle defined by the global
    //      variables.
    //      If either of the width or height is less than or equal to zero,
    //      the function must not draw anything.
    int right = left + width - 1;               // Define right coordinate.
    int bottom = top + height -1;               // Define bottom coordinate.
    //
    if (width <= 0 || height <= 0){
        return;
    }
    else{
        
        draw_line(left, top, right, top, ch);       // Creates top line.
        draw_line(right, top, right, bottom, ch);   // Creates line on right side.
        draw_line(left, bottom, right, bottom, ch); // Creates bottom line.
        draw_line(left, top, left, bottom, ch);     // Creates line on left side.
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
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '@';
    draw_rect();
    show_screen();
    //
    // draw a box.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '&';
    draw_rect();
    show_screen();
    //
    // draw a box with zero width.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 0;
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '*';
    draw_rect();
    show_screen();
    //
    // draw a box.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '#';
    draw_rect();
    show_screen();
    //
    // draw a box with negative width.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = -rand() % screen_width();
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '!';
    draw_rect();
    show_screen();
    //
    // draw a box.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = '+';
    draw_rect();
    show_screen();
    //
    // draw a box with zero height.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 0;
    ch = 'a';
    draw_rect();
    show_screen();
    //
    // draw a box.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = 'b';
    draw_rect();
    show_screen();
    //
    // draw a box with negative width.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = -rand() % screen_width();
    height = 1 + rand() % (screen_height() - top - 1);
    ch = 'c';
    draw_rect();
    show_screen();
    //
    // draw a box.
    left = rand() % screen_width() / 2;
    top = rand() % screen_height() / 2;
    width = 1 + rand() % (screen_width() - left - 1);
    height = 1 + rand() % (screen_height() - top - 1);
    ch = 'd';
    draw_rect();
    show_screen();
    //
    timer_pause(5000);
    cleanup_screen();
    return 0;
}
//
//==============================================================================//
