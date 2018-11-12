//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic02
//
//  COMPILE:
//  gcc Exercise_2_Count_down.c -o Exercise_2_Count_down -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_2_Count_down
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
// Define Constants:  |
//--------------------+
int step_size = 5;                              // Set countdown stepsize to 5.
//
//--------------------+
// Setup:             |
//--------------------+
void count_down( void ) {
	// (a) Print the introductory message.
    printf("Counting backwards in steps of 5, beginning at 341, stopping before 35.\n");
    //
	// (b) Declare an integer variable that you will use to count. Initially 
	//     the counter should equal the start value, 341.
    int counter = 341;      // Define int variable counter, begin at 341.
    //
	// (c) Begin a WHILE statement that will execute its loop body if the 
	//     counter is greater than the end value, 35.
    while(counter > 35){                     // While greater than 35.
        //
		// (e) Print the value of the counter on a line by itself.
        printf("%d\n", counter);            // Prints current counter value.
        //
		// (f) Subtract the step size, 5, from the counter.
        counter = (counter - step_size);    // Decrease counter value by 5.
        //
	// (d) End the WHILE statement
    }
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	count_down();               // Calls function 'count_down()', run once.
	return 0;
}
//
//==============================================================================//
