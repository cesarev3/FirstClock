/***************************************\
**                                     **
**   Relogio completo com termometro   **
**      Primeira grande montagem       **
**                                     **
\***************************************/

// Erros: alarme dispara depois de certo tempo e display nao acende no alarme

// carregando biblioteca para display
#include <LiquidCrystal.h>

// especifica as portas para uso no display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// definindo variaveis numericas inteiras
// hora e calendario
int segundo = 0;
int minuto = -1;
int hora = -1;
int dia= 0;
int mes = 0;
int ano = 2014;

// alarme
int alarme = 0;
int alarmehora = 0;
int alarmeminuto = 0;
int alarmeajuste = 0;
int alarmemenu = 0;
int alarmeon = 0;
int alarmedisparo = 0;
int alarmedesliga = 1;
int alarmebuzzer = 0;
int soneca = 0;

// termometro
float adclido = 0;
float temperaturac = 0;
float temperaturaf = 0;
int lertemperatura = 1;
float temperaturas [32];
int mediatemperatura = 0;
float somatemperatura = 0;
int indice = 0;
const float base5V = 0.488758553275;
const float base4_8V = 0.449657869013;


// ajustes e menu
int contadorsemana = 0;
int tempoajuste = 1;
int movimento = 0;
int saida = 0;
int tempomenu = 1;
int controle = 0;

// Luz do LCD
int valorlido = 0;
int ledpwm = 255;
int dadospwm = 0;
int tempoluz = 0;
int ativaluz = 0;
int energia = 1;
int energiamenu = 0;
int energiaajuste = 0;
int energiatemp = 1;
int energiatemp2 = 0;
int lcdoff = 0;
int tempoluzbotao = 600;
int tempoluzenergia = 16;

// Intervalo de medida do termometro
int flip = 0;
int contadorflip = 0;
int tempoflip = 25;

// definindo constantes inteiras para portas Arduino
const int botao0 = 13;
const int botao1 = 9;
const int botao2 = 8;
const int botao3 = 7;
const int buzzer = 6;
const int LDR = A1;
const int LM35 = A0;
const int led = 10;
const int lcddados = A2;

// Definindo texto de caracteres
//char semana[]= " ";
//char semana[7]= {"Dom","Seg","Ter","Qua","Qui","Sex","Sab"};
char semana1[]= "Dom";
char semana2[]= "Seg";
char semana3[]= "Ter";
char semana4[]= "Qua";
char semana5[]= "Qui";
char semana6[]= "Sex";
char semana7[]= "Sab";

// Assinalando a variavel tempo como 32 bits
unsigned long tempo; 

/********************************\
**                              **
** Definindo Rotinas de entrada **
**                              **
\********************************/

void termometro() { // Leitura do termometro

if(lertemperatura > 29) lertemperatura = 0;

adclido = analogRead(LM35) +10;
temperaturas[lertemperatura] = (adclido * ((1.1/1023)*100))-2.09;

temperaturas[31] = ( temperaturas[0]  + temperaturas[1]  + temperaturas[2]  + temperaturas[3]  + temperaturas[4]  
                   + temperaturas[5]  + temperaturas[6]  + temperaturas[7]  + temperaturas[8]  + temperaturas[9]
                   + temperaturas[10] + temperaturas[11] + temperaturas[12] + temperaturas[13] + temperaturas[14]
                   + temperaturas[15] + temperaturas[16] + temperaturas[17] + temperaturas[18] + temperaturas[19]
                   + temperaturas[20] + temperaturas[21] + temperaturas[22] + temperaturas[23] + temperaturas[24]
                   + temperaturas[25] + temperaturas[26] + temperaturas[27] + temperaturas[28] + temperaturas[29]) / 30;

temperaturac = temperaturas[31];
}

void entrahora () { // Rotina de Ajuste de horas

  lcd.setCursor(0,0);   
  lcd.print("Hora: ");
  
    if(movimento == HIGH) {   
      hora++;
        if(hora > 23) {
        hora=0; }
        
  lcd.setCursor(6,0);
  lcd.print(hora);
  lcd.print("       ");
  delay(200); } 
}

void entraminuto () { // Rotina de Ajuste de minutos

  lcd.setCursor(0,0);   
  lcd.print("Minuto: ");  
  
    if(movimento == HIGH) { 
      minuto++; 
       if(minuto > 59) {
         minuto=0; }
         
  lcd.setCursor(8,0);
  lcd.print(minuto);
  lcd.print("       ");
  delay(200); }
}


