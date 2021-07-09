//--------------------------------------------------------------------------------
//
//  Description: This file contains the intializations of both LEDs
//
//  Jamie Beamguard
//  Sep. 2019
//  Built with IAR Embedded Workbench IDE version 7.12.4
//
//--------------------------------------------------------------------------------


#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

// Prototypes
void IR_Toggle(void);

// Globals
volatile char IR_State;

// Definitions
void Init_LEDs(void){
  //------------------------------------------------------------------------------
  // LED Configurations
  //------------------------------------------------------------------------------
  // Turns on both LEDs
  GREEN_LED_OFF;
  RED_LED_OFF;
  //------------------------------------------------------------------------------
}

void IR_Toggle(void){
  switch(IR_State){
  case FALSE:                   // If IR LED is off
    P5OUT |= IR_LED;            // Turn it on
    break;
  case TRUE:                    // If IR LED is on
    P5OUT &= ~IR_LED;           // Turn it off
    break;
  default: break;
  }
}