/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/Assignments/Assignment_2/Code
//
//  EXECUTE:
//  make
//
//------------------------------------------------------------------------------//
//==============================================================================//
//------------------------------------------------------------------------------//
// C SECIFIC CODE:
//------------------------------------------------------------------------------//
//--------------------+---------------------------------------------------------//
// DEFINE DIRECTORIES:|
//--------------------+
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"
#include "lcd.h"
#include "sprite.h"
/**
//--------------------------------+---------------------------------------------//
// DEFINE FREQUENCY & PRESCALER:  |
//--------------------------------+
*/
#define FREQ (8000000.0)            // Define appropriate frequency.
#define PRESCALER (64.0)            // Define appropriate prescaler.
/**
//--------------------+---------------------------------------------------------//
// DEFINE BOOLEANS:   |
//--------------------+
*/
_Bool Game_not_started = 0;         // Boolean state for when game not started.
_Bool init_t;                       // Boolean used when initialising time.
_Bool game_over = 0;                // Boolean for termination, when game ends.
_Bool perform_check;                // Boolean used to check number of sprites.
_Bool GO_Operation = 0;             // Boolean used for exiting game over screen.
_Bool exit_game;                    // Boolean used in the repeat or exit of game.
_Bool initial_sprite_pos;           // Boolean used for Initial sprite positions.
_Bool win;                          // Boolean for win state.
_Bool init_time = 0;                // Boolean used for capturing initial time.
_Bool initial_time = 0;             // Boolean used for capturing initial time.
_Bool odd = 1;                      // Boolean used for odd & even numbers.
_Bool tree_or_house[7];             // Boolean used in distinguishing sprite imgs.
_Bool Decelerate_sequence = 0;      // Boolean used for setting decelerate mode.
_Bool Accelerate_sequence = 0;      // Boolean used for setting accelerate mode.

/**
//--------------------------------+---------------------------------------------//
// INITIALISE IMPORTANT FUNCTIONS:|
//--------------------------------+
*/
void Setup_teensy_timer(void);
void Setup_teensy_interupts(void);
void Setup_controls(void);
void setup_teensy(void);
void ISR_constants(void);
void SS_constant_values(void);
void Game_constant_values(void);
void create_tree_sprite(uint8_t i);
void create_house_sprite(uint8_t i);
void Sprite_creation(void);
void Sprite_constant_values(void);
double now(void);
void Time_logic(void);
void Time_function(void);
void Fuel_levels(void);
void Setup_pump(void);
void Introduce_pump(void);
void Process_pump(void);
void Refueling_process(void);
void Paused_view(void);
void Dashboard(void);
void Display_splash_screen(void);
void ISR_process(uint8_t array_no, uint8_t pin, uint8_t pin_no);
void draw_Road(void);
void Down_switch(_Bool min, _Bool max, float speed_lim);
void Speed_dependent( float speed_lim);
void Up_switch(_Bool min, _Bool max, float speed_lim);
void Left_switch(void);
void Right_switch(void);
void Center_switch( _Bool min, _Bool max, float speed_lim);
void Brake_or_accelerate(float speed_lim);
void No_switch_pressed( _Bool min, _Bool max, float speed_lim);
void Acceleration( _Bool min, _Bool max, float speed_lim);
void Splash_screen_opperation(void);
void Race_car_move(void);
void Tree_movement(uint8_t i);
void House_movement(uint8_t i);
void Counter(void);
void Moving(void);
void Sprite_movement(void);
void Draw_sprites(void);
void Draw_sprites(void);
_Bool collided_sprites(uint8_t i);
_Bool collided_fuel_depot(void);
void Test_sprites(void);
void Race_car_opperation(void);
void Game_over_screen_opperation(void);
void Game_over_screen(void);
void GO(void);
void Not_started_sequence(void);
void Game_over_sequence(void);
void Player_review_sequence(void);
void Terminate_game_sequence(void);
void Exit_loop_sequence(void);
void Cleanup_sequence(void);
/**
//--------------------+---------------------------------------------------------//
// HELPER FUNCTIONS:  |
//--------------------+
*/
char buffer[20];                            // Create character array/length 20.
// As There was no method in the teensey grahics file for drawing both double and
// integers on screen, these were borrowed from one of the weekly exercises.
void draw_double(uint8_t x, uint8_t y, double value, colour_t colour) {
    snprintf(buffer, sizeof(buffer), "%f", value);
    draw_string(x, y, buffer, colour);
}
//
void draw_int(uint8_t x, uint8_t y, int value, colour_t colour) {
    snprintf(buffer, sizeof(buffer), "%d", value);
    draw_string(x, y, buffer, colour);
}
/**
//--------------------+---------------------------------------------------------//
// DEFINE GLOBALS:    |
//--------------------+
*/
// SPLASH SCREEN GLOBALS:
uint8_t left_c = 0;                         // Set global left coordinate.
uint8_t top_c = 0;                          // Set global top coordinate.
uint8_t right_c = 84;                       // Set global right coordinate.
uint8_t bottom_c = 48;                      // Set global bottom coordinate.
//
// MAIN GAME GLOBALS:
uint8_t Dashboard_offset;                   // Create global for Dashboard offset.
float Initial_time;                         // Create global to hold initial time.
float current_time;                         // Create global to hold current time.
float time;                                 // Create global to hold in game time.
uint8_t minute;                             // Create global for no. of minutes.
uint8_t Condition;                          // Create global for condition of car.
float Speed;                                // Create global for speed of car.
float Fuel;                                 // Create global for fuel remaining.
uint8_t solve_dist;
uint32_t Distance;                          // Create global for total distance.
uint8_t pit_stop;                           // Create global for pit stop marker.
//
uint8_t splits;                             // Create global for splits.
uint8_t split_center;                       // Create global for splits center.
uint8_t split_1;                            // Create global for split 1.
uint8_t split_2;                            // Create global for split 2.
uint8_t split_3;                            // Create global for split 3.
//
// ROAD GLOBALS
uint8_t l_road_edge;                        // Create global for left road edge.
uint8_t r_road_edge;                        // Create global for right road edge.
//
// RACE CAR SPRITE GLOBALS:
uint8_t RC_x;                               // Create global for race car x pos.
uint8_t RC_y;                               // Create global for race car y pos.
//
// SPLASH SCREEN SPRITE GLOBALS:
uint8_t SS_x;                               // Create global for race car x pos.
uint8_t SS_y;                               // Create global for race car y pos.
//
// SCENERY SPRITE GLOBALS:
uint8_t pixel_interval;                     // Create global for pixel interval.
uint8_t first_position;                     // Create global for first position.
uint8_t counter1;                           // Create global for counter 1.
uint8_t counter2;                           // Create global for counter 2.
uint8_t sprite_im_identifier[7];            // Create global array to hold image
                                            // identifier code.
float sprite_xpos[7];                       // Create global array sprite x pos.
float sprite_ypos[7];                       // Create global array sprite y pos.
Sprite scenery[7];                          // Create global array for holding
                                            // scenery sprites.
//
// FUEL DEPOT SPRITE GLOBALS:
uint8_t FD_x;                               // Create global for fuel depot x pos.
uint8_t FD_y;                               // Create global for fuel depot y pos.
//
// SWITCH DEBOUNCING GLOBALS
uint8_t bit_count[8];                       // Create global for bit count.
uint8_t switch_closed[8];                   // Create global called switch closed.
uint8_t history[8];                         // Create global for history.
uint8_t debounced_state[8];                 // Create global for debounced state.
uint8_t bit_mask = 0b00011111;              // Create bit mask to compare with.
static uint8_t prevState[8];                // Create global for comparing
                                            // previous button press state.
