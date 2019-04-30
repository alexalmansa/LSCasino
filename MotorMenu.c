#include "PrTPropaganda.h"


static char state;
static char fitxes, partguanyades, partjugades,fitguanyades,fitperdudes;
static char opcio = 0;
static char printat = 0;
static char chars = 0;
static char timerPropaganda;
static char valors[3];

static char temp[50],op;
static int timestamp, timestamp2, total;


void myItoa(int num){
    //Post: escriu el valor ascii de num a tmp;
    temp[0] = (char)(num/1000);
    num = num - (temp[0]*1000);
    temp[1] = (char)(num /100);
    num = num - (temp[1]*100);
    temp[2] = (char) (num /10);
    num = num - (temp[2]*10);
    temp[3] = num+'0';
    temp[4] = '\0';
    temp[2]+='0';
    temp[1]+='0';
    temp[0]+='0';

}

void Menu(void) {
	SiPutsCooperatiu("\r\n\nMenu principal\r\n\0");
	SiPutsCooperatiu("\r\nTria una opcio:\r\n\0");
	SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("1. Nova aposta\r\n\0");
	SiPutsCooperatiu("2. Afegir o retirar fitxes\r\n\0");
	SiPutsCooperatiu("3. Veure estadistiques\r\n\0");
	SiPutsCooperatiu("\r\n");
	SiPutsCooperatiu("Opcio:\r\n");
}

void apostaStringSIO(void) {
	SiPutsCooperatiu("\r\nBenvingut al LSCasino\r\n\0");
	SiPutsCooperatiu("\r\nPrem '*' per retornar al menu principal\r\n\0");
	SiPutsCooperatiu("\r\nPrem '#' per apostar fitxes\r\n\0");
	SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Fitxes disponibles:\r\n\0");
	SiSendChar(fitxes);
		
}

void jugantSIO(void) {
	SiPutsCooperatiu("\r\nJUGANT\r\n\0");
}


void fitxesStringSIO(void) {
	SiPutsCooperatiu("\r\nIntrodueix un valor i prem '#' per afegir fitxes o '*' per retirar fitxes.\r\n\0");
	SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Fitxes:\r\n\0");
	
}

void statsStringSIO(void) {
	SiPutsCooperatiu("\r\n\n\nFitxes actuals: ");
	SiSendChar(fitxes);
    SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Partides guanyades: ");
	SiSendChar(partguanyades);
    SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Partides jugades:");
	SiSendChar(partjugades);
    SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Fitxes guanyades en total: ");
	SiSendChar(fitguanyades);
    SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("Fitxes perdudes en total: ");
	SiSendChar(fitperdudes);
    SiPutsCooperatiu("\r\n\0");
	SiPutsCooperatiu("\n\0");
	
    
}

void jugantLCD(void){
	LcPutString("Jugant - 200 fitxes - 69C");
}

char error(char * valor){
    return -1;
}

void initPropaganda(void){
    //Pre: La sio est� inicialitzada
    Menu();
    timerPropaganda= TiGetTimer();
    state = 0;
	printat=1;
    total=0;
    fitxes++;
    fitxes++;

}


