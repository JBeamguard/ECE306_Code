//--------------------------------------------------------------------------------
//
//  Description: This file contains the initialization of the ADC
//
//  Made by: Jamie Beamguard
//  Last Edit: October 16, 2019
//  Built with IAR Embedded Workbench IDE version 7.12.4
//
//--------------------------------------------------------------------------------

#include "macros.h"
#include "functions.h"
#include "msp430.h"

// Prototypes
void Init_ADC(void);
void Line_Check(int ADC_Right_Check, int ADC_Left_Check);
void Line_Check_2(int ADC_Right_Check, int ADC_Left_Check);
void Line_Check_3(int ADC_Right_Check, int ADC_Left_Check);
void Enable_ADC(void);
void Disable_ADC(void);
void Process_VThumb(void);
void Process_Left_Detect(void);
void Process_Right_Detect(void);

// Globals
volatile char Line_Met;
volatile char Line_Met_2;
volatile char Proj7LineCheck;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Vbat_Check;
extern volatile unsigned int ADC_VThumb_Check;
extern volatile char ADCRunning;
extern volatile char ThumbDiv;

// Definitions
void Init_ADC(void){
// -------------------------------------------------------------------------------
// V_DETECT_L   (0x04) // Pin 2 A2
// V_DETECT_R   (0x08) // Pin 3 A3
// V_BAT        (0x10) // Pin 4 A4
// V_THUMB      (0x20) // Pin 5 A5
// -------------------------------------------------------------------------------
  // ADCCTLO Register
  ADCCTL0 = FALSE;              // Reset ADC CTL0
  ADCCTL0 |= ADCSHT_2;          // 16 ADC Clocks
  ADCCTL0 |= ADCMSC;            // MSC
  ADCCTL0 |= ADCON;             // ADC ON
  
  // ADCCTL1 Register
  ADCCTL1 = FALSE;              // Reset ADC CTL1
  ADCCTL1 |= ADCSHS_0;          // 00b = ADC SC Bit
  ADCCTL1 |= ADCSHP;            // ADC sample-and-hold SAMPCON signal from sampling timer
  ADCCTL1 &= ~ADCISSH;          // ADC Invert Signal sample-and-hold
  ADCCTL1 |= ADCDIV_0;          // ADC Clock Divider - 000b = Divide by 1
  ADCCTL1 |= ADCSSEL_0;         // ADC Clock MODCLK
  ADCCTL1 |= ADCCONSEQ_0;       // ADC Conversion Sequence 00b = Single-channel single-conversion
  // ADCCTL1 & ADCBUSY identifies a conversion is in process
  
  // ADCCTL2 Register
  ADCCTL2 = FALSE;              // Reset ADC CTL2
  ADCCTL2 |= ADCPDIV0;          // ADC Pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_2;          // ADC Resoltion 10b = 12 bit (14 clock cycle conversion time)
  ADCCTL2 &= ~ADCDF;            // ADC Data read-back format 0b = Binary unsigned
  ADCCTL2 &= ~ADCSR;            // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
  
  // ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0;        // VREF - 000b = {VR+ = AVCC and VR- = AVSS}
  ADCMCTL0 |= ADCINCH_5;        // Start by selecting channel A5 - Thumbwheel
  
  ADCIE |= ADCIE0;              // Enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC;            // ADC enable conversion
  ADCCTL0 |= ADCSC;             // ADC start conversion
}

void Line_Check(int ADC_Right_Check, int ADC_Left_Check){                       // Function will process the ADC Check values
  if((ADC_Right_Check > BLACKTHRESHOLD) && (ADC_Left_Check > BLACKTHRESHOLD)){
    Line_Met = TRUE;
  } else {
    Line_Met = FALSE;
  }
}

void Line_Check_2(int ADC_Right_Check, int ADC_Left_Check){                       // Function will process the ADC Check values
  if((ADC_Right_Check > BLACKTHRESHOLD) && (ADC_Left_Check > BLACKTHRESHOLD)){
    Line_Met_2 = TRUE;
  } else {
    Line_Met_2 = FALSE;
  }
}

void Line_Check_3(int ADC_Right_Check, int ADC_Left_Check){                     // Function will process the ADC Check values
  if((ADC_Right_Check > BLACKTHRESHOLD) && (ADC_Left_Check > BLACKTHRESHOLD)){  // Left and Right see black
    Proj7LineCheck = ONLINE;                // One the line
  }
  if((ADC_Right_Check > BLACKTHRESHOLD) && (ADC_Left_Check < BLACKTHRESHOLD)){  // Left sees white and Right sees black
    Proj7LineCheck = OUTEREDGE;             // At the outer edge of the line
  }
  if((ADC_Right_Check < BLACKTHRESHOLD) && (ADC_Left_Check > BLACKTHRESHOLD)){   // Left sees black and Right sees white
    Proj7LineCheck = INNEREDGE;             // At the inner edge of the line
  }
  if((ADC_Right_Check < BLACKTHRESHOLD) && (ADC_Left_Check < BLACKTHRESHOLD)){   // Left and Right see white
    Proj7LineCheck = OFFLINE;               // Off of the line
  }
}

void Enable_ADC(void){
  ADCRunning = TRUE;            // Set the ADC Running flag to TRUE
  ADCMCTL0 |= ADCINCH_5;        // Start by selecting channel A5 - Thumbwheel
  ADCIE |= ADCIE0;              // Enable ADC conversion complete interrupt
  ADCCTL0 |= ADCENC;            // Enable ADC conversion
  ADCCTL0 |= ADCSC;             // Enable converting
}

void Disable_ADC(void){
  ADCRunning = FALSE;           // Set the ADC Running flag to FALSE
  ADCIE &= ~ADCIE0;             // Disable ADC conversion complete interrupt
  ADCCTL0 &= ~ADCENC;           // Disable ADC conversion
  ADCCTL0 &= ~ADCSC;            // Disable converting
}

void Process_VThumb(void){
  ADC_VThumb_Check = ADCMEM0;                                   // Move conversion result into ADC_VThumb
  ADC_VThumb_Check = ADC_VThumb_Check >> ThumbDiv;              // Divide the result by 9
  HEXtoBCD(ADC_VThumb_Check, VTHUMB_CONVID);                    // Convert the result to a decimal string
  //Disp_VThumb();                                                // Place the result onto LCD
}

void Process_Left_Detect(void){
  ADC_Left_Detect = ADCMEM0;                            // Move conversion result into ADC_Left_Detect
  ADC_Left_Detect = ADC_Left_Detect >> ADC_DET_DIV;     // Divide the result by 4
  HEXtoBCD(ADC_Left_Detect, LDETECT_CONVID);            // Convert the result to string
  //Disp_Left_Detect();                                   // Place the result onto LCD
}

void Process_Right_Detect(void){
  ADC_Right_Detect = ADCMEM0;                           // Move conversion result into ADC_Right_Detect
  ADC_Right_Detect = ADC_Right_Detect >> ADC_DET_DIV;   // Divide the result by 4
  HEXtoBCD(ADC_Right_Detect, RDETECT_CONVID);           // Convert the result to string
  //Disp_Right_Detect();                                  // Place the result onto LCD
}