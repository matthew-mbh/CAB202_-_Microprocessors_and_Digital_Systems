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
//---------------------------------+--------------------------------------------//
// SETUP LED BUTTONS FUNCTION:     |
//---------------------------------+
*/
void setup_led_buttons( void ) { 
    //  (a) Set the CPU speed to 8MHz (you must also be compiling at 8MHz).
    set_clock_speed(CPU_8MHz);       // Set 8MHz for CPU speed.
    //  (b) Configure the data direction register for Port B to enable output
    //  to LED0 and LED1. The data direction for LED0 is controlled by Pin 2, 
    //  while that for LED1 is controlled by Pin 3. No other pins should be 
    //  affected.
    SET_BIT(DDRB, 2);               // Set output for Pin 2 (LED0).
    SET_BIT(DDRB, 3);               // Set output for Pin 3 (LED1).
    //  (c) Turn off LED0, LED1, and all other outputs connected to Port B, by 
    //  clearing all bits in the Port B output register.
    CLEAR_BIT(PORTB, 0);            // Set port B, pin 0 low.
    CLEAR_BIT(PORTB, 1);            // Set port B, pin 1 low
    CLEAR_BIT(PORTB, 2);            // Set port B, pin 2 (LED0) low.
    CLEAR_BIT(PORTB, 3);            // Set port B, pin 3 (LED1) low.
    CLEAR_BIT(PORTB, 4);            // Set port B, pin 4 low.
    CLEAR_BIT(PORTB, 5);            // Set port B, pin 5 loww.
    CLEAR_BIT(PORTB, 6);            // Set port B, pin 6 low.
    CLEAR_BIT(PORTB, 7);            // Set port B, pin 7 low.
    //  (d) Configure the data direction register for Port F to enable input
    //  from the left button (SW1 on the pin-out diagram) and right button 
    //  (SW2 on the pin-out diagram). SW1 is activated by clearing Pin 6, and 
    //  SW2 is activated by clearing Pin 5. No other pins should be affected by 
    //  this operation.
    CLEAR_BIT(DDRF, 5);             // Set input for Pin 5 (SW2).
    CLEAR_BIT(DDRF, 6);             // Set input for Pin 6 (SW1).
}
/**
//-----------------------------------+------------------------------------------//
// PROCESS LED BUTTONS FUNCTION:     |
//-----------------------------------+
*/
void process_led_buttons( void ) {
    //  (e) Test the relevant pins in the Port F input register. If the 
    //  bits corresponding to _both_ SW1 and SW2 are set, turn off _both_ LEDs. No 
    //  pins other than those controlling LED0 and LED1 should be affected by 
    //  this action.
    if((BIT_VALUE(PINF, 5)) & (BIT_VALUE(PINF, 6))){ // Checks status of switches.
        CLEAR_BIT(PORTB,2);         // Set LED0 low (Turns off LED0).
        CLEAR_BIT(PORTB,3);         // Set LED1 low (Turns off LED1).
    }

    //  (f) Otherwise, if the bit corresponding to SW1 is set, turn on LED0
    //  while ensuring that no other pins are affected.
    else if(BIT_VALUE(PINF, 6)){    // Checks status of SW1.
        SET_BIT(PORTB,2);           // Set LED0 high (Turns on LED0).
    }
    //  (g) Otherwise, if the bit corresponding to SW2 is set, turn on LED1
    //  while ensuring that no other pins are affected.
    else if(BIT_VALUE(PINF, 5)){    // Checks status of SW2.
        SET_BIT(PORTB,3);           // Set LED1 high (Turns on LED1).
    }
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main(void) {
    setup_led_buttons();

    while ( 1 ) {
        process_led_buttons();
        _delay_ms(100);
    }

    return 0;
}

