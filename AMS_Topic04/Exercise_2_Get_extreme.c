//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic04
//
//  COMPILE:
//  gcc Exercise_2_Get_extreme.c -o Exercise_2_Get_extreme -Wall -Werror -g -I ../ZDK -L ../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./Exercise_2_Get_extreme
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
// get_extreme:       |
//--------------------+
//  (a) Begin the definition a function called get_extreme that returns the
//      maximum of its three double precision floating point 
//      arguments.
//      The arguments may be called anything, you like, but something simple
//      like x, y, and z will suffice. 
double get_extreme(double x, double y, double z){
    
    //  (c) Implement the logic required to calculate the maximum
    //      of the three input values, and return the result.
    double max;                        // max variable to hold max value.
    // Case for if there is only one with max value:
    if (x > y && x > z) {                   // x greater than y and z.
        max = x;                            // Assign max value.
    }
    if (y > x && y > z) {                   // y greater than x and z.
        max = y;                            // Assign max value.
    }
    if (z > x && z > y) {                   // z greater than x and y.
        max = z;                            // Assign max value.
    }
    //
    // Case for if there is two sharing max value:
    if (x == y && x > z ) {                 // Both x & y equal & greater than z.
        max = x;                            // Assign max value.
    }
    if (x == z && x > y) {                  // Both x & z equal & greater than y.
        max = x;                            // Assign max value.
    }
    if (y == z && y > x) {                  // Both y & z equal & greater than x.
        max = y;                            // Assign max value.
    }
    //
    // Case for if they all share the max value:
    if (x == y && x == z ) {                // x, y and z are all equal.
        max = x;                            // Assign max value.
    }
    
    return max;                             // Return max value.

//  (b) End the definition of get_extreme.
}

//
//------------------------+
// Call run_test fun.:    |
//------------------------+
void run_test(double x, double y, double z, char * label);
//
//--------------------+
// Opperation:        |
//--------------------+
// main function is used to run a series of tests to determin the success
// and failure points of the get_extreme function. Ensuring that it can be
// tested, improved until it is successful in passing all tests.
int main(void) {
    run_test(1, 1, 1, "All items equal");
    run_test(1, 2, 3, "Ascending");
    run_test(3, 2, 1, "Descending");
    run_test(1, 1, 3, "Two in a row, then ascending");
    run_test(3, 3, 1, "Two in a row, then descending");
    run_test(1, 4, 4, "Two in a row, then ascending");
    run_test(5, 1, 1, "Two in a row, then descending");
    run_test(3, 1, 5, "Minimum in the middle");
    run_test(1, 5, 3, "Maximum in the middle");
    return 0;
}
//
//------------------------+
// Declare run_test fun.: |
//------------------------+
void run_test(double x, double y, double z, char * label) {
    printf("\nRunning test: %s\nData = %0.17f, %0.17f, %0.17f\n", label, x, y, z);
    double extreme = get_extreme(x, y, z);
    printf("The extreme value is %0.17f\n", extreme);
}

