


//
// Created by Alex Almansa on 18/04/2019.
//

#include "PWM.h"
#include "time.h"
//#define TEMPSA1 20;
static char estatPWM;
static char timerPWM, temps;
static char start = 0;

static int TEMPSA1= 1, GRAUSXFLANC = 1, FREQ = 20, countPWM=0;


    void PWMInit(void){
        timerPWM = TiGetTimer();
        estatPWM = 1;
        PWMV = '0';
        PWMON;
        //TRISBbits.TRISB10 = 0;
}

    

    void incrementPWM(void) {

        //Post: Incrementa el valor de countPWM
        countPWM = countPWM + 1;

    }

    void setGraus(int graus) {
      
      start = graus * GRAUSXFLANC;
      //estatPWM = 1;
      
    }
    void PWMOn(){
       PWMON ;
       estatPWM = 1;
       TiResetTics(timerPWM);
    }
    void PWMOff(){
        PWMOFF;
        estatPWM = 3;
        
    }

    void MotorPWM (void) {
        switch(estatPWM) {
            

           
            case 1:
                
                    temps = TiGetTics(timerPWM) ;
                    PWMV = 1;
                    if(temps >= TEMPSA1){
                        estatPWM = 2;
                        
                    }
                    if (countPWM >= 276){
                        countPWM = 0;
                        
                        PWMOff();
                        
                    }
                break;

                case 2:
                    temps = TiGetTics(timerPWM) ;
                    PWMV = 0;
                    if(temps > FREQ){
                        
                        TiResetTics(timerPWM);
                        //incrementPWM();
                        countPWM++;
                        estatPWM = 1;
                        
                    }
                    break;
                
        }
    }
    