//
// TIMER GLOBALS:
volatile uint32_t cycle_count;              // Create global to hold cycle count.
uint8_t start_time;                         // Create global to hold start time.
float time_sec;                             // Create global to hold time seconds.
float hold_time;                            // Create global to hold time value.
float max_time;                             // Create global to hold max time.
//
// ADDITIONAL GLOBALS:
float Accelerating;                         // Create global to hold accelerating.
float brake;                                // Create global to hold brake.
uint8_t count;                              // Create global to hold count.
/**
//-------------------------------+----------------------------------------------//
// DEFINE SPRITE PARAMETERS:     |
//-------------------------------+
*/
/**SPLASH SCREEN BITMAP**/
# define SS_width (80)                      // Initialise splash screen width.
# define SS_height (27)                     // Initialise splash screen height.
Sprite Splash_screen;                       // Initialise sprite splash screen.
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t Splash_screen_bitmap[] = {          // Create splash screen bit map.
    0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, //Bite1.
    0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, // Bite2.
    0b10001111, 0b10000000, 0b11111100, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00000000, 0b00010000, 0b01110001, // Bite3.
    0b10011111, 0b11000000, 0b11000110, 0b00000000, 0b00000000, 0b00000000, 0b00110000, 0b00000000, 0b00101001, 0b11111001, // Bite4.
    0b10110000, 0b01100000, 0b11000110, 0b01111100, 0b01111100, 0b01111100, 0b01111000, 0b11111000, 0b01010101, 0b11101101, // Bite5.
    0b10010111, 0b01000000, 0b11111100, 0b00000110, 0b11000110, 0b11000110, 0b00110001, 0b10001100, 0b10101010, 0b00101101, // Bite6.
    0b10010000, 0b01000110, 0b11011000, 0b01111110, 0b11000000, 0b11111110, 0b00110001, 0b10001101, 0b11111111, 0b00110001, // Bite7.
    0b10010111, 0b01001110, 0b11001100, 0b11000110, 0b11000110, 0b11000000, 0b00110001, 0b10001100, 0b10000010, 0b00100001, // Bite8.
    0b10110000, 0b01101110, 0b11000110, 0b01111110, 0b01111100, 0b01111100, 0b00011100, 0b11111000, 0b10111010, 0b01000001, // Bite9.
    0b10010111, 0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10111010, 0b01000001, // Bite11.
    0b10010000, 0b01000010, 0b10011111, 0b11000000, 0b00000000, 0b00011000, 0b00011000, 0b00000000, 0b10000010, 0b01000001, // Bite12.
    0b11111111, 0b11111101, 0b00000000, 0b11000000, 0b00000000, 0b00011000, 0b00000000, 0b00000000, 0b11111111, 0b11111101, // Bite13.
    0b10101010, 0b10101001, 0b00000001, 0b10001111, 0b10011101, 0b11011111, 0b10011001, 0b11110000, 0b10000011, 0b01010101, // Bite14.
    0b10111111, 0b11111011, 0b00000011, 0b00011000, 0b11011010, 0b11011000, 0b11011011, 0b00011000, 0b11111111, 0b11111101, // Bite15.
    0b10000000, 0b00000000, 0b00000110, 0b00011000, 0b11011010, 0b11011000, 0b11011011, 0b11111000, 0b00000000, 0b00000001, // Bite16.
    0b10001010, 0b10000000, 0b00001100, 0b00011000, 0b11011010, 0b11011000, 0b11011011, 0b00000000, 0b00000000, 0b11100001, // Bite17.
    0b10000100, 0b10000000, 0b00011111, 0b11001111, 0b10011010, 0b11011111, 0b10011001, 0b11110000, 0b00000001, 0b11111001, // Bite18.
    0b10000111, 0b01100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b11111001, // Bite19.
    0b10010110, 0b11000100, 0b00010000, 0b00000000, 0b00000000, 0b00000110, 0b00000000, 0b00110000, 0b00000111, 0b11110001, // Bite10.
    0b10001011, 0b10100110, 0b00110000, 0b00000000, 0b00000000, 0b00000110, 0b00000000, 0b00000000, 0b00000110, 0b11000001, // Bite20.
    0b10000111, 0b00000111, 0b01110011, 0b11100110, 0b00110111, 0b11001111, 0b00011111, 0b00110111, 0b11000010, 0b10010001, // Bite21.
    0b10000011, 0b00000111, 0b11110110, 0b00110110, 0b00110110, 0b01100110, 0b00000001, 0b10110110, 0b01100001, 0b10111001, // Bite22.
    0b10000011, 0b00000110, 0b10110110, 0b00110110, 0b00110110, 0b01100110, 0b00011111, 0b10110110, 0b01100000, 0b10110001, // Bite23.
    0b10000111, 0b10000110, 0b00110110, 0b00110110, 0b00110110, 0b01100110, 0b00110001, 0b10110110, 0b01100000, 0b11000001, // Bite24.
    0b10001111, 0b11000110, 0b00110011, 0b11100011, 0b11110110, 0b01100011, 0b10011111, 0b10110110, 0b01100000, 0b10000001, // Bite25.
    0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, // Bite26.
    0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111  // Bite27.
};
//
/**RACE CAR BITMAP**/
# define RC_width (8)                       // Initialise Race Car sprite width.
# define RC_height (9)                      // Initialise Race Car sprite height.
Sprite Race_car;                            // Initialise sprite race car.
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t car_bitmap[] = {                    // Create sprite race car bit map.
    0b00100100,                             // Bite 1.
    0b01000010,                             // Bite 2.
    0b10100101,                             // Bite 3.
    0b10011001,                             // Bite 4.
    0b10111101,                             // Bite 5.
    0b10111101,                             // Bite 6.
    0b11000011,                             // Bite 7.
    0b10111101,                             // Bite 8.
    0b01111110                              // Bite 9.
};
//
/**FUEL DEPOT BITMAP**/
# define FD_width (24)                      // Initialise Fuel Depot sprite width.
# define FD_height (10)                     // Initialise Fuel Depot sprite width.
Sprite Fuel_depot;                          // Initialise sprite Fuel Depot.
// 10 rows of  three bite's, each bite is an eight bit operator, so spans eight
// bit's columns. In this case, because it spans 3 bites in width, this results in
// it spanning twenty four bit's/columns.
uint8_t Fuel_depot_bitmap[] = {             // Create sprite Fuel Depot bit map
    0b01100000, 0b10000000, 0b00100110,     // Bites 1,2 & 3(three bites wide).
    0b11111110, 0b10000000, 0b00100110,     // Bites 4,5 & 6(three bites wide).
    0b10101010, 0b10000000, 0b00101111,     // Bites 7,8 & 9(three bites wide).
    0b11010110, 0b10000000, 0b00101111,     // Bites 10,11 & 12(three bites wide).
    0b10101010, 0b10000000, 0b00100110,     // Bites 13,14 & 15(three bites wide).
    0b11111110, 0b10000000, 0b00100110,     // Bites 16,17 & 18(three bites wide).
    0b10000010, 0b10000000, 0b00101111,     // Bites 19,20 & 21(three bites wide).
    0b10111010, 0b10000000, 0b00101111,     // Bites 22,23 & 24(three bites wide).
    0b10101010, 0b10000000, 0b00100110,     // Bites 25,26 & 27(three bites wide).
    0b10101010, 0b10000000, 0b00100110      // Bites 28,29 & 30(three bites wide).
};
//
/**LARGE HOUSE BITMAPS**/
# define HL_width (16)                      // Initialise House L sprite width.
# define HL_height (13)                     // Initialise House L sprite height.
Sprite House_large[4];                      // Initialise sprite House large.
// 13 rows of  two bite's, each bite is an eight bit operator, so spans eight
// bit's columns. In this case, because it spans 2 bites in width, this results in
// it spanning sixteen bit's/columns.
uint8_t House2_bitmap[] = {                 // Create sprite House 2 bit map.
    0b00000000, 0b00001100,                 //Bites 1 & 2 (two bites wide).
    0b00001000, 0b01111110,                 //Bites 3 & 4 (two bites wide).
    0b00010100, 0b11111110,                 //Bites 5 & 6 (two bites wide).
    0b00101010, 0b11110111,                 //Bites 7 & 8 (two bites wide).
    0b01010101, 0b00010111,                 //Bites 9 & 10 (two bites wide).
    0b11111111, 0b10011000,                 //Bites 11 & 12 (two bites wide).
    0b01000001, 0b00010000,                 //Bites 13 & 14 (two bites wide).
    0b01011101, 0b00100000,                 //Bites 15 & 16 (two bites wide).
    0b01011101, 0b00100000,                 //Bites 17 & 18 (two bites wide).
    0b01000001, 0b00100000,                 //Bites 19 & 20 (two bites wide).
    0b01111111, 0b11111111,                 //Bites 21 & 22 (two bites wide).
    0b01000001, 0b10101010,                 //Bites 23 & 24 (two bites wide).
    0b01111111, 0b11111111                  //Bites 25 & 26 (two bites wide).
};
// 13 rows of  two bite's, each bite is an eight bit operator, so spans eight
// bit's columns. In this case, because it spans 2 bites in width, this results in
// it spanning sixteen bit's/columns.
uint8_t House3_bitmap[] = {                 // Create sprite House 3 bit map
    0b00011111, 0b00000000,                 // Bites 1 & 2 (two bites wide).
    0b00111111, 0b10000000,                 // Bites 3 & 4 (two bites wide).
    0b01100000, 0b11000000,                 // Bites 5 & 6 (two bites wide).
    0b00101110, 0b10001110,                 // Bites 7 & 8 (two bites wide).
    0b00100000, 0b10011111,                 // Bites 9 & 10 (two bites wide).
    0b00101110, 0b10011111,                 // Bites 11 & 12 (two bites wide).
    0b00111111, 0b10000100,                 // Bites 13 & 14 (two bites wide).
    0b01100000, 0b11000101,                 // Bites 15 & 16 (two bites wide).
    0b00101110, 0b10000101,                 // Bites 17 & 18 (two bites wide).
    0b00100000, 0b10000010,                 // Bites 19 & 20 (two bites wide).
    0b11111111, 0b11111010,                 // Bites 21 & 22 (two bites wide).
    0b01010101, 0b01010001,                 // Bites 23 & 24 (two bites wide).
    0b01111111, 0b11110011                  // Bites 25 & 26 (two bites wide).
};
// 13 rows of  two bite's, each bite is an eight bit operator, so spans eight
// bit's columns. In this case, because it spans 2 bites in width, this results in
// it spanning sixteen bit's/columns.
uint8_t House4_bitmap[] = {                 // Create sprite House 4 bit map
    0b00011111, 0b11110000,                 // Bites 1 & 2 (two bites wide).
    0b00101010, 0b10101000,                 // Bites 3 & 4 (two bites wide).
    0b01010101, 0b01010100,                 // Bites 5 & 6 (two bites wide).
    0b11111111, 0b11111110,                 // Bites 7 & 8 (two bites wide).
    0b10000010, 0b00010100,                 // Bites 9 & 10 (two bites wide).
    0b10111010, 0b00010100,                 // Bites 11 & 12 (two bites wide).
    0b10111010, 0b00010100,                 // Bites 13 & 14 (two bites wide).
    0b10111010, 0b00010100,                 // Bites 15 & 16 (two bites wide).
    0b10000010, 0b00010100,                 // Bites 17 & 18 (two bites wide).
    0b11111111, 0b11111100,                 // Bites 19 & 20 (two bites wide).
    0b10000011, 0b01010100,                 // Bites 21 & 22 (two bites wide).
    0b11111111, 0b11111110,                 // Bites 23 & 24 (two bites wide).
    0b11111111, 0b11111111                  // Bites 25 & 26 (two bites wide).
};
// 13 rows of  two bite's, each bite is an eight bit operator, so spans eight
// bit's columns. In this case, because it spans 2 bites in width, this results in
// it spanning sixteen bit's/columns.
uint8_t House5_bitmap[] = {                 // Create sprite House 5 bit map
    0b00011100, 0b00111000,                 // Bites 1 & 2 (two bites wide).
    0b00101010, 0b11111100,                 // Bites 3 & 4 (two bites wide).
    0b01010101, 0b01111111,                 // Bites 5 & 6 (two bites wide).
    0b11111111, 0b10110111,                 // Bites 7 & 8 (two bites wide).
    0b10000001, 0b00100011,                 // Bites 9 & 10 (two bites wide).
    0b10111101, 0b00101100,                 // Bites 11 & 12 (two bites wide).
    0b10111101, 0b00111000,                 // Bites 13 & 14 (two bites wide).
    0b10000001, 0b00100000,                 // Bites 15 & 16 (two bites wide).
    0b11111111, 0b11111100,                 // Bites 17 & 18 (two bites wide).
    0b11000001, 0b01110100,                 // Bites 19 & 20 (two bites wide).
    0b11111111, 0b11111100,                 // Bites 21 & 22 (two bites wide).
    0b10110011, 0b01101110,                 // Bites 23 & 24 (two bites wide).
    0b10110011, 0b01101011                  // Bites 25 & 26 (two bites wide).
};
//
/**TREE BITMAPS**/
# define T_width (8)                        // Initialise Tree sprite width.
# define T_height (10)                      // Initialise Tree sprite height.
Sprite Tree[4];                             // Initialise sprite Tree.
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t Tree1_bitmap[] = {                  // Create sprite Tree 1 bit map
    0b01010100,                             // Bite 1.
    0b00100100,                             // Bite 2.
    0b00111011,                             // Bite 3.
    0b10110110,                             // Bite 4.
    0b01011101,                             // Bite 5.
    0b00111000,                             // Bite 6.
    0b00011000,                             // Bite 7.
    0b00011000,                             // Bite 8.
    0b00111100,                             // Bite 9.
    0b01111110                              // Bite 10.
};
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t Tree2_bitmap[] = {                  // Create sprite Tree 2 bit map
    0b00001000,                             // Bite1.
    0b00011000,                             // Bite2.
    0b00111100,                             // Bite3.
    0b00111100,                             // Bite4.
    0b01111110,                             // Bite5.
    0b11111111,                             // Bite6.
    0b01111110,                             // Bite7.
    0b00111100,                             // Bite8.
    0b00001000,                             // Bite9.
    0b00001000                              // Bite10.
};
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t Tree3_bitmap[] = {                  // Create sprite Tree 3 bit map
    0b00111000,                             // Bite1.
    0b01111110,                             // Bite2.
    0b11111111,                             // Bite3.
    0b11011111,                             // Bite4.
    0b01110010,                             // Bite5.
    0b00110110,                             // Bite6.
    0b00011100,                             // Bite7.
    0b00011000,                             // Bite8.
    0b00011000,                             // Bite9.
    0b00111100                              // Bite10.
};
// 9 rows of bite's, each bite is an eight bit operator, so spans eight
// bit's/ columns.
uint8_t Tree4_bitmap[] = {                  // Create sprite Tree 4 bit map
    0b00011100,                             // Bite1.
    0b00111111,                             // Bite2.
    0b01111111,                             // Bite3.
    0b11111110,                             // Bite4.
    0b11011000,                             // Bite5.
    0b01010010,                             // Bite6.
    0b00110111,                             // Bite7.
    0b00010110,                             // Bite8.
    0b00011000,                             // Bite9.
    0b00010000                              // Bite10.
};
/**
//----------------------------+-------------------------------------------------//
// INTERUPT SERVICE ROUTINE'S:|
//----------------------------+-------------------------------------------------//
//----------------------------+-------------------------------------------------//
// INTERUPT SERVICE ROUTINE 0:|
//----------------------------+
*/
// This interupt service makes use of the 8 bit timer, timer zero and is used for
// monitoring the debouncinging component of the swwitch controls.
ISR(TIMER0_OVF_vect) {
    // CONTROLS:
    // SWITCH 1 (JOYSTIC):
    ISR_process( 1, PINB, 0);               // Set input for Pin 0 (Center).
    ISR_process( 2, PINB, 1);               // Set input for Pin 1 (Left).
    ISR_process( 3, PINB, 7);               // Set input for Pin 7 (Down).
    ISR_process( 4, PIND, 0);               // Set input for Pin 0 (Right).
    ISR_process( 5, PIND, 1);               // Set input for Pin 1 (Up).
    // SWITCH 2:
    ISR_process( 6, PINF, 6);               // Set input for Pin 6 (SW2).
    // SWITCH 3:
    ISR_process( 7, PINF, 5);               // Set input for Pin 5 (SW3).
}
/**
//----------------------------+-------------------------------------------------//
// INTERUPT SERVICE ROUTINE 3:|
//----------------------------+
*/
// This interupt service makes use of the 16 bit timer, timer three and is used
// for monitoring the cycle count. Achieved by interupting all running processes,
// returning the cycle count value, which can be used to solve for the time. This
// will also not commence opperation until the actual game begins.
ISR(TIMER3_OVF_vect) {
    // TIME:
    if (start_time == !1) {                 // if boolean not equal to 1, run.
        cycle_count ++;                     // Store cycle count value.
    }
}
/**
//--------------------+---------------------------------------------------------//
// SETUP TIMER:       |
//--------------------+
*/
void Setup_teensy_timer(void) {
    TCCR0A = 0;                             // Set timer 0 to normal mode.
    TCCR0B = 4;                             // Set timer 0 overflow period to use.
    TCCR3A = 0;                             // Set timer 1 to normal mode.
    TCCR3B = 3;                             // Set timer 1 overflow period to use.
}
/**
//--------------------+---------------------------------------------------------//
// SETUP INTERUPTS:   |
//--------------------+
*/
void Setup_teensy_interupts(void) {
    TIMSK0 = 1;                             // Timer overflow interrupt Time 0.
    TIMSK3 = 1;                             // Timer overflow interrupt Time 0.
    sei();                                  // Turn on/enables interupts.
}
/**
//--------------------+---------------------------------------------------------//
// SETUP CONTROLS:    |
//--------------------+
*/
void Setup_controls(void) {
    // LED0:
    SET_BIT(DDRB, 2);                       // Set Output for Pin 2 (LED0).
    // SWITCH 1 (JOYSTIC):
    CLEAR_BIT(DDRB, 0);                     // Set input for Pin 0 (Center).
    CLEAR_BIT(DDRB, 1);                     // Set input for Pin 1 (Left).
    CLEAR_BIT(DDRB, 7);                     // Set input for Pin 7 (Down).
    CLEAR_BIT(DDRD, 0);                     // Set input for Pin 0 (Right).
    CLEAR_BIT(DDRD, 1);                     // Set input for Pin 1 (Up).
    // SWITCH 2:
    CLEAR_BIT(DDRF, 6);                     // Set input for Pin 6 (SW2).
    // SWITCH 3:
    CLEAR_BIT(DDRF, 5);                     // Set input for Pin 5 (SW3).
}
/**
//--------------------+---------------------------------------------------------//
// SETUP TEENSY:      |
//--------------------+
*/
void setup_teensy(void) {
    set_clock_speed(CPU_8MHz);              // Set teensy clock speed.
    lcd_init(LCD_DEFAULT_CONTRAST);         // Set LCD to default contrast.
    lcd_clear();                            // Clears LCD screen.
    //SETUP FUNCTIONS:
    Setup_teensy_timer();                   // Calls  teensy timer function.
    Setup_teensy_interupts();               // Calls  teensy interupts function.
    Setup_controls();                       // Calls  setup controls function.
}
/**
//--------------------+---------------------------------------------------------//
// ISR CONSTANTS:     |
//--------------------+
*/
void ISR_constants(void) {
    // For loop sets the initial value to zero for the following unsighned 8 bit
    // integers arrays. Each array by the end of the loop, will contain seven
    // initial values.
    for (uint8_t i=1; i<8; i++ ){
        bit_count[i] = 0;                   // Set bit count initial values.
        history[i] = 0;                     // Set history initial values.
        debounced_state[i] = 0;             // set debounced state initial values.
        prevState[i] = 0;                   // Set previous state initial values.
    }
}
/**
//--------------------------------+---------------------------------------------//
// SPLASH SCREEN CONSTANT VALUES: |
//--------------------------------+
*/
void SS_constant_values( void ) {
    // DEFINE X & Y POSITION:
    SS_x = 2.0;                             // Set splash screen x position.
    SS_y = 2.0;                             // Set splash screen y position.
    //
    sprite_init(&Splash_screen, SS_x, SS_y, SS_width, SS_height, Splash_screen_bitmap);              // Initialise splash screen sprite.
}
/**
//------------------------+-----------------------------------------------------//
// GAME CONSTANT VALUES:  |
//------------------------+
*/
void Game_constant_values( void ) {
    //Dashboard_offset = 1;                 // Initialise offset equals one.
    time = 0.0;                             // Initialise time equals zero.
    minute = 0;                             // Initialise minutes equals zero.
    Condition = 100;                        // Condition of race car.
    Speed = 0;                              // Current speed of the race car.
    Fuel = 100;                             // Amount of fuel remaining.
    solve_dist = 0;                         // Assists with calculating distance.
    Distance = 0;                           // Distance traveled in game.
    pit_stop = 2;                           // Initialise pit stop first value.
    count = 0;                              // Initialise count, set to zero.
    //
    splits = round(right_c/3);              // Defines width of splits.
    split_center = splits/3;                // Finds center point of splits.
    split_1 = split_center;                 // set split 1 x coordinate.
    split_2 = splits + split_center;        // set split 2 x coordinate.
    split_3 = (splits*2) + split_center;    // set split 3 x coordinate.
}
/**
//------------------------+-----------------------------------------------------//
// CREATE TREE SPRITE:    |
//------------------------+
*/
void create_tree_sprite(uint8_t i) {
    uint8_t randomiser = 1 + rand() % 4;    // Finds a random value between 1 & 4.
    sprite_im_identifier[i] = randomiser;   // Saved sprite values defining image.
    tree_or_house[i] = 0;                   // Boolean 0 refferences tree sprites.
    //
    if (sprite_ypos[i] > 48) {              // If y position greater than 48.
        sprite_ypos[i] = 10 - ((T_height) - (sprite_ypos[i] - 48)); //Y pos.
        sprite_xpos[i] = (((84/3)*2) + rand() % ((84/3) - (T_width + 1)));//X pos.
    }
    else {sprite_ypos[i] = sprite_ypos[i];} // sprite y position remains same.
    //
    if(randomiser == 1) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree1_bitmap);}  // Tree sprite Posability 1.
    if(randomiser == 2) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree2_bitmap);}  // Tree sprite Posability 2.
    if(randomiser == 3) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree3_bitmap);}  // Tree sprite Posability 3.
    if(randomiser == 4) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree4_bitmap);}  // Tree sprite Posability 4.
}
/**
//------------------------+-----------------------------------------------------//
// CREATE HOUSE SPRITE:   |
//------------------------+
*/
void create_house_sprite(uint8_t i) {
    uint8_t randomiser = 1 + rand() % 4;    // Finds a random value between 1 & 4.
    sprite_im_identifier[i] = randomiser;   // Saved sprite values defining image.
    tree_or_house[i] = 1;                   // Boolean 1 refferences tree sprites.
    //
    if (sprite_ypos[i] > 48) {              // If y position greater than 48.
        sprite_ypos[i] = 10 - ((HL_height) - (sprite_ypos[i] - 48)); //Y pos.
        sprite_xpos[i] =  1 + rand() % ((l_road_edge - (HL_width + 3))); //X pos.
    }
    else {sprite_ypos[i] = sprite_ypos[i];} // sprite y position remains same.
    //
    if(randomiser == 1) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House2_bitmap);}// House sprite Posability 1.
    if(randomiser == 2) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House3_bitmap);}// House sprite Posability 2.
    if(randomiser == 3) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House4_bitmap);}// House sprite Posability 3.
    if(randomiser == 4) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House5_bitmap);}// House sprite Posability 4.
}
/**
//------------------------+-----------------------------------------------------//
// SPRITE CREATION:       |
//------------------------+
*/
void Sprite_creation( void ) {
    uint8_t next = 0;                       // Define and set next too zero.
    srand(now());                           // srand function seeded with now().
    //
    for (uint8_t i = 1; i < 7; i++) {       // Cycle through 6 times.
        next = next + 1;                    // Increase value of next by one.
        sprite_ypos[i] = (first_position - pixel_interval); //  set new y pos.
        if (next == 2) {                    // If next equal too two.
            pixel_interval = pixel_interval + 14; // Increase pixel interval size.
            next = 0;                       // Set next too value of zero.
        }
        if (odd == 1) {                     // When odd.
            sprite_xpos[i] =  1 + rand() % ((l_road_edge - (HL_width + 3)));
            create_house_sprite(i);         // Calls create house sprite function.
            odd = 0;                        // Changes to even classification.
        }
        else if (odd == 0) {                // When even.
            sprite_xpos[i] = (((84/3)*2) + rand() % ((84/3) - (T_width + 1)));
            create_tree_sprite(i);          // Calls create tree sprite function.
            odd = 1;                        // Changes to odd classification.
        }
    }
    scenery->is_visible = 0;                // Set scenery sprites too invisible.
}
/**
//------------------------+-----------------------------------------------------//
// SPRITE CONSTANT VALUES:|
//------------------------+
*/
void Sprite_constant_values( void ) {
    RC_x = round((right_c/2) - (RC_width/2)); // Define race car initial x pos.
    RC_y = bottom_c - (RC_height+1);        // Define race car initial y pos.
    sprite_init(&Race_car, RC_x, RC_y, RC_width, RC_height, car_bitmap);
    //
    pixel_interval = 14;                    // Set pixel interval value.
    first_position = 39 + pixel_interval;   // Set first position value.
    //
    Sprite_creation();                      // Calls sprite creation function.
}
/**
//-------------------+----------------------------------------------------------//
// NOW FUNCTION:     |
//-------------------+
 */double now(void){
     // Formula to shift cycle count into seconds.
     double elapsed_time = ( cycle_count * 65536.0 + TCNT3 ) * PRESCALER  / FREQ;
     return elapsed_time;                   // Returns new result when called.
 }
