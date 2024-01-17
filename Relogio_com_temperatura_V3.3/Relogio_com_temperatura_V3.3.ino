/***************************************\
 **                                     **
 **   Relogio completo com termometro   **
 **             usando RTC              **
 **      Primeira grande montagem       **
 **                                     **
 \***************************************/


// carregando biblioteca para display e RTC
#include <LiquidCrystal.h>
#include "Wire.h"

// definindo o endereco I2C para o RTC
#define DS1307_ADDRESS 0x68

// especifica as portas para uso no display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// definindo a variavel para zerar o contador do RTC
byte zero = 0x00; //workaround for issue #527

// definindo variaveis numericas inteiras
// hora e calendario
int ajusteSegundo = 0;
int ajusteMinuto = -1;
int ajusteHora = -1;
int ajusteDia= 0;
int ajusteMes = 0;
int ajusteAno = 2014;

// alarme
int alarme = 0;
int alarmeHora = 0;
int alarmeMinuto = 0;
int alarmeAjuste = 0;
int alarmeMenu = 0;
int alarmeOn = 0;
int alarmeDisparo = 0;
int alarmeDesliga = 1;
int alarmeBuzzer = 0;
int alarmeSoneca = 0;

// termometro
float adcLido = 0;
float temperaturaC = 0;
int temperaturaLer = 1;
float temperaturas [32];

// ajustes e menu
int delayAjuste = 200; // tempo que o botao saida deve ficar pressionado para entrar no menu ajuste de tempo
int contadorSemana = 0; // controle do dia de semana
int tempoAjuste = 0; 
int movimento = 0;
int saida = 0;
int tempoMenu = 1;
int controle = 0;
int funcao = 0;
int timerMenu = 0;
int timerAjuste = 0;
int timerMinuto = 0;
int timerOn = 0;
int timerMinutoAjuste = 0;
int luzAjuste = 0;
int luzMenu = 0;

// Luz do LCD
int ldrValor = 0;
int ldrOn = 1; // define se a luz do LCD funcionara pelo LDR ou sempre acesa
int ledPWM = 255;
int tempoLuz = 0;
int ativaLuz = 0;
int tempoLuzBotao = 600;

// definindo constantes inteiras para portas Arduino
const int lcdLed = 10;
const int botao0 = 13;
const int botao1 = 9;
const int botao2 = 8;
const int botao3 = 7;
const int buzzer = 6;
const int LDR = A1;
const int LM35 = A0;

// Definindo texto de caracteres
//char semana[]= " ";
//char semana[7]= {"Dom","Seg","Ter","Qua","Qui","Sex","Sab"};
char semana0[]= "Dom";
char semana1[]= "Seg";
char semana2[]= "Ter";
char semana3[]= "Qua";
char semana4[]= "Qui";
char semana5[]= "Sex";
char semana6[]= "Sab";

// Assinalando a variavel tempo como 32 bits
unsigned long tempo; 


/********************************\
 **                              **
 **   Iniciando as Declaracoes   **
 **                              **
 \********************************/

// Declaracoes
void setup() {

  // declarando a biblioteca Wire 
  Wire.begin();

  // definindo modo dos pinos  
  pinMode (botao0, INPUT);
  pinMode (botao1, INPUT);
  pinMode (botao2, INPUT);
  pinMode (botao3, INPUT);
  pinMode (lcdLed, OUTPUT);
  pinMode (buzzer, OUTPUT);

  // definindo conteudo da variavel tempo  
  tempo=0;   

  // definindo comunicacao serial
  Serial.begin(9600);

  // especificando tensao de referencia das portas analogicas para o LM35
  analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1

  // Acende backlight e dados do LCD 
  analogWrite(lcdLed, ledPWM); 

  // tela de introducao LCD
  lcd.begin(16, 2);
  lcd.setCursor(0,0);   
  lcd.print("  Data e hora ");   
  lcd.setCursor(0,1);   
  lcd.print("  com Arduino");   
  delay (2500); 
  lcd.clear();
  lcd.setCursor(0,0);   
  lcd.print("   Versao 3.3");
  lcd.setCursor(0,1);   
  lcd.print("   by Magneto");   
  delay (3000); 
  lcd.clear();
}


