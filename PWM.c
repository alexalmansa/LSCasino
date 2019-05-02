//
// Created by Alex Almansa on 18/04/2019.
//

#include "PWM.h"
//#define TEMPSA1 20;
static char estatPWM;
static char timerPWM, temps;
static char PWM,countPWM;

void PWMInit(){
    void PwInit(){
        timerPWM = TiGetTimer();
        estatPWM = 0;
        PWM = '0';
        //TRISBbits.TRISB10 = 0;
}
    void changePWM() {

        //Post: Posa a 1 o 0 el PWM , depenent del temps que estigui

        PWM = (PWM >= temps ? 1 : 0);


    }

    void incrementPWM() {

        //Post: Incrementa el valor de countPWM
        countPWM = countPWM + 1;

    }

    void MotorPWM (char start) {
        switch(estatPWM) {
            case 0:

                if(start > countPWM){
                    estatPWM = 1;
                    TiResetTics(timerPWM);
                } else{
                    PWM = 0;
                }
                

                break;
            case 1:
                if(countPWM >= start){

                    estatPWM = 0;
                }else{
                    temps = TiGetTics(timerPWM) ;
                    changePWM();

                    if(temps > TEMPSA1){
                        estatPWM = 2;
                    }
                }
                
                break;
               
                case 2:
                    TiResetTics(timerPWM);
                    incrementPWM();
                    estatPWM = 1;
                    break;
        }
    }
}