/**
//---------------------+--------------------------------------------------------//
// TIME LOGIC FUNCTION:|
//---------------------+
*/
void Time_logic( void ) {
    if ((time) >= (6000.0/(4.0*(1.0 - 0.5242882)))){ // If greater\equal.
        time_sec = 0.0;                     // Reset seconds count.
        time = 0.0;                         // Reset time count.
        minute = minute + 1.0;              // Minute value increases by 1.
    }
}
/**
 //---------------------+-------------------------------------------------------//
 // TIME FUNCTION:      |
 //---------------------+
 */
void Time_function( void ) {
    if ( switch_closed[7] != prevState[7] ) { // Checks if switch three closed.
        prevState[7] = switch_closed[7];    // Mark previous state as trigured.
        if (switch_closed[7] == 1) {        // Switch three closed.
            Time_logic();                   // Calls time logic function.
            time = time;                    // Time value remains same value.
            time_sec = minute+((time/100000.0)*(4.0*(1.0 - 0.5242882))); //
            SET_BIT(PORTB, 2);              // Set LED0 high (Turns on LED0).
            clear_screen();                 // Clears screen.
            Paused_view();                  // Calls paused view function.
            show_screen();                  // Show screen.
            _delay_ms(1000);                // Calls for a 1000 millisecond delay.
        }
    }
    else{
        Time_logic();                       // Calls time logic function.
        time = time + now();                // Time increases in value.
        time_sec = minute+((time/100000.0)*(4.0*(1.0 - 0.5242882))); // seconds.
    }
}
/**
//--------------------+---------------------------------------------------------//
// FUEL LEVELS:       |
//--------------------+
*/
void Fuel_levels(void){
    if (Speed <= 0){                        // If Speed smaller/ equal to zero.
        Fuel = Fuel;                        // Fuel stays the same value.
    }
    if (Speed > 0){                         // If speed greater than zero.
        Fuel = Fuel - (0.01*Speed);         // Fuel is set to decrease in value.
    }
}
/**
//---------------------+--------------------------------------------------------//
// SETUP PUMP FUNCTION:|
//---------------------+
*/
void Setup_pump(void) {
    FD_x = - FD_width;                      // Set Fuel Depot x pos off screen.
    FD_y = - FD_height;                     // Set Fuel Depot y pos off screen.
    //
    // INITIALISE FUEL DEPOT SPRITE:
    sprite_init(&Fuel_depot, FD_x, FD_y, FD_width, FD_height, Fuel_depot_bitmap);
}

