//--------------------------------------------------------------------------------
//
//  Description: This file contains the macros used for the project
//
//  Jamie Beamguard
//  Last Revision: November 25, 2019
//  Built with IAR Embedded Workbench IDE version 7.12.4
//
//--------------------------------------------------------------------------------

#define RED_LED_ON      (P1OUT |= RED_LED)
#define RED_LED_OFF     (P1OUT &= ~RED_LED)
#define GREEN_LED_ON    (P6OUT |= GRN_LED)
#define GREEN_LED_OFF   (P6OUT &= ~GRN_LED)
#define ALWAYS                         (1)
#define RESET_STATE                    (0)
#define RED_LED                     (0x01) // RED LED 0
#define GRN_LED                     (0x40) // GREEN LED 1

// Port Defintions -------------------------------------

// Housekeeping
#define P2PUPDEN        (P2OUT) // Port 2 Pull-up/-down Enable
#define P4PUPDEN        (P4OUT) // Port 4 Pull-up/-down Enable
#define TRUE            (1)
#define FALSE           (0)

// Port 1 Pins
#define RedLED          (0x01)  // Pin 1.0
#define A1_SEEED        (0x02)  // Pin 1.1
#define V_Detect_L      (0x04)  // Pin 1.2
#define V_Detect_R      (0x08)  // Pin 1.3
#define V_Bat           (0x10)  // Pin 1.4
#define V_Thumb         (0x20)  // Pin 1.5
#define UCA0RXD         (0x40)  // Pin 1.6
#define UCA0TXD         (0x80)  // Pin 1.7

// Port 2 Pins
#define P2_0            (0x01)  // Pin 2.0
#define P2_1            (0x02)  // Pin 2.1
#define P2_2            (0x04)  // Pin 2.2
#define SW2             (0x08)  // Pin 2.3
#define P2_4            (0x10)  // Pin 2.4
#define P2_5            (0x20)  // Pin 2.5
#define XOUT            (0x40)  // Pin 2.6
#define XIN             (0x80)  // Pin 2.7

// Port 3 Pins
#define P3_0            (0x01)  // Pin 3.0
#define P3_1            (0x02)  // Pin 3.1
#define P3_2            (0x04)  // Pin 3.2
#define P3_3            (0x08)  // Pin 3.3
#define SMCLK           (0x10)  // Pin 3.4
#define P3_5            (0x20)  // Pin 3.5
#define IOT_Link        (0x40)  // Pin 3.6
#define P3_7            (0x80)  // Pin 3.7

// Port 4 Pins
#define Reset_LCD       (0x01)  // Pin 4.0
#define SW1             (0x02)  // Pin 4.1
#define UCA1RXD         (0x04)  // Pin 4.2
#define UCA1TXD         (0x08)  // Pin 4.3
#define UCB1_CS_LCD     (0x10)  // Pin 4.4
#define UCB1SCK         (0x20)  // Pin 4.5
#define UCB1SIMO        (0x40)  // Pin 4.6
#define UCB1SOMI        (0x80)  // Pin 4.7

// Port 5 Pins
#define IOT_Reset               (0x01)  // Pin 5.0
#define IR_LED                  (0x02)  // Pin 5.1
#define IOT_Program_Select      (0x04)  // Pin 5.2
#define IOT_Program_Mode        (0x10)  // Pin 5.3
#define Check_Bat               (0x20)  // Pin 5.4

// Port 6 Pins
#define R_Forward       (0x01)  // Pin 6.0
#define L_Forward       (0x02)  // Pin 6.1
#define R_Reverse       (0x04)  // Pin 6.2
#define L_Reverse       (0x08)  // Pin 6.3
#define LCD_Backlight   (0x10)  // Pin 6.4
#define P6_5            (0x20)  // Pin 6.5
#define P6_6            (0x40)  // Pin 6.6

// Display Descriptors -----------------------------------------------------------

// Line IDs
#define FirstDispLine   (0)     // First LCD Line
#define SecondDispLine  (1)     // Second LCD Line
#define ThirdDispLine   (2)     // Third LCD Line
#define FourthDispLine  (3)     
#define LINE4           (3)     // Fourth LCD Line

