#include "PrTPropaganda.h"


static char state, opcio, printat, chars, guanyem, timerPropaganda = 0;
static char temp[50], op;
static char valors[3] = {'0', '0', '0'};
static char caselles[3] = {'0', '0', '0'};
static char estadistiques[4] = {'0', '0', '0', '0'};

static int fitxes;
static int convertitCas, convertitVal, convertitGuany, casellaGuany, timestamp, timestamp2, total,fitxesguanyades;


void myItoa(int num) {
    //Post: escriu el valor ascii de num a tmp;
    temp[0] = (char) (num / 1000);
    num = num - (temp[0] * 1000);
    temp[1] = (char) (num / 100);
    num = num - (temp[1] * 100);
    temp[2] = (char) (num / 10);
    num = num - (temp[2] * 10);
    temp[3] = num + '0';
    temp[4] = '\0';
    temp[2] += '0';
    temp[1] += '0';
    temp[0] += '0';
}

void myAtoi(char *str, char val) {
    if (val == '0') {
        convertitCas = (str[0] - '0') * 100 + (str[1] - '0') * 10 + (str[2] - '0');
    } else {
        convertitVal = (str[0] - '0') * 100 + (str[1] - '0') * 10 + (str[2] - '0');
    }
}


void Menu(void) {
    SiPutsCooperatiu("\r\n\n\nMenu principal\r\n\0");
    SiPutsCooperatiu("\r\nTria una opcio:\r\n\0");
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("1. Nova aposta\r\n\0");
    SiPutsCooperatiu("2. Afegir o retirar fitxes\r\n\0");
    SiPutsCooperatiu("3. Veure estadistiques\r\n\0");
    SiPutsCooperatiu("\r\n");
    SiPutsCooperatiu("Opcio:\r\n");
}


// FUNCIONS DE PRINTAR STRINGS

void apostaStringSIO(void) {
    SiPutsCooperatiu("\r\n\n\nBenvingut al LSCasino\r\n\0");
    SiPutsCooperatiu("\r\nPrem '*' per retornar al menu principal\r\n\0");
    SiPutsCooperatiu("\r\nPrem '#' per apostar fitxes\r\n\0");
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Fitxes disponibles: ");
    myItoa(fitxes);
    SiPutsCooperatiu(temp);
    //SiSendChar(valors[0]);   Podria passar fitxes a ser un CHAR
    //SiSendChar(valors[1]);
    //SiSendChar(valors[2]);
    SiPutsCooperatiu("\r\n\0");
}

void fitxesStringSIO(void) {
    SiPutsCooperatiu("\r\n\n\nIntrodueix un valor i prem '#' per afegir fitxes o '*' per retirar fitxes.\r\n\0");
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Fitxes:\r\n\0");
}

void statsStringSIO(void) {
    SiPutsCooperatiu("\r\n\n\nPanell d'estadistiques: \n");
    SiPutsCooperatiu("\r\nFitxes actuals: \0");
    // Cal enviar el int de numero de fitxes
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Partides guanyades: \0");
    SiSendChar(estadistiques[0]);
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Partides jugades: \0");
    SiSendChar(estadistiques[1]);
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Fitxes guanyades en total: \0");
    SiSendChar(estadistiques[2]);
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Fitxes perdudes en total: \0");
    SiSendChar(estadistiques[3]);
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("\n\0");
}

void jugantSIO(void) {
    SiPutsCooperatiu("\r\n\nIniciant ruleta...\r\n\0");
}

void jugantLCD(void) {
    LcPutString("Jugant - 200 fitxes - 69C");
}


// FUNCIONS DE CONTROL DE ERRORS

char error() {
    if (op != '*' && op != '#') {
        SiPutsCooperatiu("\nCaracter de operacio erroni\0");
        return -1;
    } else {
        if (op == '*') {
            if (convertitVal > fitxes) {
                SiPutsCooperatiu("\nError! Retirant mes fitxes de les que disposes\0");
                return -1;
            }
        }
        SiPutsCooperatiu("\nOperacio realitzada correctament\0");
        return 1;
    }
}

char errorAposta() {
    if (convertitVal > fitxes) {
        SiPutsCooperatiu("\nError! Apostant mes fitxes de les que disposes\0");
        return -1;
    } else if (convertitCas == 100 || convertitCas == 200 || convertitCas < 37) {
        return 1;
    } else {
        SiPutsCooperatiu("\nError! Casella invalida \0");
        return -1;
    }
}


// MOTOR

void initPropaganda(void) {
    //Pre: La sio esta inicialitzada

    Menu();
    timerPropaganda = TiGetTimer();
    state = 0;

    printat = 1;
    total = 0;

    // Inicializacio variable test
    casellaGuany = 21;
    fitxes = 100;

}

