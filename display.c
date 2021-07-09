// -------------------------------------------------------------------------------
//
//      Description: This file contains functions for ease of access
//              with dealing with the display
//
//      Made by: Jamie Beamguard
//      Last Revised: 11/3/2019
//
// -------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

// Prototypes
void Init_HomeScreen(void);
void Disp_Forward(void);
void Disp_Reverse(void);
void Disp_LeftTurn(void);
void Disp_RightTurn(void);
void Disp_Pause(void);
void Disp_IRLED(char IR_State);
void Disp_adc_Right_Detect(void);
void Disp_adc_Left_Detect(void);
void Disp_LineMet(void);
void Disp_LineUnmet(void);
void Disp_ClockUpdate(void);
void Disp_OffLine(void);
void Disp_OnLine(void);
void Disp_OuterEdge(void);
void Disp_InnerEdge(void);
void Disp_Adjusting(void);
void Disp_BaudRate(char BaudSelect);
void Disp_ScreenWipe(void);
void Print_RX(void);
void Disp_ReceiveReady(void);
void Disp_MessageReceived(void);
void Disp_Transmitting(void);
void Disp_VThumb(void);
void Disp_IOT_Baud(char IOTBaudSelect);
void Disp_USB_Baud(char USBBaudSelect);
void Disp_IPAddress1(void);
void Disp_IPAddress2(void);
void Disp_SSID(void);
void Disp_ClearBottomLine(void);
void Disp_NextState(void);

// Globals
extern char display_line[DispRowCount][DispRowLength];
extern char *display[DispRowCount];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern char LDetect_adc_char[ADC_CHAR_ARRAYSIZE];
extern char RDetect_adc_char[ADC_CHAR_ARRAYSIZE];
extern char VBat_adc_char[ADC_CHAR_ARRAYSIZE];
extern char Thumb_adc_char[ADC_CHAR_ARRAYSIZE];
char Init_IR = TRUE;
extern volatile char clock[CLOCKARRAYSIZE];
extern volatile char IOTBaudSelect;
extern volatile char USBBaudSelect;
extern volatile char IOT_Char_rx[];
extern volatile char USB_Char_rx[];
extern volatile char IP_Address[];
extern volatile char SSID[];
extern volatile char PadNumber;

// Definitions
void Init_HomeScreen(void){
  strcpy(display_line[SecondDispLine], "Project 10");
  update_string(display_line[SecondDispLine], SecondDispLine);
  enable_display_update();
}

void Disp_Right_Detect(void){
  display_line[FourthDispLine][RIGHTDETECTLCD1] = RDetect_adc_char[ADCLCD1];
  display_line[FourthDispLine][RIGHTDETECTLCD2] = RDetect_adc_char[ADCLCD2];
  display_line[FourthDispLine][RIGHTDETECTLCD3] = RDetect_adc_char[ADCLCD3];
  display_line[FourthDispLine][RIGHTDETECTLCD4] = RDetect_adc_char[ADCLCD4];
  update_string(display_line[ThirdDispLine], ThirdDispLine);
  display_changed = TRUE;
}

void Disp_Left_Detect(void){
  display_line[FourthDispLine][LEFTDETECTLCD1] = LDetect_adc_char[ADCLCD1];
  display_line[FourthDispLine][LEFTDETECTLCD2] = LDetect_adc_char[ADCLCD2];
  display_line[FourthDispLine][LEFTDETECTLCD3] = LDetect_adc_char[ADCLCD3];
  display_line[FourthDispLine][LEFTDETECTLCD4] = LDetect_adc_char[ADCLCD4];
  update_string(display_line[ThirdDispLine], ThirdDispLine);
  display_changed = TRUE;
}

