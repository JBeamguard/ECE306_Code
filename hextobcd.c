// -------------------------------------------------------------------------------
//
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
// -------------------------------------------------------------------------------

#include "macros.h"
#include "msp430.h"
#include "functions.h"

// Prototypes
void HEXtoBCD(int hex_value, char comp_ID);

// Globals
char Thumb_adc_char[ADC_CHAR_ARRAYSIZE] = {'0','0','0','0'};
char VBat_adc_char[ADC_CHAR_ARRAYSIZE] = {'0','0','0','0'};
char LDetect_adc_char[ADC_CHAR_ARRAYSIZE] = {'0','0','0','0'};
char RDetect_adc_char[ADC_CHAR_ARRAYSIZE] = {'0','0','0','0'};

// Definitions
void HEXtoBCD(int hex_value, char comp_ID){
  int value;
  switch(comp_ID){
  case VTHUMB_CONVID:
    value = FALSE;
    Thumb_adc_char[ADCLCD1] = '0';                    // Nullify adc_char array
    while (hex_value > (THOUS-TRUE)){
      hex_value = hex_value - THOUS;
      value = value + TRUE;
      Thumb_adc_char[ADCLCD1] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (HUNDS-TRUE)){
      hex_value = hex_value -  HUNDS;
      value = value + TRUE;
      Thumb_adc_char[ADCLCD2] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (TEN-TRUE)){
      hex_value = hex_value - TEN;
      value = value + TRUE;
      Thumb_adc_char[ADCLCD3] = ZERO + value;
    }
    Thumb_adc_char[ADCLCD4] = ZERO + hex_value;
    break;
  case VBAT_CONVID:
    value = FALSE;
    VBat_adc_char[ADCLCD1] = '0';                    // Nullify adc_char array
    while (hex_value > (THOUS-TRUE)){
      hex_value = hex_value - THOUS;
      value = value + TRUE;
      VBat_adc_char[ADCLCD1] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (HUNDS-TRUE)){
      hex_value = hex_value -  HUNDS;
      value = value + TRUE;
      VBat_adc_char[ADCLCD2] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (TEN-TRUE)){
      hex_value = hex_value - TEN;
      value = value + TRUE;
      VBat_adc_char[ADCLCD3] = ZERO + value;
    }
    VBat_adc_char[ADCLCD4] = ZERO + hex_value;
    break;
  case LDETECT_CONVID:
    value = FALSE;
    LDetect_adc_char[ADCLCD1] = '0';                    // Nullify adc_char array
    while (hex_value > (THOUS-TRUE)){
      hex_value = hex_value - THOUS;
      value = value + TRUE;
      LDetect_adc_char[ADCLCD1] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (HUNDS-TRUE)){
      hex_value = hex_value -  HUNDS;
      value = value + TRUE;
      LDetect_adc_char[ADCLCD2] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (TEN-TRUE)){
      hex_value = hex_value - TEN;
      value = value + TRUE;
      LDetect_adc_char[ADCLCD3] = ZERO + value;
    }
    LDetect_adc_char[ADCLCD4] = ZERO + hex_value;
    break;
  case RDETECT_CONVID:
    value = FALSE;
    RDetect_adc_char[ADCLCD1] = '0';                    // Nullify adc_char array
    while (hex_value > (THOUS-TRUE)){
      hex_value = hex_value - THOUS;
      value = value + TRUE;
      RDetect_adc_char[ADCLCD1] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (HUNDS-TRUE)){
      hex_value = hex_value -  HUNDS;
      value = value + TRUE;
      RDetect_adc_char[ADCLCD2] = ZERO + value;
    }
    value = FALSE;
    while (hex_value > (TEN-TRUE)){
      hex_value = hex_value - TEN;
      value = value + TRUE;
      RDetect_adc_char[ADCLCD3] = ZERO + value;
    }
    RDetect_adc_char[ADCLCD4] = ZERO + hex_value;
    break;
  default: break;
  }
}