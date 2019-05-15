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

#include<xc.h>
#include "time.h"

//Files del teclat
#define F4 LATBbits.LATB6
#define F3 LATBbits.LATB7
#define F2 LATBbits.LATB8
#define F1 LATBbits.LATB9

 //Columnes    
#define C3 PORTBbits.RB10
#define C2 PORTBbits.RB11
#define C1 PORTBbits.RB12




void PbInit(void);
//Posa els ports d'entrada i demana un timer!


void MotorPulsador();

#endif	/* PBTPUSHBUTTON_H */