/********************************\
 **                              **
 **    Iniciando o programa      **
 **                              **
 \********************************/

// Programa
void loop() {

  // lendo posicao dos botoes
  funcao = digitalRead(botao0);
  movimento = digitalRead(botao1);
  saida = digitalRead(botao2);
  alarme = digitalRead(botao3);

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  // carregando as variaveis com informacao do RTC
  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read()); 

  // Indo para rotina do termometro
  termometro();

  // Indo para rotina de iluminacao do display
  if(ativaLuz == 0) luzdisplay();
  if(hora >= 22 && ativaLuz == 0) ledPWM = 0;
  if(hora >= 0 && hora < 7 && ativaLuz == 0) ledPWM = 0;
  analogWrite(lcdLed, ledPWM);

  //Configura a hora e calendario   
  if (tempoAjuste == 1 && tempoMenu > 0) {
    if (saida == HIGH) {
      saitempoAjuste(); 
    }
    switch (tempoMenu) {
      case (1):
      entrahora();
      break;
      case (2):
      entraminuto();
      break;
      case (3):
      entradia();
      break;
      case (4):
      entrames();
      break;
      case (5):
      entraano();
      break;
      case (6):
      entrasemana();
      break; 
    }
  }

  //Configura o alarme  
  if (alarmeAjuste == 1 && alarmeMenu > 0) {
    analogWrite(lcdLed, 255);
    if (saida == HIGH) {
      saialarmeAjuste(); 
    }
    switch (alarmeMenu) {
      case (1):
      entraalarmeHora();
      break;
      case (2):
      entraalarmeMinuto();
      break;
      case (3):
      entraalarmeOn();
      break; 
    }
  }

  //Configura ajuste Luz Display  
  if (luzAjuste == 1 && luzMenu > 0) {
    analogWrite(lcdLed, 255);
    if (saida == HIGH) {
      sailuzAjuste(); 
    }
    switch (luzMenu) {
      case (1):
      entraluzAjuste();
      break;
    }
  }

  //Configura as funcoes  
  if (timerAjuste == 1 && timerMenu > 0) {
    analogWrite(lcdLed, 255);
    if (saida == HIGH) {
      saifuncaotimer(); 
    }
    switch (timerMenu) {
      case (1):
      entrafuncaotimerOn();
      break;
      case (2):
      entrafuncaotimer();
      break;
    }
  }

  // Chave de selecao de calculo ou ajuste
  if(tempoAjuste == 0 && alarmeAjuste == 0 && timerAjuste == 0 && luzAjuste == 0) {

    // Imprimindo no Display
    imprimindodados();

    // Habilitando entrada no ajuste de tempo
    if(saida == HIGH) {
      controle++; 
    }

    if(controle > delayAjuste) {
      lcd.clear();
      delay(1000);
      tempoAjuste = 1;
      tempoMenu = 1;
      controle = 0; 
    }

    // Acende a luz do display
    if(movimento == HIGH || saida == HIGH) {
      tempoLuz = 1;
      ativaLuz = 1; 
    }

    if(ativaLuz == 1) {
      acendedisplay(); 
    }

    // Ajuste Entrada na funcao luz
    if (funcao == HIGH && movimento == HIGH) {   
      lcd.clear();
      delay(300);
      luzAjuste = 1; 
      luzMenu = 1;
      timerAjuste = 0; 
      timerMenu = 0;
    }

    // Ajuste entrada no Timer
    if (funcao == HIGH && movimento == LOW) {   
      lcd.clear();
      delay(200);
      luzAjuste = 0; 
      luzMenu = 0;
      timerAjuste = 1; 
      timerMenu = 1;
    }

    // Ajuste do alarme
    if (alarme == HIGH) {
      lcd.clear();
      delay(200);
      alarmeAjuste = 1;
      alarmeMenu = 1; 
    }

    // Disparo, alarmeSoneca e desligamento do alarme
    if (hora == alarmeHora && minuto == alarmeMinuto && alarmeOn == 1) {
      disparaalarme(); 
    } 
    else digitalWrite(buzzer, LOW);

    // Repique do disparo para mais 2 minutos da hora original
    if (hora == alarmeHora &&
      minuto == alarmeMinuto+1 &&
      alarmeOn == 1 &&
      alarmeDesliga == 0 &&
      segundo == 1) {

      alarmeMinuto = alarmeMinuto + 2;
      if(alarmeMinuto > 59) {
        alarmeMinuto = alarmeMinuto - 59;
        alarmeHora++; 
      }
    }

    // Desliga temporizador da Luz
    if (ativaLuz == 1 && tempoLuz >= tempoLuzBotao) {
      ativaLuz = 0;
      tempoLuz = 0; 
    }
  }

  // incrementa o valor do indice da matriz em 1
  temperaturaLer++;

  // degub na tela via USB
  debugnatela();

}

