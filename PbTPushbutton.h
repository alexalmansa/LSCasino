/* 
 * File:   PbTPushbutton.h
 * Author: JNM
 *
 * TAD Que controla un parell de pulsadors i té un motor per filtrar els rebots
 *
 * Created on 27 de enero de 2014, 19:19
 */

#ifndef PBTPUSHBUTTON_H
#define	PBTPUSHBUTTON_H

//Files del teclat
#define F1 LATBbits.LATB6
#define F2 LATBbits.LATB7
#define F3 LATBbits.LATB8
#define F4 LATBbits.LATB9

 //Columnes    
#define C1 PORTBbits.PORTB10
#define C2 PORTBbits.PORTB11
#define C3 PORTBbits.PORTB12

#define STEPBL  5 //Més val que sigui múltiple de BLPERIOD....

#include<xc.h>
#include "time.h"
#include "BlTBacklight.h"
void PbInit(void);
//Posa els ports d'entrada i demana un timer!
char getPB1(void);
//Post: retorna l'estat del pulsador - (0 o 1)

char getPB2(void);
//Post: retorna l'estat del pulsador + (0 o 1)

void MotorPulsador();

#endif	/* PBTPUSHBUTTON_H */

