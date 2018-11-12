/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
*/
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/Assignments/Assignment_1/Code
//
//  COMPILE:
//  gcc a1_n8548625.c -o a1_n8548625 -Wall -Werror -g -I ../../../ZDK -L ../../../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./a1_n8548625
/**
//------------------------------------------------------------------------------//
//
//==============================================================================//
//------------------------------------------------------------------------------//
// C SECIFIC CODE:
//------------------------------------------------------------------------------//
//--------------------+---------------------------------------------------------//
// DEFINE DIRECTORIES:|
//--------------------+
*/
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
/**
//--------------------+---------------------------------------------------------//
// DEFINE DELAYS:     |
//--------------------+
*/
#define DELAY1 100/* milliseconds */
#define DELAY2 10/* milliseconds */
/**
//--------------------+---------------------------------------------------------//
// DEFINE BOOLEANS:   |
//--------------------+
*/
bool Game_not_started;              // Boolean state for when game not started.
bool init_t;                        // Boolean used when initialising time.
bool game_over;                     // Boolean for termination, when game ends.
bool perform_check;                 // Boolean used to check number of sprites.
bool GO_Operation;                  // Boolean used for exiting game over screen.
bool exit_game;                     // Boolean used in the repeat or exit of game.
bool initial_sprite_pos = false;    // Boolean used for Initial sprite positions.
bool win = false;                   // Boolean for win state.
/**
//--------------------------------+---------------------------------------------//
// INITIALISE IMPORTANT FUNCTIONS:|
//--------------------------------+
*/
void SS_constant_values(void);
void Game_constant_values(void);
void Sprite_constant_values(void);
void Iterate_1( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 );
void Iterate_2( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 );
void Iterate( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 );
void Display_splash_screen(void);
void Game_over_screen( void );
void Display_Race_Car(void);
void Splash_screen_opperation(void);
void GO( void );
void Game_over_screen_opperation( void );
void Race_car_opperation(void);
void Time_function(void);
void Dashboard(void);
void draw_border(void);
void draw_Road(void);
void Acceleration( bool min, bool max, double speed_lim);
sprite_id Scenery_Position( int count, int index, int sp_w, int sp_h, int sp_im);
void Draw_Scenery( int sprite_no );
bool collided ( sprite_id sprite1, sprite_id sprite2 );
void Test_sprites(void);
void Fuel_levels(void);
/**
//--------------------+---------------------------------------------------------//
// DEFINE GLOBALS:    |
//--------------------+
*/
// Sprite Screen Globals:
int left_c;                                 // Create global left coordinate.
int top_c;                                  // Create global top coordinate.
int right_c;                                // Create global right coordinate.
int bottom_c;                               // Create global bottom coordinate.
//
int itteration_val;                         // Create global for itteration value.
int key;                                    // Create global for key pressed.
//
// Main Game Globals:
// Boarder:
int l_bo;                                   // Create global left boarder.
int t_bo;                                   // Create global top boarder.
int r_bo;                                   // Create global right boarder.
int b_bo;                                   // Create global bottom boarder.
//
int Dashboard_offset;                       // Create global for Dashboard offset.
double Initial_time;                        // Create global to hold initial time.
double current_time;                        // Create global to hold current time.
double Time;                                // Create global to hold in game time.
int Minute;                                 // Create global for no. of minutes.
int Condition;                              // Create global for condition of car.
double Speed;                               // Create global for speed of car.
double Fuel;                                // Create global for fuel remaining.
double Distance;                            // Create global for total distance.
int pit_stop;                               // Create global for pit stop marker.
//
int splits;                                 // Create global for splits.
int split_center;                           // Create global for splits center.
int split_1;                                // Create global for split 1.
int split_2;                                // Create global for split 2.
int split_3;                                // Create global for split 3.
int split_4;                                // Create global for split 4.
int split_5;                                // Create global for split 5.
//
// Road:
int l_road_edge;                            // Create global for left road edge.
int r_road_edge;                            // Create global for right road edge.
//
// Main Game Sprite Globals:
int RC_w; int RC_h; int RC_x; int RC_y;     //  - Race Car.
int F_w; int F_h; int F_x; int F_y;         //  - Fuel Station.
int Z_w; int Z_h;                           //  - Zombie.
int T_w; int T_h;                           //  - Tree.
int S_w; int S_h;                           //  - Sign.
int H_w; int H_h;                           //  - House.
int M_w1; int M_h1;                         //  - Mountain 1.
int M_w2; int M_h2;                         //  - Mountain 2.aaaa
//
// Scenery Position:
int sprite_count;                           // Create global for sprite count.
int sprite_index;                           // Create global for sprite index.
int sprite_w[6];                            // Create global array sprite width.
int sprite_h[6];                            // Create global array sprite height.
char * sprite_im[6];                        // Create global array sprite image.
/**
//---------------------+--------------------------------------------------------//
// INITIALISE SPRITES: |
//---------------------+
*/
sprite_id splash_screen;                    // Initialise sprite splash screen.
sprite_id Race_car;                         // Initialise sprite race car.
sprite_id Fuel_station;                     // Initialise sprite fuel station.
sprite_id scenery[7];                       // Initialise sprite array scenery.
sprite_id GO_screen;                        // Initialise sprite game over screen.
/**
//----------------------+-------------------------------------------------------//
// DEFINE SPRITE IMAGES:|
//----------------------+
*/
// Splash Screen - Sprite:
char * SS_image_1 =
"+--------------------------------------------------------------------------+"
"| ____    __    ___  ____                 +------------------------------+ |"
"|(  _ \\  /__\\  / __)( ___) ___            |by Mathew Hutchison (n8548625)| |"
"| )   / /(__)\\( (__  )__)    / /          +------------------------------+ |"
"|(_)\\_)(__)(__)\\___)(____)  / /     ___      _   __     / __     ( )  ___  |"
"|               +-+-+      / /    //   ) ) // ) )  ) ) //   ) ) / / //___) |"
"|               |t|o|     / /    //   / / // / /  / / //   / / / / //      |"
"|/|    //| |    +-+-+    / /___ ((___/ / // / /  / / ((___/ / / / ((____   |"
"|//|   // | |     ___                __    __  ___  ___     ( )   __       |"
"|// |  //  | |   //   ) ) //   / / //   ) )  / /   //   ) ) / / //   ) )   |"
"|//  | //   | |  //   / / //   / / //   / /  / /   //   / / / / //   / /   |"
"|//   |//    | | ((___/ / ((___( ( //   / /  / /   ((___( ( / / //   / /   |"
"+---------------------+--------------+---------------------+---------------+"
"|     INSTRUCTION:    |     KEY:     |     INSTRUCTION:    |     KEY:      |"
"+---------------------+--------------+---------------------+---------------+"
"|    Move Left (<-)   |   Press 'a'  |    Move Right (->)  |   Press 'd'   |"
"|    Move UP (^)      |   Press 'w'  |    Move Down (v)    |   Press 's'   |"
"+---------------------+--------------+---------------------+---------------+"
"|.-..-..--.-..-.    .  . .. .  . ..--. .  ---.-.   .-.-.. .----.-. .. ..-- |"
"||-'|-'|- `-.`-.   /_\\ |\\| Y   |< |-  Y    | | |  (  | ||\\| |  | |\\|| ||- o|"
"|'  '`-'--`-'`-'  '   '' ' '   ' `'-- '    ' `-'   `-`-'' ' ' -'-' '`-''--o|"
"+--------------------------------------------------------------------------+";
//
char * SS_image_2 =
"+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+"
"* ____    __    ___  ____                 +------------------------------+ |"
"|(  _ \\  /__\\  / __)( ___) ___            |by Mathew Hutchison (n8548625)| *"
"* )   / /(__)\\( (__  )__)    / /          +------------------------------+ |"
"|(_)\\_)(__)(__)\\___)(____)  / /     ___      _   __     / __     ( )  ___  *"
"*                          / /    //   ) ) // ) )  ) ) //   ) ) / / //___) |"
"|                         / /    //   / / // / /  / / //   / / / / //      *"
"*/|    //| |             / /___ ((___/ / // / /  / / ((___/ / / / ((____   |"
"|//|   // | |     ___                __    __  ___  ___     ( )   __       *"
"*// |  //  | |   //   ) ) //   / / //   ) )  / /   //   ) ) / / //   ) )   |"
"|//  | //   | |  //   / / //   / / //   / /  / /   //   / / / / //   / /   *"
"*//   |//    | | ((___/ / ((___( ( //   / /  / /   ((___( ( / / //   / /   |"
"+---------------------+--------------+---------------------+---------------+"
"*     INSTRUCTION:    |     KEY:     |     INSTRUCTION:    |     KEY:      |"
"+---------------------+--------------+---------------------+---------------+"
"*    Move Left (<-)   |   Press 'a'  |    Move Right (->)  |   Press 'd'   |"
"|    Move UP (^)      |   Press 'w'  |    Move Down (v)    |   Press 's'   *"
"+---------------------+--------------+---------------------+---------------+"
"|                                                                          *"
"*                                                                          |"
"|                                                                          *"
"+*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-+";
//
//Racing Car - Sprite:
char * Stationary_img =
"|#|/T\\|#|"
"|#| + |#|"
"|#|\\_/|#|"
"  _| |_  "
" /_____\\ "
"|\\_____/|"
"|#|\\_/|#|"
"|#| ! |#|";
//
char * move_1_img =
"|*|/T\\|*|"
"|#| + |#|"
"|*|\\_/|*|"
"  _| |_  "
" /_____\\ "
"|\\_____/|"
"|*|\\_/|*|"
"|#| ! |#|";
//
char * move_2_img =
"|#|/T\\|#|"
"|*| + |*|"
"|#|\\_/|#|"
"  _| |_  "
" /_____\\ "
"|\\_____/|"
"|#|\\_/|#|"
"|*| ! |*|";
//
// Zombie - sprite:
char * Zombie_1_img =
" >X< "
"(o o)"
" (_) ";
//
char * Zombie_2_img =
" <X> "
"(o o)"
" (o) ";
//
// Tree - sprite:
char * Tree_img =
" (\\-v-/) "
"(_\\\\o//_)"
"  (/|\\)  ";
//
// Sign - sprite:
char * Sign_img =
" ____ "
"|STOP|"
"|____|";
//
// House - sprite:
char * House_img =
"     @     "
"  __/_\\__  "
" /_\\/_\\/_\\ "
"| +  _  + |"
"|   | |   |"
"|___| |___|";
//
// Mountain - sprite:
char * Mountain_1_img =
"      /\\  "
"  /\\ /\\ \\ "
"/\\  v  \\ \\";
//
char * Mountain_2_img =
"   /\\         "
"  /\\ /\\       "
" /  v  \\   /\\ "
"/       \\_/  \\";
//
// Fuel Station - sprite:
char * Fuel_Station_img =
"|>>>>>>>>>|   |>>| "
"|         |  (|==|)"
"|    F    |   |  | "
"|    U    |  (|==|)"
"|    E    |  (|==|)"
"|    L    |   |  | "
"|         |  (|==|)"
"|>>>>>>>>>|   |>>| ";

