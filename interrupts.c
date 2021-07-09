// -------------------------------------------------------------------------------
//
//      Description: This file contains the necessary interrupts of timers
//      for the system.
//
//      Made by James Beamguard
//      Last revision: 11/25/2019
//      Made with IAR Embedded Workbench IDE v7.12.4
//
// -------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

// Prototypes

// Global
extern volatile unsigned int Time_Sequence;
volatile unsigned int Switch1Debounce = FALSE;
volatile unsigned int Switch2Debounce = FALSE;
volatile char SW1_Debounce_Counter;
volatile char SW2_Debounce_Counter;
volatile char ScreenUpdateCount = FALSE;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile char one_time;
volatile unsigned int Debounce_Counter = FALSE;
volatile int ADC_Channel = FALSE;
volatile unsigned int ADC_Left_Detect = FALSE;
volatile unsigned int ADC_Right_Detect = FALSE;
volatile unsigned int ADC_Vbat_Check = FALSE;
volatile unsigned int ADC_VThumb_Check = FALSE;
extern volatile int ADC_Check_Timer = FALSE;
volatile char ADC_Enable = TRUE;
volatile int Time_Counter = FALSE;
volatile int Second_Counter = FALSE;
volatile char InitialOneTime = TRUE;
extern volatile char IOT_Char_rx[];
extern volatile char IOT_Ring_rx_write;
extern volatile char IOT_Char_tx[];
extern volatile char IOT_Ring_tx_read;
volatile char Transmit_Complete = FALSE;
extern volatile char USB_Char_rx[];
extern volatile char USB_Char_tx[];
extern volatile char USB_Ring_rx_write;
extern volatile char USB_Ring_tx_read;
extern volatile char USB_Command[];
extern volatile char USB_Command_write;
volatile char ReceivedOneTime = TRUE;
extern volatile char Received_Comm[];
volatile char Receive_Complete = FALSE;
volatile char ADCRunning = TRUE;
volatile char ThumbDiv = ADC_VTHUMB_DIV;
extern volatile char USBCommunications;
volatile char IOTBootCounter = FALSE;
volatile char IOTBootOneTime = TRUE;
volatile char ADCActive = FALSE;
volatile char FRAMCommandReceived = FALSE;
extern volatile char IOTBaudSelect;
extern volatile char USBBaudSelect;
extern volatile char IP_Address[];
extern volatile char BootSuccess;
extern volatile char TCP_Running;
volatile char IOT_Comm_Index = FALSE;
extern volatile char FoundSuccess;
extern volatile char ReadyToSend;
volatile char TimerStop = FALSE;
extern volatile char ResetDone;
extern volatile char CommandReady;
volatile unsigned int CommandTimeCounter = FALSE;
volatile unsigned int CommandDuration = FALSE;
volatile char CommandTimerStop = FALSE;
volatile char CommTimeTempOneTime = TRUE;
volatile unsigned int CommTimeTemp;
extern volatile char SSID_Found;
extern volatile char IPAddressFound;
extern volatile char SSIDLook;
volatile char DisplayDone = FALSE;
extern volatile char IOT_Command[];
extern volatile char SecondCommand;
volatile char SecondCommandTimeMode = FALSE;
volatile char temp = FALSE;
volatile char RealClockEnabled = FALSE;