// Misc.
#define LineWidth       (10)    // Line Character Width
#define DispLineStart   (0)     // Starting Index of Display Rows
#define DispRowCount    (4)     // Number of Rows in the Display Array
#define DispRowLength   (11)    // Number of Columns in the Display Array
#define DispStartIndex  (0)     // Starting point for the display string
#define ROW1            (0)     // Row location definitions ----------------------
#define ROW2            (1)     //
#define ROW3            (2)     //
#define ROW4            (3)     // End of row locations --------------------------
#define COL1            (0)     // Column location definitions -------------------
#define COL2            (1)     //
#define COL3            (2)     //
#define COL4            (3)     //
#define COL5            (4)     //
#define COL6            (5)     //
#define COL7            (6)     //
#define COL8            (7)     //
#define COL9            (8)     //
#define COL10           (9)     // End of column locations -----------------------
#define IPCOL           (i-7)   // Calculation for the column IP Address
#define IPiSTART        (8)     // Start for the second half of the display for IP
#define IPiSTOP1        (8)     // Max size for first half of IP
#define IPiSTOP2        (15)    // Max size for second half of IP

// Timers ------------------------------------------------------------------------
#define TB0CCR0_INTERVAL        (50000)         // 8MHz / 2 / 8 / (1/100ms) for Project 7 Counter
#define TB0CCR1_INTERVAL        (50000)         // 8Mhz / 2 / 8 / (1/100ms) for Debounce Timer
#define TB0CCR2_INTERVAL        (50000)         // 8Mhz / 2 / 8 / (1/100ms) for Screen Update/Real clock timer
#define TB1CCR0_INTERVAL        (5000)          // 8Mhz / 2 / 8 / (1/10ms) for ADC Timing
#define TB1CCR1_INTERVAL        (25000)         // 8MHz / 2 / 8 / (1/50ms) for IOT Transmission
#define TB1CCR2_INTERVAL        (25000)         // 8MHz / 2 / 8 / (1/50ms) for IOT Transmission
#define TB0CCR1ISR              (2)             // Occurs at 2
#define TB0CCR2ISR              (4)             // Occurs at 4
#define TIMERB0OVERFLOW         (14)            // Occurs at 14
#define TB1CCR1ISR              (2)             // Occurs at 2
#define TB1CCR2ISR              (4)             // Occurs at 4
#define TIMERB1OVERFLOW         (14)            // Occurs at 14
#define LCDCHANGE               (10)            // Change after 10 cycles
#define SCREENUPDATE            (1)             // Update at 2x100ms
#define RANGE                   (14)            // Used in TB0
#define REENABLESWITCHES        (8)             // Re-enable at 8x100ms
#define SECONDRESET             (6000)          // Reset the second counter after 6000s

// PWM Definitions ---------------------------------------------------------------
#define RIGHT_FORWARD_SPEED     (TB3CCR1)       // CCR1 is right forward
#define LEFT_FORWARD_SPEED      (TB3CCR2)       // CCR2 is left forward
#define RIGHT_REVERSE_SPEED     (TB3CCR3)       // CCR3 is right reverse
#define LEFT_REVERSE_SPEED      (TB3CCR4)       // CCR4 is left reverse
#define WHEEL_PERIOD            (40000)         // Period for PWM
#define WHEEL_OFF               (0)             // Wheel off
#define R_FORWARD_ON            (35500)         // Right Forward Speed
#define L_FORWARD_ON            (25500)         // Left Forward Speed
#define R_REVERSE_ON            (15000)         // Right Reverse Speed
#define L_REVERSE_ON            (30000)         // Left Reverse Speed
#define R_CLOCKWISE_ON          (11000)         // Right Clockwise Speed
#define L_CLOCKWISE_ON          (11000)         // Left Clockwise Speed
#define R_COUNTERCLOCK_ON       (11000)         // Right Counter Clockwise Speed
#define L_COUNTERCLOCK_ON       (11000)         // Left Counter Clockwise Speed
#define R_ADJUST_ON             (7000)          // Right Adjustment Speed
#define L_ADJUST_ON             (18000)         // Left Adjustment Speed
#define R_LINEFORWARD_ON        (7000)          // Right Forward Speed During Line Follow
#define L_LINEFORWARD_ON        (10000)         // Left Forward Speed During Line Follow