//
// Game over - sprite:
char * Win_img =
"+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+"
"+                 ______                                                   +"
"+                /      \\                                                  +"
"+               |  $$$$$$\\  ______   ______ ____    ______                 +"
"+               | $$ __\\$$ |      \\ |      \\    \\  /      \\                +"
"+               | $$|    \\  \\$$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\               +"
"+               | $$ \\$$$$ /      $$| $$ | $$ | $$| $$    $$               +"
"+               | $$__| $$|  $$$$$$$| $$ | $$ | $$| $$$$$$$$               +"
"+               \\$$    $$ \\$$    $$| $$ | $$ | $$ \\$$     \\                +"
"+                \\$$$$$$   \\$$$$$$$ \\$$  \\$$  \\$$  \\$$$$$$$                +"
"+                          .-----.--.--.-----.----.                        +"
"+                          |  _  |  |  |  -__|   _|                        +"
"+                          |_____|\\___/|_____|__|                          +"
"+--------------------+--------------------------------+--------------------+"
"+    ELAPSED TIME:   |       __      ___ _ __         | DISTANCE TRAVELED: +"
"+--------------------+       \\ \\ /\\ / / | '_ \\        +--------------------+"
"+                    |        \\ V  V /| | | | |       |                    +"
"+                    |         \\_/\\_/ |_|_| |_|       |                    +"
"+--------------------+--------------------------------+--------------------+"
"+                       Press 'q' to quit the game                         +"
"+                      Press 'r' to restart the game                       +"
"+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+";