// Definitions
#pragma vector = PORT4_VECTOR
__interrupt void P4_Interrupt(void){
  // For switch 1
  if(P4IFG & SW1) {
    P4IFG &= ~SW1;                      // Clear the switch ISR flag
    
    lcd_BIG_mid();                      // Set middle line big for the menu
    //Disp_Menu_Select();                 // Display the default menu screen
    ThumbDiv = ADC_VTHUMB_DIV;          // Set the division back to 9 for the menu
    
    ADCActive = TRUE;                   // Enable the ADC Timer
    
    Switch1Debounce = TRUE;             // Set the SW1 debounce flag
    SW1_Debounce_Counter = FALSE;       // Reset debounce counter
    
    P4IE &= ~SW1;                       // Disable the SW1 interrupt
    TB0CCTL1 |= CCIE;                   // Enable the debounce counter
  }
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_Interrupt(void){
  // For switch 2
  if(P2IFG & SW2) {
    P2IFG &= ~SW2;                      // Clear the switch ISR flag
      
    TB1CCTL2 |= CCIE;                   // Enable the AT+RESET=1 transmission for IOT
    //TB1CCTL0 |= CCIE;                   // Enable the ADC Checking Timer
    
    Switch2Debounce = TRUE;             // Set the SW2 Debounce flag
    SW2_Debounce_Counter = FALSE;       // Reset SW2 debounce counter
    P2IE &= ~SW2;                       // Disable the SW2 interrupt
    TB0CCTL1 |= CCIE;                   // Enable the debounce counter
  }
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler
  //    ISR will increment Time_Counter every 100ms
  //------------------------------------------------------------------------------
  Time_Counter++;                       // When the CCR0 ISR occurs, increment Second Counter
  
  if(!SecondCommandTimeMode){           // If not in second command timer mode
    if(Time_Counter == SECONDCOUNT){      // When Time_Counter = 10, 1s has passed
      Second_Counter++;
      Time_Counter = FALSE;               // Reset the time counter
    }
    
    if(Second_Counter == IOTBOOT){
      if(IOTBootOneTime){                 // Until IOT has booted, count cycles
        P5OUT |= IOT_Reset;               // Set the reset port output high
        IOTBootOneTime = FALSE;           // Disable the boot flag
      }
    }
  }
  
  if(Second_Counter == SECONDRESET){
      Second_Counter = FALSE;           // Reset the second counter
  }
  
  if(SecondCommandTimeMode){            // If timer is being used as a second command timer
    if(Time_Counter == SECONDCOMMAND){  // After waiting 1000ms, run the next command
      TB0CCTL0 &= ~CCIE;                // Turn off the timer
      Time_Counter = FALSE;             // Reset the counter
      CommandProcess();                 // Process the second command
      SecondCommandTimeMode = FALSE;    // Disable the flag
    }
  }
  
  if(Time_Counter != FALSE){
    TB0CCTL0 |= CCIE;                     // Enable the CCR0 interrupt
  }
  TB0CCR0 += TB0CCR0_INTERVAL;          // Add Offset to TBCCR0
}
                   
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //------------------------------------------------------------------------------
  //  TimerB0 1 2, Overflow Interrupt Vector (TBIV ) handler
  //    CCR1 will handle Debouncing the switches
  //    CCR2 will update the LCD and update the real clock
  //------------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,RANGE)){
    case FALSE:
      // No interrupt
      break;
    case TB0CCR1ISR:                            // CCR1 used for switch debouncing
      if(Switch1Debounce){                      // If SW1 is in debounce
        SW1_Debounce_Counter++;
      }
      if(Switch2Debounce){                      // If SW2 is in debounce
        SW2_Debounce_Counter++;
      }
      if(SW1_Debounce_Counter == REENABLESWITCHES){     // If SW1 debounce has timed out
        SW1_Debounce_Counter = FALSE;           // Clear the SW1 Counter
        Switch1Debounce = FALSE;                // Clear the Switch 1 Flag
        P4IE |= SW1;                            // Re-enable Switch 1
      }
      if(SW2_Debounce_Counter == REENABLESWITCHES){     // If SW2 debounce has timed out
        SW2_Debounce_Counter = FALSE;           // Clear the SW2 Counter
        Switch2Debounce = FALSE;                // Clear the Switch 2 Flag
        P2IE |= SW2;                            // Re-enable Switch 2
      }
      if((!Switch1Debounce) && (!Switch2Debounce)){       // If done with both
        TB0CCTL1 &= ~CCIE;                      // Disable the debounce timer
      }
      TB0CCR1 += TB0CCR1_INTERVAL;              // Add offset to TBCCR1
      break;
    case TB0CCR2ISR:                            // CCR2 used for display refreshing timer
      if(ScreenUpdateCount == SCREENUPDATE){    // After 200ms (two cycles)
        update_display = TRUE;                  // Must be set for LCD code
        display_changed = TRUE;                 // Must be set for LCD code
        one_time = TRUE;                        // Must be set for LCD code
        ScreenUpdateCount = FALSE;              // Reset update counter
        if(RealClockEnabled){                   // If the real clock is wanted
          RealClock_Update();                   // Update the real time clock
        }
      } else {
        ScreenUpdateCount++;                    // Increment after 100ms
      }
      TB0CCR2 += TB0CCR2_INTERVAL;              // Add Offset to TBCCR2
      break;
    case TIMERB0OVERFLOW:                       // overflow
      // Don't need anything since not using the overflow
      break;
    default: break;
    }
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB1 CCR0 Interrupt handler
  //  ISR will run every 10 ms
  //------------------------------------------------------------------------------
  if(ADCActive){                                // If the ADC is active:
    IR_Toggle();                                // Turn on the IR LED
    Enable_ADC();                               // Enable the ADC
  }
    
  TB1CCTL0 |= CCIE;                             // Timer B1 CCR0 enable interrupt
  TB1CCR0 += TB1CCR0_INTERVAL;                  // Add Offset to TB1CCR0
}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void Timer1_B1_ISR(void){
  //------------------------------------------------------------------------------
  //    Timer B1 CCR1 and CCR2 Interrupt handler
  //       CCR1 will run every 5ms and used to communicate with IOT
  //------------------------------------------------------------------------------
  switch(__even_in_range(TB1IV,RANGE)){
  case FALSE:                                   // Zero case
    // No interrupt
    break;
  case TB1CCR1ISR:                              // Timer B1 CCR1 used to send to IOT
    IOT_TCP_Connect();                          // Send the TCP Commands
    
    if(!TimerStop){
      TB1CCTL1 |= CCIE;                         // Timer B1 CCR1 enable interrupt
    }
    TB1CCR1 += TB1CCR1_INTERVAL;                // Add Offset to TB1CCR1
    break;
  case TB1CCR2ISR:                              // Timer B1 CCR2 used for command timing
    CommandTimeCounter++;                       // Every 50ms, increment the Command Time Counter
    
    if(CommandTimeCounter == CommandDuration){
      CommandTimerStop = TRUE;                  // Stop the timer increase
      TB1CCTL2 &= ~CCIE;                        // Disable the timer
      CommandTimeCounter = FALSE;               // Reset the counter
      Wheels_Off();                             // Stop movement
    }
    
    if(SecondCommand && CommandTimerStop){      // If a command is still in the buffer and done with first command running
      SecondCommandTimer();                     // Process the second command
      SecondCommandTimeMode = TRUE;             // Enable the flag
      SecondCommand = FALSE;                    // Disable the flag
    }
    
    if(!CommandTimerStop){
      TB1CCTL2 |= CCIE;                         // Timer B1 CCR2 enable interrupt
    }
    TB1CCR2 += TB1CCR2_INTERVAL;                // Add Offset to TB1CCR2
    break;
  case TIMERB1OVERFLOW:                         // Timer B1 Overflow
    // Not using TB1 Overflow
    break;
  default:
    break;
  }
}

