/**
//------------------------------------------------------------------------------//
// SPECIFIC TERMINAL COMANDS:
//------------------------------------------------------------------------------//
//
//  LOCATE FILE:
//  cd /Users/Matthew_Hutchison/Documents/QUT_Uni/Engineering/year_3/Semester_1/CAB202/AMS_Topic10
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
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"
/**
//--------------------------+---------------------------------------------------//
// SETUP UART FUNCTION:     |
//--------------------------+
*/
//	(a) Implement a function called setup_uart which requires no arguments and
//	returns no value.
void setup_uart(void){
	//	(a.a) Set the data transmission rate to 115200 bits per second,
	//	using the formula provided in the Topic 10 Technical Notes.
    uint32_t BAUD = 115200;                 // Baud rate.
    UBRR1 = (F_CPU/4/BAUD - 1)/2;           // Apply formula for double speed.
    //
	//	(a.b) Set the UART speed to double speed.
    UCSR1A = (1 << U2X1);                   // double speed mode, set to 1.
    //
	//	(a.c) Enable receive and transmit, but do not enable any UART-related
	//	interrupts.
    UCSR1B = (1 << RXEN1) |(1 << TXEN1);    // enable recieve and transmit.

	//	(a.d) Set the character size to 5 bits, with even parity
	//	and 2 stop bits.
    // 5 bits: Set the following bits to zero (0): UCSZ12, UCSZ11 & UCSZ10.
    // Even parity: Set UPM11 bit to one (1) and UPM10 bit to zero (0).
    // 2 Stop bits: Set USBS1 bit to one (1).
    UCSR1C =(0 << UCSZ12) | (0 << UCSZ11) | (0 << UCSZ10) | (1 << UPM11)|(0 << UPM10) |( 1 << USBS1);
    //
//	(b) End of function setup_uart
}
/**
//--------------------+---------------------------------------------------------//
// OPERATION:         |
//--------------------+
*/
int main(void) {
	setup_uart();

	for ( ;; ) {}
}
/**
//------------------------------------------------------------------------------//
*/
