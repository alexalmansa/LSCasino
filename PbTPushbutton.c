 #include "PbTPushbutton.h"



static char estat,timerTeclat, charAvaliable;
char asterisc, numero,hastag;

void PbInit(void){
    //Sortides pic escombrat(FILES)
  TRISBbits.TRISB6 = 0;
  TRISBbits.TRISB7 = 0;
  TRISBbits.TRISB8 = 0;
  TRISBbits.TRISB9 = 0;

//Entrades pic  (COLUMNES)
  TRISBbits.TRISB10 = 1;
  TRISBbits.TRISB11 = 1;
  TRISBbits.TRISB12 = 1;
   
    F3=0;
    F2=0;
    F1=0;
    F4=0;
estat = 0;
 timerTeclat = TiGetTimer();
 charAvaliable = 0;
}

char CharAvaliablet(){
    if (charAvaliable == 1){
      charAvaliable = 0;  
      return 1;  
    }else{
      return 0;    
    }  
}

char GetNumerot(){
    return numero;
}


void MotorPulsador(){
    switch(estat){
        case 0:

            if(C1 == 0 && C2 == 0 && C3 == 0){
              if (TiGetTics(timerTeclat) >= 2){
                estat = 1;
                TiResetTics(timerTeclat);
                F2=0;
                F3=0;
                F4=0;
                F1 = 1;
              }
            }else{
              estat=4;
              TiResetTics(timerTeclat);
            }
            break;
        case 1:

            if(C1 == 0 && C2 ==0 && C3 == 0){
              if (TiGetTics(timerTeclat) >= 2){
                estat = 2;
                TiResetTics(timerTeclat);
                F1=0;
                F3=0;
                F4=0;
                F2 = 1;
              }
            }else{
              estat=4;
              TiResetTics(timerTeclat);
            }
            break;
        case 2:
          if(C1 == 0 && C2 == 0 && C3 == 0){
            if (TiGetTics(timerTeclat) >= 2){
              estat = 3;
              TiResetTics(timerTeclat);
              F3 = 1;
              F1=0;
              F2=0;
              F4=0;

            }
          }else{
            estat=4;
            TiResetTics(timerTeclat);
          }
          break;
        case 3:

        if(C1 == 0 && C2 == 0 && C3 == 0){
          if (TiGetTics(timerTeclat) >= 2){
            estat = 0;
            TiResetTics(timerTeclat);
            F4 = 1;
            F1=0;
            F2=0;
            F3=0;

          }
        }else{
          estat=4;
          TiResetTics(timerTeclat);
        }
        break;



        case 4:
          if(C1 + C2 + C3 >= 1 && TiGetTics(timerTeclat) >= 2){
            //Espero rebots....
               estat = 5;
            }
            if (TiGetTics(timerTeclat) >= 2 && C1 + C2 + C3 == 0) {
              estat = 1;
              TiResetTics(timerTeclat);
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
            
            
            
            charAvaliable = 1;
            if (TiGetTics(timerTeclat) >= 2) {
              estat = 1;
              TiResetTics(timerTeclat);
            }            
            break;

    }
}