char * Lose_img =
"+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+"
"+                 ______                                                   +"
"+                /      \\                                                  +"
"+               |  $$$$$$\\  ______   ______ ____    ______                 +"
"+               | $$ __\\$$ |      \\ |      \\    \\  /      \\                +"
"+               | $$|    \\  \\$$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\               +"
"+               | $$ \\$$$$ /      $$| $$ | $$ | $$| $$    $$               +"
"+               | $$__| $$|  $$$$$$$| $$ | $$ | $$| $$$$$$$$               +"
"+               \\$$    $$ \\$$    $$| $$ | $$ | $$ \\$$     \\                +"
"+                \\$$$$$$   \\$$$$$$$ \\$$  \\$$  \\$$  \\$$$$$$$                +"
"+                          .-----.--.--.-----.----.                        +"
"+                          |  _  |  |  |  -__|   _|                        +"
"+                          |_____|\\___/|_____|__|                          +"
"+--------------------+--------------------------------+--------------------+"
"+    ELAPSED TIME:   |       | | ___  ___  ___        | DISTANCE TRAVELED: +"
"+--------------------+       | |/ _ \\/ __|/ _ \\       +--------------------+"
"+                    |       | | (_) \\__ \\  __/       |                    +"
"+                    |       |_|\\___/|___/\\___|       |                    +"
"+--------------------+--------------------------------+--------------------+"
"+                       Press 'q' to quit the game                         +"
"+                      Press 'r' to restart the game                       +"
"+-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*+";
/**
//--------------------------------+---------------------------------------------//
// SPLASH SCREEN CONSTANT VALUES: |
//--------------------------------+
*/
void SS_constant_values( void ) {
    left_c = 0;                                 // Set global left coordinate.
    top_c = 0;                                  // Set global top coordinate.
    right_c = (screen_width());                 // Set global right coordinate.
    bottom_c = (screen_height());               // Set global bottom coordinate.
    //
    itteration_val = 0;                         // Initial itteration value = 0.
    key = 0;                                    // Key value initially equals 0.
    //
    initial_sprite_pos = false;
    win = false;
}
/**
//------------------------+-----------------------------------------------------//
// GAME CONSTANT VALUES:  |
//------------------------+
*/
void Game_constant_values( void ) {
    Dashboard_offset = 1;                       // Initialise offset equals one.
    Time = 0;                                   // Initialise time equals zero.
    Minute = 0;                                 // Initialise minutes equals zero.
    Condition = 100;                            // Condition of race car.
    Speed = 0;                                  // Current speed of the race car.
    Fuel = 100;                                 // Amount of fuel remaining.
    Distance = 0;                               // Distance traveled in game.
    pit_stop = 2;                               // Initialise pit stop first value.
    //
    splits = round(right_c/5);                  // Defines width of splits.
    split_center = splits/5;                    // Finds center point of splits.
    split_1 = split_center;                     // set split 1 x coordinate.
    split_2 = splits + split_center;            // set split 2 x coordinate.
    split_3 = (splits*2) + split_center;        // set split 3 x coordinate.
    split_4 = (splits*3) + split_center;        // set split 4 x coordinate.
    split_5 = (splits*4) + split_center;        // set split 5 x coordinate.
}
/**
//------------------------+-----------------------------------------------------//
// SPRITE CONSTANT VALUES:|
//------------------------+
*/
void Sprite_constant_values( void ) {
    // Define sprite width and height constants:
    RC_w = 9; RC_h = 8;                         //  - Race Car.
    F_w = 17; F_h = 8;                          //  - Fuel Station.
    Z_w = 5; Z_h = 3;                           //  - Zombie.
    T_w = 9; T_h = 3;                           //  - Tree.
    S_w = 6; S_h = 3;                           //  - Sign.
    H_w = 11; H_h = 6;                          //  - House.
    M_w1 = 10; M_h1 = 3;                        //  - Mountain 1.
    M_w2 = 14; M_h2 = 4;                        //  - Mountain 2.
    //
    RC_x = round((right_c/2) - (RC_w/2))-1;     // Define race car initial x pos.
    RC_y = bottom_c - (RC_h+1);                 // Define race car initial y pos.
    //
    sprite_count = 0;                           // Set initial sprite count to 0.
    sprite_index = 0;                           // Set initial sprite index to 0.
    // Define values for sprite width, height and image, based on the sprite
    // scenery options:
    sprite_w[1] = T_w; sprite_w[2] = S_w; sprite_w[3] = H_w; sprite_w[4] = M_w1; sprite_w[5] = M_w2;
    sprite_h[1] = T_h; sprite_h[2] = S_h; sprite_h[3] = H_h; sprite_h[4] = M_h1; sprite_h[5] = M_h2;
    sprite_im[1] = Tree_img; sprite_im[2] = Sign_img; sprite_im[3] = House_img; sprite_im[4] = Mountain_1_img; sprite_im[5] = Mountain_2_img;
}
/**
//---------------------+--------------------------------------------------------//
// TIME FUNCTION:      |
//---------------------+
*/
void Time_function( void ) {
    // if time exceeds or equal to the value of 60, boolean init_t set to false
    // and minute count increased by one. this only occurs once every 60 seconds.
    if (Time >= 60){
        init_t = false;                          // Set boolean to false.
        Minute = Minute + 1;                     // Minute count increased by one.
    }
    // Saves initial time as constant, keeping this value as a refference to
    // compare with the time value, determining the second count thats passed.
    if (!init_t){
        Initial_time = get_current_time();      // Saves initial time as constant.
        init_t = true;                          // Set boolean back to true.
    }
    //
    current_time = get_current_time();          // Used in solving for game time.
    Time = round((current_time - Initial_time)*100)/100; // Finds second count.
}
/**
 //------------------------+-----------------------------------------------------//
 // ITERATION FUNCTION 1:  |
 //------------------------+
 */