//--------------------------------------------------------------------------------
//      ADC Interrupt Handler
//
//--------------------------------------------------------------------------------
#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG:  // When a conversion result is writtern to the ADCMEM0
    break;                      // before its previous conversion result was read
  case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
    break;
  case ADCIV_ADCHIIFG:  // Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG:  // Window comparator interrupt flag
    break;
  case ADCIV_ADCINIFG:  // Window comparator interrupt flag
    break;
  case ADCIV_ADCIFG:    // ADCMEM0 memory register with the conversion result
    ADCCTL0 &= ~ADCENC; // Disable ENC bit
    switch(ADC_Channel++){
    case ADC_VTHUMB_CHECK:                      // Channel A5 Interrupt: Thumbwheel Voltage
      ADCMCTL0 &= ~ADCINCH_5;                   // Disable previous channel A5 conversion
      Process_VThumb();                         // Process the thumbwheel voltage
      ADCMCTL0 |= ADCINCH_2;                    // Enable next channel A2 - Left Detect
      break;
    case ADC_LEFT_DETECT_CHECK:                 // Channel A2 Interrupt: Left Detector
      ADCMCTL0 &= ~ADCINCH_2;                   // Disable previous channel A2
      Process_Left_Detect();                    // Process the left detector
      ADCMCTL0 |= ADCINCH_3;                    // Enable next channel A3 - Right Detect
      break;
    case ADC_RIGHT_DETECT_CHECK:                // Channel A3 Interrupt: Right Detector
      ADCMCTL0 &= ~ADCINCH_3;                   // Disable previous channel A3
      Process_Right_Detect();                   // Process the right detector
      ADC_Channel = FALSE;                      // Reset channel switcher
      IR_Toggle();                              // Turn off the IR LED
      Disable_ADC();                            // Disable the ADC until ready again
      break;
    default: break;
    }
    if(ADCRunning){             // If still using the ADC
      ADCCTL0 |= ADCENC;        // Enable conversions
      ADCCTL0 |= ADCSC;         // Start next sample
    }
    break;
  default: break;
  }
}