void Disp_VThumb(void){
  display_line[ROW1][VTHUMBLCD1] = Thumb_adc_char[ADCLCD1];
  display_line[ROW1][VTHUMBLCD2] = Thumb_adc_char[ADCLCD2];
  display_line[ROW1][VTHUMBLCD3] = Thumb_adc_char[ADCLCD3];
  display_line[ROW1][VTHUMBLCD4] = Thumb_adc_char[ADCLCD4];
  update_string(display_line[ROW3], ROW3);
  display_changed = TRUE;
}

void Disp_ClearBottomLine(void){
  strcpy(display_line[ROW3], "          ");
  update_string(display_line[ROW3], ROW3);
  display_changed = TRUE;
}

void Disp_LineMet(void){
  strcpy(display_line[SecondDispLine], "  Found   ");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_LineUnmet(void){
  strcpy(display_line[SecondDispLine], " Searching");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}
  
void Disp_Forward(void){
  strcpy(display_line[ROW2], " Forward  ");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Disp_Reverse(void){
  strcpy(display_line[ROW2], " Reverse  ");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Disp_LeftTurn(void){
  strcpy(display_line[ROW2], "Left  Turn");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Disp_RightTurn(void){
  strcpy(display_line[ROW2], "Right Turn");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Disp_Pause(void){
  strcpy(display_line[ROW2], "   Stop   ");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Disp_ClockUpdate(void){
  display_line[ROW3][COL10] = clock[ms];
  display_line[ROW3][COL9] = '.';
  display_line[ROW3][COL8] = clock[TENS];
  display_line[ROW3][COL7] = clock[HUNDREDS];
  display_line[ROW3][COL6] = clock[THOUSANDS];
  update_string(display_line[ROW3], ROW3);
  display_changed = TRUE;
}

void Disp_OffLine(void){
  strcpy(display_line[SecondDispLine], " Off Line ");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_OnLine(void){
  strcpy(display_line[SecondDispLine], "  On Line ");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_OuterEdge(void){
  strcpy(display_line[SecondDispLine], "Outer Edge");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_InnerEdge(void){
  strcpy(display_line[SecondDispLine], "Inner Edge");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_Adjusting(void){
  strcpy(display_line[ThirdDispLine], "  Adjust  ");
  update_string(display_line[SecondDispLine], SecondDispLine);
  display_changed = TRUE;
}

void Disp_BaudRate(char BaudSelect){
  if(BaudSelect == BSEL115200){
    strcpy(display_line[ROW3], " 115,200  ");
    update_string(display_line[ROW4], ROW4);
    display_changed = TRUE;
  }
  if(BaudSelect == BSEL460800){
    strcpy(display_line[ROW3], " 460,800  ");
    update_string(display_line[ROW3], ROW3);
    display_changed = TRUE;
  }
}

void Disp_USB_Baud(char USBBaudSelect){
  display_line[ROW3][COL1] = 'U';
  display_line[ROW3][COL2] = 'S';
  display_line[ROW3][COL3] = 'B';
  display_line[ROW3][COL4] = ':';
  switch(USBBaudSelect){
  case BSEL9600:                          // If set as 9,600 baud
    display_line[ROW3][COL5] = ' ';
    display_line[ROW3][COL6] = '9';
    display_line[ROW3][COL7] = ',';
    display_line[ROW3][COL8] = '6';
    display_line[ROW3][COL9] = '0';
    display_line[ROW3][COL10] = '0';
    break;
  case BSEL115200:                        // If set as 115,200 baud
    display_line[ROW3][COL5] = '1';
    display_line[ROW3][COL6] = '1';
    display_line[ROW3][COL7] = '5';
    display_line[ROW3][COL8] = '2';
    display_line[ROW3][COL9] = '0';
    display_line[ROW3][COL10] = '0';
    break;
  default: break;
  }
  update_string(display_line[ROW3], ROW3);
  display_changed = TRUE;
}

void Disp_IOT_Baud(char IOTBaudSelect){
  display_line[ROW4][COL1] = 'I';
  display_line[ROW4][COL2] = 'O';
  display_line[ROW4][COL3] = 'T';
  display_line[ROW4][COL4] = ':';
  switch(IOTBaudSelect){
  case BSEL9600:                          // If set as 9,600 baud
    display_line[ROW4][COL5] = ' ';
    display_line[ROW4][COL6] = '9';
    display_line[ROW4][COL7] = ',';
    display_line[ROW4][COL8] = '6';
    display_line[ROW4][COL9] = '0';
    display_line[ROW4][COL10] = '0';
    break;
  case BSEL115200:                        // If set as 115,200 baud
    display_line[ROW4][COL5] = '1';
    display_line[ROW4][COL6] = '1';
    display_line[ROW4][COL7] = '5';
    display_line[ROW4][COL8] = '2';
    display_line[ROW4][COL9] = '0';
    display_line[ROW4][COL10] = '0';
    break;
  default: break;
  }
  update_string(display_line[ROW4], ROW4);
  display_changed = TRUE;
}

void Disp_ScreenWipe(void){
  strcpy(display_line[ROW2], "          ");
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}

void Print_RX(void){
  int i;
  for(i=FALSE; i<SCREENROWLENGTH; i++){
    display_line[ROW4][i] = IOT_Char_rx[i];
  }
  display_changed = TRUE;
}

void Disp_ReceiveReady(void){
  strcpy(display_line[ROW1], " Waiting  ");
  update_string(display_line[ROW1], ROW1);
  display_changed = TRUE;
}

void Disp_MessageReceived(void){
  strcpy(display_line[ROW1], " Received ");
  update_string(display_line[ROW1], ROW1);
  display_changed = TRUE;
}

void Disp_Transmitting(void){
  strcpy(display_line[ROW1], " Transmit ");
  update_string(display_line[ROW1], ROW1);
  strcpy(display_line[ROW4], "          ");
  update_string(display_line[ROW4], ROW4);
  display_changed = TRUE;
}

void Disp_IPAddress1(void){
  char i;
  
  strcpy(display_line[ROW2], "          "); 
  update_string(display_line[ROW2], ROW2);
  for(i=FALSE;i<IPiSTOP1;i++){
    if(IP_Address[i] != NULL){
      display_line[ROW2][i+TRUE] = IP_Address[i];
    }
  }
  update_string(display_line[ROW2], ROW2);
  display_changed = TRUE;
}
  
void Disp_IPAddress2(void){
  char i;
  
  strcpy(display_line[ROW3], "          ");
  update_string(display_line[ROW3], ROW3);
  for(i=IPiSTART;i<=IPiSTOP2;i++){
    if(IP_Address[i] != NULL){
      display_line[ROW3][IPCOL] = IP_Address[i];
    }
  }
  update_string(display_line[ROW3], ROW3);
  display_changed = TRUE;
}

void Disp_SSID(void){
  display_line[ROW1][COL1] = SSID[COL1];
  display_line[ROW1][COL2] = SSID[COL2];
  display_line[ROW1][COL3] = SSID[COL3];
  display_line[ROW1][COL4] = SSID[COL4];
  display_line[ROW1][COL5] = SSID[COL5];
  display_line[ROW1][COL6] = SSID[COL6];
  display_line[ROW1][COL7] = SSID[COL7];
  display_line[ROW1][COL8] = SSID[COL8];
  display_line[ROW1][COL9] = SSID[COL9];
  display_line[ROW1][COL10] = SSID[COL10];
  update_string(display_line[ROW1], ROW1);
  display_changed = TRUE;
}

void Disp_NextState(void){
  display_line[ROW1][COL1] = 'A';
  display_line[ROW1][COL2] = 'r';
  display_line[ROW1][COL3] = 'r';
  display_line[ROW1][COL4] = 'i';
  display_line[ROW1][COL5] = 'v';
  display_line[ROW1][COL6] = 'e';
  display_line[ROW1][COL7] = 'd';
  display_line[ROW1][COL8] = ' ';
  display_line[ROW1][COL9] = '0';
  display_line[ROW1][COL10] = PadNumber;
  display_changed = TRUE;
}