/**
//--------------------------+---------------------------------------------------//
// INTRODUCE PUMP FUNCTION: |
//--------------------------+
*/
void Introduce_pump(void) {
    uint8_t threshold = round((-1.1111 * Fuel) + 111.11); // Linear approximation.
    if ( threshold > 100 ) {                // If threshold greater than 100.
        threshold = 100;                    // Limit threshold to max of 100.
    }
    uint8_t random_value = rand() % 100000; // Find random value.
    if (random_value < threshold ) {        // If random val smaller to threshold.
        if (rand() % 2 == 0) {
            FD_y = 10 - (FD_height);        // Set y position  of fuel depot.
            FD_x =  1 + rand() % ((l_road_edge - (FD_width + 3))); // Set L X.
        }
        else {
            FD_y = 10 - (FD_height);        // Set y position  of fuel depot.
            FD_x = (((84/3)*2) + rand() % ((84/3) - (FD_width + 1))); // Set R X.
        }
    }
}
/**
//-----------------------+------------------------------------------------------//
// PROCESS PUMP FUNCTION:|
//-----------------------+
*/
void Process_pump(void) {
    if ( (FD_y >= 10 - (FD_height)) & (FD_y <= 48) ) { // If y position on screen.
        if (counter1 >= 30){                // If counter greater/ equal too 30.
            FD_y = FD_y + Speed;            // Increase y position through speed.
        }
    }
    else {
        Introduce_pump();                   // Calls introduce pump function.
    }
    //
    // INITIALISE FUEL DEPOT SPRITE:
    sprite_init(&Fuel_depot, FD_x, FD_y, FD_width, FD_height, Fuel_depot_bitmap);
}
/**
//----------------------------+-------------------------------------------------//
// REFUELING PROCESS FUNCTION:|
//----------------------------+
*/
void Refueling_process(void) {
    float time_per_fuel = 3/100;            // Max value for fuel increase rate.
    float variation = 3/110;                // Min value for fuel increase rate.
    
    if ((Speed < 1) & (Fuel < 100)) {       // If speed and fuel bellow values.
        if ((RC_y >= FD_y) & (RC_y <= (FD_y + FD_height))) {
            if (initial_time == 0) {        // If boolean false.
                hold_time = time_sec;       // Hold time equals the second count.
                initial_time = 1;           // Set hold time equal too one.
            }
            max_time = time_sec - hold_time;// Max time opperation.
            if ((max_time >= variation) & (max_time <= time_per_fuel)) {
                Fuel = Fuel + 1;            // Fuel increases by one.
                initial_time = 0;           // Set hold time equal too zero.
            }
        }
    }
    else {
        hold_time = 0;                      // Set hold time equal too zero.
        max_time = 0;                       // Set max time equal too zero.
        initial_time = 0;                   // Set initial time equal too zero.
        
    }
}