/**********************************\
 **                               **
 ** Definindo Rotinas do programa **
 **                               **
 \*********************************/

byte decToBcd(byte val){
  // Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
  // Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}


void termometro() { // Leitura do termometro

    if(temperaturaLer > 29) temperaturaLer = 0;

  adcLido = analogRead(LM35);
  temperaturas[temperaturaLer] = (adcLido * ((1.1/1023)*100)) - 0.5; // equiparar multimetro com prototipo
  //  temperaturas[temperaturaLer] = (adcLido * ((1.1/1023)*100)) - 0.8; // equiparar multimetro com projeto caixa

  temperaturas[31]  = ( temperaturas[0]   + temperaturas[1]  + temperaturas[2]
    + temperaturas[3]  + temperaturas[4]  + temperaturas[5]  + temperaturas[6]
    + temperaturas[7]  + temperaturas[8]  + temperaturas[9]  + temperaturas[10]
    + temperaturas[11] + temperaturas[12] + temperaturas[13] + temperaturas[14]
    + temperaturas[15] + temperaturas[16] + temperaturas[17] + temperaturas[18]
    + temperaturas[19] + temperaturas[20] + temperaturas[21] + temperaturas[22]
    + temperaturas[23] + temperaturas[24] + temperaturas[25] + temperaturas[26]
    + temperaturas[27] + temperaturas[28] + temperaturas[29]) / 30;

  temperaturaC = temperaturas[31];
}

void luzdisplay() { //luz do display

    ldrValor = analogRead(LDR);

  if(ldrValor > 500 && ldrOn == 1) {
    ledPWM = 255; // Totalmente aceso
  }

  if(ldrValor < 30 && ldrOn == 1) {
    ledPWM = 5; // pouca luz para nao atrapalhar no escuro
  }

  if(ldrValor > 29 && ldrValor < 501 && ldrOn == 1) {
    //ledPWM = ldrValor / 2; // controle de luminisidade >> Futuro fazer degraus
    ledPWM = map(ldrValor,30,500,10,250);
  }

  if(ldrOn == 0) {
    ledPWM = 255; // Totalmente aceso
  }
}

void acendedisplay () { // Rotina de acendimento do Display (anytime)

  if(tempoLuz < tempoLuzBotao) { 
    ledPWM = 255;
    tempoLuz++; 
  }
}

void entraluzAjuste () { // Rotina de selecao do controle de Luz: auto ou manual

  lcd.setCursor(0,0);   
  lcd.print("Modo LDR: ");

  if(ldrOn == 1) {
    lcd.print("On ");
  }
  else {
    lcd.print("Off");
  }

  if(movimento == HIGH) {   
    ldrOn++;
    if(ldrOn > 1) {
      ldrOn = 0; 
    }

    lcd.setCursor(10,0);
    if(ldrOn == 1) {
      lcd.print("On "); 
      lcd.print(" ");
      delay(200);
    } 
    if(ldrOn == 0) {
      lcd.print("Off"); 
      lcd.print(" ");
      delay(200);
    } 
  } 
}

void sailuzAjuste () {  // Rotina de saida menu funcao

  luzMenu++;
  delay(200);

  if(luzAjuste == 1) {
    lcd.clear(); 
  }

  if(luzMenu > 1) {
    luzMenu = 0;
    luzAjuste = 0; 
  }
}

void entrafuncaotimer () { // Rotina de Ajuste do timer (Max: 59 minutos)

  lcd.setCursor(0,0);   
  lcd.print("Timer: ");

  lcd.setCursor(0,1);
  if(timerMinuto < 10) {
    lcd.print("Ativo: 0");
    lcd.print(timerMinuto);
    lcd.print("m   ");
  }
  else {
    lcd.print("Ativo: ");
    lcd.print(timerMinuto);
    lcd.print("m   ");
  }

  if(timerOn == 1) {
    lcd.print("On ");
  }
  else {
    lcd.print("Off");
  }

  if(movimento == HIGH) { 
    timerMinutoAjuste++; 
    if(timerMinutoAjuste > 59) {
      timerMinutoAjuste = 0; 
    }

    lcd.setCursor(7,0);
    if(timerMinuto < 10) {
      lcd.print("0");
      lcd.print(timerMinutoAjuste);
      lcd.print(" min.");
    }
    else {
      lcd.print(timerMinutoAjuste);
      lcd.print(" min.");
    }
    delay(200); 
  }
}

void entrafuncaotimerOn () { // Rotina de ativacao do Timer: On e Off

  lcd.setCursor(0,0);   
  lcd.print("Timer: ");  
  lcd.setCursor(7,0);   
  if(timerMinutoAjuste < 10) {
    lcd.print("0");
    lcd.print(timerMinutoAjuste);
    lcd.print(" min.");
  }
  else {
    lcd.print(timerMinutoAjuste);
    lcd.print(" min.");
  }

  lcd.setCursor(0,1);
  if(timerMinuto < 10) {
    lcd.print("Ativo: 0");
    lcd.print(timerMinuto);
    lcd.print("m   ");
  }
  else {
    lcd.print("Ativo: ");
    lcd.print(timerMinuto);
    lcd.print("m   ");
  }

  if(timerOn == 1) {
    lcd.print("On ");
  }
  else {
    lcd.print("Off");
  }

  if(movimento == HIGH) { 
    timerOn++; 
    if(timerOn > 1) {
      timerOn = 0; 
    }

    lcd.setCursor(13,1);
    if(timerOn == 1) {
      lcd.print("On ");
    }
    else {
      lcd.print("Off");
    }
    delay(200); 
  }
}

void saifuncaotimer () {  // Rotina de saida menu funcao

  timerMenu++;
  delay(200);

  if(timerAjuste == 1) {
    lcd.clear(); 
  }

  if(timerMenu > 2) {
    timerMenu = 0;
    timerAjuste = 0; 
  }
}

void entrahora () { // Rotina de Ajuste de horas

  lcd.setCursor(0,0);   
  lcd.print("Hora: ");

  if(movimento == HIGH) {   
    ajusteHora++;
    if(ajusteHora > 23) {
      ajusteHora = 0; 
    }

    lcd.setCursor(6,0);
    lcd.print(ajusteHora);
    lcd.print("       ");
    delay(200); 
  } 
}

void entraminuto () { // Rotina de Ajuste de minutos

  lcd.setCursor(0,0);   
  lcd.print("Minuto: ");  

  if(movimento == HIGH) { 
    ajusteMinuto++; 
    if(ajusteMinuto > 59) {
      ajusteMinuto = 0; 
    }

    lcd.setCursor(8,0);
    lcd.print(ajusteMinuto);
    lcd.print("       ");
    delay(200); 
  }
}


void entradia () { // Rotina de Ajuste dia do mes

  lcd.setCursor(0,0);   
  lcd.print("Dia: ");  

  if(movimento == HIGH) {
    ajusteDia++;
    if(ajusteDia > 31) {
      ajusteDia = 1; 
    }

    lcd.setCursor(5,0);
    lcd.print(ajusteDia);
    lcd.print("       ");
    delay(200); 
  }
}

void entrames () { // Rotina de Ajuste do mes

    lcd.setCursor(0,0);   
  lcd.print("Mes: ");   

  if(movimento == HIGH) {
    ajusteMes++;
    if(ajusteMes > 12) {
      ajusteMes = 1; 
    }

    lcd.setCursor(5,0);
    lcd.print(ajusteMes);
    lcd.print("       ");
    delay(200); 
  }
}

void entraano () { // Rotina de Ajuste do ano

    lcd.setCursor(0,0);   
  lcd.print("Ano: 20");   

  if(movimento == HIGH) {
    ajusteAno++;
    if(ajusteAno > 20) {
      ajusteAno = 15; 
    }

    lcd.setCursor(7,0);
    lcd.print(ajusteAno);
    lcd.print("       ");
    delay(200); 
  }
}

void entrasemana () {  // Rotina de Ajuste do dia da semana

    lcd.setCursor(0,0);   
  lcd.print("Dia Semana: ");   

  if(movimento == HIGH) {
    contadorSemana++;
    if(contadorSemana > 6) {
      contadorSemana = 0; 
    }

    lcd.setCursor(12,0);

    if(contadorSemana == 0) {
      lcd.print(semana0);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 1) {
      lcd.print(semana1);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 2) {
      lcd.print(semana2);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 3) {
      lcd.print(semana3);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 4) {
      lcd.print(semana4);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 5) {
      lcd.print(semana5);
      lcd.print("       ");
      delay(200); 
    }

    if(contadorSemana == 6) {
      lcd.print(semana6);
      lcd.print("       ");
      delay(200); 
    }
  }   

}

void saitempoAjuste () {  // Rotina de saida menu ajuste

    tempoMenu++;
  delay(200);

  if(tempoAjuste == 1) {
    lcd.clear(); 
  }

  if(tempoMenu > 6) {
    tempoMenu = 0;
    tempoAjuste = 0;
    setDateTime(); 
  }
}

void setDateTime() {

  byte segundo = ajusteSegundo;
  byte minuto = ajusteMinuto;
  byte hora = ajusteHora;
  byte weekDay = contadorSemana;
  byte dia = ajusteDia;
  byte mes = ajusteMes;
  byte ano  = ajusteAno;

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //stop Oscillator

  Wire.write(decToBcd(segundo));
  Wire.write(decToBcd(minuto));
  Wire.write(decToBcd(hora));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(dia));
  Wire.write(decToBcd(mes));
  Wire.write(decToBcd(ano));

  Wire.write(zero); //start 

  Wire.endTransmission();

}


