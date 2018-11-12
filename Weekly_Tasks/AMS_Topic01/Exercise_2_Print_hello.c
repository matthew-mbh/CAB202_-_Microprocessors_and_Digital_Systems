//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_2_Print_hello.c -o Exercise_2_Print_hello -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_2_Print_hello
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
#include <stdio.h>
//
//--------------------+
// Setup:             |
//--------------------+
void print_hello( void ) {
	// (a) Use printf() to say hello to your student number, on a line by itself.
    //
    // printf function from stdio direc. prints Hello CAB202!" on a line by
    // itself in the terminal window.
    printf( "Hello n8548625!\n" );
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	print_hello();                  // calls function, printing desired text.
	return 0;
}
//
//==============================================================================//