void entradia () { // Rotina de Ajuste dia do mes

  lcd.setCursor(0,0);   
  lcd.print("Dia: ");  
  
    if(movimento == HIGH) {
      dia++;
       if(dia > 31) {
         dia=1; }

  lcd.setCursor(5,0);
  lcd.print(dia);
  lcd.print("       ");
  delay(200); }
}

void entrames () { // Rotina de Ajuste do mes

  lcd.setCursor(0,0);   
  lcd.print("Mes: ");   
  
    if(movimento == HIGH) {
      mes++;
       if(mes > 12) {
         mes=1; }

  lcd.setCursor(5,0);
  lcd.print(mes);
  lcd.print("       ");
  delay(200); }
}

void entraano () { // Rotina de Ajuste do ano
   
 lcd.setCursor(0,0);   
 lcd.print("Ano: 20");   
  
   if(movimento == HIGH) {
    ano++;
     if(ano > 20) {
       ano=15; }
 
  lcd.setCursor(7,0);
  lcd.print(ano);
  lcd.print("       ");
  delay(200); }
}

void entrasemana () {  // Rotina de Ajuste do dia da semana
 
  lcd.setCursor(0,0);   
  lcd.print("Dia Semana: ");   
  
    if(movimento == HIGH) {
      contadorsemana++;
       if(contadorsemana > 7) {
         contadorsemana=1; }
 
  lcd.setCursor(12,0);

    if(contadorsemana == 1) {
      lcd.print(semana1);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 2) {
      lcd.print(semana2);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 3) {
      lcd.print(semana3);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 4) {
      lcd.print(semana4);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 5) {
      lcd.print(semana5);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 6) {
      lcd.print(semana6);
      lcd.print("       ");
      delay(200); }

    if(contadorsemana == 7) {
      lcd.print(semana7);
      lcd.print("       ");
      delay(200); }
      }   
     
}

void saitempoajuste () {  // Rotina de saida menu ajuste

  tempomenu++;
  delay(200);

 if(tempoajuste == 1) {
   lcd.clear(); }

   if(tempomenu > 6) {
     tempomenu=0;
     tempoajuste=0; }
}

void entraalarmehora() { // Rotina de hora do alarme 
  
  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmehora < 10) {
    lcd.print("0");
    lcd.print(alarmehora); }
  else lcd.print(alarmehora); 
  
  lcd.print(":");
  if(alarmeminuto < 10) {
    lcd.print("0");
    lcd.print(alarmeminuto); }
  else lcd.print(alarmeminuto); 
  
  lcd.print(" ");
  if(alarmeon == 1) {
    lcd.print("On "); }
  else lcd.print("Off"); 
  
  lcd.setCursor(0,0);   
  lcd.print("Alarme Hora: ");
//  lcd.setCursor(0,1);   
//  lcd.print("                "); 
    if(movimento == HIGH) {   
      alarmehora++;
        if(alarmehora > 23) {
        alarmehora=0; }
        
  lcd.setCursor(13,0);
  lcd.print(alarmehora);
  lcd.print("       ");
  delay(200); } 
}

void entraalarmeminuto() { // Rotina de minuto do alarme 

  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmehora < 10) {
    lcd.print("0");
    lcd.print(alarmehora); }
  else lcd.print(alarmehora); 
  
  lcd.print(":");
  if(alarmeminuto < 10) {
    lcd.print("0");
    lcd.print(alarmeminuto); }
  else lcd.print(alarmeminuto); 
  
  lcd.print(" ");
  if(alarmeon == 1) {
    lcd.print("On "); }
  else lcd.print("Off"); 
  
  lcd.setCursor(0,0);   
  lcd.print("Alarme Min: ");
//  lcd.setCursor(0,1);   
//  lcd.print("                ");   
  
    if(movimento == HIGH) { 
      alarmeminuto++; 
       if(alarmeminuto > 59) {
         alarmeminuto=0; }
         
  lcd.setCursor(12,0);
  lcd.print(alarmeminuto);
  lcd.print("       ");
  delay(200); }
}

void entraalarmeon() { // Rotina de alarme On - Off 

  lcd.setCursor(0,1);   
  lcd.print("Alarme ");
  if(alarmehora < 10) {
    lcd.print("0");
    lcd.print(alarmehora); }
  else lcd.print(alarmehora); 
  
  lcd.print(":");
  if(alarmeminuto < 10) {
    lcd.print("0");
    lcd.print(alarmeminuto); }
  else lcd.print(alarmeminuto); 
  
  lcd.print(" ");
  if(alarmeon == 1) {
    lcd.print("On "); }
  else lcd.print("Off"); 

  lcd.setCursor(0,0);   
  lcd.print("Alarme: ");
//  lcd.setCursor(0,1);   
//  lcd.print("                ");   
  
  if(movimento == HIGH) { 
    alarmeon++; 
      if(alarmeon > 1) {
        alarmeon=0; }
         
  if(alarmeon == 1) {
    lcd.setCursor(8,0);
    lcd.print("On     "); }

   if(alarmeon == 0) {
    lcd.setCursor(8,0);
    lcd.print("Off    "); }
    
  delay(200); }
}

