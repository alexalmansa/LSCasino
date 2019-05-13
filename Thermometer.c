#include "Thermometer.h"
static char TimerTermo, state = 0, clocks = 0;
unsigned int temp, tempbona;

char negat;

unsigned char mayor[8];
unsigned char menor[8];
static char merda[13] = "1111111111111", merda2[16];
static char tempe[5];
long int entera, decimal;

void ThermometerInit() {

    state = 0;
    
    

    CLOCK = 0;
    INOUT = 1;
    CSTRIS= 0;

    TimerTermo = TiGetTimer();
    TiResetTics(TimerTermo);


    CS=1;
    
    /*mayor[7]=1;
    mayor[6]=1;
    mayor[5]=1;
    mayor[4]=0;
    mayor[3]=0;
    mayor[2]=1;
    mayor[1]=0;
    mayor[0]=0;*/



}

char* GetTemperature() {

    return tempe;

}

void MotorThermometer(void) {


    switch (state) {
        case 0:
            //if (TiGetTics(TimerTermo) > 1000) {
                CS = 0;   
                state = 1;
                //INOUT = 0;
            //}
            break;
        case 1:
            if (clocks < 13) {
                clocks++;
                T = 1;
                state = 2;
            } else if (clocks >= 13) {
                //INOUT = 1;
                clocks = 0;
                state = 3;
                //SERIE = 0;
                TiResetTics(TimerTermo);
                //tempbona = temp;
                //temp = 0;
                //strcpy(merda,merda2);

            }
            break;
        case 2:
            llegeixBit();
            T = 0;
            state = 1;
            break;
        case 3:
            CS=1;
            //Post: escriu el valor ascii de num a tmp;
            entera = 0;
            decimal = 0;

            if (mayor[6] == 1) {
                entera = entera + 128.0;
            }
            if (mayor[5] == 1) {
                entera = entera + 64.0;
            }
            if (mayor[4] == 1) {
                entera = entera + 32.0;
            }
            if (mayor[3] == 1) {
                entera = entera + 16.0;
            }
            if (mayor[2] == 1) {
                entera = entera + 8.0;
            }
            if (mayor[1] == 1) {
                entera = entera + 4.0;
            }
            if (mayor[0] == 1) {
                entera = entera + 2.0;
            }


            if (menor[7] == 1) {
                entera = entera + 1.0;
            }
            if (menor[6] == 1) {
                decimal = decimal + 500;
            }
            if (menor[5] == 1) {
                decimal = decimal + 250;
            }
            if (menor[4] == 1) {
                decimal = decimal + 125;
            }

            //sprintf(s1, "%3.1f", ((mayor<<8|menor)>>3)*0.0625);   
            if (mayor[7] == 1) {
                entera = 511 - (entera + 256);
                negat = 1;
                decimal = 1000 - decimal;
            } else {
                negat = 0;
            }


            myItoaa(entera);


            state = 0;
            break;
        case 4:
            state = 3;
            T = 0;
            break;
    }
}

void llegeixBit() {
    if(clocks < 8){
      //menor[9-clocks]=SERIE;  
      mayor[8-clocks]=SERIE;  
    }else{
      //mayor[1-clocks]=SERIE;
      menor[15-clocks]=SERIE;

    }
    merda[14-clocks] = SERIE + '0';
    //merda[4] = '\0';
    //temp <<= 1;
    //if(SERIE)temp |= 1;

}

void myItoaa(int num) {
    //Post: escriu el valor ascii de num a tmp;
    tempe[0] = (char) (num / 1000);
    num = num - (tempe[0] * 1000);
    tempe[1] = (char) (num / 100);
    num = num - (tempe[1] * 100);
    tempe[2] = (char) (num / 10);
    num = num - (tempe[2] * 10);
    tempe[3] = num + '0';
    tempe[4] = '\0';
    tempe[2] += '0';
    tempe[1] += '0';
    tempe[0] += '0';
    if (negat == 1) {
        tempe[0] = '-';
    }
}
