//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic01
//
//  COMPILE:
//  gcc Exercise_1_Hello_world.c -o Exercise_1_Hello_world -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_1_Hello_world
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
void hello_cab202(void){
	// (a)	Use the printf function to display the text "Hello CAB202!" on a line
    //      by itself.
    //
    // printf function from stdio direc. prints Hello CAB202!" on a line by
    // itself in the terminal window.
    printf( "Hello CAB202!\n" );
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	hello_cab202();                 // calls function, printing desired text.
	return 0;
}
//
//==============================================================================//