void saialarmeajuste () {  // Rotina de saida menu ajuste alarme

  alarmemenu++;
  delay(200);
  
 if(alarmeajuste == 1) {
   lcd.clear(); }

    if(alarmemenu > 3) {
      alarmemenu=0;
      alarmeajuste=0; }
}

void entraenergiaajuste () {  // Rotina de ajuste do modo economia de energia

  lcd.setCursor(0,0);   
  lcd.print("Energy: ");
  lcd.setCursor(0,1);   
  lcd.print("                "); 
    if(movimento == HIGH) {   
      energia++;
    if(energia > 3) {
      energia=1; }
  lcd.setCursor(8,0);
   if(energia == 1) {
     lcd.print("AC Power");
     lcd.print("   ");
     delay(200); } 
   else if(energia == 2) {
     lcd.print("Battery ");
     lcd.print("   ");
     delay(200); } 
   else if(energia == 3) {
     lcd.print("Batt Off ");
     lcd.print("   ");
     delay(200); } 
 /*  else if(energia == 4) {
     lcd.print("15m");
     lcd.print("   ");
     delay(200); } 
   else if(energia == 5) {
     lcd.print("All");
     lcd.print("   ");
     delay(200); } 
*/
}
//   energiatemp=energia;
}

void saienergiaajuste () {  // Rotina de saida do ajuste da economia de energia
  energiaajuste=0;
  delay(200); }
  
void disparaalarme () { // Rotina de disparo do alarme
  
//  energia=1;
  alarmedisparo=1;
  alarmebuzzer++;
  if(alarmebuzzer > 150) {
    alarmebuzzer=0; }
  if(alarmebuzzer >= 0 && alarmebuzzer < 51) {
    analogWrite(buzzer, 200); }  
  if(alarmebuzzer >= 50 && alarmebuzzer < 101) {
    analogWrite(buzzer, 50); }
  if(alarmebuzzer >= 100 && alarmebuzzer < 151) {
    analogWrite(buzzer, 100); }  
  
  if(movimento == HIGH || saida == HIGH){ 
    digitalWrite (buzzer, LOW);
    soneca++;
    if(soneca > 2) { // desligamento do alarme  
     soneca=0;
     energiatemp=energia;
     alarmedisparo=0;
     alarmedesliga=1;
     alarmeon=0; }
     
    else { // soneca do alarme
      alarmeminuto = alarmeminuto + 9;
      if(alarmeminuto > 59){
        alarmeminuto = alarmeminuto - 59;
        alarmehora++;}
   }
}
  if(movimento == LOW && saida == LOW) {
    alarmedesliga=0; }
}

void acendedisplay () { // Rotina de acendimento do Display (anytime)
  
 if(tempoluz < tempoluzbotao) { 
  ledpwm=255;
  dadospwm=0;
  tempoluz++; }
  
  else {
   if(ledpwm > 255) {
     ledpwm=255;
     dadospwm=0; }

   if(ledpwm < 0) {
     ledpwm=0;
     dadospwm=255; }
  
   if(valorlido < 15) {
     ledpwm=0;
     dadospwm=255; }

   if(valorlido > 1000) {
     ledpwm=255;
     dadospwm=0; }
  }
}

// Rotina de Luz do Display
void luzdisplay () {
  
if (energia == 1 || energia == 3) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW);}
   
   if (energia == 2 && ativaluz == 1) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW);}
/*
if (energia == 2 && hora == 0 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }

if (energia == 3 && minuto == 30 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
   
if (energia == 3 && hora == 0 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
   
if (energia == 4 && minuto == 15 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
   
if (energia == 4 && minuto == 30 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
   
if (energia == 4 && minuto == 45 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
    
if (energia == 4 && hora == 0 && segundo < tempoluzenergia) {
   analogWrite(led, ledpwm);
   digitalWrite(lcddados, LOW); }
*/
}

/********************************\
**                              **
**   Iniciando as Declaracoes   **
**                              **
\********************************/