/**
//-----------------------+------------------------------------------------------//
// PAUSED VIEW FUNCTION: |
//-----------------------+
*/
void Paused_view(void){
    draw_line(0, 10, 84, 10, BG_COLOUR);    // Draw section line.
    draw_string(14, 0, "PAUSED VIEW", FG_COLOUR); // Draw string paused view.
    draw_line(0, 10, 84, 10, FG_COLOUR);    // Draw section line.
    // TIME:
    draw_string(0, 15, "Time =", FG_COLOUR);// Draw string time.
    draw_double(36, 15, time_sec, FG_COLOUR); // Draw previous round total time.
    // DISTANCE:
    draw_string(0, 30, "Dist =", FG_COLOUR);// Draw string 'dist' for distance.
    draw_int(36, 30, Distance, FG_COLOUR);  // Draw result for total distance.
}
/**
//---------------------+--------------------------------------------------------//
// DASHBOARD FUNCTION: |
//---------------------+
*/
void Dashboard( void ) {
    // CONDITION:
    draw_string(0, 0, "C:", FG_COLOUR);              // Draws condition string.
    draw_int(split_1, 0, Condition, FG_COLOUR);      // Draws condition value.
    // SPEED:
    draw_string(split_2-11, 0, "|S:    ", FG_COLOUR);// Draws string for speed.
    draw_int(split_2+4, 0, Speed, FG_COLOUR);        // Draws int for speed value.
    // FUEL:
    draw_string(split_3-11, 0, "|F:", FG_COLOUR);    // Draws string for fuel.
    draw_int(split_3+3, 0, Fuel, FG_COLOUR);         // Draws int for fuel value.
    //
    draw_line(0, 10, 84, 10, FG_COLOUR);             // Draws line.
}
/**
//---------------------------------+--------------------------------------------//
// DISPLAY SPLASH SCREEN FUNCTION: |
//---------------------------------+
*/
void Display_splash_screen( void ) {
    sprite_draw(&Splash_screen);            // Draw splash screen.
    draw_string(7, 30, "Matt Hutchison", FG_COLOUR); // Draw student name.
    draw_string(22, 38, "n8548625", FG_COLOUR);      // Draw student number.
}
/**
//-----------------------------------+------------------------------------------//
// INTERUPT SERVICE ROUTINE PROCESS: |
//-----------------------------------+
*/
void ISR_process( uint8_t array_no, uint8_t pin, uint8_t pin_no) {
    bit_count[array_no] = (bit_count[array_no] << 1); // Left shift one space.
    //
    // BITWISE AND AND MASK:
    bit_count[array_no] = bit_count[array_no] | BIT_VALUE(pin, pin_no); // AND.
    bit_count[array_no] = (bit_count[array_no] & bit_mask); // Mask.
    //
    // STORE TRIGGERED VALUE IN HISTORY ARRAY:
    history[array_no] = (history[array_no] & bit_mask) | BIT_IS_SET(pin, pin_no);
    //
    if (bit_count[array_no] == bit_mask){   // Switch closed five times in a row.
        switch_closed[array_no] = 1;        // Assign value of one.
    }
    if (bit_count[array_no] == 0){          // Switch open five times in a row.
        switch_closed[array_no] = 0;        // Assign value of zero.
    }
}
/**
//------------------------+-----------------------------------------------------//
// DRAW ROAD FUNCTION:    |
//------------------------+
*/
void draw_Road(void){
    l_road_edge = ((right_c - left_c)/3);  // Define left road edge value.
    r_road_edge = ((right_c - left_c)/3)*2;// Define right road edge value.
    //
    // Draws line for right and left edge of the road:
    draw_line( l_road_edge, 10, l_road_edge, bottom_c, FG_COLOUR ); // Left.
    draw_line( r_road_edge, 10, r_road_edge, bottom_c, FG_COLOUR ); // Right.
}
/**
//------------------------+-----------------------------------------------------//
// DOWN SWITCH FUNCTION:  |
//------------------------+
*/
void Down_switch( _Bool min, _Bool max, float speed_lim){
    if ( switch_closed[3] != prevState[3] ) { // If down switch closed.
        prevState[3] = switch_closed[3];    // Mark previous state as trigured.
        if (switch_closed[3] == 1) {        // Down switch closed.
            if (Speed <= 0) {Speed = 0;}    // If smaller than, set too 0.
            else {
            SET_BIT(PORTB, 2);              // Set LED0 high (Turns on LED0).
            Speed = Speed - 1;              // Subtract 0.1 off speed value.
            }
        }
    }
    if (Speed <= 0) {Speed = 0;}            // If smaller than, set too 0.
}
/**
//---------------------------+--------------------------------------------------//
// SPEED DEPENDENT FUNCTION: |
//---------------------------+
*/
void Speed_dependent( float speed_lim){
    if (round(speed_lim) == 3){             // If greater or equal to three.
        Accelerating = 3.0/ ((speed_lim)*25); // Accellerate for 3 seconds.
    }
    if (round(speed_lim) == 10){            // If greater or equal to ten.
        Accelerating = 3.0/ ((speed_lim)*2.5); // Accellerate for 3 seconds.
    }
}
/**
//------------------------+-----------------------------------------------------//
// UP SWITCH FUNCTION:    |
//------------------------+
*/
void Up_switch( _Bool min, _Bool max, float speed_lim){
    //
    if (Decelerate_sequence == 0) {         // // If boolean false.
        Speed_dependent( speed_lim);        // Calls speed dependent function.
        if ( switch_closed[5] != prevState[5] ) { // If up switch closed.
            prevState[5] = switch_closed[5];// Mark previous state as trigured.
            if (switch_closed[5] == 1) {    // Up switch closed.
                SET_BIT(PORTB, 2);          // Set LED0 high (Turns on LED0).
                if (Speed == speed_lim){    // If speed equals speed limit.
                    Speed = speed_lim;      // Set speed to speed limit.
                    Accelerate_sequence = 0;// Set boolean too false (zero value).
                }
                else {
                    Accelerate_sequence = 1;// Set boolean too true (one value).
                    Speed = Speed + (Accelerating); // Add to speed value.
        }}}
        if ((Accelerate_sequence == 1) & (Speed != speed_lim)) { // If met.
            Speed = Speed + (Accelerating);
            if (Speed >= speed_lim) {       // If speed smaller than 0.
                Accelerate_sequence = 0;    // Set boolean too false (zero value).
}}}}
/**
//------------------------+-----------------------------------------------------//
// LEFT SWITCH FUNCTION:  |
//------------------------+
*/
void Left_switch( void ){
    if ( switch_closed[2] != prevState[2] ) { // If left switch closed.
        prevState[2] = switch_closed[2];    // Mark previous state as trigured.
        if (switch_closed[2] == 1) {        // Left switch closed.
            SET_BIT(PORTB, 2);              // Set LED0 high (Turns on LED0).
            if (RC_x > left_c+1){           // Is RC x greater left boarder.
                RC_x = RC_x - Speed;        // Minus one off RC x value.
                sprite_init(&Race_car, RC_x, RC_y, RC_width, RC_height, car_bitmap);            // Initialise race car sprite.
            }
        }
    }
}
/**
//------------------------+-----------------------------------------------------//
// RIGTH SWITCH FUNCTION: |
//------------------------+
*/
void Right_switch( void ){
    if ( switch_closed[4] != prevState[4] ) { // // If center switch closed.
        prevState[4] = switch_closed[4];    // Mark previous state as trigured.
        if (switch_closed[4] == 1) {        // If right switch closed.
            SET_BIT(PORTB, 2);              // Set LED0 high (Turns on LED0).
            if (RC_x < (right_c - (RC_width))){ // Is RC greater right boarder.
                RC_x = RC_x + Speed;        // Plus one off RC x value.
                sprite_init(&Race_car, RC_x, RC_y, RC_width, RC_height, car_bitmap);            // Initialise race car sprite.
            }
        }
    }
}
/**
//------------------------+-----------------------------------------------------//
// CENTER SWITCH FUNCTION:|
//------------------------+
*/
void Center_switch( _Bool min, _Bool max, float speed_lim){
    if (Accelerate_sequence == 0) {         // If boolean false.
        if ( switch_closed[1] != prevState[1] ) { // Switch closed if different.
            prevState[1] = switch_closed[1];// Mark previous state as trigured.
            if (switch_closed[1] == 1) {    // If center switch closed.
                if (Speed == 0) {           // If speed smaller than 0.
                    Speed = 0;              // Set speed equal to zero.
                }                           // Speed set to equal 0.
                else {
                    SET_BIT(PORTB, 2);      // Set LED0 high (Turns on LED0).
                    Decelerate_sequence = 1;// Set boolean too true (one value).
        }}}
        brake = 2.0/ (Speed - 1.1);         // Apply brake for  3 seconds
        if (Decelerate_sequence == 1) {     // If boolean true.
            Speed = Speed - brake;          // Subtract brake from the speed.
            if (Speed <= 0) {               // If speed smaller than 0.
                Speed = 0;                  // Set speed equal to zero.
                Decelerate_sequence = 0;    // Set boolean too false (zero value).
}}}}
/**
//-------------------------------+----------------------------------------------//
// BRAKE OR ACCELERATE FUNCTION: |
//-------------------------------+
*/
void Brake_or_accelerate(float speed_lim){
    if (round(speed_lim) >= 3){             // If greater or equal to three.
        brake = 3.0/ ((speed_lim)*14);      // Apply brake for 3 seconds.
        Accelerating = 3.0/ ((speed_lim)*18); // Accelerate for 3 seconds.
    }
    if (round(speed_lim) >= 10){            // If greater or equal to ten.
        brake = 3.0/ ((speed_lim)*1.6);     // Apply brake for 3 seconds.
        Accelerating = 2.0/ ((speed_lim)*4);// Accelerate for 2 seconds.
    }
}

