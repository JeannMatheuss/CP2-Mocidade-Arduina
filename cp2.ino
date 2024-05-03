#include "DHT.h"
#include <LiquidCrystal.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
 
#define DHTPIN 2
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);
 
String cor;
const int rs = 7;
const int en = 6;  
const int d4 = 12;  
const int d5 = 10;  
const int d6 = 9;    
const int d7 = 8;
 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
int azul = 3;
int verde = 11;
int vermelho = 5;
int LDR = A0;
int valorLDR = 0;
int intensidadeLuz;
int buzzer = 13;
 
int tempo = 150;
 
// logo da equipe
byte LOGO1[8] = { B00000, B00001, B00001, B00001, B00001, B00001, B00000, B00000 };
byte LOGO2[8] = { B00000, B10000, B01000, B10100, B11011, B11000, B10000, B10000 };
byte LOGO3[8] = { B00000, B00001, B00010, B00101, B11011, B00011, B00001, B00001 };
byte LOGO4[8] = { B00000, B10000, B10000, B10000, B10000, B10000, B00000, B00000 };
byte LOGO5[8] = { B00001, B00001, B00000, B00001, B00000, B00000, B00000, B00000 };
byte LOGO6[8] = { B00100, B10000, B00000, B10000, B01000, B10100, B00011, B00001 };
byte LOGO7[8] = { B00100, B00001, B00000, B00001, B00010, B00101, B11000, B10000 };
byte LOGO8[8] = { B10000, B10000, B00000, B10000, B00000, B00000, B00000, B00000 };
 
const unsigned long intervaloEvento = 2000;
unsigned long tempoPrevio = 0;
int estadoDisplay = 0;
 
void setup() {
  Serial.begin(9600);
 
  dht.begin();
  lcd.begin(16,2);
 
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(LDR, INPUT);
  digitalWrite(LDR, LOW);
  pinMode(buzzer, OUTPUT);
 
  // Logo da equipe
  lcd.createChar(1, LOGO1);
  lcd.createChar(2, LOGO2);
  lcd.createChar(3, LOGO3);
  lcd.createChar(4, LOGO4);
  lcd.createChar(5, LOGO5);
  lcd.createChar(6, LOGO6);
  lcd.createChar(7, LOGO7);
  lcd.createChar(8, LOGO8);
 
  // iniciando o sistema
  lcd.clear();
  lcd.print("    L");
  delay(200);
  lcd.clear();
  lcd.print("    LO");
  delay(200);
  lcd.clear();
  lcd.print("    LOA");
  delay(200);
  lcd.clear();
  lcd.print("    LOAD");
  delay(200);
  lcd.clear();
  lcd.print("    LOADIN");
  delay(200);
  lcd.clear();
  lcd.print("    LOADING");
  lcd.setCursor(0, 1);
  lcd.print("      .");
  delay(200);
  lcd.clear();
  lcd.print("    LOADING");
  lcd.setCursor(0, 1);
  lcd.print("      ..");
  delay(200);
  lcd.clear();
  lcd.print("    LOADING");
  lcd.setCursor(0, 1);
  lcd.print("      ...");
  delay(3000);
  // mostra a logo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(0, 1);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
  lcd.write(8);
  lcd.setCursor(5, 0);
  lcd.print("MOCIDADE");
  lcd.setCursor(5, 1);
  lcd.print("ARDUINA");
  delay(5000);
 
}
 
void loop() {
 
  if(Serial.available()){
    cor = Serial.readString();
    Serial.println(cor);
  }
  unsigned long tempoAtual = millis();
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
 
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println(F("Houve uma falha ao ler o sensor DHT!"));
    return;
  }
 
  int numeroLeituras = 10;
  int sensorSoma = 0;
 
  for (int i = 0; i < numeroLeituras; i++) {
    valorLDR = analogRead(LDR);
    intensidadeLuz = map(valorLDR, 0, 990, 0, 100);
    sensorSoma += intensidadeLuz;
    delay(1);
  }
  int sensorMedia = sensorSoma / numeroLeituras;
 
 
  if (tempoAtual - tempoPrevio >= intervaloEvento) {
    switch (estadoDisplay) {
      case 0:
        Luz(sensorMedia);
        estadoDisplay = 1;
        break;
      case 1:
        Umidade(umidade);
        estadoDisplay = 2;
        break;
      case 2:
        Temperatura(temperatura);
        estadoDisplay = 0;
        break;
    }
 
    Serial.print(F("Temperatura: "));
    Serial.print(temperatura);
    Serial.print(F("°C Umidade: "));
    Serial.print(umidade);
    Serial.println(F("%"));
    Serial.print("Intensidade de Luz 0 - 1023 = ");
    Serial.println(valorLDR);
    Serial.print("Intensidade de Luz 0 - 100% = ");
    Serial.println(sensorMedia);
    Serial.println("---------------------------------");
 
    tempoPrevio = tempoAtual;
  }
}
 
void Verde() //Void para ligar o led RGB na cor Verde
{
  analogWrite(vermelho, 0);
  analogWrite(verde, 255);
  analogWrite(azul, 0);
}
 
void Vermelho() //Void para ligar o led RGB na cor Vermelha
{
  analogWrite(vermelho, 255);
  analogWrite(verde, 0);
  analogWrite(azul, 0);
}
 
void Amarelo() //Void para ligar o led RGB na cor Amarela
{
  analogWrite(vermelho, 255);
  analogWrite(verde, 255);
  analogWrite(azul, 0);
}
 
void Luz(int sensorMedia) {
  lcd.clear();
 
  if (sensorMedia >= 40 && sensorMedia <= 80) {
    Amarelo();
    tone(buzzer, 2000, 1000);
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
    delay(5000);
  } else if (sensorMedia < 40) {
    lcd.setCursor(0,0);
    Verde();
    lcd.print("Ambiente com");
    lcd.setCursor(0,1);
    lcd.print("luz baixa");
    delay(5000);
  } else {
    Vermelho();
    tone(buzzer, 2000, 5000);
    lcd.setCursor(0,0);
    lcd.print("Ambiente muito");
    lcd.setCursor(0,1);
    lcd.print("claro");
    delay(5000);
  }
}
 
void Umidade(float umidade) {
  lcd.clear();
 
  if (umidade >= 50 && umidade <= 70) {
    Verde();
    lcd.setCursor(0,0);
    lcd.print("Umidade OK");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  } else if (umidade < 50) {
    Vermelho();
    tone(buzzer, 2000, 5000);
    lcd.setCursor(0,0);
    lcd.print("Umidade BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  } else {
    Vermelho();
    tone(buzzer, 2000, 5000);
    lcd.setCursor(0,0);
    lcd.print("Umidade ALTA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  }
}
 
void Temperatura(float temperatura) {
  lcd.clear();
 
  if (temperatura >= 10 && temperatura <= 15) {
    Verde();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223);
    lcd.print("C");
    delay(5000);
  } else if (temperatura < 10) {
    Amarelo();
    tone(buzzer, 2000, 5000);
    lcd.setCursor(0,0);
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223);
    lcd.print("C");
    delay(5000);
  } else {  
    Amarelo();
    tone(buzzer, 2000, 5000);
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223);
    lcd.print("C");
    delay(5000);
  }
}