// ADC Definitions ---------------------------------------------------------------
#define ADC_VTHUMB_CHECK        (0)     // Case of the Thumbwheel check
#define ADC_VBAT_CHECK          (1)     // Case of the V battery check
#define ADC_LEFT_DETECT_CHECK   (2)     // Case of the left detect check
#define ADC_RIGHT_DETECT_CHECK  (3)     // Case of the right detect check
#define ADC_VTHUMB_DIV          (9)     // Divide by 512 by bit shifting by 9
#define ADC_VBAT_DIV            (2)     // Divide by 4 by bit shifting by 2
#define ADC_DET_DIV             (1)     // Divide by 2 by bit shifting by 1
#define ADCLCD1                 (0)     // adc_char locations for the detectors
#define ADCLCD2                 (1)     //
#define ADCLCD3                 (2)     //
#define ADCLCD4                 (3)     // ---------------------------------------
#define LEFTDETECTLCD1          (0)     // LCD Array locations for Left Detector
#define LEFTDETECTLCD2          (1)     //
#define LEFTDETECTLCD3          (2)     //
#define LEFTDETECTLCD4          (3)     // ---------------------------------------
#define RIGHTDETECTLCD1         (6)     // LCD Array locations for Right Detector
#define RIGHTDETECTLCD2         (7)     //
#define RIGHTDETECTLCD3         (8)     //
#define RIGHTDETECTLCD4         (9)     // ---------------------------------------
#define VTHUMBLCD1              (6)     // LCD Array locations for Thumbwheel
#define VTHUMBLCD2              (7)     //
#define VTHUMBLCD3              (8)     //
#define VTHUMBLCD4              (9)     // ---------------------------------------
#define VBATLCD1                (6)     // LCD Array locations for VBat
#define VBATLCD2                (7)     //
#define VBATLCD3                (8)     //
#define VBATLCD4                (9)     // ---------------------------------------
#define VTHUMB_CONVID           (0)     // HEXtoBCD Conversion IDs
#define VBAT_CONVID             (1)     //
#define LDETECT_CONVID          (2)     //
#define RDETECT_CONVID          (3)     // ---------------------------------------
#define ADC_CHAR_ARRAYSIZE      (5)     // Size of the char arrays for ADC
#define BLACKTHRESHOLD          (500)   // Threshold for black line detection
#define LINETIMECHECK           (2)     // Interval for checking the line detecting ADC
#define BEGINTURN               (10)    // Time to wait before starting turn 10*100ms

// Real Clock Definitions --------------------------------------------------------
#define THOUSANDS               (0)     // Array locations for real time clock
#define HUNDREDS                (1)     // Hundreds
#define TENS                    (2)     // Tens
#define ms                      (4)     // milliseconds
#define msOFFSET                (2)     // Offset used to increment ms count
#define TENSOFFSET              (5)     // After 5 increments of the ms, increment the tens
#define HUNDOFFSET              (10)    // After 10 increments of tens, increment the hundreds
#define THOUOFFSET              (10)    // After 10 increments of hundreds, increment the thousands
#define LIMITMET                (10)    // After 10 increments of thousands, reset clock
#define CLOCKARRAYSIZE          (6)     // Size of clock array

// Project 7 Definitions ---------------------------------------------------------
#define ONLINE                  (0)     // Value when car is on the line
#define OUTEREDGE               (1)     // Value when car is on the outer edge of line
#define INNEREDGE               (2)     // Value when car is on the inner edge of line
#define OFFLINE                 (3)     // Value when car is off the line
#define P7START                 (10)    // Start project 7 after 10*100ms pass
#define BEGINP6                 (10)    // Start project 6 section after 10*100ms pass