void Iterate_1( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 ) {
    clear_screen();                             // Clears screen.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        for (int i=1; i<7; i++){                // For loop for scenery creation.
            Draw_Scenery(i);                    // Runs draw scenery Function.
        }
    }
    sprite = sprite_create( x, y, width, height, img1 );    // Creates sprite.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        draw_Road();                            // Runs draw road function.
    }
    sprite_draw(sprite);                        // Draw sprites.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        Dashboard();                            // Runs dashboard function.
        draw_border();                          // Runs draw boarder function.
    }
    show_screen();                              // reveals on screen.
    timer_pause(Delay);                         // timer pause.
    itteration_val = 1;                         // Set itteration value to 1.
}
/**
 //------------------------+-----------------------------------------------------//
 // ITERATION FUNCTION 2:  |
 //------------------------+
 */
void Iterate_2( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 ) {
    clear_screen();                             // Clears screen.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        for (int i=1; i<7; i++){                // For loop for scenery creation.
            Draw_Scenery(i);                    // Runs draw scenery Function.
        }
    }
    sprite = sprite_create( x, y, width, height, img2 );    // Creates sprite.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        draw_Road();                            // Runs draw road function.
    }
    sprite_draw(sprite);                        // Draw sprites.
    if (Dash_Board == 1){                       // Checks value of Dashboard.
        Dashboard();                            // Runs dashboard function.
        draw_border();                          // Runs draw boarder function.
    }
    show_screen();                              // reveals on screen.
    timer_pause(Delay);                         // timer pause.
    itteration_val = 0;                         // Set itteration value to 0.
}
/**
//------------------------+-----------------------------------------------------//
// ITERATION FUNCTION:    |
//------------------------+
*/
void Iterate( int Delay, int Dash_Board, sprite_id sprite, int x, int y, int width, int height, char * img1, char * img2 ) {
    //
    // Calls itteration 1 function if "itteration_val" set equal to 0.
    if (itteration_val == 0){
        Iterate_1( Delay, Dash_Board, sprite, x, y, width, height, img1, img2 );
    }
    //
    // Calls itteration 1 function if "itteration_val" set equal to 1.
    if (itteration_val == 1){
        Iterate_2( Delay, Dash_Board, sprite, x, y, width, height, img1, img2 );
    }
}
/**
//---------------------------------+--------------------------------------------//
// DISPLAY SPLASH SCREEN FUNCTION: |
//---------------------------------+
*/
void Display_splash_screen( void ) {
    //
    int SS_w = 76;                              // Define splash screen width.
    int SS_h = 22;                              // Define splash screen height.
    int SS_x = ((right_c - SS_w) / 2);          // Set splash screen x position.
    int SS_y = ((bottom_c - SS_h) / 2);         // Set splash screen y position.
    //
    // Call itterate function, where the splash screen will switch between two
    // images, creating an animated illusion.
    Iterate(DELAY1, 0, splash_screen, SS_x, SS_y, SS_w, SS_h, SS_image_1, SS_image_2 );
}
/**
 //------------------------------------+-----------------------------------------//
 // DISPLAY GAME OVER SCREEN FUNCTION: |
 //------------------------------------+
 */
