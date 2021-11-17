/* File: adc.c
 * 
 * ADC converter functions
 *		
 *   *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      			Comments on this revision		
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould		December 15 2016     								-v1.1
 *    
 *  
 *
 **********************************************************************/
//A lot of people complaining about AN5 not working with the PIC32MX795F512L, 
// seem to be using an Explorer16 kit. Most likely they would be using the 
// PIC32MX795F512L USB/CAN PIM module with that. Then everybody starts worrying 
// about Vbuson and FVBUSONIO, supposedly causing trouble since that function is
// multiplexed with RB5. That would have been correct if only.... 
// the PIM socket pin numbers were a 1 to 1 match to the PIC pins. But they are not. 
// Just check the document that comes with the PIM:
//and you will find that pin 20 on the Explorer16 (the pin actually connected to the potmeter),
//connects to pin 23 on the device, which is AN2. 
//So just read out AN2 (remember to adjust AD1PCFG and AD1CHS) instead and
//you will get a perfect representation of your potmeter's position!

#include "adc32.h"
//#include "configuration.h"

/* initialize the ADC for single conversion, select Analog input pins */
void initADC(void) 
{
    AD1PCFGbits.PCFG2 = 0; // AN2 is an adc pin for the pot
    AD1CON3bits.ADCS = 2; // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
    // 2*3*12.5ns = 75ns
    AD1CON1bits.ADON = 1; // turn on A/D converter
} //initADC

/**
  Prototype:        int readADC( int ch)
  Input:            Channel to read
  Output:           returns the conversion result
  Description:      Select the specified input channel, samples the channel 
                    and then returns the converted value.
  Comment:          
  Usage:           
*/

/* In simulation mode, reaADC() is provided by DCMotor_model3.c */
/* In target mode,  reaADC() is provided respectively by adc32.c */
int readADC( int ch)
{
    // adc pin the pin should be configured as an
    // analog input in AD1PCFG
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = ch; // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1; // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) {
    ; // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0; // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
    ; // wait for the conversion process to finish
    }
    return ADC1BUF0; // read the buffer with the result
} // readADC