/**
//-----------------------------+------------------------------------------------//
// NO SWITCH PRESSED FUNCTION: |
//-----------------------------+
*/
void No_switch_pressed( _Bool min, _Bool max, float speed_lim){
    if ((switch_closed[1] == 0) & (switch_closed[3] == 0) & (switch_closed[5] == 0)) {                               // if switch center, down, up closed.
        if ((Decelerate_sequence == 0) & (Accelerate_sequence == 0)) { //
            Brake_or_accelerate(speed_lim); // Calls brake or accel. function.
            if (count >= 20) {              // If count greater/equal too twenty.
                if (Speed > 1) {            // If speed greater than one.
                    if (round(Speed) ==1 ){ // If speed equal to one.
                        Speed = 1;          // Set speed too value of one.
                        count = 0;          // Set count equal too value of zero.
                    }
                    else {Speed  = Speed - brake;} // Decrease speed.
                }
                if ((Speed >= 0) & (Speed <= 1)) { // If between one and zero.
                    Speed = Speed + Accelerating;  // Increase speed.
                    if (Speed < 0) {Speed = 0;}    // If smaller than, set too 0.
                }
            }
            else {
                Speed = Speed;              // Speed value remains the same.
                count = count + 1;          // Increase count in value by one.
}}}}
/**
//------------------------+-----------------------------------------------------//
// ACCELERATION FUNCTION: |
//------------------------+
*/
void Acceleration( _Bool min, _Bool max, float speed_lim){
    if (min & max){                         // Check min and max state.
        if (Speed >= 0 || Speed <= speed_lim) { // If speed within defined limits.
            Down_switch( min, max, speed_lim);  // Calls down switch function.
            Center_switch( min, max, speed_lim);// Calls center switch function.
            Up_switch( min, max, speed_lim);// Calls up switch function.
            No_switch_pressed( min, max, speed_lim); // Calls no switch function.
            if (Speed == 0) {               // If speed smaller than 0.
                Speed = 0;}                 // Speed set to equal 0.
            if (Speed > speed_lim) {        // If speed greater than speed limit.
            //
            // If speed greater than 3 and speed limit greater than the speed
            // limit plus 0.1:
                if ((speed_lim == 3) & (Speed > (speed_lim+1))) {
                    if (Speed == speed_lim){// If speed equal speed limit.
                        Speed = speed_lim;} // Speed equals speed limit.
                    if (Speed > speed_lim){ // If speed greater than speed limit.
                        Speed = Speed - 1;}}// Subtract 0.1 off speed value.
                else{
                    Speed = speed_lim;      // Speed equal to speed limit.
                    CLEAR_BIT(PORTB, 2);}}}}} // Set LED0 low (Turns off LED0).
