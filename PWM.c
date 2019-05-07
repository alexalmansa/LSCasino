
//
// Created by Alex Almansa on 18/04/2019.
//

#include "PWM.h"
#include "time.h"
//#define TEMPSA1 20;
static char estatPWM;
static char timerPWM, temps;
static char countPWM, start = 0, startAntic;
static int TEMPSA1= 4, GRAUSXFLANC = 1, FREQ = 20;


    void PWMInit(void){
        timerPWM = TiGetTimer();
        estatPWM = 1;
        PWMV = '0';
        PWMON;
        //TRISBbits.TRISB10 = 0;
}
    void changePWM(void) {

        //Post: Posa a 1 o 0 el PWM , depenent del temps que estigui

        PWMV = (TEMPSA1 >= temps ? 1 : 0);


    }

    

    void incrementPWM(void) {

        //Post: Incrementa el valor de countPWM
        countPWM = countPWM + 1;

    }

    void setGraus(int graus) {
      
      start = graus * GRAUSXFLANC;
      estatPWM = 1;
      
    }
    void PWMOn(){
       PWMON ;
    }
    void PWMOff(){
        PWMOFF;
    }

    void MotorPWM (void) {
        switch(estatPWM) {
            

           
            case 1:
                
                    temps = TiGetTics(timerPWM) ;
                    PWMV = 1;
                    if(temps > TEMPSA1){
                        estatPWM = 2;
                        
                    }
                break;

                case 2:
                    temps = TiGetTics(timerPWM) ;
                    PWMV = 0;
                    if(temps > FREQ){
                        
                        TiResetTics(timerPWM);
                        //incrementPWM();
                        estatPWM = 1;
                    }
                    break;
                
        }
    }