void entraalarmeHora() { // Rotina de hora do alarme 

  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmeHora < 10) {
    lcd.print("0");
    lcd.print(alarmeHora); 
  }
  else lcd.print(alarmeHora); 

  lcd.print(":");
  if(alarmeMinuto < 10) {
    lcd.print("0");
    lcd.print(alarmeMinuto); 
  }
  else lcd.print(alarmeMinuto); 

  lcd.print(" ");
  if(alarmeOn == 1) {
    lcd.print("On "); 
  }
  else lcd.print("Off"); 

  lcd.setCursor(0,0);   
  lcd.print("Alarme Hora: ");
  //  lcd.setCursor(0,1);   
  //  lcd.print("                "); 
  if(movimento == HIGH) {   
    alarmeHora++;
    if(alarmeHora > 23) {
      alarmeHora = 0; 
    }

    lcd.setCursor(13,0);
    lcd.print(alarmeHora);
    lcd.print("       ");
    delay(200); 
  } 
}

void entraalarmeMinuto() { // Rotina de minuto do alarme 

  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmeHora < 10) {
    lcd.print("0");
    lcd.print(alarmeHora); 
  }
  else lcd.print(alarmeHora); 

  lcd.print(":");
  if(alarmeMinuto < 10) {
    lcd.print("0");
    lcd.print(alarmeMinuto); 
  }
  else lcd.print(alarmeMinuto); 

  lcd.print(" ");
  if(alarmeOn == 1) {
    lcd.print("On "); 
  }
  else lcd.print("Off"); 

  lcd.setCursor(0,0);   
  lcd.print("Alarme Min: ");
  //  lcd.setCursor(0,1);   
  //  lcd.print("                ");   

  if(movimento == HIGH) { 
    alarmeMinuto++; 
    if(alarmeMinuto > 59) {
      alarmeMinuto=0; 
    }

    lcd.setCursor(12,0);
    lcd.print(alarmeMinuto);
    lcd.print("       ");
    delay(200); 
  }
}

