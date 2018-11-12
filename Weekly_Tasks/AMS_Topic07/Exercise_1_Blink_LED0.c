/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic07
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
#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
/**
//--------------------------+---------------------------------------------------//
// SETUP LED0 FUNCTION:     |
//--------------------------+
*/
void setupLed0( void ) {
    //  (a) Set the CPU speed to 8MHz (you must also be compiling at 8MHz).
    set_clock_speed(CPU_8MHz);       // Set 8MHz for CPU speed.
    //
    //  (b) Configure the data direction register for Port B to use LED0 for 
    //  output. The data direction for LED0 is controlled by Pin 2. No other 
    //  pins should be affected.
    SET_BIT(DDRB, 2);               // Set Output for Pin 2 (LED0).
    //
    //  (c) Turn off LED0 (and all other outputs connected to Port B) by 
    //  clearing all bits in the Port B output register.
    //
    // 'CLEAR_BIT(register, pin)' is used to clear bits of a register. In this
    // case, all bits (bits stored in pins 0 to 7), of port b must be cleared:
    CLEAR_BIT(PORTB, 0);            // Set port B, pin 0 low.
    CLEAR_BIT(PORTB, 1);            // Set port B, pin 1 low
    CLEAR_BIT(PORTB, 2);            // Set port B, pin 2 (LED0) low.
    CLEAR_BIT(PORTB, 3);            // Set port B, pin 3 low.
    CLEAR_BIT(PORTB, 4);            // Set port B, pin 4 low.
    CLEAR_BIT(PORTB, 5);            // Set port B, pin 5 loww.
    CLEAR_BIT(PORTB, 6);            // Set port B, pin 6 low.
    CLEAR_BIT(PORTB, 7);            // Set port B, pin 7 low.
    //
}
/**
//-----------------------------+------------------------------------------------//
// TURN ON LED0 FUNCTION:      |
//-----------------------------+
*/
void turnOnLed0( void ) {
    //  (d) Set pin 2 of the Port B output register. No other pins should be 
    //  affected.
    SET_BIT(PORTB, 2);              // Set LED0 high (Turns on LED0).
}
/**
//-----------------------------+------------------------------------------------//
// TURN OFF LED0 FUNCTION:     |
//-----------------------------+
*/
void turnOffLed0( void ) {
    //  (e) Clear pin 2 of the Port B output register. No other pins should be
    //  affected.
    CLEAR_BIT(PORTB, 2);             // Set LED0 low (Turns off LED0).
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main(void) {
    setupLed0();

    while ( 1 ) {
        turnOnLed0();
        _delay_ms(500);

        turnOffLed0();
        _delay_ms(500);
    }

    return 0;
}