// Serial Communications Definitions ---------------------------------------------
#define BUFFERSTART             (0)     // Starting point of the ring buffer r/w indices
#define SMALL_RING_SIZE         (17)     // Size of a small ring buffer + room for NULL
#define LARGE_RING_SIZE         (17)    // Size of a large ring buffer + room for NULL
#define NULL                    ('\0')  // Hex value of a '\0'
#define RETURN                  (0x0D)  // Hex value of '\n'
#define BR115200_BRx            (4)     // Value of BRx for 115,200 baud
#define BR115200_UCA0MCTLW      (0x5551) // Value of UCA0MCTLW for 115,200 baud
#define BR460800_BRx            (1)     // Value of BRx for 460,800 baud
#define BR460800_UCA0MCTLW      (0x4A11) // Value of UCA0MCTLW for 460,800 baud
#define BR9600_BRx              (52)    // Value of BRx for 9,600 baud
#define BR9600_UCA0MCTLW        (0x4911) // Value of UCA0MCTLW for 9,600 baud
#define NCSUCHARLENGTH          (9)     // Length of the NCSU  #1 array
#define BCHARLENGTH1            (7)     // Length of the 115,200 array
#define BCHARLENGTH2            (7)     // Length of the 460,800 array
#define BSEL115200              (0)     // BaudSelect for 115,200
#define BSEL460800              (1)     // BaudSelect for 460,800
#define BSEL9600                (2)     // BaudSelect for 9,600
#define SECONDCOUNT             (10)    // When Time_Counter = 10, 1 second has passed
#define SCREENWIPE              (5)     // After 5s, wipe the second line
#define EUSCIRANGE              (0x08)  // Range of the eUSCI interrupt switch statement
#define EUSCIRXIFG              (0x02)  // Case of RXIFG
#define EUSCITXIFG              (0x04)  // Case of TXIFG
#define TRANSMITTIME            (2)     // After 2s, transmit
#define T0                      (0)     // Case number for Char_tx[0]
#define T1                      (1)     // Case number for Char_tx[1]
#define T2                      (2)     // Case number for Char_tx[2]
#define T3                      (3)     // Case number for Char_tx[3]
#define T4                      (4)     // Case number for Char_tx[4]
#define T5                      (5)     // Case number for Char_tx[5]
#define T6                      (6)     // Case number for Char_tx[6]
#define T7                      (7)     // Case number for Char_tx[7]
#define T8                      (8)     // Case number for Char_tx[8]
#define PRINT115200             (1)     // After 1s print the Char_RX
#define SCREENROWLENGTH         (10)     // Rows are 10 columns long (indices 0 thru 9)

// HEX to BCD Definitions --------------------------------------------------------
#define THOUS                   (1000)  // Thousands place for conversion
#define HUNDS                   (100)   // Hundreds Place for conversion
#define TEN                     (10)    // Tens place for conversion
#define ZERO                    (0x30)  // Hex value for '0'

// IOT Module Definitions --------------------------------------------------------
#define IOTBOOT                 (1)     // After 1000ms, boot the IOT Module
#define IPADDRESSSIZE           (16)    // Size of the array needed to store the IP address
#define SSIDSIZE                (11)    // Size of the SSID max
#define TCPINTERVALSIZE         (21)    // Size of the TCP Interval command
#define TCPPORTSIZE             (18)    // Size of the TCP Port command
#define TCPPINGSIZE             (26)    // Size of the TCP Ping command
#define TCPNSTATSIZE            (12)    // Size of the TCP NSTAT command
#define TCPRESETSIZE            (12)    // Size of the TCP RESET command
#define TCP_DISSOCINTERVAL      (0)     // Case for TCP Dissociation Interval
#define TCP_PORTINIT            (1)     // Case for TCP Port
#define TCP_PING                (2)     // Case for TCP Ping
#define TCP_NSTAT               (3)     // Case for TCP NSTAT
#define SIZEOFTCPCOMM           (20)    // Max size of TCP Commands
#define COMMANDCHAR             (5)     // Location for the command characters
#define TIMEUNITS_HUNDS         (6)     // Location for the hundreds units in IOT Command
#define TIMEUNITS_TENS          (7)     // Location for the tens units in IOT Command
#define TIMEUNITS_ONES          (8)     // Location for the ones units in IOT Command
#define ESC                     (0x1B)  // Hex value for escape key
#define SECONDCOMMLOC           (9)     // Second location of command
#define SECONDCOMMAND           (10)    // After 1000ms process second command