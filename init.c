//--------------------------------------------------------------------------------
//
//  Description: This file contains the initial conditions of the display
//
//  Jamie Beamguard
//  Sep. 2019
//  Built with IAR Embedded Workbench IDE version 7.12.4
//
//--------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"

extern char display_line[DispRowCount][DispRowLength];
extern char *display[DispRowCount];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
  //------------------------------------------------------------------------------
  int i;
  
  for(i=0;i<11;i++){
    display_line[FirstDispLine][i] = RESET_STATE;
    display_line[SecondDispLine][i] = RESET_STATE;
    display_line[ThirdDispLine][i] = RESET_STATE;
    display_line[FourthDispLine][i] = RESET_STATE;
  }
  display_line[FirstDispLine][LineWidth] = DispStartIndex;
  display_line[SecondDispLine][LineWidth] = DispStartIndex;
  display_line[ThirdDispLine][LineWidth] = DispStartIndex;
  display_line[FourthDispLine][LineWidth] = DispStartIndex;
  
  display[FirstDispLine] = &display_line[FirstDispLine][DispLineStart];
  display[SecondDispLine] = &display_line[SecondDispLine][DispLineStart];
  display[ThirdDispLine] = &display_line[ThirdDispLine][DispLineStart];
  display[FourthDispLine] = &display_line[FourthDispLine][DispLineStart];
  update_display = 0;
  update_display_count = 0;
  // Interrupts are disabled by default, enable them.
  enable_interrupts();
  //------------------------------------------------------------------------------
}