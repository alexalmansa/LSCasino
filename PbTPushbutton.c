 #include "PbTPushbutton.h"



static char estat,timer, charAbaliable;
char asterisc, numero,hastag;

void PbInit(void){
    //Entrades del teclat (FILES)
#define  TRISBbits.LATB6 = 1;
#define  TRISBbits.LATB7 = 1;
#define  TRISBbits.LATB8 = 1;
#define  TRISBbits.LATB9 = 1;

//Sortides del teclat (COLUMNES)
#define  TRISBbits.LATB10 = 0;
#define  TRISBbits.LATB11 = 0;
#define  TRISBbits.LATB12 = 0;

    



    estat = 0;
    timer = TiGetTimer();
}

char CharAbaliable(){
    if (charAbaliable ==1){
      charAbaliable = 0;  
      return 1;  
    }else{
      return 0;    
    }  
}

char GetNumero(){
    return numero;
}


void MotorPulsador(){
    switch(estat){
        case 0:

            if(C1 == C2 == C3 == 0){
              if (TiGetTics(timer) >= 100){
                estat = 1;
                TiResetTics(timer);
                F2=F3=F4=0;
                F1 = 1;
              }
            }else{
              estat=4;
              TiResetTics(timer);
            }
            break;
        case 1:

            if(C1 == C2 == C3 == 0){
              if (TiGetTics(timer) >= 100){
                estat = 2;
                TiResetTics(timer);
                F1=F3=F4=0;
                F2 = 1;
              }
            }else{
              estat=4;
              TiResetTics(timer);
            }
            break;
        case 2:
          if(C1 == C2 == C3 == 0){
            if (TiGetTics(timer) >= 100){
              estat = 3;
              TiResetTics(timer);
              F3 = 1;
              F1=F2=F4=0;

            }
          }else{
            estat=4;
            TiResetTics(timer);
          }
          break;
        case 3:

        if(C1 == C2 == C3 == 0){
          if (TiGetTics(timer) >= 100){
            estat = 0;
            TiResetTics(timer);
            F4 = 1;
            F1=F2=F3=0;

          }
        }else{
          estat=4;
          TiResetTics(timer);
        }
        break;



        case 4:
          if(C1 + C2 + C3 >= 1 && TiGetTics(timer) >= 100){
            //Espero rebots....
               estat = 5;
            }
            if (TiGetTics(timer) >= 100 && C1 + C2 + C3 == 0) {
              estat = 1;
              TiResetTics(timer);
            }

            break;
        case 5:
            //Han apretat el teclat, toca fer feina
            if(F1 == 1 && C1 == 1){
                numero = '1';
            }else if(F1 == 1 && C2 == 1){
                numero = '2';
            }else if(F1 == 1 && C3 == 1){
                numero = '3';
            }else if(F2 == 1 && C1 == 1){
                numero = '4';
            }else if(F2 == 1 && C2 == 1){
                numero = '5';
            }else if(F2 == 1 && C3 == 1){
                numero = '6';
            }else if(F3 == 1 && C1 == 1){
                numero = '7';
            }else if(F3 == 1 && C2 == 1){
                numero = '8';
            }else if(F3 == 1 && C3 == 1){
                numero = '9';
            }else if(F4 == 1 && C1 == 1){
                numero = '#';
            }else if(F4 == 1 && C2 == 1){
                numero = '0';
            }else if(F4 == 1 && C3 == 1){
                numero = '*';
            }
            
            
            estat = 1;
            charAbaliable = 1;
            if (TiGetTics(timer) >= 100) {
              estat = 1;
              TiResetTics(timer);
            }            
            break;

    }
}

