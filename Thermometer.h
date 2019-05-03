//* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Thermometer
#define	Thermometer

#include <xc.h> // include processor files - each processor file is guarded.  
#define T LATBbits.LATB13
#define SERIE LATBbits.LATB14

#define INOUT TRISBbits.TRISB14

void MotorThermometer(void);
void llegeixBit();
char* GetTemperature();





#endif	