//--------------------------------------------------------------------------------
//      eUSCI_A0 Interrupt Handler
//              IOT Module Communcations
//--------------------------------------------------------------------------------
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  //unsigned int RX_Temp;
  //unsigned int TX_Temp;
  volatile unsigned int IP_Temp;
  char Char_Temp;
  //unsigned int TX_Temp;
  switch(__even_in_range(UCA0IV,EUSCIRANGE)){
  case FALSE:       // Vector 0 - no interrupt
    break;
  case EUSCIRXIFG:                                      // Vector 2 - RXIFG
    Char_Temp = UCA0RXBUF;                              // Copy what is received into Char_Temp
    
    if(!TCP_Running){                                   // Run if TCP not setup
      Check_Bootup_Success(Char_Temp);                  // Check for successful bootup to connect the TCP port
    }
    
    if(SSIDLook){
      Get_SSID(Char_Temp);                              // Get the SSID
    }
    
    if(SSID_Found){
      SSIDLook = FALSE;                                 // Disable SSID look
      Get_IPAddress(Char_Temp);                         // Get the IP Address
    }
    
    if(IPAddressFound){
      SSID_Found = FALSE;                               // Disable flag
      Disp_SSID();                                      // Update SSID display
      Disp_IPAddress1();                                // Update IP Address display
      Disp_IPAddress2();                                // Update IP Address display
      DisplayDone = TRUE;                               // Done with IP and SSID displays
      IPAddressFound = FALSE;                           // Disable the display update section
    }
    
    if(DisplayDone){                                    // After the display is updated
      CommandReady = TRUE;                              // System is ready for commands to be sent
    }
    
    if(CommandReady){                                   // Ready to receive commands
      CommandSearch(Char_Temp);                         // Parse for commands
    }
    
    UCA1TXBUF = Char_Temp;                              // Send the received character out of UCA1 (USB)
    break;
  case EUSCITXIFG:       // Vector 4 - TXIFG
    // Interrupt is unused
    break;
  default: break;
  }
}

//--------------------------------------------------------------------------------
//      eUSCI_A1 Interrupt Handler
//              USB Communications
//--------------------------------------------------------------------------------
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  unsigned int RX_Temp;
  unsigned int TX_Temp;
  char Char_Temp;
  //char *USB_Command_Ptr;
  //unsigned int TX_Temp;
  switch(__even_in_range(UCA1IV,EUSCIRANGE)){
  case FALSE:       // Vector 0 - no interrupt
    break;
  case EUSCIRXIFG:                                      // Vector 2 - RXIFG
    Char_Temp = UCA1RXBUF;                              // Copy the received character to Char_Temp
    
    
    if(Char_Temp == '%'){                               // If the command character is received
      FRAMCommandReceived = TRUE;                       // Mark the FRAM command flag true
    }
    switch(FRAMCommandReceived){
    case TRUE:                                          // FRAM command has been received
      if(Char_Temp != RETURN){                          // If the return hasn't been reached (i.e. the string hasn't ended)
        RX_Temp = USB_Command_write++;                  // RX_Temp set to the write pointer, then the pointer is incremented
        USB_Command[RX_Temp] = Char_Temp;               // Copy what has been received to the command array location
      }
      if(Char_Temp == RETURN){                          // If the return has been reached (i.e string is complete)
        FRAMCommandReceived = FALSE;                    // Reset the command flag
        CommandProcess();                               // Process what was received
      }
      break;
    case FALSE:                                         // FRAM command not received
      if(Char_Temp != RETURN){                          // If the return hasn't been reached (i.e. the string hasn't ended)
        UCA0TXBUF = Char_Temp;                          // Put what was received into UCA0TXBUF (IOT)
        //RX_Temp = USB_Ring_rx_write++;                  // RX_Temp set to the write pointer, then the pointer is incremented
        //USB_Char_rx[RX_Temp] = Char_Temp;               // Copy what is being received into the regular ring buffer
      }
      if(Char_Temp == RETURN){
        UCA0TXBUF = Char_Temp;
      }
      break;
    default: break;
    }
    
    RX_Temp = USB_Ring_rx_write++;                      // Use the current write value to know where to write next
    USB_Char_rx[RX_Temp] = UCA1RXBUF;                   // Value in UCA1RXBUFFER goes into USB_Char_Rx
    if(USB_Ring_rx_write >= SMALL_RING_SIZE){           // If reached end of buffer
      USB_Ring_rx_write = BUFFERSTART;                  // Circle back again
    }
    if(USB_Char_rx[RX_Temp] == '\n'){                   // If reached the new line character, done receiving
      Receive_Complete = TRUE;                          // Update the display
    }
    break;
  case EUSCITXIFG:       // Vector 4 - TXIFG
    if(USBCommunications){                              // Once the PC is ready
      TX_Temp = USB_Ring_tx_read++;                     // Set the TX_Temp to the next value in the TX Ring buffer
      if(USB_Char_tx[TX_Temp] != NULL){                 // If not at a null character yet
        UCA1TXBUF = USB_Char_tx[TX_Temp];               // Put the character into the TX buffer
      }
      if(USB_Ring_tx_read >= SMALL_RING_SIZE){          // If reached end of buffer
        USB_Ring_tx_read = BUFFERSTART;                 // Circle back again
      }
      if(USB_Char_tx[TX_Temp] == NULL){                 // If reached the end null
        Transmit_Complete = TRUE;                       // Change the end transmission flag
        //USBCommunications = FALSE;                      // Disable until ready again
      }
    }
    break;
  default: break;
  }
}