void Game_over_screen( void ) {
    //
    int GO_w = 76;                              // Define game over screen width.
    int GO_h = 22;                              // Define game over screen height.
    int GO_x = ((right_c - GO_w) / 2);          // Set game over screen x position.
    int GO_y = ((bottom_c - GO_h) / 2);         // Set game over screen y position.
    //
    // If false creates game lost game over screen.
    clear_screen();
    if ( win == false) {
        GO_screen = sprite_create( GO_x, GO_y, GO_w, GO_h, Lose_img );
    }
    // If false creates game won game over screen.
    if ( win == true) {
        GO_screen = sprite_create( GO_x, GO_y, GO_w, GO_h, Win_img );
    }
    sprite_draw(GO_screen);              // Draws selected game over screen.
    draw_double((GO_x+7), (GO_y+17), Minute);   // Double for minute value.
    draw_string((GO_x+9), (GO_y+17), ":");      // Draws string for colon.
    draw_double((GO_x+10), (GO_y+17), Time);     // Double for second value.
    draw_double((GO_x+61), (GO_y+17), Distance); // Double for Distance value.
    show_screen();
}
/**
//---------------------------------+--------------------------------------------//
// DISPLAY RACE CAR FUNCTION:      |
//---------------------------------+
*/
void Display_Race_Car( void ) {
    //
    if (Speed <= 0){                            // If speed equal or less to 0.
        clear_screen();                         // Clears screen.
        if (sprite_index < 6){                  // If smaller than the value of 6.
            for (int i=1; i<7; i++){            // For loop itterates 6 times.
                sprite_index = sprite_index + 1;// Increase sprite_index by 1.
                Draw_Scenery(i);}}              // Iterativly create new scenery.
        if (sprite_index == 6){                 // If equal to the value of 6.
            for (int i=1; i<7; i++){            // for loop itterates 6 times.
                Draw_Scenery(i);}}              // Iterativly Draw scenery sprites.
        // Create race car sprite.
        Race_car = sprite_create( RC_x, RC_y, RC_w, RC_h, Stationary_img );
        draw_Road();                            // Calls draw road function.
        sprite_draw(Race_car);                  // Draws Race car sprite.
        Dashboard();                            // Calls dashboard function.
        draw_border();                          // Calls draw boarder function.
        show_screen();                          // Show to screen.
        timer_pause(DELAY2);}                   // pause timer based on delay 2.
    //
    if(Speed > 0){                              // if speed greater than 0.
        // Calls itterate function (this is where the basic sprite animation
        // comes from):
        Iterate(DELAY2,1, Race_car, RC_x, RC_y, RC_w, RC_h, move_1_img, move_2_img );}}