void MotorPropaganda(void) {

    if (TiGetTics(timerPropaganda) > 1000) {                                                                            // Contem un segon
        total++;                                                                                                        // Sumem al temps total de execucio
        if (++timestamp == 10000) timestamp = 0;
        TiResetTics(timerPropaganda);
    }

    switch (state) {
        case 0:
            chars = 0;

            if (opcio == 0 && !SiCharAvail() && printat == 0) {
                LcPutString("Menu principal - 200 fitxes - 69C");
                Menu();
                printat = 1;

            } else if (opcio == 0 && SiCharAvail()) {
                opcio = SiGetChar();
                SiSendChar(opcio);
            } else if (opcio == '1') {
                timestamp = 0;
                LcPutString("Esperant aposta - 200 fitxes - 69C");
                apostaStringSIO();
                state = 2;
                printat = 0;
                convertitGuany = 0;
            } else if (opcio == '2') {
                LcPutString("Afegint/retirant fitxes - 200 fitxes - 69C");
                fitxesStringSIO();
                state = 3;
                printat = 0;
            } else if (opcio == '3') {
                LcPutString("Mostrant estadistiques - 200 fitxes - 69C");
                statsStringSIO();
                state = 5;
                printat = 0;
            }
            break;

        case 2:                                                                                                         // Nova Aposta
            if (SiCharAvail() && timestamp < 16) {
                op = SiGetChar();
                state = 8;
            } else if (timestamp >= 16) {                                                                               // Comença la ruleta
                //accionaRuleta(RANDOM());
                jugantLCD();
                jugantSIO();
                timestamp = 0;
                //audioInici();
                state = 10;
            } else if (timestamp2 != timestamp) {
                timestamp2 = timestamp;
                myItoa(timestamp);
                SiSendChar('\r');
                SiPutsCooperatiu("[Temps restant ");
                SiPutsCooperatiu(temp);
                SiPutsCooperatiu(" segons]");
            }
            break;

        case 3:                                                                                                         // Afegir/Retirar fitxes
            if (SiCharAvail()) {
                if (chars < 3) {
                    valors[chars] = SiGetChar();
                    SiSendChar(valors[chars]);
                } else {
                    op = SiGetChar();
                    SiSendChar(op);
                }
                chars++;
                state = 6;
            }
            break;

        case 5:                                                                                                         // Estadistiques
            if (timestamp2 != total) {
                timestamp2 = total;
                myItoa(total);
                SiPutsCooperatiu("\rTemps del sistema: ");
                SiPutsCooperatiu(temp);
            } else if (SiCharAvail()) {
                state = 0;
                opcio = 0;
                SiGetChar();
            }
            break;

        case 6:                                                                                                         // Afegir/Retirar fitxes
            if (chars < 4) {
                state = 3;
            } else if (chars == 4) {
                SiPutsCooperatiu("\r\n\0");
                myAtoi(valors, '1');
                char err = error();
                if (err == -1) {
                    opcio = 0;
                    state = 0;
                } else if (err != -1) {
                    if (op == '*') {
                        fitxes -= convertitVal;
                    } else {
                        fitxes += convertitVal;
                        if (fitxes > 999) {
                            fitxes = 999;
                        }
                    }
                    opcio = 0;
                    state = 0;
                }
            }
            break;

        case 8:                                                                                                         // Nova Aposta
            if (op == '*') {
                state = 0;
                opcio = 0;
            } else if (op == '#') {
                chars = 0;
                SiPutsCooperatiu("\r\n\n\nIntrodueix numero de fitxes a apostar:\r\n\0");
                state = 9;
            } else if (op != '*' || op != '#') {
                state = 2;
            }
            break;

        case 9:                                                                                                         // Nova Aposta
            if (SiCharAvail()) {
                valors[chars] = SiGetChar();
                SiSendChar(valors[chars]);                                                                              
                chars++;
                state = 11;
            } else if (timestamp >= 16) {
                //accionaRuleta(RANDOM());
                jugantLCD();
                jugantSIO();
                //audioInici();
                timestamp = 0;
                state = 10;
            }
            break;

        case 10:                                                                                                        // Accions ruleta
            chars = 0;
            //audioDurantGira();
            if (timestamp >= 5) {                // T_ que ha de girar
                //audioFinal();
                //fitxes=apostaAcabadaSIO();

                myItoa(casellaGuany);                                                                                   // ERROR----------------------------------
                SiPutsCooperatiu("\r\nLa cela gunyadora es la ");
                SiPutsCooperatiu(temp);                                                                                 // ERROR----------------------------------
                SiPutsCooperatiu(", guanyen les ");
                
                int resultat = casellaGuany % 2;
                
                if (resultat == 0) {
                    SiPutsCooperatiu("Negres\r\n\0");
                } else {
                    SiPutsCooperatiu("Vermelles\r\n\0");
                }
                
                guanyem=0;
                if(casellaGuany==convertitCas){
                    fitxesguanyades=convertitVal*37;
                    guanyem=1;
                }else if((resultat == 0 && convertitCas == 200) || (resultat == 1 && convertitCas == 100)){
                    fitxesguanyades=convertitVal*2;
                    guanyem=1;
                }
                state=7;
            }

            break;
            
        case 7:
            myItoa(convertitVal);                                                                                       // ERROR----------------------------------
                
                if(guanyem==1){            
                    
                    estadistiques[0]++;
                    estadistiques[2]+=fitxesguanyades;
                    fitxes+=fitxesguanyades;
                    if(fitxes > 999) fitxes=999;
                    SiPutsCooperatiu("\r\nFelicitats! Has guanyat ");
                    SiPutsCooperatiu(temp);                                                                             // ERROR----------------------------------
                    SiPutsCooperatiu(" fitxes!\r\n\0");
                }else{
                    SiPutsCooperatiu("\r\nHo sentim, has perdut ");
                    SiPutsCooperatiu(temp);                                                                             // ERROR----------------------------------
                    SiPutsCooperatiu("f itxes!\r\n\0");
                    estadistiques[3]+=convertitVal;                                                                     // Sumem a stats les fitxes perdudes
                }
                estadistiques[1]++;
                
                state = 0;
                opcio = 0;
            break;

        case 11:                                                                                                        // Nova Aposta
            if (chars < 3) {
                state = 9;
            } else if (chars == 3) {
                SiPutsCooperatiu("\r\nIntrodueix la cela [0-36 = Individual | 100 - Red | 200 - Black]:\r\n\0");
                chars = 0;
                state = 12;
            }

            break;

        case 12:                                                                                                        // Nova Aposta
            if (timestamp >= 16) {                                                                                      // Comenca la ruleta
                //accionaRuleta(RANDOM());
                jugantLCD();
                jugantSIO();
                //audioInici();
                timestamp = 0;
                state = 10;
            } else if (SiCharAvail()) {
                caselles[chars] = SiGetChar();
                SiSendChar(caselles[chars]);
                chars++;

                state = 14;
            }
            break;

        case 14:                                                                                                        // Nova Aposta
            if (chars < 3) {
                state = 12;
            } else if (chars == 3) {
                SiPutsCooperatiu("\r\n\0");
                SiPutsCooperatiu("\r\n\0");

                myAtoi(caselles, '0');
                char error = errorAposta();
                if (error == 1) {
                    //myItoa(valors);
                    SiPutsCooperatiu("\r\nHas apostat ");
                    //SiPutsCooperatiu(temp);
                    SiSendChar(valors[0]);                                                                              // ERROR----------------------------------
                    SiSendChar(valors[1]);
                    SiSendChar(valors[2]);
                    
                    int resultat = casellaGuany % 2;
                    if(convertitCas < 37){
                        SiPutsCooperatiu(" fitxes a la casella ");
                        SiPutsCooperatiu(caselles);                                                                     // ERROR----------------------------------
                        SiPutsCooperatiu("!! \r\n\0");    
                    }else if(resultat==0){
                        SiPutsCooperatiu(" fitxes al negre!! \r\n\0");
                    }else if(resultat==1){
                        SiPutsCooperatiu(" fitxes al vermell!! \r\n\0");
                    }
                    
                    myAtoi(valors, '1');
                    fitxes -= convertitVal;                                                                             // Restem les fitxes que hem apostat
                    chars = 0;
                    state = 16;
                } else if (error == -1) {
                    chars = 0;
                    state = 9;
                    SiPutsCooperatiu("\r\n\nIntrodueix numero de fitxes a apostar:\r\n\0");
                }
            }
            break;

        case 16:                                                                                                        // Comenca Ruleta
            if (timestamp >= 16) {
                //accionaRuleta(RANDOM());
                jugantLCD();
                jugantSIO();
                //audioInici();
                state = 10;
                timestamp = 0;
            }
            break;

    }
}

