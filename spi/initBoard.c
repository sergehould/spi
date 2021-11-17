/***********************************************************************************************
*
*
* FileName:  initBoard.c      
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date            Version     Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould      14 Jan. 2021		v1.0.0      Setup for PIC32    
* Serge Hould      27 Apr. 2021     v1.1        Set PBCLK to 80MHz to facilitate simulation.  
*                                               Both sysclk and pbclk are the same.
*                                               T2 pre-scaler set to 1:4
* Serge Hould      6 Sept. 2021     v1.2        Disable JTAG inside initIO() - JTAG shared with RA5, 
*                                               RA4, RA1 and RA0                                          
* Serge Hould      13 Sept. 2021    v2.0        Add MX3 board compatibility.  Macro MX3 is defined 
*                                               in properties->xc32-gcc->Processing and messages       
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
#include "initBoard.h"
#include <stdint.h>
#include <xc.h>
#include <sys/attribs.h>


#if defined EXPLORER_16_32
 // Configuration Bit settings
// SYSCLK = 80 MHz 
//(8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz
// Primary Osc w/PLL (HS+PLL)
// WDT OFF, Peripheral Bus is CPU clock÷8
// Other options are default as per datasheet
// see file:C:\Program Files (x86)\Microchip\xc32\v1.40\docs\config_docs\32mx795f512l.html
#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1 
#pragma config POSCMOD = HS, FNOSC = PRIPLL
#pragma config FPBDIV = DIV_1  // PBCLK = SYSCLK/DIV_1
#pragma config FWDTEN =  OFF    // disable
#elif defined MX3
#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      
/* ------------------------------------------------------------ */
/*						Configuration Bits		                */
/* ------------------------------------------------------------ */
// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	EC
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_1

// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

#endif

/* Sets up the IOs */
#if defined EXPLORER_16_32
void initIOs(void){
    DDPCONbits.JTAGEN = 0; // JTAG shared with RA5, RA4, RA1 and RA0
    /* LEDs */
    TRISAbits.TRISA7 = 0;       //LED D10
    TRISAbits.TRISA5 = 0;       //LED D8
    TRISAbits.TRISA4 = 0;       //LED D7
    TRISAbits.TRISA3 = 0;       //LED D6
    TRISAbits.TRISA2 = 0;       //LED D5
    TRISAbits.TRISA1 = 0;       //LED D4
    TRISAbits.TRISA0 = 0;       //LED D3
    
   
    TRISDbits.TRISD6 =1; //S3
    TRISDbits.TRISD7 =1;//S6
    TRISDbits.TRISD13 =1;//S4
    TRISAbits.TRISA6 =1; //S5 - shared with LED D9
	
    /* Turns off all LEDs*/
     LATA = LATA & 0xffff0000;
}
#elif defined MX3
void initIOs(void){
    /* LEDs */
    TRISAbits.TRISA7 = 0;       //LED7
    TRISAbits.TRISA6 = 0;       //LED6
    TRISAbits.TRISA5 = 0;       //LED5
    TRISAbits.TRISA4 = 0;       //LED4
    TRISAbits.TRISA3 = 0;       //LED3
    TRISAbits.TRISA2 = 0;       //LED2
    TRISAbits.TRISA1 = 0;       //LED1
    TRISAbits.TRISA0 = 0;       //LED0
    LATA = LATA &0xffffff00;
    
    /* Switches*/
    TRISFbits.TRISF3 =1;    // SWT0 
    TRISFbits.TRISF5 =1;    // SWT1 
    TRISFbits.TRISF4 =1;    // SWT2
    TRISDbits.TRISD15 =1;   // SWT3
    TRISDbits.TRISD14 =1;   // SWT4
    TRISBbits.TRISB11 =1;   // SWT5
    ANSELBbits.ANSB11 = 0;  // disable analog (set pins as digital))
    TRISBbits.TRISB10 =1;   // SWT6
    ANSELBbits.ANSB10 = 0;  // disable analog (set pins as digital))
    TRISBbits.TRISB9 =1;    // SWT7
    ANSELBbits.ANSB9 = 0;  // disable analog (set pins as digital))

    /* Buttons */
    TRISBbits.TRISB1 =1;   // BTNU
    ANSELBbits.ANSB1 = 0;  // disable analog (set pins as digital))
    TRISBbits.TRISB0 =1;   // BTNL
    ANSELBbits.ANSB0 = 0;  // disable analog (set pins as digital))
    TRISFbits.TRISF0 =1;   // BTNC
    TRISBbits.TRISB8 =1;   // BTNR
    ANSELBbits.ANSB8 = 0;  // disable analog (set pins as digital))
    TRISAbits.TRISA15 =1;   // BTND
}


/* ------------------------------------------------------------ */
/***	RGBLED_Init
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes the hardware involved in the RGBLED module: 
**      the pins corresponding to R, G and B colors are initialized as digital outputs and Timer 5 in configured.
**          
*/
void RGBLED_Init()
{
    // Configure RGBLEDs as digital outputs.

    //    RPD2R = 0x0B; // LED8_R RPD2 is OC3 - for PWM usage
    RPD2R = 0;      // no remapable
    TRISDbits.TRISD2 = 0;    // RED output 
  
    //RPD12R 1011 = OC5
    //   RPD12R = 0x0B; // LED8_G RPD12 is OC5 - for PWM usage
    RPD12R = 0;      // no remapable
    TRISDbits.TRISD12 = 0;    // Green  output
 
    //    RPD3R = 0x0B; // LED8_B RPD3 is OC4 - for PWM usage
    RPD3R = 0;      // no remapable
    TRISDbits.TRISD3 = 0;    // Blue output
    
    // disable analog (set pins as digital))
    ANSELDbits.ANSD2 = 0;
    ANSELDbits.ANSD3= 0;
    
    // Turn them off
    LATDbits.LATD2 = 0;     // Red
    LATDbits.LATD12 = 0;    // Green
    LATDbits.LATD3= 0;      // Blue
}

#endif


#if defined EXPLORER_16_32
/*
	Function that set timer 2 
	input: 
	output:

*/
void initTimer2( void){
// Initialize and enable Timer2
	T2CONbits.TON = 0; // Disable Timer
	T2CONbits.TCS = 0; // Select internal instruction cycle clock
	T2CONbits.TGATE = 0; // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b010; // Select 1:4 Prescaler
   // T2CONbits.TCKPS = 0b000; // Select 1:1 Prescaler
	TMR2 = 0x00; // Clear timer register
	PR2=0xffff; // Load the period value. 
	IPC2bits.T2IP = 0x01; // Set Timer 2 Interrupt Priority Level
	IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
	IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
   // _T2IP = 6; // Enable Timer 2 interrupt
	T2CONbits.TON = 1; // Start Timer              
} // init
#elif defined MX3
#endif