void entraalarmeOn() { // Rotina de alarme On - Off 

  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmeHora < 10) {
    lcd.print("0");
    lcd.print(alarmeHora); 
  }
  else lcd.print(alarmeHora); 

  lcd.print(":");
  if(alarmeMinuto < 10) {
    lcd.print("0");
    lcd.print(alarmeMinuto); 
  }
  else lcd.print(alarmeMinuto); 

  lcd.print(" ");
  if(alarmeOn == 1) {
    lcd.print("On "); 
  }
  else lcd.print("Off"); 

  lcd.setCursor(0,0);   
  lcd.print("Alarme: ");
  //  lcd.setCursor(0,1);   
  //  lcd.print("                ");   

  if(movimento == HIGH) { 
    alarmeOn++; 
    if(alarmeOn > 1) {
      alarmeOn = 0; 
    }

    if(alarmeOn == 1) {
      lcd.setCursor(8,0);
      lcd.print("On     "); 
    }

    if(alarmeOn == 0) {
      lcd.setCursor(8,0);
      lcd.print("Off    "); 
    }

    delay(200); 
  }
}

void saialarmeAjuste () {  // Rotina de saida menu ajuste alarme

    alarmeMenu++;
  delay(200);

  if(alarmeAjuste == 1) {
    lcd.clear(); 
  }

  if(alarmeMenu > 3) {
    alarmeMenu = 0;
    alarmeAjuste = 0; 
  }
}

