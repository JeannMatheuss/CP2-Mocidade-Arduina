#include "DHT.h" // Inclui a biblioteca para o sensor DHT
#include <LiquidCrystal.h> // Inclui a biblioteca para controle do display LCD
#include <FastLED.h> // Inclui a biblioteca para controle do LED RGB
#include <Adafruit_NeoPixel.h> // Inclui a biblioteca para controle de LEDs RGB (não utilizada diretamente no código)

#define DHTPIN 2 // Define o pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT11 // Define o tipo de sensor como DHT11

DHT dht(DHTPIN, DHTTYPE); // Instancia um objeto do tipo DHT

String cor; // Variável para armazenar a cor definida via comunicação serial
const int rs = 7;
const int en = 6;  
const int d4 = 12;  
const int d5 = 10;  
const int d6 = 9;    
const int d7 = 8;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Instancia um objeto do tipo LiquidCrystal para controle do display LCD

int azul = 3;
int verde = 11;
int vermelho = 5;
int LDR = A0; // Define o pino ao qual o sensor LDR está conectado
int valorLDR = 0;
int intensidadeLuz;
int buzzer = 13;

int tempo = 150; // Variável de tempo

// Logo da equipe
byte LOGO1[8] = { B00000, B00001, B00001, B00001, B00001, B00001, B00000, B00000 };
byte LOGO2[8] = { B00000, B10000, B01000, B10100, B11011, B11000, B10000, B10000 };
byte LOGO3[8] = { B00000, B00001, B00010, B00101, B11011, B00011, B00001, B00001 };
byte LOGO4[8] = { B00000, B10000, B10000, B10000, B10000, B10000, B00000, B00000 };
byte LOGO5[8] = { B00001, B00001, B00000, B00001, B00000, B00000, B00000, B00000 };
byte LOGO6[8] = { B00100, B10000, B00000, B10000, B01000, B10100, B00011, B00001 };
byte LOGO7[8] = { B00100, B00001, B00000, B00001, B00010, B00101, B11000, B10000 };
byte LOGO8[8] = { B10000, B10000, B00000, B10000, B00000, B00000, B00000, B00000 };

const unsigned long intervaloEvento = 2000; // Intervalo de tempo para atualização das leituras
unsigned long tempoPrevio = 0;
int estadoDisplay = 0; // Variável de controle do estado do display

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial

  dht.begin(); // Inicia o sensor DHT
  lcd.begin(16,2); // Inicia o display LCD com 16 colunas e 2 linhas

  pinMode(azul, OUTPUT); // Define os pinos do LED RGB como saída
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(LDR, INPUT); // Define o pino do sensor LDR como entrada
  digitalWrite(LDR, LOW); // Desliga o sensor LDR
  pinMode(buzzer, OUTPUT); // Define o pino do buzzer como saída

  // Logo da equipe
  lcd.createChar(1, LOGO1);
  lcd.createChar(2, LOGO2);
  lcd.createChar(3, LOGO3);
  lcd.createChar(4, LOGO4);
  lcd.createChar(5, LOGO5);
  lcd.createChar(6, LOGO6);
  lcd.createChar(7, LOGO7);
  lcd.createChar(8, LOGO8);

  // Inicialização do sistema
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
  // Mostra a logo
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
  // Verifica se há dados disponíveis na porta serial
  if(Serial.available()){
    cor = Serial.readString(); // Lê a cor definida via comunicação serial
    Serial.println(cor); // Imprime a cor lida
  }

  unsigned long tempoAtual = millis(); // Obtém o tempo atual em milissegundos
  float temperatura = dht.readTemperature(); // Lê a temperatura do sensor DHT
  float umidade = dht.readHumidity(); // Lê a umidade do sensor DHT

  // Verifica se houve falha ao ler os sensores DHT
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println(F("Houve uma falha ao ler o sensor DHT!"));
    return;
  }

  int numeroLeituras = 10;
  int sensorSoma = 0;

  // Realiza múltiplas leituras do sensor LDR e calcula a média
  for (int i = 0; i < numeroLeituras; i++) {
    valorLDR = analogRead(LDR);
    intensidadeLuz = map(valorLDR, 0, 990, 0, 100);
    sensorSoma += intensidadeLuz;
    delay(1);
  }
  int sensorMedia = sensorSoma / numeroLeituras;

  // Verifica se é hora de atualizar o display
  if (tempoAtual - tempoPrevio >= intervaloEvento) {
    switch (estadoDisplay) {
      case 0:
        Luz(sensorMedia); // Chama a função Luz passando a média de intensidade de luz
        estadoDisplay = 1;
        break;
      case 1:
        Umidade(umidade); // Chama a função Umidade passando o valor da umidade
        estadoDisplay = 2;
        break;
      case 2:
        Temperatura(temperatura); // Chama a função Temperatura passando o valor da temperatura
        estadoDisplay = 0;
        break;
    }

    // Imprime as leituras dos sensores e a intensidade de luz
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

    tempoPrevio = tempoAtual; // Atualiza o tempo anterior
  }
}

// Função para configurar o LED RGB na cor Verde
void Verde() {
  analogWrite(vermelho, 0);
  analogWrite(verde, 255);
  analogWrite(azul, 0);
}

// Função para configurar o LED RGB na cor Vermelha
void Vermelho() {
  analogWrite(vermelho, 255);
  analogWrite(verde, 0);
  analogWrite(azul, 0);
}

// Função para configurar o LED RGB na cor Amarela
void Amarelo() {
  analogWrite(vermelho, 255);
  analogWrite(verde, 255);
  analogWrite(azul, 0);
}

// Função para exibir informações de luz no display LCD
void Luz(int sensorMedia) {
  lcd.clear();

  // Verifica a intensidade de luz e exibe a mensagem correspondente
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

// Função para exibir informações de umidade no display LCD
void Umidade(float umidade) {
  lcd.clear();

  // Verifica a umidade e exibe a mensagem correspondente
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

// Função para exibir informações de temperatura no display LCD
void Temperatura(float temperatura) {
  lcd.clear();

  // Verifica a temperatura e exibe a mensagem correspondente 
  if (temperatura >= 10 && temperatura <= 15) {
    Verde();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223); // Exibe o símbolo de grau Celsius
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
    lcd.print((char)223); // Exibe o símbolo de grau Celsius
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
    lcd.print((char)223); // Exibe o símbolo de grau Celsius
    lcd.print("C");
    delay(5000);
  }
}