/**
//------------------------------------+-----------------------------------------//
// SPLASH SCREEN OPPERATION FUNCTION: |
//------------------------------------+
*/
void Splash_screen_opperation( void ) {
    // Checks for change in boolean state of "Game_not_started" if change
    // detected, while loop ends.
    while ( !Game_not_started ) {               // While state not changed.
        //
        timer_pause(DELAY1);                    // Pause timer with delay 1.
        key = get_char();                       // Check for any key press.
        if (key >= 0){                          // Checks key value.
            Game_not_started = true;            // Sets bool state to true.
            clear_screen();                     // clear screen.
        }
        else {
            Display_splash_screen();            // Not pressed, cont. looping.
        }
    }
}
/**
 //---------------------------------------+--------------------------------------//
 // GAME OVER SCREEN OPPERATION FUNCTION: |
 //---------------------------------------+
 */void GO( void ) {
    timer_pause(DELAY1);                    // Pause timer with delay 1.
    key = get_char();                       // Check for any key press.
    if (key == 'q'){                        // If key equal to 'q'.
        GO_Operation = !GO_Operation;       // Sets bool state to true.
        exit_game = true;             // Changes bool state.
        clear_screen();}                    // Clears screen.
    if (key == 'r'){                        // Checks key value.
        GO_Operation = true;       // Sets bool state to true.
        clear_screen();                     // clear screen.
        
    }
    else {
        Game_over_screen();                 // Not pressed, cont. looping.
    }
 }
/**
 //---------------------------------------+--------------------------------------//
 // GAME OVER SCREEN OPPERATION FUNCTION: |
 //---------------------------------------+
 */
void Game_over_screen_opperation( void ) {
    if (Condition <= 0 || Fuel <= 0 ){
        game_over = !game_over;                   // Terminates and ends game.
        win = false;
    }
    if (Minute >= 4 || Distance >= 15 ){
        game_over = !game_over;                   // Terminates and ends game.
        win = true;
    }
}
/**
//-------------------------------+----------------------------------------------//
// RACE CAR OPPERATION FUNCTION: |
//-------------------------------+
*/
void Race_car_opperation( void ) {
    Display_Race_Car();                         // Run display race car func.
    //
    key = get_char();                           // key equals character pressed.
    if (Speed > 0){                             // If speed is greater than 0.
        if (key == 'a'){                        // If key equal to 'a'.
            if (RC_x > l_bo+1){                 // Is RC x greater left boarder.
                RC_x = RC_x-1;}}                // Minus one off RC x value.
        if (key == 'd'){                        // If key equal to 'd'.
            if (RC_x < (r_bo - (RC_w))){        // Is RC greater right boarder.
                RC_x = RC_x + 1;}}}             // Plus one off RC x value.
    //
    // Calls acceleration Function three times. Each of the three designate the max
    // speed for each of the specific regions, left grass/scenery area, center
    // road and right grass/scenery area.
    Acceleration((RC_x >= l_road_edge+1), (RC_x <= (r_road_edge - RC_w)), 10.0);
    Acceleration((RC_x >= l_bo), (RC_x <= (l_road_edge)), 3.0);
    Acceleration((RC_x >= (r_road_edge - RC_w+1)), (RC_x <= (r_bo - RC_w)), 3.0);
    //
    Distance = Distance + ((Speed/1000)/5);     // Assain value for disstance.
    //
    Test_sprites();
    Fuel_levels();
    //
    Game_over_screen_opperation();
    if (key == 'q'){                            // If key equal to 'q'.
        game_over = true;                       // Terminates and ends game.
        exit_game = !exit_game;                 // Changes bool state.
        clear_screen();}}                       // Clears screen.
