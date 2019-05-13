#ifndef Thermometer
#define	Thermometer

#include <xc.h> // include processor files - each processor file is guarded.  


#define CLOCK TRISBbits.TRISB13
#define T LATBbits.LATB13

//#define INOUT TRISBbits.TRISB14
//#define SERIE PORTBbits.RB14
#define INOUT TRISAbits.TRISA2
#define SERIE PORTAbits.RA2

#define CSTRIS TRISAbits.TRISA3
#define CS PORTAbits.RA3


void ThermometerInit();
void MotorThermometer(void);
void llegeixBit();
char* GetTemperature();





#endif	