#define     MAXCOLUMNES 16
static char estatLCD,lcdmenu = 0;
static int getLenght[]={34,35,26,43,33};
const unsigned char cadena[] = {"SDM 2013-14     "}; //Mes val que tingui 16 car�cters...
static unsigned char timerLCD, caracterInici, i, j;
static unsigned int mostra;
static unsigned char menuLinia[34]={"Menu Principal - YYY fitxes - XX C"};
static unsigned char esperaLinia[35]={"Esperant aposta - YYY fitxes - XX C"};
static unsigned char jugantLinia[26]={"Jugant - YYY fitxes - XX C"};
static unsigned char afegintLinia[43]={"Afegint/Retirant fitxes - YYY fitxes - XX C"};
static unsigned char statsLinia[33]={"Estadistiques - YYY fitxes - XX C"};

void netejaProgress(void){
	LcGotoXY(0, 1);
	LcPutString("                ");
	LcGotoXY(0, 1);
}

void addProgress(void){
	LcPutChar(0x10);																	// Caracter de casella plena
}

void setMenuLCD(void){
	LcGotoXY(0, 1);

}

void setFitxes(char lcd){
	myItoa(fitxes);
	switch (lcd)
	{
		case 0:
			menuLinia[18]=temp[0];
			menuLinia[19]=temp[1];
			menuLinia[20]=temp[2];
			break;
		case 1:
			esperaLinia[19]=temp[0];
			esperaLinia[20]=temp[1];
			esperaLinia[21]=temp[2];
			break;
		case 2:
			jugantLinia[10]=temp[0];
			jugantLinia[11]=temp[1];
			jugantLinia[12]=temp[2];
			break;
		case 3:
			statsLinia[26]=temp[0];
			statsLinia[27]=temp[1];
			statsLinia[28]=temp[2];
			break;	
		case 4:
			statsLinia[17]=temp[0];
			statsLinia[18]=temp[1];
			statsLinia[19]=temp[2];
			break;		
	}

}

