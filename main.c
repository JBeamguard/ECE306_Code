//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jamie Beamguard
//  Last Revision: November 14, 2019
//  Built with IAR Embedded Workbench Version: 7.12.4
//
//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);

// Global Variables
volatile char slow_input_down;
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
extern volatile char USBBaudSelect;
extern volatile char IOTBaudSelect;
extern volatile char Transmit_Complete;
extern volatile char Receive_Complete;
extern volatile char ReceivedOneTime;
volatile char MenuSelect = FALSE;
extern volatile unsigned int ADC_VThumb_Check;

void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //------------------------------------------------------------------------------
  
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  
  Init_Ports();                         // Initialize Ports
  Init_Clocks();                        // Initialize Clock System
  Init_Conditions();                    // Initialize Variables and Initial Conditions
  Init_Timer_B0();                      // Initialize Timer B0
  Init_Timer_B1();                      // Initialize Timer B1
  Init_Timer_B3();                      // Initialize Timer B3
  Init_LCD();                           // Initialize LCD
  Init_ADC();                           // Initialize ADC
  Init_HomeScreen();                    // Display the homescreen text
  Init_Serial_UCA0(IOTBaudSelect);      // Initialize UART 0
  Init_Serial_UCA1(USBBaudSelect);      // Initialize UART 1
  Disp_USB_Baud(USBBaudSelect);         // Display the initial baudrate
  Disp_IOT_Baud(IOTBaudSelect);         // Display the initial IOT baudrate
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS){
    Display_Process();                  // Update Display
  }
  //------------------------------------------------------------------------------
}