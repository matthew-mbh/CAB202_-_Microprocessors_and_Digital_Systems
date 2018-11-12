//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic02
//
//  COMPILE:
//  gcc Exercise_1_List_consecutive_integers.c -o Exercise_1_List_consecutive_integers -Wall -I../ZDK -L../ZDK -lzdk -lncurses
//
//  EXECUTE:
//  ./Exercise_1_List_consecutive_integers
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
void list_integers( void ) {
	// (a) Print the introductory message.
    printf("Listing integers between 25 and 375...\n");
	//
	// (b) Declare an integer variable that will be used as a counter. 
	//     Make it initially equal to the start value.
    int counter = 25;   // Define int variable counter, begin at 25.
	//
	// (c) Begin a WHILE statement that will execute its loop body if the
	//     counter is less than or equal to the end value.
    while(counter <= 375){          // While less than or equal to 375.
	//
		// (e) Print the current value of the counter variable.
        printf("%d\n", counter);    // Prints current counter value.
		//
		// (f) Add 1 to the counter variable.
        counter = counter + 1;      // Increase counter value by 1.
		//
	// (d) End the WHILE statement that starts at (c).
    }
	//
}
//
//--------------------+
// Operation:         |
//--------------------+
int main( void ) {
	list_integers();			// Calls function 'list_integers()', run once.
	return 0;
}
//
//==============================================================================//
