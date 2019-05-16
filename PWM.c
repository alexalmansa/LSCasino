

//
// Created by Alex Almansa on 18/04/2019.
//

#include "PWM.h"
#include "time.h"
//#define TEMPSA1 20;
static char estatPWM;
static char timerPWM, temps;
static char start = 0;

static int TEMPSA1= 1, FREQ = 20, countPWM=0,casella;
static double FLANCSXCASELLA = 1.44 , restants,flancs = 263;
static int posicions[36] = {0,14,31,2,33,18,27,6,21,10,19,23,4, 25,12,35,16,29,8 ,34,13,32,9 ,20,17,30,1 ,26,5 ,7 ,22,11,36,15,28,3 ,24};
//                          0,1 ,2 ,3 ,4, 5, 6,7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 

    void PWMInit(void){
        timerPWM = TiGetTimer();
        estatPWM = 1;
        PWMV = '0';
        
        //TRISBbits.TRISB10 = 0;
}

    

    void incrementPWM(void) {

        //Post: Incrementa el valor de countPWM
        countPWM = countPWM + 1;

    }
    void vesA0(){
        flancs = casella;
        PWMOn();
    }

    void novaTirada(int casellac) {
      
      casella = posicions[casellac] ;
      flancs = casella * FLANCSXCASELLA + flancs;
      restants = 51.8 - casella; 
      PWMOn();
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
                    if (countPWM >= /*263*/flancs){
                        countPWM = 0;
                        flancs = 259 + restants;
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
    

