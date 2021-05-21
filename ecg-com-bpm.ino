int bpm = 0;
int count = 0;  //timer start
int countEnd = 2950;  //timer end, equivale a aproximadamente 60 segundos
int ondaR = 400;  //pico mais algo do pulso

void setup() 
{
   Serial.begin(9600); //9600   
   pinMode(PD5, INPUT); // Configuração para detecção de derivações LO+
   pinMode(PD6, INPUT); // Configuração para detecção de leads off LO-
}

void loop() {

    if((digitalRead(PD6) == 1) || (digitalRead(PD5) == 1)){
     Serial.println(0);  
  }else{
    Serial.println(analogRead(A0));
    
    if(analogRead(A0) >= ondaR) {
      bpm = bpm + 1;
    }
  }

  if (count == countEnd) {
    Serial.print("BPM: ");
    Serial.println(bpm);
    count = 0;  //restaura timer
    delay(1000);
    exit(0);  //Finaliza teste ECG
  }

  
  count = count + 1;
  delay(20); //intervalo de 20 milissegundos entre as leituras

}
