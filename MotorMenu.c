#include "PrTPropaganda.h"


static char state, opcio, printat, chars, guanyem, timerPropaganda, lcdmenu, conta = 0;
static char temp[5], op, fitxestemp[3], celatemp[3];
static char casella[3],printafit[5];
static char valors[3] = {'0', '0', '0'};
static char estadistiques0[3], estadistiques1[3], estadistiques2[3], estadistiques3[3];
static int estadistiques[4];
static int fitxes;
static int convertitCas, convertitVal, casellaGuany, timestamp, timestamp2, total, fitxesguanyades;


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

void randomNumber(void){
    casellaGuany = (rand()+ total) % 37;
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
    SiPutsCooperatiu(fitxestemp);
    SiPutsCooperatiu("\r\n\0");
}

void fitxesStringSIO(void) {
    SiPutsCooperatiu("\r\n\n\nIntrodueix un valor i prem '#' per afegir fitxes o '*' per retirar fitxes.\r\n\0");
    SiPutsCooperatiu("\r\n\0");
    SiPutsCooperatiu("Fitxes:\r\n\0");
}

void statsStringSIO(void) {

    SiPuts("\r\n\n\nPanell d'estadistiques: \n");
    SiPuts("\r\nFitxes actuals: \0");
    SiPuts(fitxestemp);

    myItoa(estadistiques[0]);
    cstringcpy(temp, estadistiques0);

    SiPuts("\r\n\0");
    SiPuts("Partides guanyades: \0");
    SiPuts(estadistiques0);


    myItoa(estadistiques[1]);
    cstringcpy(temp, estadistiques1);

    SiPuts("\r\n\0");
    SiPuts("Partides jugades: \0");
    SiPuts(estadistiques1);

    myItoa(estadistiques[2]);
    cstringcpy(temp, estadistiques2);

    SiPuts("\r\n\0");
    SiPuts("Fitxes guanyades en total: \0");
    SiPuts(estadistiques2);

    myItoa(estadistiques[3]);
    cstringcpy(temp, estadistiques3);

    SiPuts("\r\n\0");
    SiPuts("Fitxes perdudes en total: \0");
    SiPuts(estadistiques3);

    SiPuts("\r\n\0");
    SiPuts("\n\0");


}

void jugantSIO(void) {
    SiPutsCooperatiu("\r\n\nIniciant ruleta...\r\n\0");
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

    estadistiques[0] = 0;
    estadistiques[1] = 0;
    estadistiques[2] = 0;
    estadistiques[3] = 0;

    
    
    // Inicializacio variable test
    //casellaGuany = 21;
    randomNumber();
    fitxes = 100;

}