void disparaalarme () { // Rotina de disparo do alarme

    alarmeDisparo = 1;
  alarmeBuzzer++;
  if(alarmeBuzzer > 150) {
    alarmeBuzzer = 0; 
  }
  if(alarmeBuzzer >= 0 && alarmeBuzzer < 51) {
    analogWrite(buzzer, 200); 
  }  
  if(alarmeBuzzer >= 50 && alarmeBuzzer < 101) {
    analogWrite(buzzer, 50); 
  }
  if(alarmeBuzzer >= 100 && alarmeBuzzer < 151) {
    analogWrite(buzzer, 100); 
  }  

  if(movimento == HIGH || saida == HIGH){ 
    digitalWrite (buzzer, LOW);
    alarmeSoneca++;
    if(alarmeSoneca > 2) { // desligamento do alarme  
      alarmeSoneca=0;
      alarmeDisparo = 0;
      alarmeDesliga = 1;
      alarmeOn = 0; 
    }

    else { // alarmeSoneca do alarme
      alarmeMinuto = alarmeMinuto + 9;
      if(alarmeMinuto > 59){
        alarmeMinuto = alarmeMinuto - 59;
        alarmeHora++;
      }
    }
  }
  if(movimento == LOW && saida == LOW) {
    alarmeDesliga = 0; 
  }
}

