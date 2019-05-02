#include "PbTPushbutton.h"



static char estat,timer, charAbaliable;
char asterisc, numero,hastag;

void PbInit(void){
    //Entrades del teclat (FILES)
#define  TRISBbits.LATB6 = 0;
#define  TRISBbits.LATB7 = 0;
#define  TRISBbits.LATB8 = 0;
#define  TRISBbits.LATB9 = 0;

//Sortides del teclat (COLUMNES)
#define  TRISBbits.LATB10 = 1;
#define  TRISBbits.LATB11 = 1;
#define  TRISBbits.LATB12 = 1;

    



    estat = 0;
    timer = TiGetTimer();
}

char CharAbaliable(){
    if (charAbaliable ==1){
      charAbaliable =0;  
      return 1;  
    }else{
      return 0;    
    }
    
    
}


void MotorPulsador(){
    switch(estat){
        case 1:

            if(F1 == F2 == F3 == F4 == 0){
              if (TiGetTics(timer) >= 100){
                estat = 2;
                TiResetTics(timer);
                C2 = 1;
              }
            }else{
              estat=4;
              TiResetTics(timer);
            }
            break;
        case 2:
          if(F1 == F2 == F3 == F4 == 0){
            if (TiGetTics(timer) >= 100){
              estat = 3;
              TiResetTics(timer);
              C3 = 1;
            }
          }else{
            estat=4;
            TiResetTics(timer);
          }
          break;
        case 3:

        if(F1 == F2 == F3 == F4 == 0){
          if (TiGetTics(timer) >= 100){
            estat = 1;
            TiResetTics(timer);
            C1 = 1;
          }
        }else{
          estat=4;
          TiResetTics(timer);
        }
        break;



        case 4:
          if(F1 + F2 + F3 + F4 >= 1 && TiGetTics(timer) >= 100){
            //Espero rebots....
               estat = 5;
            }
            if (TiGetTics(timer) >= 100 && F1 + F2 + F3 + F4 == 0) {
              estat = 1;
              TiResetTics(timer);
            }

            break;
        case 5:
            //Han apretat el teclat, toca fer feina

            numero = ((1*C1 + 2*C2 + 3*C3) -1 ) *3 +  (1*F1 + 2*F2 + 3*F3);
            asterisc = C1 * F4;
            hastag = C3 * F4;
            
            estat = 1;
            charAbaliable = 1;
            if (TiGetTics(timer) >= 100) {
              estat = 1;
              TiResetTics(timer);
            }            
            break;

    }
}
