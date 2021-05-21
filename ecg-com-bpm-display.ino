#include "Adafruit_GFX.h"       // Adafruit graphics library
#include "Adafruit_ST7735.h"    // Adafruit ST7735 display library
#include "SPI.h"                // Arduino SPI library 

using namespace std;

#define TFT_RST  4              //D4 - reset line
#define TFT_CS   8              //D8 - chip select line
#define TFT_DC   7              //D7 - data/command line
#define TFT_SCLK  12
#define MOSI  11

// inverted color definitions
#define BLACK   0xFFFF
#define WHITE   0x0000
#define BLUE    0x07FF
#define RED     0xFFE0 
#define GREEN   0xF81F
#define CYAN    0xFFE0
#define MAGENTA 0x07E0
#define YELLOW  0xF800 
#define ORANGE  0xFE00  
#define POISON  0x68FF

int colunaStart=160, linhaStart=40, linhaFim=0;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, MOSI, TFT_SCLK, TFT_RST);

int bpm = 0;
int count = 0;  //timer start
int countEnd = 2950;  //timer end, equivale a aproximadamente 60 segundos
int ondaR = 400;  //pico mais algo do pulso

int x0, xt, ye;
void graficoBox();


void setup() 
{
   Serial.begin(9600); //9600   
   pinMode(PD5, INPUT); // Configuração para detecção de derivações LO+
   pinMode(PD6, INPUT); // Configuração para detecção de leads off LO-

  tft.initR(INITR_MINI160x80);    // INITR_BLACKTAB  - INITR_MINI160x80  initialize ST7735S TFT display
  tft.setRotation(3);             //Rotação do lcd
  tft.fillScreen(BLACK); 
  

}


void loop() {
  graficoBox();
    tft.setTextColor(RED);

    if((digitalRead(PD6) == 1) || (digitalRead(PD5) == 1)){
     Serial.println(0);  
  }else{
    Serial.println(analogRead(A0));
    tft.drawLine(colunaStart, linhaStart, colunaStart-2, (analogRead(A0)/9), RED); //col start - line start, col end,line end
    linhaStart = analogRead(A0)/9;
    colunaStart = colunaStart - 2;

    if(colunaStart == 0) { 
      colunaStart = 160;

      tft.fillRect(0, 0, 160, 39, BLACK);
      tft.fillRect(0, 41, 160, 80, BLACK);
     }

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
  
  delay(20); //intervalo de 20 milissegundos entre as leituras
}

void graficoBox() {
  tft.setTextColor(RED);
  for(x0=0; x0<=160; x0++)
  {
    tft.setCursor(x0, 40);
    tft.drawPixel(x0, 40, WHITE);
  }

  for(xt=0; xt<=160; xt++) 
  {
    tft.setCursor(xt, 79);
    tft.drawPixel(xt, 79, WHITE);
  }

  for(ye=0; ye<=80; ye++)
  {
    tft.setCursor(159, ye);
    tft.drawPixel(159, ye, WHITE);
  }
}
