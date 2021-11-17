/* ADC converter functions
 *		
 *   *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      			Comments on this revision		
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould		December 15 2016     								-v1.1
 *
 * 
 *
 **********************************************************************/
 
#ifndef __ADC_H_
#define __ADC_H_

#include <xc.h>

#define SAMPLE_TIME 10 // 10 core timer ticks = 250 ns

//#include "p24Fxxxx.h"
void initADC(void);
int readADC( int ch);

#endif