/**
//------------------------------------+-----------------------------------------//
// SPLASH SCREEN OPPERATION FUNCTION: |
//------------------------------------+
*/
void Splash_screen_opperation( void ) {
    // Checks for change in boolean state of "Game_not_started" if change
    // detected, while loop ends.
    for (int i=6; i<8; i++ ){               // Singling out switch two and three.
        if ( switch_closed[i] != prevState[i] ) { // Switch closed if different.
            prevState[i] = switch_closed[i];// Mark previous state as trigured.
            if (switch_closed[i] == 1) {    // Switch's closed.
                Game_not_started = 1;       // Set boolean  to value of one/true.
                start_time = 1;             // Set boolean  to value of one/true.
                SET_BIT(PORTB, 2);          // Set LED0 high (Turns on LED0).
    }}}
    Display_splash_screen();                // Not pressed, cont. looping.
    CLEAR_BIT(PORTB, 2);                    // Set LED0 low (Turns off LED0).
}
/**
//-------------------------------+----------------------------------------------//
// RACE CARE MOVEMENT FUNCTION:  |
//-------------------------------+
*/
void Race_car_move( void ) {
    // Calls acceleration Function three times. Each of the three designate the
    // max speed for each of the specific regions, left grass/scenery area,
    // center road and right grass/scenery area.
    Acceleration((RC_x >= l_road_edge+1), (RC_x <= (r_road_edge - RC_width)), 10);
    Acceleration((RC_x >= left_c), (RC_x <= (l_road_edge)), 3);
    Acceleration((RC_x >= (r_road_edge - RC_width+1)), (RC_x <= (right_c - RC_width)), 3);
    //
    solve_dist = (solve_dist + Speed);      // Part of distance plus speed.
    if ((solve_dist >= 1) & (Speed > 0)){   // Moves on based on two parameters.
        Distance = Distance + 1;            // Asign value for distance.
    }
}

/**
//-------------------------------+----------------------------------------------//
// TREE MOVEMENT FUNCTION:       |
//-------------------------------+
*/
void Tree_movement(uint8_t i) {
    if (counter1 >= 30){                    // If counter greater/ equal in value.
        sprite_ypos[i] = sprite_ypos[i] + Speed; // Addition of y pos and speed.
    }
    //
    if(sprite_im_identifier[i] == 1) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree1_bitmap);} // Move Tree sprite.
    if(sprite_im_identifier[i] == 2) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree2_bitmap);} // Move Tree sprite.
    if(sprite_im_identifier[i] == 3) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree3_bitmap);} // Move Tree sprite.
    if(sprite_im_identifier[i] == 4) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], T_width, T_height, Tree4_bitmap);} // Move Tree sprite.
}
/**
//-------------------------------+----------------------------------------------//
// HOUSE MOVEMENT FUNCTION:      |
//-------------------------------+
*/
void House_movement(uint8_t i) {
    if (counter2 >= 30){                    // If counter greater/ equal in value.
        sprite_ypos[i] = sprite_ypos[i] + Speed; // Addition of y pos and speed.
    }
    //
    if(sprite_im_identifier[i] == 1) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House2_bitmap);}// Move House sprite.
    if(sprite_im_identifier[i] == 2) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House3_bitmap);}// Move House sprite.
    if(sprite_im_identifier[i] == 3) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House4_bitmap);}// Move House sprite.
    if(sprite_im_identifier[i] == 4) {sprite_init(&scenery[i], sprite_xpos[i], sprite_ypos[i], HL_width, HL_height, House5_bitmap);}// Move House sprite.
}
/**
//-----------------------+------------------------------------------------------//
// COUNTER FUNCTION:     |
//-----------------------+
*/
void Counter(void) {
    if ((counter1 >= 30) & (counter2 >= 30)){ // If counters are greater in value.
        counter1 = 0;                       // Return counter 1 too zero.
        counter2 = 0;                       // Return counter 2 too zero.
    }
    else {
        counter1 = counter1 + Speed;        // Addition of counter 1 and speed.
        counter2 = counter2 + Speed;        // Addition of counter 2 and speed.
    }
}
/**
//----------------------+-------------------------------------------------------//
// MOVING FUNCTION:     |
//----------------------+
*/
void Moving(void) {
    if (Speed > 0){                         // If speed is greater than zero.
        for (uint8_t i = 1; i < 7; i++) {   // Runs for loop six times.
            if (tree_or_house[i] == 0) {    // Zero result for tree sprites.
                if (sprite_ypos[i] > 48) { create_tree_sprite(i); } // call func.
                else {Tree_movement(i);}    // Else tree sprite remains the same.
            }
            if (tree_or_house[i] == 1) {    // Result  of one for house sprites.
                if (sprite_ypos[i] > 48) { create_house_sprite(i); } // call func.
                else {House_movement(i);}   // Else house sprite remains the same.
            }
        }
        Counter();                          // Calls counter function.
    }
}
/**
//-------------------------------+----------------------------------------------//
// SPRITE MOVEMENT FUNCTION:     |
//-------------------------------+
*/
void Sprite_movement(void){
    if (Speed == 0){                        // If speed is equal to zero.
        for (uint8_t i = 1; i < 7; i++) {   // Repeats six times.
            scenery[i] = scenery[i];        // Sprites remain the same.
        }
    }
    Moving();                               // Calls moving function.
}
/**
//----------------------------+-------------------------------------------------//
// DRAW SPRITES FUNCTION:     |
//----------------------------+
*/
void Draw_sprites( void ) {
    Sprite_movement();                      // Calls sprite movement function.
    for (uint8_t i = 1; i < 7; i++) {       // Repeats six times.
        sprite_draw(&scenery[i]);           // Draws each of the six sprites.
    }
    scenery->is_visible = 1;                // Set scenery sprites to visible.
}
/**
//-------------------------------+----------------------------------------------//
// CONCEAL DASHBOARD FUNCTION:   |
//-------------------------------+
*/
void Conceal_dashboard( void ) {
    // Used for hiding the sprites from appearing in the dashboard, as they scroll
    // down from the top of the screen.
    for (uint8_t i = 0; i < 10; i++) {      // Repeats nine times.
        draw_line(0, i, 84, i, BG_COLOUR);  // Draws nine invisible lines.
    }
}
/**
//------------------------+-----------------------------------------------------//
// COLLIDED FUNCTION:     |
//------------------------+
*/
// Description of function: Call function in function, imputing the name of
// the two sprites you intend to test for collision.
_Bool collided_sprites( uint8_t i ){
    uint8_t tRC = RC_y;                     // Racing car top coordinate.
    uint8_t lRC = RC_x;                     // Racing car left coordinate.
    uint8_t rRC = (lRC + RC_width - 1);     // Racing car right coordinate.
    uint8_t bRC = (tRC + RC_height - 1);    // Racing car bottom coordinate.
    uint8_t tS = sprite_ypos[i];            // Sprite top coordinate.
    uint8_t lS = sprite_xpos[i];            // Sprite left coordinate.
    uint8_t rS;                             // L global sprite right coordinate.
    uint8_t bS;                             // L global sprite bottom coordinate.
    if (tree_or_house[i] == 0) {            // If false, use tree characteristics.
        rS = (lS + T_width - 1);            // Sets sprite right coordinate.
        bS = (tS + T_height - 1);           // Sets sprite bottom coordinate.
    }
    if (tree_or_house[i] == 1) {            // If true, use house characteristics.
        rS = (lS + HL_width - 1);           // Sets sprite right coordinate.
        bS = (tS + HL_height - 1);          // Sets sprite bottom coordinate.
    }
    if (tS > bRC) return 0;                 // If greater value, return false.
    if (tRC > bS) return 0;                 // If greater value, return false.
    if (lRC > rS) return 0;                 // If greater value, return false.
    if (lS > rRC) return 0;                 // If greater value, return false.
    else return 1;                          // All else, return true.
}
/**
//------------------------+-----------------------------------------------------//
// COLLIDED FUNCTION:     |
//------------------------+
*/
// Description of function: Call function in function, imputing the name of
// the two sprites you intend to test for collision.
_Bool collided_fuel_depot( void ){
    uint8_t tRC = RC_y;                     // Racing car top coordinate.
    uint8_t lRC = RC_x;                     // Racing car left coordinate.
    uint8_t rRC = (lRC + RC_width - 1);     // Racing car right coordinate.
    uint8_t bRC = (tRC + RC_height - 1);    // Racing car bottom coordinate.
    //
    uint8_t tFD = FD_y;                     // Fuel depot top coordinate.
    uint8_t lFD = FD_x;                     // Fuel depot left coordinate.
    uint8_t rFD = (lFD + FD_width - 1);     // Fuel depot right coordinate.
    uint8_t bFD = (tFD + FD_height - 1);    // Fuel depot bottom coordinate.
//
    if (tFD > bRC) return 0;                // If greater value, return false.
    if (tRC > bFD) return 0;                // If greater value, return false.
    if (lRC > rFD) return 0;                // If greater value, return false.
    if (lFD > rRC) return 0;                // If greater value, return false.
    else return 1;                          // All else, return true.
}
/**
//--------------------+---------------------------------------------------------//
// TEST SPRITES:      |
//--------------------+
*/
void Test_sprites(void){
    for (uint8_t i=1; i<7; i++){            // For loop itterates 6 times.
        if  (collided_sprites( i ) == 1){   // Collided with sprite/s true.
            Condition = Condition - 20;     // Reduces car condition by 20.
            Speed = 0;
            RC_x = round((right_c/2) - (RC_width/2)); //
        }
    }
    if  (collided_fuel_depot() == 1){       // Collided with fuel depot true.
        Condition = Condition - Condition;  // Collission with FD results in zero.
    }
    //
    // INITIALISE RACE CAR SPRITE:
    sprite_init(&Race_car, RC_x, RC_y, RC_width, RC_height, car_bitmap);
}
/**
//-------------------------------+----------------------------------------------//
// RACE CAR OPPERATION FUNCTION: |
//-------------------------------+
*/
void Race_car_opperation( void ) {
    Time_function();                    // Calls time function.
    Fuel_levels();                      // Calls Fuel levels function.
    if (Speed > 0){                     // If speed is greater than 0.
        Left_switch();                  // Calls left switch function.
        Right_switch();                 // Calls right switch function.
    }
    Draw_sprites();                     // Calls draw sprites function.
    Process_pump ();                    // Calls process pump function.
    sprite_draw(&Fuel_depot);           // Draw sprite  for fuel depot.
    Refueling_process();                // Calls refueling process function.
    Test_sprites();                     // Calls test sprites function.
    Conceal_dashboard();                // Calls conceal dashboard function.
    Race_car_move();                    // Calls race car move function.
    draw_Road();                        // Calls draw road function.
    Dashboard();                        // Calls dashboard function.
    sprite_draw(&Race_car);             // Draw race car sprite.
    CLEAR_BIT(PORTB, 2);                // Set LED0 low (Turns off LED0).
}
/**
//---------------------------------------+--------------------------------------//
// GAME OVER SCREEN OPPERATION FUNCTION: |
//---------------------------------------+
*/
void Game_over_screen_opperation( void ) {
    if (Condition <= 0 || Fuel <= 0 ){  // Conditions for player losing.
        game_over = 1;                  // Terminates and ends game.
        win = 0;                        // Boolean set to false, means lost game.
    }
    if (minute >= 4 || Distance >= 2400 ){ // Conditions for player winning.
        game_over = 1;                  // Terminates and ends game.
        win = 1;                        // Boolean set to true, means won game.
    }
}
/**
//------------------------------------+-----------------------------------------//
// DISPLAY GAME OVER SCREEN FUNCTION: |
//------------------------------------+
*/
void Game_over_screen( void ) {
    if ( win == 1) {                    // If true creates player wins screen.
        draw_string(14, 0, "PLAYER WINS", FG_COLOUR); // Draw string player wins.
    }
    if ( win == 0) {                    // If false creates player lost screen.
        draw_string(14, 0, "PLAYER LOST", FG_COLOUR); // Draw string player lost.
    }
    draw_line(0, 8, 84, 8, FG_COLOUR);  // Draw section line.
    // TIME:
    draw_string(0, 10, "Time =", FG_COLOUR);  // Draw string time.
    draw_double(36, 10, time_sec, FG_COLOUR); // Draw previous round total time.
    // DISTANCE:
    draw_string(0, 19, "Dist =", FG_COLOUR);  // Draw string 'dist' for distance.
    draw_int(36, 19, Distance, FG_COLOUR);    // Draw result for total distance.
    
    draw_line(0, 27, 84, 27, FG_COLOUR);// Draw section line.
    //
    draw_string(14, 29, "PLAY AGAIN?", FG_COLOUR); // Draw string, play again.
    draw_string(4, 37, "Y: SW2 | N: SW3", FG_COLOUR); // Draw string for yes or no
}
/**
//---------------------------------------+--------------------------------------//
// GAME OVER SCREEN OPPERATION FUNCTION: |
//---------------------------------------+
*/
void GO( void ) {
    for (uint8_t i=6; i<8; i++ ){       // singling out switch two and three.
        if ( switch_closed[i] != prevState[i] ) { // switch closed if different.
            prevState[i] = switch_closed[i]; // mark previous state as trigured.
            if (switch_closed[7] == 1) {// Switch three closed.
                GO_Operation = 1;       // Sets bool state to true.
                exit_game = 1;          // Changes bool state.
                SET_BIT(PORTB, 2);      // Set LED0 high (Turns on LED0).
            }
        }
            if (switch_closed[6] == 1) {// Switch two closed.
                GO_Operation = 1;       // Sets bool state to true.
                SET_BIT(PORTB, 2);      // Set LED0 high (Turns on LED0).
            }
        else {
            Game_over_screen();         // Not pressed, cont. looping.
        }
    }
    CLEAR_BIT(PORTB, 2);                // Set LED0 low (Turns off LED0).
 }
