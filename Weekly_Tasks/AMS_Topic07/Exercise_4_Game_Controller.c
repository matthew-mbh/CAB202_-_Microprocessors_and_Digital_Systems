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
//-------------------------------------+----------------------------------------//
// SETUP GAME CONTROLLER FUNCTION:     |
//-------------------------------------+
*/
void setup_game_controller( void ) { 
    //  (a) Set the CPU speed to 8MHz (you must also be compiling at 8MHz).
    set_clock_speed(CPU_8MHz);       // Set 8MHz for CPU speed.
    //  (b) Configure the data direction register for Port B to enable output
    //  to LED0 and LED1. The data direction for LED0 is controlled by Pin 2, 
    //  while that for LED1 is controlled by Pin 3. No other pins should be 
    //  affected.
    SET_BIT(DDRB, 2);               // Set output for Pin 2 (LED0).
    SET_BIT(DDRB, 3);               // Set output for Pin 3 (LED1).
    //  (c) Configure the data direction register for Port B to enable input
    //  from the Centre, Left, and Down switches on the joystick. These 
    //  are controlled by Pins 0, 1, and 7 respectively. No other pins should be 
    //  affected.
    CLEAR_BIT(DDRB, 0);            // Set input for Pin 0 (Center Switch).
    CLEAR_BIT(DDRB, 1);            // Set input for Pin 1 (Left Switch).
    CLEAR_BIT(DDRB, 7);            // Set input for Pin 7 (Down Switch).
    //  (d) Turn off LED0, LED1, and all other outputs connected to Port B, by 
    //  clearing all bits in the Port B output register.
    CLEAR_BIT(PORTB, 0);            // Set port B, pin 0 low.
    CLEAR_BIT(PORTB, 1);            // Set port B, pin 1 low.
    CLEAR_BIT(PORTB, 2);            // Set port B, pin 2 (LED0) low.
    CLEAR_BIT(PORTB, 3);            // Set port B, pin 3 (LED1) low.
    CLEAR_BIT(PORTB, 4);            // Set port B, pin 4 low.
    CLEAR_BIT(PORTB, 5);            // Set port B, pin 5 low.
    CLEAR_BIT(PORTB, 6);            // Set port B, pin 6 low.
    CLEAR_BIT(PORTB, 7);            // Set port B, pin 7 low.
    //  (e) Configure the data direction register for Port D to enable input
    //  from the Right and Up switches on the joystick. These are controlled by
    //  Pins 0 and 1 respectively. No other pins should be affected by this 
    //  operation.
    CLEAR_BIT(DDRD, 0);            // Set input for Pin 0 (Right Switch).
    CLEAR_BIT(DDRD, 1);            // Set input for Pin 1 (Up Switch).
}
/**
//---------------------------------------+--------------------------------------//
// PROCESS GAME CONTROLLER FUNCTION:     |
//---------------------------------------+
*/
void process_game_controller( void ) {
    //  (f) Test the relevant pin in the Port D input register to determine
    //  if the Up switch is closed. If it is, turn on both LEDs without 
    //  disrupting any other pins.
    if(BIT_VALUE(PIND, 1)){         // Checks status of up switch.
        SET_BIT(PORTB,2);           // Set LED0 high (Turns on LED0).
        SET_BIT(PORTB,3);           // Set LED1 high (Turns on LED1).
    }
    //  (g) OTHERWISE, test the relevant pin of the Port B input register
    //  to determine if the Down switch is closed. If it is, turn off both LEDs
    //  without affecting any other pins.
    else if(BIT_VALUE(PINB, 7)){      // Checks status of down switch.
        CLEAR_BIT(PORTB,2);           // Set LED0 low (Turns off LED0).
        CLEAR_BIT(PORTB,3);           // Set LED1 low (Turns off LED1).
    }
    //  (h) OTHERWISE, test the relevant pin of the Port B input register
    //  to determine if the Left switch is closed. If it is, turn on the left LED
    //  and turn off the right LED without affecting any other pins.
    else if(BIT_VALUE(PINB, 1)){      // Checks status of Left Switch.
        SET_BIT(PORTB,2);             // Set LED0 high (Turns on LED0).
        CLEAR_BIT(PORTB,3);           // Set LED1 low (Turns off LED1).
    }
    //  (i) OTHERWISE, test the relevant pin of the Port D input register
    //  to determine if the Right switch is closed. If it is, turn on the right LED
    //  and turn off the left LED without affecting any other pins.
    else if(BIT_VALUE(PIND, 0)){      // Checks status of Right Switch.
        CLEAR_BIT(PORTB,2);           // Set LED0 low (Turns off LED0).
        SET_BIT(PORTB,3);             // Set LED1 high (Turns on LED1).
    }
    //  (j) OTHERWISE, test the relevant pin of the Port B input register
    //  to determine if the Centre switch is closed. If it is, toggle both LEDs
    //  without affecting any other pins.
    else if(BIT_VALUE(PINB, 0)){      // Checks status of center switch.
        PORTB ^= (1 << 2);            // Toggle LED0.
        PORTB ^= (1 << 3);            // Toggle LED1.
    }
}
/**
//--------------------+---------------------------------------------------------//
// Operation:         |
//--------------------+
*/
int main(void) {
    setup_game_controller();

    while ( 1 ) {
        process_game_controller();
        _delay_ms(100);
    }

    return 0;
}