// Declaracoes
void setup() {
  
// definindo modo dos pinos  
pinMode (botao0, INPUT);
pinMode (botao1, INPUT);
pinMode (botao2, INPUT);
pinMode (botao3, INPUT);
pinMode (led, OUTPUT);
pinMode (buzzer, OUTPUT);
pinMode (lcddados, OUTPUT);

// definindo conteudo da variavel tempo  
tempo=0;   

// definindo comunicacao serial
Serial.begin(9600);

// especificando tensao de referencia das portas analogicas para o LM35
analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1

// Acende LCD
analogWrite(led, ledpwm); 

// Acende Dados LCD
digitalWrite(lcddados, LOW);

// tela de introducao LCD
lcd.begin(16, 2);
lcd.setCursor(0,0);   
lcd.print("  Data e hora ");   
lcd.setCursor(0,1);   
lcd.print("  com Arduino");   
delay (2500); 
lcd.clear();
lcd.begin(16, 2);
lcd.setCursor(0,0);   
lcd.print("  MagnetoAero ");   
lcd.setCursor(0,1);   
lcd.print("  Version 2.1");   
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
energiamenu = digitalRead(botao0);
movimento = digitalRead(botao1);
saida = digitalRead(botao2);
alarme = digitalRead(botao3);

termometro();

// Luz do display 
if(energiaajuste == 0) {
  analogWrite(led, 0);
  digitalWrite(lcddados, HIGH);
  luzdisplay(); }

//Configura a hora e calendario   
if (tempoajuste == 1 && tempomenu > 0) {
  if (saida == HIGH) {
    saitempoajuste(); }
  switch (tempomenu) {
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
      break; }
}

//Configura o alarme  
if (alarmeajuste == 1 && alarmemenu > 0) {
  analogWrite(led, 255);
  digitalWrite(lcddados, LOW);
  if (saida == HIGH) {
    saialarmeajuste(); }
  switch (alarmemenu) {
    case (1):
      entraalarmehora();
      break;
    case (2):
      entraalarmeminuto();
      break;
    case (3):
      entraalarmeon();
      break; }
}

//Configura modo de economia de energia  
if (energiaajuste == 1 && energia > 0) {
  analogWrite(led, 255);
  digitalWrite(lcddados, LOW);
  if (saida == HIGH) {
    saienergiaajuste(); }
  entraenergiaajuste(); }

// Chave de selecao de calculo ou ajuste
if(tempoajuste == 0 && alarmeajuste == 0 && energiaajuste == 0) {
  
// Calculando o tempo
if(millis()-tempo<0) {     
  tempo=millis(); }   
else {     
  segundo=int((millis()-tempo)/1000); } 
  
if(segundo>59) {     
  segundo=0;     
  minuto++;     
  tempo=millis();   
  
 if(minuto>59) {       
   hora++;       
   minuto=0;       

 if(hora>23) {         
   dia++;
   hora=0;
   contadorsemana++;       
       
 if(contadorsemana > 7) {
   contadorsemana=1; } 
       
 if(mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12) {           

 if(dia>31) {             
   dia=1;             
   mes++;             

 if(mes>12) {               
   ano++;               
   mes=1; }           
}         
}         

else if(mes==2) {           

 if(ano%400==0) {             
 
 if(dia>29) {               
   dia=1;               
   mes++; }           
}           

else if((ano%4==0)&&(ano%100!=0)) {             

 if(dia>29) {              
   dia=1;               
   mes++; }           
}           

 else {             
             
 if(dia>28) {               
    dia=1;               
    mes++; }           
}         
}         

else {           

if(dia>30) {             
  dia=1;             
  mes++; }         
}       
}     
}   
}   

// Imprimindo no Display
if(flip == 0) {
  if(dia < 10) {
  lcd.setCursor(0,1);    
  lcd.print("0");
  lcd.print(dia);   
  lcd.print("-"); }
else {  
  lcd.setCursor(0,1);    
  lcd.print(dia);   
  lcd.print("-"); }
  
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
if(contadorsemana == 1) {    
  lcd.print(semana1); }  
else {  
  if(contadorsemana == 2) {    
  lcd.print(semana2); }  
else {  
  if(contadorsemana == 3) {    
    lcd.print(semana3); }  
else {  
   if(contadorsemana == 4) {    
     lcd.print(semana4); }  
else {  
   if(contadorsemana == 5) {    
     lcd.print(semana5); }  
else {  
   if(contadorsemana == 6) {    
     lcd.print(semana6); }  
else {  
   if(contadorsemana == 7) {    
     lcd.print(semana7); }  
}
}
}
}
}
}
}
/*
if(flip == 1) {
  lcd.setCursor(0,1);    
  lcd.print("Alarme ");
  lcd.setCursor(7,1);
  
  if(alarmehora < 10) {   
  lcd.print("0");
  lcd.print(alarmehora);   
  lcd.print(":"); }
else {     
  lcd.print(alarmehora);   
  lcd.print(":"); }
  
  lcd.setCursor(10,1);  
if(alarmeminuto < 10) {
  lcd.print("0");  
  lcd.print(alarmeminuto);   
  lcd.print(" "); }
else {    
  lcd.print(alarmeminuto);   
  lcd.print(" "); }
  
lcd.setCursor(13,1);   
if(alarmeon == 0) {
  lcd.print("Off  "); }
if(alarmeon == 1) {
  lcd.print("On   "); }
  
lcd.setCursor(11,1);
if(energia == 1) {
  lcd.print("E=Off"); }
if(energia == 2) {
  lcd.print("E=60m"); }
if(energia == 3) {
  lcd.print("E=30m"); }
if(energia == 4) {
  lcd.print("E=15m"); }
if(energia == 5) {
  lcd.print("E=All"); }
  
}  
*/
if(hora < 10) {
  lcd.setCursor(0,0); 
  lcd.print("0");  
  lcd.print(hora);   
  lcd.print(":"); }
else {  
  lcd.setCursor(0,0);    
  lcd.print(hora);   
  lcd.print(":"); }
if(minuto < 10) {
  lcd.setCursor(3,0);
  lcd.print("0");  
  lcd.print(minuto);   
  lcd.print(":"); }
else {  
  lcd.setCursor(3,0);    
  lcd.print(minuto);   
  lcd.print(":"); }
if(segundo < 10) {
  lcd.setCursor(6,0);   
  lcd.print("0"); 
  lcd.print(segundo);
  lcd.print("   "); } 
else {  
  lcd.setCursor(6,0);    
  lcd.print(segundo);
  lcd.print("   "); }  

lcd.setCursor(11,0);   
lcd.print(temperaturac); 
lcd.setCursor(15,0);
lcd.print("C"); 



// desabilita ajuste
//tempoajuste=0;

// Habilitando entrada no ajuste de tempo
if(saida == HIGH) {
  controle++; }
  
if(controle > 100) {
  lcd.clear();
  delay(1000);
  tempoajuste=1;
  tempomenu=1;
  controle=0; }
  
// Leitura LDR
valorlido = analogRead(LDR);
ledpwm=(valorlido / 4.01176470588235);

if(movimento == HIGH || saida == HIGH) {
  tempoluz=1;
  ativaluz=1;
//  energia=1;
  }
  
if(ativaluz == 1) {
  acendedisplay(); }

// Contagem mudanca de tela
contadorflip++;
if(contadorflip > tempoflip) {
  contadorflip=0;
  flip++; }
  
if(flip > 1) {
  flip=0; }

// Ajuste Energia
if (energiamenu == HIGH) {
  lcd.clear();
  delay(200);
  energiaajuste=1; }
  
// Ajuste do alarme
if (alarme == HIGH) {
  lcd.clear();
  delay(200);
  alarmeajuste=1;
  alarmemenu=1; }

// Disparo, soneca e desligamento do alarme
if (hora == alarmehora && minuto == alarmeminuto && alarmeon == 1) {
  disparaalarme(); } 
else digitalWrite(buzzer, LOW);

// Repique do disparo para mais 2 minutos da ora original
if (hora == alarmehora && minuto == alarmeminuto+1 && alarmeon == 1 && alarmedesliga == 0 && segundo == 1) {
   alarmeminuto = alarmeminuto + 2;
   if(alarmeminuto > 59) {
     alarmeminuto = alarmeminuto - 59;
     alarmehora++; }
}

// Desliga temporizador da Luz
if (ativaluz == 1 && tempoluz >= tempoluzbotao) {
  ativaluz=0;
  tempoluz=0; }
//  energia=energiatemp; 
}

//Serial.print("Valor Menu:");
//Serial.print(tempomenu);
//Serial.print(" Contador: ");
//Serial.print(contadorsemana);
//Serial.print(" Ajuste: ");
//Serial.print(tempoajuste);
//Serial.print(" Controle: ");
//Serial.print(controle);
//Serial.print(" PWM LDR: ");
//Serial.print(ledpwm);
//Serial.print(" Valor LDR: ");
//Serial.print(valorlido);
//Serial.print(" Luz: ");
//Serial.print(ativaluz);
//Serial.print(" Tempo Luz: ");
//Serial.print(tempoluz);
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
lertemperatura++;
}
