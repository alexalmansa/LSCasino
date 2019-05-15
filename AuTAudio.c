#include "AuTAudio.h"
#include "AdTADC.h"

#include <xc.h>

static unsigned char timerAudio,timerTemps, estat,periode[MAX_PERIODES]={4,6,8,10},frequencia;

void AuInit(){
    SET_AUDIO_DIR();
    AUDIO_ON();
    timerAudio = TiGetTimer();
    timerTemps = TiGetTimer();
    estat = 2;
    frequencia = 0;
}

unsigned char* getAudioPeriode(void){
    return periode;
}

/*void setAudioPeriode(char nouPeriode){
    periode[0] = nouPeriode;
    periode[1] = nouPeriode+1;
    periode[2] = nouPeriode+2;
    periode[3] = nouPeriode+3;
}*/

void turnOffAudio(){
    estat = 2;
}

char getAudioStatus(void){
    return estat != 2;
}

void MotorAudio(){
    switch(estat){
        case 0:
            if (TiGetTics(timerAudio) >= periode[frequencia]){
                TiResetTics(timerAudio);
                AUDIO_ON();
                estat = 1;
            }
            break;
        case 1:
            if (TiGetTics(timerAudio) >= periode[frequencia]){
                TiResetTics(timerAudio);
                AUDIO_OFF();
                estat = 0;
            }
            break;
        case 2:
            break;
    }
}


char changeAudioStatus(){
    //Post Canvia l'estat d'audio
    if (estat == 2){
        estat = 0;
    }else{
        estat = 2;
        AUDIO_OFF();
    }
    return estat == 0;
}

void seguentFrequencia(){
    if(frequencia == 3){
        frequencia = 0;
    }else{
        frequencia++;
    }
}

static unsigned char estatt, melodia, cantat;
int  vanalog, vanalogantic, tempsConvertit;

void AuControlInit(){
    estatt = 1;
    melodia = 0;
    cantat=0;
    frequencia=0;
    vanalog=AdGetMostra(); 
    tempsConvertit=1.5*vanalog+200;
            
}

void MotorControlAudio(){
    switch(estatt){
        case 0:
            vanalog=AdGetMostra(); 
            tempsConvertit=(1.5*vanalog+200)*2;
            if (TiGetTics(timerTemps) >= tempsConvertit){
                if(melodia==0){
                    seguentFrequencia();
                }else if(melodia==1){
                    seguentFrequencia();
                    seguentFrequencia();
                }else if(melodia==2){
                    seguentFrequencia();
                    seguentFrequencia();
                    seguentFrequencia();
                }else if(melodia==3){
                    seguentFrequencia();
                    seguentFrequencia();
                    seguentFrequencia();
                    
                }
                cantat++;
                TiResetTics(timerTemps);
                if(cantat == 3){
                    estatt = 1;
                    changeAudioStatus();
                }
            }
            break;
            
        case 1:

            break;
        
    }
}

void audioInicial(){
    estatt=0;
    melodia=0;
    cantat=0;
    TiResetTics(timerTemps);
    changeAudioStatus();
    frequencia=0;
}

void audioDurant(){
    if(estatt==1){
        estatt=0;
        melodia=1;
        cantat=0;
        TiResetTics(timerTemps);
        
        changeAudioStatus();
        frequencia=0;
    }
}

void audioFinalGuany(){
    turnOffAudio();
    
    estatt=0;
    melodia=2;
    cantat=0;
    TiResetTics(timerTemps);
    changeAudioStatus();
    frequencia=0;
    
}

void audioFinalPerd(){
    turnOffAudio();
    estatt=0;
    melodia=3;
    cantat=0;
    TiResetTics(timerTemps);
    changeAudioStatus();
    frequencia=3;
}

int binaryToDecimal(int n) 
{ 
    int num = n; 
    int dec_value = 0; 
  
    // Initializing base value to 1, i.e 2^0 
    int basee = 1; 
  
    int temp = num; 
    while (temp) { 
        int last_digit = temp % 10; 
        temp = temp / 10; 
  
        dec_value += last_digit * basee; 
  
        basee = basee * 2; 
    } 
  
    return dec_value; 
} 