void imprimindodados() { 

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  // carregando as variaveis de tempo
  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111); //24 horas
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read()); 

  if(dia < 10) {
    lcd.setCursor(0,1);    
    lcd.print("0");
    lcd.print(dia);   
    lcd.print("-"); 
  }
  else {  
    lcd.setCursor(0,1);    
    lcd.print(dia);   
    lcd.print("-"); 
  }

  lcd.setCursor(3,1);
  if(mes == 1) lcd.print("Jan");
  if(mes == 2) lcd.print("Fev");
  if(mes == 3) lcd.print("Mar");
  if(mes == 4) lcd.print("Abr");
  if(mes == 5) lcd.print("Mai");
  if(mes == 6) lcd.print("Jun");
  if(mes == 7) lcd.print("Jul");
  if(mes == 8) lcd.print("Ago");
  if(mes == 9) lcd.print("Set");
  if(mes == 10) lcd.print("Out");
  if(mes == 11) lcd.print("Nov");
  if(mes == 12) lcd.print("Dez");
  lcd.setCursor(6,1);
  lcd.print("-");  

  lcd.setCursor(7,1);
  lcd.print("20");
  lcd.print(ano);
  lcd.print("  ");

  lcd.setCursor(13,1);
  if(weekDay == 0 || weekDay == 7) {    
    lcd.print(semana0); 
  }  
  if(weekDay == 1) {    
    lcd.print(semana1); 
  }  
  if(weekDay == 2) {    
    lcd.print(semana2); 
  }  
  if(weekDay == 3) {    
    lcd.print(semana3); 
  }  
  if(weekDay == 4) {    
    lcd.print(semana4); 
  }  
  if(weekDay == 5) {    
    lcd.print(semana5); 
  }  
  if(weekDay == 6) {    
    lcd.print(semana6); 
  }  

  if(hora < 10) {
    lcd.setCursor(0,0); 
    lcd.print("0");  
    lcd.print(hora);   
    lcd.print(":"); 
  }
  else {  
    lcd.setCursor(0,0);    
    lcd.print(hora);   
    lcd.print(":"); 
  }
  if(minuto < 10) {
    lcd.setCursor(3,0);
    lcd.print("0");  
    lcd.print(minuto);   
    lcd.print(":"); 
  }
  else {  
    lcd.setCursor(3,0);    
    lcd.print(minuto);   
    lcd.print(":"); 
  }
  if(segundo < 10) {
    lcd.setCursor(6,0);   
    lcd.print("0"); 
    lcd.print(segundo);
    lcd.print("   "); 
  } 
  else {  
    lcd.setCursor(6,0);    
    lcd.print(segundo);
    lcd.print("   "); 
  }  

  if(alarmeOn == 1) {
    lcd.setCursor(9,0);   
    lcd.print("A"); 
  }
  else {
    lcd.setCursor(9,0);   
    lcd.print(" "); 
  }

  lcd.setCursor(11,0);   
  lcd.print(temperaturaC); 
  lcd.setCursor(15,0);
  lcd.print("C"); 
}

void debugnatela() {

  //Serial.print("Valor Menu:");
  //Serial.print(tempoMenu);
  //Serial.print(" Contador Semana: ");
  //Serial.print(contadorSemana);
  //Serial.print(" Dia da Semana: ");
  //Serial.print(weekDay);
  //Serial.print(" Ajuste: ");
  //Serial.print(tempoAjuste);
  //Serial.print(" Controle: ");
  //Serial.print(controle);
  //Serial.print(" PWM LDR: ");
  //Serial.print(ledPWM);
  //Serial.print(" Valor LDR: ");
  //Serial.print(ldrValor);
  //Serial.print(" Luz: ");
  //Serial.print(ativaLuz);
  //Serial.print(" Tempo Luz: ");
  //Serial.print(tempoLuz);
  //Serial.print(" energia temporario 1: ");
  //Serial.print(energiatemp1);
  //Serial.print(" energia temporario 2: ");
  //Serial.print(energiatemp2);
  //Serial.print(" energia: ");
  //Serial.print(energia);
  //Serial.print(" indice: ");
  //Serial.print(indice);
  //Serial.print(" soma temperatura: ");
  //Serial.print(somatemperatura);
  //Serial.print(" temperatura1: ");
  //Serial.print(matriztemperatura[1]);
  //Serial.print(" temperatura2: ");
  //Serial.print(matriztemperatura[2]);
  //Serial.print(" temperatura3: ");
  //Serial.print(matriztemperatura[3]);
  //Serial.println("  ");
  //delay(50);
}

























