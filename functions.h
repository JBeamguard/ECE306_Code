//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter
void HEXtoBCD(int hex_value, char comp_ID);
void Init_ADC(void);
void Disp_Right_Detect(void);
void Disp_Left_Detect(void);
void adc_VBat(void);
void adc_VThumb(void);
void Line_Check(int ADC_Right_Check, int ADC_Left_Check);
void Line_Check_2(int ADC_Right_Check, int ADC_Left_Check);
void Line_Check_3(int ADC_Right_Check, int ADC_Left_Check);
void Enable_ADC(void);
void Disable_ADC(void);
void Process_VThumb(void);
void Process_Left_Detect(void);
void Process_Right_Detect(void);

// Clocks
void Init_Clocks(void);

// Display
void Disp_Forward(void);
void Disp_Reverse(void);
void Disp_LeftTurn(void);
void Disp_RightTurn(void);
void Disp_Clockwise(void);
void Disp_CounterClockwise(void);
void Disp_Pause(void);
void Init_HomeScreen(void);
void Disp_LineMet(void);
void Disp_LineUnmet(void);
void Disp_ClockUpdate(void);
void Disp_OffLine(void);
void Disp_OnLine(void);
void Disp_OuterEdge(void);
void Disp_InnerEdge(void);
void Disp_Adjusting(void);
void Disp_ScreenWipe(void);
void Disp_BaudRate(char BaudSelect);
void Disp_VThumb(void);
void Print_RX(void);
void Disp_Menu_Resistor(void);
void Disp_Menu_Shapes(void);
void Disp_Menu_Song(void);
void Disp_Menu_Select(void);
void Disp_SongInit(void);
void Disp_ShapesInit(void);
void Disp_ResistorInit(void);
void Disp_Black(void);
void Disp_Brown(void);
void Disp_Red(void);
void Disp_Orange(void);
void Disp_Yellow(void);
void Disp_Green(void);
void Disp_Blue(void);
void Disp_Violet(void);
void Disp_Gray(void);
void Disp_White(void);
void Disp_Circle(void);
void Disp_Square(void);
void Disp_Triangle(void);
void Disp_Octagon(void);
void Disp_Pentagon(void);
void Disp_Hexagon(void);
void Disp_Cube(void);
void Disp_Oval(void);
void Disp_Sphere(void);
void Disp_Cylinder(void);
void Disp_RedAndWhite(void);
void Disp_RW1(void);
void Disp_RW2(void);
void Disp_RW3(void);
void Disp_RW4(void);
void Disp_RW5(void);
void Disp_RW6(void);
void Disp_RW7(void);
void Disp_RW8(void);
void Disp_RW9(void);
void Disp_RW10(void);
void Disp_IOT_Baud(char IOTBaudSelect);
void Disp_USB_Baud(char USBBaudSelect);
void Disp_IPAddress1(void);
void Disp_IPAddress2(void);
void Disp_SSID(void);
void Disp_ClearBottomLine(void);
void Disp_NextState(void);

// IOT Communications
void ToggleIOTLED(void);
void Check_Bootup_Success(char Char_Temp);
void Get_IPAddress(char Char_Temp);
void Get_SSID(char Char_Temp);
void Check_Bootup_Success(char Char_Temp);
void IOT_TCP_Connect(void);
void Run_NSTAT(void);
void Transmit_TCP(void);
void IOT_ATRESET(void);
void CommandSearch(char Char_Temp);
void ClearIOTCommand(void);
void GetCommandDuration(void);
void StartCommandTimer(void);
void Shift_Commands(void);
void SecondCommandTimer(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);
void IR_Toggle(void);

  // LCD
void Disp_IRLED(char IR_State);
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);
void MainMenuSelection(void);
void Resistor(void);
void Shapes(void);
void Song(void);

// Ports
void Init_Ports(void);
void Init_Port_1(void);
void Init_Port_2(void);
void Init_Port_3(void);
void Init_Port_4(void);
void Init_Port_5(void);
void Init_Port_6(void);

// Real Clock
void RealClock_Update(void);
void Reset_RealClock(void);

// Serial Communications
void Init_Serial_UCA0(char BaudSelect);
void Init_Serial_UCA1(char BaudSelect);
void Transmit(void);
void Out_Character(char c);
void Clear_UCA0(void);
void Clear_UCA1(void);
void WaitToDisp(void);
void Disp_ReceiveReady(void);
void Disp_MessageReceived(void);
void Disp_Transmitting(void);
void ToggleBaudRate(void);
void Transmit_Test(void);
void ChangeIOTBaudRate(void);
void ChangeUSBBaudRate(void);
void CommandProcess(void);
void ClearUSBCommand(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);
void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Wheels
void Forward(void);
void Reverse(void);
void CounterClockwiseTurn(void);
void ClockwiseTurn(void);
void Pause(void);
void Wheels_Off(void);
void Adjust(void);
void LineForward(void);