void setTemp(char lcd){
	//myItoa(fitxes);
	switch (lcd)
	{
		case 0:
			menuLinia[30]='2';
			menuLinia[31]='2';
			break;
		case 1:
			esperaLinia[32]='2';
			esperaLinia[33]='2';
			break;
		case 2:
			jugantLinia[22]='2';
			jugantLinia[23]='2';
			break;
		case 3:
			statsLinia[40]='2';
			statsLinia[41]='2';
			break;	
		case 4:
			statsLinia[30]='2';
			statsLinia[31]='2';
			break;		
	}

}


void initMotorLCD(void) {
    //Pre: El LCD est� inicialitzat
    timerLCD = TiGetTimer();
	lcdmenu=0;
    caracterInici = 0;
    LcClear();
    
}

void PosaChar(char lcd){
	switch (estatLCD) {
        case 0:							//Menu
            LcPutChar(menuLinia[j++]);
            if (j == 34) j = 0;
            break;

		case 1:							//Esperant
            LcPutChar(esperaLinia[j++]);
            if (j == 35) j = 0;
            break;

		case 2:							//Jugant
            LcPutChar(jugantLinia[j++]);
            if (j == 26) j = 0;
            break;

		case 3:							//Afegint retirant
            LcPutChar(afegintLinia[j++]);
            if (j == 43) j = 0;
            break;

		case 4:							//Stats
            LcPutChar(statsLinia[j++]);
            if (j == 33) j = 0;
            break;			
	}

	if (i++ > MAXCOLUMNES) {
		estatLCD = 1;
		TiResetTics(timerLCD);
		LcGotoXY(0, 1);
    }		
}

void MotorLCD(void) {
    switch (estatLCD) {
        case 0:							//Menu
			PosaChar(lcdmenu);
            break;

        case 1: //Preparo el string
            setFitxes(lcdmenu);
            estatLCD = 2;
            break;

        case 2: //Aqui faig l'itoa, que deu trigar una bona estona el pobre...
            setTemp(lcdmenu);
            estatLCD = 3;
            break;

        case 3:
            if (TiGetTics(timerLCD) > 50) {
                //Observo que si estresso molt al LCD arriba un punt que alguna
                //vegada pinta malament un car�cter. Deu tenir una cua interna?
                //si la t�, aposto a que �s de 24 posicions (mal n�mero)...
                //Cap problema, donem 50 ms. de calma entre r�fega i r�fega i gas
                TiResetTics(timerLCD);
                i = 0;
                estatLCD = 4;
            }
            break;

        case 4:
            if (TiGetTics(timerLCD) >= 250) {
                //Alerta, ja porto 50 ms. des de l'�ltim refresc
                caracterInici++;
                if (caracterInici == getLenght[lcdmenu])
                    caracterInici = 0;
                estatLCD = 0;
                LcGotoXY(0, 0);
                j = caracterInici;
                i = 0;
            }
            break;
    }
}
