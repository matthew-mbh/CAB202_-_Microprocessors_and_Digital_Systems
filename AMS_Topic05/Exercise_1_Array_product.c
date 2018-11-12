//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic05
//
//  COMPILE:
//  gcc Exercise_1_Array_product.c -o Exercise_1_Array_product -Wall -Werror -g -I ../ZDK -L ../ZDK -lzdk -lncurses -lm
//
//  EXECUTE:
//  ./Exercise_1_Array_product
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
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
//
//--------------------+
// Define Array:      |
//--------------------+
void array_product( double x, int count ) {
	// TODO: INSERT CODE HERE
	// The function must compute the product of all finite elements in the
    // useable part of the array, and return this value as its result.
    //
    // You may use the standard library function isfinite() to determine if a
    // floating point value is finite.
    //
    // If the number of useable elements is 0, or if none of the elements in
    // the array are finite, your function should return the special floating
    // point value NAN – not a number.
    //
    // The function should not perform any input or output operations.
    
    // for loop checks count if count <= 0 printf('NAN'), else run for loop on
    // each itteration of the loop add next value from array to variable x. at the end printf final value for x.
    if (count <= 0 || isfinite(x) == false){
        return NAN;
    }
    else {
        int sum = 0;
        for (int run = 0; run < count; run++){
            sum = sum + x(run);
        }
        x = sum;
    }

}
//
//--------------------+
// call_function:     |
//--------------------+
void call_function( const char * label, double x[], int count ) {
	double prod = array_product( x, count );
	printf( "%s\n", label );
	printf( "\tInput data:\n" );

	for ( int i = 0; i < count; i++ ) {
		printf( "\t%d\t%f\n", i, x[i] );
	}

	printf( "\tProduct = %f\n\n", prod );
}
//
//--------------------+
// Process:           |
//--------------------+
int main( void ) {
	double x1[] = {0};
	call_function( "Count == 0", x1, 0 );
	
	double x2[] = { NAN, +INFINITY, -INFINITY };
	call_function( "No finite values", x2, 3 );

	double x3[] = { 1, 2, 3, 4, 5, 6, 7 };
	call_function( "Several finite values", x3, 7 );

	double x4[] = { 2, M_PI, NAN, 3, INFINITY, 4 };
	call_function( "A mix of finite values and infinities", x4, 6 );
	
	return 0;
}
//
//==============================================================================//