/**
//------------------------+-----------------------------------------------------//
// NOT STARTED SEQUENCE:  |
//------------------------+
*/
void Not_started_sequence(void) {
    while ( Game_not_started == 0) {    // While state not changed.
        clear_screen();                 // Clear screen.
        Splash_screen_opperation();     // Call SS opperation function.
        show_screen();                  // show screen.
    }
}
/**
//------------------------+-----------------------------------------------------//
// GAME OVER SEQUENCE:    |
//------------------------+
*/
void Game_over_sequence(void) {
    while (game_over == 0) {            // While game not over, continue.
        clear_screen();                 // Clear screen.
        Race_car_opperation();          // Calls race car opperation function.
        Game_over_screen_opperation();  // Calls game over screen opp. function.
        show_screen();                  // Show screen.
    }
}
/**
//------------------------+-----------------------------------------------------//
// PLAYER REVIEW SEQUENCE:|
//------------------------+
*/
void Player_review_sequence(void) {
    while ( GO_Operation == 0 ) {       // While state not changed.
        clear_screen();                 // Clear screen.
        GO();                           // Calls GO function.
        show_screen();                  // Show screen.
    }
}
/**
//-------------------------+----------------------------------------------------//
// TERMINATE GAME SEQUENCE:|
//-------------------------+
*/
void Terminate_game_sequence(void) {
    clear_screen();                     // Clear screen.
    show_screen();                      // Show screen
    Game_not_started = 0;               // Set boolran game not started to zero.
    game_over = 0;                      // Set boolran game over to zero.
    GO_Operation = 0;                   // Set boolran GO opperation to zero.
}
/**
//-------------------------+----------------------------------------------------//
// EXIT LOOP SEQUENCE:     |
//-------------------------+
*/
void Exit_loop_sequence(void) {
    while (!exit_game){                 //
        SS_constant_values();           // Run once SS constant function.
        Game_constant_values();         // Run once game constant function.
        Sprite_constant_values();       // Run once sprite constant function.
        Setup_pump ();                  // Run once setup pump function.
        //
        Not_started_sequence();         // Calls not started sequence function.
        Game_over_sequence();           // Calls game over sequence function.
        Player_review_sequence();       // Calls player review sequence function.
        Terminate_game_sequence();      // Calls terminate game sequence function.
    }
}
/**
//-------------------------+----------------------------------------------------//
// CLEANUP SEQUENCE:       |
//-------------------------+
*/
void Cleanup_sequence(void) {
    CLEAR_BIT(PORTB, 2);                // Set LED0 low (Turns off LED0).
    clear_screen();                     // Clear screen.
    draw_string(19.5, 1, "GAME OVER", FG_COLOUR); // Draw game over string.
    show_screen();                      // Show screen.
    _delay_ms(3000);                    // Dellay by 3000 millisecinds.
    clear_screen();                     // Clear screen.
    show_screen();                      // Show screen.
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/

int main( void ) {
    setup_teensy();                     // Calls setup teensey function.
    ISR_constants();                    // Calls ISR constants function.
    //
    Exit_loop_sequence();               // Calls exit loop sequence function.
    //
    Cleanup_sequence();                 // Calls cleanup sequence function.
    // exit(0); //terminates program
}
/**
//==============================================================================//
*/
