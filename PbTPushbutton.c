#include "PbTPushbutton.h"
#include "../../../../../Downloads/PIC24FJ32GA002Test/AuTAudio.h"
#include "../../../../../Downloads/PIC24FJ32GA002Test/SwTSwitch.h"



static char estat,timer, temp;

void PbInit(void){
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB12 = 1;





    int f15,f16,f17,f18,c21,c22,c23
    int numero;
    //Cal posar tots els polsadors aqui
    estat = 0;
    timer = TiGetTimer();
}


void MotorPulsador(){
    switch(estat){
        case 1:

            if(f15 == f16 == f17 == f18 == 0){
              if (TiGetTics(timer) >= 100){
                estat = 2;
                TiResetTics(t);
                columna = 2;
              }
            }else{
              estat=4;
              TiResetTics(t);
            }
            break;
        case 2:
          if(f15 == f16 == f17 == f18 == 0){
            if (TiGetTics(timer) >= 100){
              estat = 3;
              TiResetTics(t);
              columna = 3;
            }
          }else{
            estat=4;
            TiResetTics(t);
          }
          break;
        case 3:

        if(f15 == f16 == f17 == f18 == 0){
          if (TiGetTics(timer) >= 100){
            estat = 1;
            TiResetTics(t);
            columna = 1;
          }
        }else{
          estat=4;
          TiResetTics(t);
        }
        break;

            //Han apretat el pulsador de - toca fer feina:
            numero = 1 *c21 + 2*c22 + 3*c23;
            estat = 3;
            TiResetTics(timer);
            break;


        case 4:
          if(f15 + f16 + f17 + f18 >= 1 && TiGetTics(timer) >= 100){
            //Espero rebots....
               estat = 5;
            }
            if (TiGetTics(timer) >= 100 && f15 + f16 + f17 + f18 == 0) {
              estat = 1;
              TiResetTics(t);
            }

            break;
        case 5:
            //Han apretat el teclat, toca fer feina

            numero = (columna -1 ) *3 +  (1*f15 + 2*f16 + 3*f17);
            asterisc = c21 * f4;
            hastag = c23 * f4;
            estat = 1;
            if (TiGetTics(timer) >= 100) {
              estat = 1;
              TiResetTics(t);
            }            break;

    }
}