/**
//---------------------+--------------------------------------------------------//
// DASHBOARD FUNCTION: |
//---------------------+
*/
void Dashboard( void ) {
    Time_function();                            // Calls time function.
    //
    // Time:
    draw_string(left_c, top_c, "                                                                                                                                                                                                                                                                                 ");                                    // Blank space, hides scenery.
    draw_string(bottom_c, top_c, "                                                                                                                                                                                                                                                                                 ");                                    // Blank space, hides scenery.
    draw_string(split_1, top_c, "TIME=");      // Draws string for time.
    draw_double((split_1+5), top_c, Minute);   // Double for minute value.
    draw_string((split_1+7), top_c, ":");      // Draws string for colon.
    draw_double((split_1+8), top_c, Time);     // Double for second value.
    // Condition:
    draw_string(split_2, top_c, "CONDITION="); // Draws string for condition.
    draw_double((split_2+10), top_c, Condition); // Double for condition value.
    // Speed:
    draw_string(split_3, top_c, "SPEED=");     // Draws string for speed.
    draw_double((split_3+6), top_c, Speed);    // Double for speed value.
    // Fuel:
    draw_string(split_4, top_c, "FUEL=");      // Draws string for fuel.
    draw_double((split_4+5), top_c, Fuel);     // Double for fuel value.
    // Distance:
    draw_string(split_5, top_c, "DISTANCE=");  // Draws string for distance.
    draw_double((split_5+9), top_c, Distance); // Double for Distance value.
    //
}
/**
//------------------------+-----------------------------------------------------//
// DRAW BOARDER FUNCTION: |
//------------------------+
*/
void draw_border( void ) {
    //
    // DEFINE BOARDER COORDINATES:
    l_bo = left_c;                             // Set left boarder coordinate.
    t_bo = top_c+Dashboard_offset;             // Set top boarder coordinate.
    //
    // Checks to see whether screen width and screen height smaller than the
    // minimum values of: 80 in the width and 24 in the height. If smaller
    // boarder is set to minimum coordinate values, else use screen width and
    // screen height values.
    if (right_c <= 80 || bottom_c <= 24) {
        r_bo = 80-1;                           // Set right boarder coordinate.
        b_bo = 24-1;                           // Set bottom boarder coordinate.
    }
    else {
        r_bo = (right_c - 1);                  // Set right boarder coordinate.
        b_bo = (bottom_c - 1);                 // Set bottom boarder coordinate.
    }
    //
    // DEFINE BOARDER CHARACTERS:
    char Horiz = '-';                          // Horizontal boarder character.
    char verti = '|';                          // Virtical boarder character.
    char corner = '+';                         // Boarder corner character.
    //
    // DRAW BOARDER LINES:
    draw_line( l_bo+1, t_bo, r_bo-1, t_bo, Horiz );     // Create top boarder.
    draw_line( l_bo, t_bo+1, l_bo, b_bo-1, verti );     // Create left boarder.
    draw_line( l_bo+1, b_bo, r_bo-1, b_bo, Horiz );     // Create bottom boarder.
    draw_line( r_bo, t_bo+1, r_bo, b_bo-1, verti );     // Create right boarder.
    //
    // DRAW BOARDER COARNERS:
    draw_char(l_bo, t_bo, corner);             // Create top-left corner.
    draw_char(r_bo, t_bo, corner);             // Create top-right corner.
    draw_char(l_bo, b_bo, corner);             // Create bottom-left corner.
    draw_char(r_bo, b_bo, corner);             // Create bottom-right corner.
    //
}
/**
//------------------------+-----------------------------------------------------//
// DRAW Road FUNCTION: |
//------------------------+
*/
void draw_Road( void ){
    l_road_edge = ((r_bo-l_bo)/3);             // Define left road edge value.
    r_road_edge = ((r_bo-l_bo)/3)*2;           // Define right road edge value.
    //
    char road_edge = '@';                      // Define Character for road.
    //
    // Draws line for right and left edge of the road:
    draw_line( l_road_edge, t_bo+1, l_road_edge, b_bo-1, road_edge );   // Left.
    draw_line( r_road_edge, t_bo+1, r_road_edge, b_bo-1, road_edge );   // Right.
}
/**
//------------------------+-----------------------------------------------------//
// ACCELERATION FUNCTION: |
//------------------------+
*/
void Acceleration( bool min, bool max, double speed_lim){
    if (min & max){                            // Check min and max state.
        if (Speed >= 0 || Speed <= speed_lim) {// If speed within defined limits.
            if (key == 's') {                  // If key equals 's'.
                Speed = Speed - 0.1;}          // Subtract 0.1 off speed value.
            if (key == 'w') {
                if (Speed == speed_lim){       // If speed equals speed limit.
                    Speed = speed_lim;}        // Set speed to speed limit.
                else {
                    Speed = Speed + 0.1;}}     // Add 0.1 too the speed value.
            if (Speed < 0) {                   // If speed smaller than 0.
                Speed = 0;}                    // Speed set to equal 0.
            if (Speed > speed_lim) {           // If speed greater than speed limit.
                // If speed greater than 3 and speed limit greater than the speed
                // limit plus 0.1:
                if ((speed_lim == 3) & (Speed > (speed_lim+0.1))) {
                    if (Speed == speed_lim){   // If speed equal speed limit.
                        Speed = speed_lim;}    // Speed equals speed limit.
                    if (Speed > speed_lim){    // If speed greater than speed limit.
                    Speed = Speed - 0.1;       // Subtract 0.1 off speed value.
                    }}
                else{
                    Speed = speed_lim;}}}}}    // Speed equal to speed limit.
