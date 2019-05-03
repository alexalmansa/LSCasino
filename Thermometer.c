include "AuTAudio.h"
#include "Thermometer.h"

static char TimerTermo, state = 0, clocks = 0;
int temp;
static char arr[3];

void ThermometerInit(){
    
    state = 0;
   
    TimerTermo = TiGetTimer();
    TiResetTics(TimerTermo);
    INOUT = 0;
}
char* GetTemperature(){
    
    //Post: escriu el valor ascii de num a tmp;
    arr[0] = (char) (temp / 1000);
    temp = temp - (arr[0] * 1000);
    arr[1] = (char) (temp / 100);
    temp = temp - (arr[1] * 100);
    arr[2] = (char) (temp / 10);
    temp = temp - (arr[2] * 10);
    arr[3] = temp + '0';
    arr[4] = '\0';
    arr[2] += '0';
    arr[1] += '0';
    arr[0] += '0';
    return arr;

}
    

void MotorThermometer(void) {
	

	switch(state) {
		case 0:
			if (TiGetTics(TimerTermo) > 1000) {
				//CS = 0;   No se si caldra
				state = 1;
                INOUT = 0;
			}
		break;
		case 1:
			if (clocks < 16) {
				clocks ++;
				T = 1;
				state = 2;
			}
            else if (clocks >= 16) {
				INOUT = 1;
				clocks = 0;
				state = 3;
			}
		break;
		case 2:
			T = 0;
			llegeixBit();
			state = 1;
		break;
		case 3:
			if (clocks <= 16) {
				clocks++;
                T = 1;
				state = 4;
			}
			else if (clocks>16) {
				//CS = 1;
				state = 0;
			}
		break;
		case 4:
			state = 3;
            T = 0;
		break;
	}
}

void llegeixBit(){
	//No mola gaire aquest bucle
	int i;
	for( i= 0; i < clocks; i++)
	{
		temp = temp + 2 * SERIE;
	}
	
}
