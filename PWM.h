
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PWM
#define	PWM

#include <xc.h> // include processor files - each processor file is guarded.  

void MotorPWM (void);


void PWMInit(void);
//Pre:

 //Post:

void setGraus(int graus);

#define PWM LATAbits.LATA4



#endif	