/**
//---------------------------+--------------------------------------------------//
// SCENERY POSITION FUNCTION:|
//---------------------------+
*/
sprite_id Scenery_Position( int count, int index, int sp_w, int sp_h, int sp_im) {
    int sprite_x;                              // Local global for sprite x pos.
    int sprite_y;                              // Local global for sprite y pos.
    // If count equals value of one, two or three. Then define random x coordinate
    // on the left hand side of the game.
    if (count == 1 || count == 2 || count == 3){
        sprite_x =  1 + rand() % (l_road_edge - (sprite_h[sp_h] + 1));
    }
    // If count equals value of four, five, six. Then define random x coordinate
    // on the right hand side of the game.
    if (count == 4 || count == 5 || count == 6){
        sprite_x = (((screen_width()/3)*2) + rand() % ((screen_width()/3) - (sprite_h[sp_h] + 1)));
    }
    // Based on count value this will set the initial random y position for the
    //sprites.
    if (count == 1 || count == 4) {sprite_y = 1 + rand() % 3;}
    if (count == 2 || count == 5) {sprite_y = (round(screen_height()/3)) + rand() % (sprite_h[sp_h]);}
    if (count == 3 || count == 6) {sprite_y = (round((screen_height()/3)*2)) + rand() % (sprite_h[sp_h]);}
    // Creates sprite.
    sprite_id sprite = sprite_create( sprite_x, sprite_y, sprite_w[sp_w], sprite_h[sp_h], sprite_im[sp_im] );
    //
    sprite_draw( sprite );                     // Draws sprite.
    return sprite;                             // Returns the sprite as output.
}
/**
//------------------------+-----------------------------------------------------//
// DRAW SCENERY FUNCTION: |
//------------------------+
*/
void Draw_Scenery( int sprite_no ){
    if (initial_sprite_pos == false){          // Checks for false bool. assignment.
        int test = rand() % 5;                 // random test value smaller than 5.
        // Create new sprite based on scenery position function.
        scenery[sprite_no] = Scenery_Position( sprite_no, sprite_index, test, test, test);
        if (sprite_no == 6){                   // Checks if 'sprite_no' equal to 6.
            initial_sprite_pos = true;}}       // Set boolean to true.
    //
    else {
        if (Speed <= 0){                       // If speed smaller or equal too 0.
            sprite_draw(scenery[sprite_no]);}  // Draw scenery sprite.
        if(Speed > 0){                         // If speed greater than zero.
            // Checks the y position of the scenery sprite.
            if (sprite_y( scenery[sprite_no] ) >= b_bo){
                // Moves sprite based on parameters.
                sprite_move(scenery[sprite_no], 0, -(b_bo + sprite_height(scenery[sprite_no])));}
            // Moves sprite based on parameters.
            sprite_move(scenery[sprite_no], 0, + (Speed/10) );
            // Draws scenery sprite.
            sprite_draw(scenery[sprite_no]);}}}
/**
 //------------------------+-----------------------------------------------------//
 // COLLIDED FUNCTION:     |
 //------------------------+
 */
// Description of function: Call function in function, imputing the name of
// the two sprites you intend to test for collision.
bool collided( sprite_id sprite1, sprite_id sprite2 ){
    int th = round(sprite_y(sprite1));
    int lh = round(sprite_x(sprite1));
    int rh = (lh + sprite_width(sprite1)-1);
    int bh = (th + sprite_height(sprite1)-1);
    
    int tz = round(sprite_y(sprite2));
    int lz = round(sprite_x(sprite2));
    int rz = (lz + sprite_width(sprite2)-1);
    int bz = (tz + sprite_height(sprite2)-1);
    
    if (tz > bh) return false;
    if (th > bz) return false;
    if (lh > rz) return false;
    if (lz > rh) return false;
    
    else return true;
}
/**
 //--------------------+---------------------------------------------------------//
 // TEST SPRITES:      |
 //--------------------+
 */
void Test_sprites(void){
    for (int i=1; i<7; i++){            // For loop itterates 6 times.
        bool testing = collided( Race_car, scenery[i] );
        if  (testing == true){
            Condition = Condition - 20;
        }
    }
}

/**
 //--------------------+---------------------------------------------------------//
 // FUEL LEVELS:       |
 //--------------------+
 */
void Fuel_levels(void){
    if (Speed <= 0){
        Fuel = Fuel-1+1;
    }
    if (Speed > 0){
        Fuel = Fuel - (0.05/10)*Speed;
    }
    //if (round(Distance) == pit_stop){
        
    //}
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main( void ) {
    setup_screen();                                // Screen Setup.
    while (!exit_game){
        SS_constant_values();                      // Run once SS constant function.
        Game_constant_values();                    // Run once game constant function.
        Sprite_constant_values();                  // Run once sprite constant function.
        //
        Splash_screen_opperation();                // Call SS opperation function.
        //
        while (!game_over) {                       // While game not over, continue.
            Race_car_opperation();                 // Call RC opperation function.
        }
        while ( !GO_Operation ) {                  // While state not changed.
        GO();
        }
    }
    cleanup_screen();                              // Cleanup screen.
}
/**
//==============================================================================//
*/