void MotorPropaganda(void) {
     
    if (TiGetTics(timerPropaganda) > 2000) {                                                                            // Contem un segon
        total++;                                                                                                        // Sumem al temps total de execucio
        if (++timestamp == 10000) timestamp = 0;
        TiResetTics(timerPropaganda);
        
        
        
        /*char* temperatura = (char*)GetTemperature();
        SiPuts(temperatura);
        SiSendChar('\n');
        SiSendChar('\n\r');*/
       
    }

    switch (state) {
        case 0:
            chars = 0;
            
            if (opcio == 0 && !SiCharAvail() && printat == 0 &&  !CharAvaliablet()) {
                
                lcdmenu = 0;
                Menu();
                netejaProgress();
                printat = 1;

            } else if (opcio == 0  ) {
                if(SiCharAvail()){
                    opcio= SiGetChar();
                    SiSendChar(opcio);
                }else if(CharAvaliablet()){
                    opcio = GetNumerot();
                    SiSendChar(opcio);
                }
                

            } else if (opcio == '1') {
                randomNumber();
                timestamp = 0;
                guanyem = 2;
                lcdmenu = 1;
                netejaProgress();
                apostaStringSIO();
                state = 2;
                printat = 0;
                

            } else if (opcio == '2') {
                
                lcdmenu = 3;
                netejaProgress();
                fitxesStringSIO();
                state = 3;
                printat = 0;
            } else if (opcio == '3') {
                
                lcdmenu = 4;
                netejaProgress();
                
                statsStringSIO();
                //SiGetChar();
                //GetNumerot();
                state = 5;
                printat = 0;
            } else{
                lcdmenu = 0;
            }
            break;

        case 2:                                                                                                         // Nova Aposta
            if ( timestamp < 16 && (SiCharAvail() || CharAvaliablet())) {
                if(SiCharAvail()){
                    op = SiGetChar();
                    state = 8;
                }else if(CharAvaliablet()){
                    op = GetNumerot();
                    state = 8;
                }
                
            } else if (timestamp >= 16) {                                                                               // Comença la ruleta
                comencaRuleta();
                
            } else if (timestamp2 != timestamp) {
                timestamp2 = timestamp;
                myItoa(16-timestamp);
                SiSendChar('\r');
                SiPutsCooperatiu("[Temps restant ");
                SiPutsCooperatiu(temp);
                SiPutsCooperatiu(" segons]");
                addProgress();
            }
            break;

        case 3:                                                                                                         // Afegir/Retirar fitxes
            if ( CharAvaliablet()) {
                if (chars < 3) {
                    valors[chars] = GetNumerot();//SiGetChar();
                    SiSendChar(valors[chars]);
                } else {
                    op = GetNumerot();//SiGetChar();
                    SiSendChar(op);
                }
                chars++;
                state = 6;
            }else if (SiCharAvail()) {
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
            } else if (CharAvaliablet()) {
                state = 0;
                opcio = 0;
                GetNumerot();
            }else if (SiCharAvail()) {
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
            if (CharAvaliablet()) {
                valors[chars] = GetNumerot();
                SiSendChar(valors[chars]);
                chars++;
                state = 11;
            } else if (SiCharAvail()) {
                valors[chars] = SiGetChar();
                SiSendChar(valors[chars]);
                chars++;
                state = 11;
            } 
            else if (timestamp >= 16) {
                comencaRuleta();
            }
            break;

        case 10:                                                                                                        // Accions ruleta
            chars = 0;
            
            if (timestamp >= 5) {                                                                                       // T_ que ha de girar

                myItoa(casellaGuany);

                SiPuts("\r\nLa cela gunyadora es la ");
                SiPuts(temp);
                SiPuts(", guanyen les ");

                int resultat = casellaGuany % 2;

                if (resultat == 0) {
                    SiPuts("Negres\r\n\0");
                } else {
                    SiPuts("Vermelles\r\n\0");
                }

                
                if (casellaGuany == convertitCas) {
                    audioFinalGuany();
                    fitxesguanyades = convertitVal * 37;
                    guanyem = 1;
                } else if ((resultat == 0 && convertitCas == 200) || (resultat == 1 && convertitCas == 100)) {
                    audioFinalGuany();
                    fitxesguanyades = convertitVal * 2;
                    guanyem = 1;
                }else{
                    
                    audioFinalPerd();
                }
                      
                state = 7;
            } else {
                audioDurant();          //posara un char a 1, per tant no tornara a comencar cada cop q sexecuti aqueta funcio, quan acabi de reproduirse es posa a 0
                myItoa(casellaGuany);
                cstringcpy(temp, celatemp);
            }

            break;

        case 7:
            myItoa(convertitVal);
            cstringcpy(temp, printafit);
           
            if (guanyem == 1) {

                estadistiques[0]++;
                estadistiques[2] += fitxesguanyades-convertitVal;

                fitxes += fitxesguanyades;

                if (fitxes > 999) fitxes = 999;
                SiPutsCooperatiu("\r\nFelicitats! Has guanyat ");
                SiPutsCooperatiu(printafit);
                SiPutsCooperatiu(" fitxes!\r\n\0");
                estadistiques[1]++;
            } else if (guanyem == 0){
                SiPutsCooperatiu("\r\nHo sentim, has perdut ");
                SiPutsCooperatiu(printafit);
                SiPutsCooperatiu(" fitxes!\r\n\0");
                estadistiques[3] += convertitVal;                                                                       // Sumem a stats les fitxes perdudes
                estadistiques[1]++;
            }
            


            state = 0;
            opcio = 0;
            break;

        case 11:                                                                                                        // Nova Aposta
            if (chars < 3) {
                
                state = 9;
            } else if (chars == 3) {
                myAtoi(valors, '1');
                SiPutsCooperatiu("\r\nIntrodueix la cela [0-36 = Individual | 100 - Red | 200 - Black]:\r\n\0");
                chars = 0;
                state = 12;
            }

            break;

        case 12:                                                                                                        // Nova Aposta
            if (timestamp >=
                16) {                                                                                                   // Comenca la ruleta
                comencaRuleta();
            } else if (CharAvaliablet()) {
                casella[chars] = GetNumerot();
                SiSendChar(casella[chars]);
                chars++;

                state = 14;
            }else if (SiCharAvail()) {
                casella[chars] = SiGetChar();
                SiSendChar(casella[chars]);
                chars++;

                state = 14;
            }
            break;

        case 14:                                                                                                        // Nova Aposta
            if (chars < 3) {
                state = 12;
            } else if (chars == 3) {
                SiPuts("\r\n\0");
                SiPuts("\r\n\0");

                myAtoi(casella, '0');
                char error = errorAposta();
                if (error == 1) {
                    guanyem = 0;
                    SiPuts("\r\nHas apostat ");
                    SiPuts(valors);

                    //int resultat = convertitCas % 2;
                    if (convertitCas < 37) {
                        SiPuts(" fitxes a la casella ");
                        SiSendChar(casella[0]);
                        SiSendChar(casella[1]);
                        SiSendChar(casella[2]);
                        SiPuts("!! \r\n\0");

                    } else if (convertitCas == 200) {
                        SiPuts(" fitxes al negre!! \r\n\0");
                    } else if (convertitCas == 100) {
                        SiPuts(" fitxes al vermell!! \r\n\0");
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
                comencaRuleta();
            } else if (timestamp2 != timestamp) {
                timestamp2 = timestamp;
                myItoa(16-timestamp);
                SiSendChar('\r');
                SiPutsCooperatiu("[Temps restant ");
                SiPutsCooperatiu(temp);
                SiPutsCooperatiu(" segons]");

                while (timestamp != conta) {
                    addProgress();
                }
            }
            break;

    }
}

#define     MAXCOLUMNES 16
static char estatLCD = 0;
static int getLenght[] = {36, 37, 28, 45, 35};
static unsigned char timerLCD, caracterInici, i, j;
static unsigned char menuLinia[36] = {"Menu Principal - YYY fitxes - XX C  "};
static unsigned char esperaLinia[37] = {"Esperant aposta - YYY fitxes - XX C  "};
static unsigned char jugantLinia[28] = {"Jugant - YYY fitxes - XX C  "};
static unsigned char afegintLinia[45] = {"Afegint/Retirant fitxes - YYY fitxes - XX C  "};
static unsigned char statsLinia[35] = {"Estadistiques - YYY fitxes - XX C  "};

void netejaProgress(void) {
    LcGotoXY(0, 1);
    LcPutString("                ");
    LcGotoXY(0, 1);
    conta = 0;
}

void addProgress(void) {
    LcGotoXY(conta, 1);
    LcPutChar('X');                                                                    // Caracter de casella plena
    conta++;
}


void setFitxes(char lcd) {
    myItoa(fitxes);
    cstringcpy(temp, fitxestemp);

    switch (lcd) {
        case 0:
            menuLinia[17] = temp[1];
            menuLinia[18] = temp[2];
            menuLinia[19] = temp[3];
            break;
        case 1:
            esperaLinia[18] = temp[1];
            esperaLinia[19] = temp[2];
            esperaLinia[20] = temp[3];
            break;
        case 2:
            jugantLinia[9] = temp[1];
            jugantLinia[10] = temp[2];
            jugantLinia[11] = temp[3];
            break;
        case 3:
            afegintLinia[26] = temp[1];
            afegintLinia[27] = temp[2];
            afegintLinia[28] = temp[3];
            break;
        case 4:
            statsLinia[16] = temp[1];
            statsLinia[17] = temp[2];
            statsLinia[18] = temp[3];
            break;
    }

}

void setTemp(char lcd) {
    char* temperatura = (char*)GetTemperature();
    
    switch (lcd) {
        case 0:
            menuLinia[30] = temperatura[2];
            menuLinia[31] = temperatura[3];
            break;
        case 1:
            esperaLinia[31] = temperatura[2];
            esperaLinia[32] = temperatura[3];
            break;
        case 2:
            jugantLinia[22] = temperatura[2];
            jugantLinia[23] = temperatura[3];
            break;
        case 3:
            afegintLinia[39] = temperatura[2];
            afegintLinia[40] = temperatura[3];
            break;
        case 4:
            statsLinia[29] = temperatura[2];
            statsLinia[30] = temperatura[3];
            break;
    }

}

void cstringcpy(char *src, char *dest) {
    while (*src) {
        *(dest++) = *(src++);
    }
    *dest = '\0';
}

void comencaRuleta(){
    novaTirada(casellaGuany);
    //accionaRuleta(RANDOM());
    jugantSIO();
    netejaProgress();
    lcdmenu = 2;
    audioInicial();
    timestamp = 0;
    state = 10;
}

void initMotorLCD(void) {
    //Pre: El LCD esta inicialitzat
    timerLCD = TiGetTimer();
    caracterInici = 0;
    LcClear();

}

void PosaChar(char lcd) {
    switch (lcd) {
        case 0:                            //Menu
            LcPutChar(menuLinia[j++]);
            //netejaProgress();
            if (j == 36) j = 0;
            break;

        case 1:                            //Esperant
            LcPutChar(esperaLinia[j++]);            
            if (j == 37) j = 0;
            break;

        case 2:                            //Jugant
            LcPutChar(jugantLinia[j++]);
            //netejaProgress();
            if (j == 28) j = 0;
            break;

        case 3:                            //Afegint retirant
            LcPutChar(afegintLinia[j++]);
            //netejaProgress();
            
            if (j == 45) j = 0;
            break;

        case 4:                            //Stats
            LcPutChar(statsLinia[j++]);
            //netejaProgress();
            if (j == 35) j = 0;
            break;
    }

    if (i++ > MAXCOLUMNES) {
        estatLCD = 1;
        TiResetTics(timerLCD);
        LcGotoXY(0, 0);
    }
}

void MotorLCD(void) {
    switch (estatLCD) {
        case 0:                            //Menu
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
            if (TiGetTics(timerLCD) > 200) {
                TiResetTics(timerLCD);
                i = 0;
                estatLCD = 4;
            }
            break;

        case 4:
            if (TiGetTics(timerLCD) >= 1400) {
                //Alerta, ja porto 50 ms. des de l'?ltim refresc
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
