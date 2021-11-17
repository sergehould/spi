/* 
 * File:   tone.h
 * Author: sh
 *
 * Created on September 22, 2021, 5:59 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

void heartbeat(void);
void init_heartbeat(void);
void tone_high(int cnt);
void tone_low(int cnt);
void init_tone(void);
void delay_ms( unsigned int);
void delay_10us( unsigned int);

#ifdef	__cplusplus
}
#endif

#endif	/* TONE_H */

