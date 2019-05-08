
void audioFinal(){
    estatt=0;
    melodia=2;
    cantat=0;
    TiResetTics(timerTemps);
    changeAudioStatus();
    frequencia=0;
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