void MotorPropaganda(void) {

	if (TiGetTics(timerPropaganda) > 1000){
        total++;
		if (++timestamp == 10000) timestamp=0;
		TiResetTics(timerPropaganda);
	}	

	switch(state) {
		case 0:
			chars=0;
          
            
			if (opcio==0 && !SiCharAvail() && printat == 0) {
				LcPutString("Menu principal - 200 fitxes - 69C");
				Menu();
				printat=1;
			}
			else if (opcio==0 && SiCharAvail()) {
				opcio=SiGetChar();
				SiSendChar(opcio);
			}
			else if (opcio=='1') {
                timestamp=0;
				LcPutString("Esperant aposta - 200 fitxes - 69C");
				apostaStringSIO();
				state = 2;
				printat=0;
			}
			else if (opcio=='2') {
				LcPutString("Afegint/retirant fitxes - 200 fitxes - 69C");
				fitxesStringSIO();
				state = 3;
				printat=0;
			}
			else if (opcio=='3') {
				LcPutString("Mostrant estadistiques - 200 fitxes - 69C");
                statsStringSIO();
				state = 5;
				printat=0;
			}
		break;
		
		case 2:
            
			if (SiCharAvail() && timestamp < 16) {
				op=SiGetChar();
				
				state = 8;
			}
			else if (timestamp >= 16) {
				//accionaRuleta(RANDOM());
				jugantLCD();
				jugantSIO();
				//audioInici();
				state = 10;
			}else if(timestamp2 != timestamp){
                timestamp2=timestamp;
                myItoa(timestamp);
                SiSendChar('\r');
                SiPutsCooperatiu("[Temps restant ");
                SiPutsCooperatiu(temp);
                SiPutsCooperatiu(" segons]");
            
            }
		break;
		case 3:
			if (SiCharAvail()) {
//				valors[chars]=SiGetChar();			// cal canviarho per un string, array de chars era?
				if (chars==3) {
					op=SiGetChar();
				}
				chars++;
				SiSendChar(op);
				state = 6;
			}
		break;
		
		case 5:
                
			if(timestamp2 != total){
                timestamp2=total;
                myItoa(total);
				//SiSendChar('\r');
                SiPutsCooperatiu("\rTemps del sistema: ");
                SiPutsCooperatiu(temp);
            }else if (SiCharAvail()) {
                state = 0;
                opcio=0;
                SiGetChar();
                //SiPutsCooperatiu("ENTRAAA ");
                
                
			}
			
		break;
		case 6:
			if (error(valors)==-1  &&  chars==4) {
				opcio=0;
				state = 0;
			}
			else if (!error(valors) && chars==4) {
				//operacioStringSIO(valors,op);
				opcio=0;
				//fitxes+-=valors;
				state = 7;
			}
			else if (chars < 4) {
				state = 3;
			}
		break;
		case 7:
			state = 0;
		break;
		case 8:
			if (op == '*') {
				state = 0;
                opcio=0;
			}else if (op == '#') {
				SiPutsCooperatiu("\r\nIntrodueix número de fitxes a apostar::\r\n\0");
                SiPutsCooperatiu("YWEE");

				state = 9;
			}
			else if (op != '*'||op != '#') {
				state = 2;
			}
			
		break;
		case 9:
			if (SiCharAvail()) {
//				valors[chars]=SiGetChar();
				chars++;
				SiSendChar(valors[chars-1]);
				state = 11;
			}
			else if (timestamp>= 16) {
				//accionaRuleta(RANDOM());
				jugantLCD();
				jugantSIO();
				//audioInici();
				state = 10;
			}
		break;
		case 10:
			chars=0;
			//audioDurantGira();
			if (timestamp >= 5) {				// T_ que ha de girar
				//audioFinal();
				//fitxes=apostaAcabadaSIO();
				state = 2;
			}
		break;
		case 11:
			if (chars<3) {
				state = 9;
			}
			else if (!error(valors) && chars == 3) {								// podem fer que error(valor) sigui una funcio que retorni un boolea
				SiPutsCooperatiu("\r\nIntrodueix la cela [0-36 = Individual | 100 - Red | 200 - Black]:\r\n\0");
				chars=0;
				state = 12;
			}
			else if (error(valors) && chars == 3) {
				valors[3]=0;												//esta malament, la idea es borrar tots els valors rebuts
				chars=0;
				state = 13;
			}
		break;
		case 12:
			if (timestamp>= 16) {
				//accionaRuleta(RANDOM());
				jugantLCD();
				jugantSIO();
				//audioInici();
				state = 10;
			}else if (SiCharAvail()) {
//				valors[chars]=SiGetChar();
				chars++;
				SiSendChar(valors[chars-1]);
				state = 14;
			}
		break;
		case 13:
			state = 9;
		break;
		case 14:
			if (chars < 3) {
				state = 12;
			}
			else if (!error(valors) && chars == 3) {
				SiPutsCooperatiu("\r\nS’han apostat 69 fitxes al vermell!! \r\n\0");
				chars=0;
				state = 16;
			}
			else if (error(valors) && chars == 3) {
				chars=0;
				state = 9;
			}
		break;
		case 16:
			if (timestamp>= 16) {
				//accionaRuleta(RANDOM());
				jugantLCD();
				jugantSIO();
				//audioInici();
				state = 10;
			}
		break;
		
	}
}

#define     MAXCOLUMNES 16
static char estatLCD = 0;
const unsigned char cadena[]={"SDM 2013-14     "}; //M�s val que tingui 16 car�cters...
static unsigned char timerLCD, caracterInici, i,j;
static unsigned int mostra;
static unsigned char segonaLinia[MAXCOLUMNES];


void initMotorLCD(void){
    //Pre: El LCD est� inicialitzat
    timerLCD = TiGetTimer();
    caracterInici = 0;
    LcClear();
    //Hi ha caselles de la segona l�nia que sempre valdran el mateix, les preparo!
    segonaLinia[0]='S';
    segonaLinia[1]='W';
    segonaLinia[2]=':';
    segonaLinia[5]=' ';
    segonaLinia[6]='P';
    segonaLinia[7]='B';
    segonaLinia[8]=':';
    segonaLinia[11]=' ';
}


void MotorLCD(void){
    switch (estatLCD){
        case 0:
            LcPutChar(cadena[j++]);
            if (j==16) j= 0;
            if (i++ > MAXCOLUMNES) {
                estatLCD = 1;
                TiResetTics(timerLCD);
                LcGotoXY(0,1);
            }
            break;

        case 1: //Preparo el string
            segonaLinia[3] = getSwitch1()+'0';
            segonaLinia[4] = getSwitch2()+'0';
            segonaLinia[9] = getPB1()+'0';
            segonaLinia[10] = getPB2() + '0';
            estatLCD= 2;
            break;
        case 2: //Aqu� faig l'itoa, que deu trigar una bona estona el pobre...
            mostra = AdGetMostra();
            myItoa(mostra);
            segonaLinia[12]=temp[0];
            segonaLinia[13]=temp[1];
            segonaLinia[14]=temp[2];
            segonaLinia[15]=temp[3];
            estatLCD = 3;
            break;
        case 3:
            if (TiGetTics(timerLCD)>50){
                //Observo que si estresso molt al LCD arriba un punt que alguna
                //vegada pinta malament un car�cter. Deu tenir una cua interna?
                //si la t�, aposto a que �s de 24 posicions (mal n�mero)...
                //Cap problema, donem 50 ms. de calma entre r�fega i r�fega i gas
                TiResetTics(timerLCD);
                i=0;
                estatLCD = 4;
            }
            break;
        case 4:
            LcPutChar(segonaLinia[i++]);
            if (i > MAXCOLUMNES) {
                estatLCD = 5;
                TiResetTics(timerLCD);
            }
            break;
                
        case 5:
            if (TiGetTics(timerLCD)>= 250){
                //Alerta, ja porto 50 ms. des de l'�ltim refresc
                caracterInici++;
                if (caracterInici==16)
                    caracterInici=0;
                estatLCD = 0;
                LcGotoXY(0,0);
                j = caracterInici;
                i=0;
            }
            break;
    }
}