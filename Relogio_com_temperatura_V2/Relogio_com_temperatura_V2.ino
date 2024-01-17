/***************************************\
** Relogio completo com termometro **
* *
** Primeira grande montagem  **
\***************************************/


// carregando biblioteca para display
#include <LiquidCrystal.h>

// especifica as portas para uso no display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// definindo variaveis numericas inteiras
int segundo, minuto, hora, dia, mes, ano; 
int ADClido = 0;
int temperatura = 0;
int contador = 0;
int ajuste = 1;
int movimento = 0;
int saida = 0;
int menu = 1;
int controle = 0;
int valorlido = 0;
int pwm = 0;
int tempoluz = 0;
int ativaluz = 0;
int alarme = 0;
int alarmehora = 0;
int alarmeminuto = 0;
int alarmeajuste = 0;
int alarmemenu = 0;
int alarmeon = 0;
int alarmedisparo = 0;
int freqbuzzer = 0;
int flip = 0;
int contadorflip = 0;
int soneca = 0;
int energia = 0;
int energiamenu = 0;
int energiaajuste = 0;
int energiatemporizador = 0;


// definindo variaveis numerias decimais
//float temperatura = 0;

// definindo constantes inteiras para portas Arduino
const int botao0 = 13;
const int botao1 = 9;
const int botao2 = 8;
const int botao3 = 7;
const int buzzer = 6;
//const int highbuzzer = 13;
const int LDR = A1;
const int LM35 = A0;
const int Led = 10;
const int lcddados = A2;

// Definindo texto de caracteres
char semana[]= " ";
char semana1[]= "Dom";
char semana2[]= "Seg";
char semana3[]= "Ter";
char semana4[]= "Qua";
char semana5[]= "Qui";
char semana6[]= "Sex";
char semana7[]= "Sab";

// nao sei exatamento o comando, apenas sei que trabalha com o tempo para contar horas
unsigned long UtlTime; 

// Declaracoes
void setup() {
  
// definindo modo dos pinos dos botoes  
pinMode (botao0, INPUT);
pinMode (botao1, INPUT);
pinMode (botao2, INPUT);
pinMode (botao3, INPUT);
pinMode (Led, OUTPUT);
pinMode (buzzer, OUTPUT);
pinMode (lcddados, OUTPUT);

// definindo conteudo das variaveis  
UtlTime=0;   
minuto=-1;   
hora=-1;   
dia=0;   
mes=0;   
ano=14;
contador=0;
tempoluz=0;
ativaluz=0;
pwm=255;
alarmeajuste=0;
alarmehora=0;
alarmeminuto=0;
alarme=0;
energia=1;
energiamenu=0;
menu=1;
ajuste=1;

// definindo comunicacao serial
Serial.begin(9600);

// especificando tensao de referencia das portas analogicas para o LM35
analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1

// Acende LCD
analogWrite(Led, pwm); 

// Acende Dados LCD
digitalWrite(lcddados, LOW);

// tela de introducao LCD
lcd.begin(16, 2);
lcd.setCursor(0,0);   
lcd.print("  Data e hora ");   
lcd.setCursor(0,1);   
lcd.print("  com Arduino");   
delay (2000); 
lcd.clear();
}
// Modelo de entrada serial **** FUTURO
//Configura o minuto   
//lcd.clear();   
//lcd.setCursor(0,0);   
//lcd.print("Minuto: ");   
//Serial.print("\nEntre Minuto:");  
//while(minuto==0)   {     
//if (Serial.available() > 0)     
//{       
//minuto= Serial.parseInt();     
//}   
//}   
//lcd.print(minuto);   
//delay(1000); 

// Programa
void loop() {

// lendo posicao dos botoes
energiamenu = digitalRead(botao0);
movimento = digitalRead(botao1);
saida = digitalRead(botao2);
alarme = digitalRead(botao3);

// Preparando leitura do LM35
ADClido = analogRead(LM35);
temperatura = ADClido * 0.1075268817204301;

// Regula luz display 

analogWrite(Led, 0); 

if (energia == 1) {
analogWrite(Led, pwm); }

if (energia == 2 && hora == 0 && segundo < 16) {
  analogWrite(Led, pwm); }

if (energia == 3 && minuto == 30 && segundo < 16) {
   analogWrite(Led, pwm); }
   
if (energia == 3 && hora == 0 && segundo < 16) {
   analogWrite(Led, pwm); }
   
if (energia == 4 && minuto == 15 && segundo < 16) {
   analogWrite(Led, pwm); }
   
if (energia == 4 && minuto == 30 && segundo < 16) {
   analogWrite(Led, pwm); }
   
if (energia == 4 && minuto == 45 && segundo < 16) {
   analogWrite(Led, pwm); }
    
if (energia == 4 && hora == 0 && segundo < 16) {
   analogWrite(Led, pwm); }
 
//Configura a hora   
if(menu == 1 && ajuste == 1) {
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
else {

//Configura o minuto   
if(menu == 2 && ajuste == 1) { 
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
else {

//Configura o dia do mes   
if(menu == 3 && ajuste == 1) { 
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
else {
  
//Configura o Mes   
if(menu == 4 && ajuste == 1) {  
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
else {
  
//Configura o Ano   
if(menu == 5 && ajuste == 1) {   
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
else {
  
//Configura o dia da semana   
if(menu == 6 && ajuste == 1) {   
  lcd.setCursor(0,0);   
  lcd.print("Dia Semana: ");   
  
    if(movimento == HIGH) {
      contador++;
       if(contador > 7) {
         contador=1; }
 
  lcd.setCursor(12,0);
    if(contador == 1) {
      lcd.print(semana1);
      lcd.print("       ");
      delay(200); }

    if(contador == 2) {
      lcd.print(semana2);
      lcd.print("       ");
      delay(200); }

    if(contador == 3) {
      lcd.print(semana3);
      lcd.print("       ");
      delay(200); }

    if(contador == 4) {
      lcd.print(semana4);
      lcd.print("       ");
      delay(200); }

    if(contador == 5) {
      lcd.print(semana5);
      lcd.print("       ");
      delay(200); }

    if(contador == 6) {
      lcd.print(semana6);
      lcd.print("       ");
      delay(200); }

    if(contador == 7) {
      lcd.print(semana7);
      lcd.print("       ");
      delay(200); }
      }
}
}
}
}
}
}

if(saida == HIGH) {
  menu++;
  delay(200);

 if(ajuste == 1) {
   lcd.clear(); }

   if(menu > 6) {
     menu=0;
     ajuste=0; }
}

//Configura o tipo de economia de Energia   
if(energiaajuste == 1) {
  lcd.setCursor(0,0);   
  lcd.print("Energy Save: ");
  lcd.setCursor(0,1);   
  lcd.print("                "); 
    if(movimento == HIGH) {   
      energia++;
        if(energia > 5) {
        energia=1; }
               
  lcd.setCursor(13,0);
  if(energia == 1) {
   lcd.print("Off");
   lcd.print("   ");
   delay(200); } 
   else if(energia == 2) {
     lcd.print("60m");
     lcd.print("   ");
     delay(200); } 
     else if(energia == 3) {
        lcd.print("30m");
        lcd.print("   ");
        delay(200); } 
        else if(energia == 4) {
           lcd.print("15m");
           lcd.print("   ");
           delay(200); } 
           else if(energia == 5) {
             lcd.print("All");
             lcd.print("   ");
             delay(200); } 
}

if(saida == HIGH) {
  energiaajuste=0; }
}

//Configuração do Alarme
//Configura a hora   
if(alarmemenu == 1 && alarmeajuste == 1) {
  lcd.setCursor(0,0);   
  lcd.print("Alarme Hora: ");
  lcd.setCursor(0,1);   
  lcd.print("                "); 
    if(movimento == HIGH) {   
      alarmehora++;
        if(alarmehora > 23) {
        alarmehora=0; }
        
  lcd.setCursor(13,0);
  lcd.print(alarmehora);
  lcd.print("       ");
  delay(200); } 
}
else {
  
//Configura o minuto   
if(alarmemenu == 2 && alarmeajuste == 1) { 
  lcd.setCursor(0,0);   
  lcd.print("Alarme Min: ");
  lcd.setCursor(0,1);   
  lcd.print("                ");   
  
    if(movimento == HIGH) { 
      alarmeminuto++; 
       if(alarmeminuto > 59) {
         alarmeminuto=0; }
         
  lcd.setCursor(12,0);
  lcd.print(alarmeminuto);
  lcd.print("       ");
  delay(200); }
}

//Configura o Alarme On - Off   
if(alarmemenu == 3 && alarmeajuste == 1) { 
  lcd.setCursor(0,0);   
  lcd.print("Alarme: ");
  lcd.setCursor(0,1);   
  lcd.print("                ");   
  
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
}
if(saida == HIGH) {
  alarmemenu++;
  delay(200);
  
 if(alarmeajuste == 1) {
   lcd.clear(); }

    if(alarmemenu > 3) {
      alarmemenu=0;
      alarmeajuste=0; }
}
//Serial.print("Valor Menu:");
//Serial.print(menu);
//Serial.print(" Contador: ");
//Serial.print(contador);
//Serial.print(" Ajuste: ");
//Serial.print(ajuste);
//Serial.print(" Controle: ");
//Serial.print(controle);
//Serial.print(" PWM LDR: ");
//Serial.print(pwm);
//Serial.print(" Valor LDR: ");
//Serial.print(valorlido);
//Serial.print(" Luz: ");
//Serial.print(ativaluz);
//Serial.print(" Tempo Luz: ");
//Serial.print(tempoluz);
//Serial.print(" energia: ");
//Serial.println(energia);


// Chave de selecao de calculo ou ajuste
if(ajuste == 0 && alarmeajuste == 0 && energiaajuste == 0) {
  
// Calculando o tempo
if(millis()-UtlTime<0) {     
  UtlTime=millis(); }   
else {     
  segundo=int((millis()-UtlTime)/1000); } 
  
if(segundo>59) {     
  segundo=0;     
  minuto++;     
  UtlTime=millis();   
  
  if(minuto>59) {       
    hora++;       
    minuto=0;       

     if(hora>23) {         
       dia++;
       hora=0;
       contador++;       
       
        if(contador > 7) {
         contador=1; } 
       
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
  lcd.print("/"); }
else {  
  lcd.setCursor(0,1);    
  lcd.print(dia);   
  lcd.print("/"); }
if(mes < 10) {
  lcd.setCursor(3,1);
  lcd.print("0");  
  lcd.print(mes);   
  lcd.print("/"); }
else {  
  lcd.setCursor(3,1);    
  lcd.print(mes);   
  lcd.print("/"); }
  
lcd.setCursor(6,1);   
lcd.print(ano);
lcd.print("     ");

lcd.setCursor(13,1);
if(contador == 1) {    
  lcd.print(semana1); }  
else {  
  if(contador == 2) {    
  lcd.print(semana2); }  
    else {  
      if(contador == 3) {    
        lcd.print(semana3); }  
      else {  
        if(contador == 4) {    
          lcd.print(semana4); }  
        else {  
          if(contador == 5) {    
            lcd.print(semana5); }  
          else {  
            if(contador == 6) {    
              lcd.print(semana6); }  
            else {  
              if(contador == 7) {    
                lcd.print(semana7); }  
            }
           }
          }
         }
        }
}
}
if(flip == 1) {
  if(alarmehora < 10) {
  lcd.setCursor(0,1);    
  lcd.print("0");
  lcd.print(alarmehora);   
  lcd.print(":"); }
else {  
  lcd.setCursor(0,1);    
  lcd.print(alarmehora);   
  lcd.print(":"); }
if(alarmeminuto < 10) {
  lcd.setCursor(3,1);
  lcd.print("0");  
  lcd.print(alarmeminuto);   
  lcd.print(" "); }
else {  
  lcd.setCursor(3,1);    
  lcd.print(alarmeminuto);   
  lcd.print(" "); }
  
lcd.setCursor(6,1);   
if(alarmeon == 0) {
  lcd.print("Off "); }
if(alarmeon == 1) {
  lcd.print("On  "); }
  
lcd.setCursor(10,1);
if(energia == 1) {
  lcd.print("ES:Off"); }
if(energia == 2) {
  lcd.print("ES:60m"); }
if(energia == 3) {
  lcd.print("ES:30m"); }
if(energia == 4) {
  lcd.print("ES:15m"); }
if(energia == 5) {
  lcd.print("ES:All"); }
}  
  
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
  lcd.print("     "); } 
else {  
  lcd.setCursor(6,0);    
  lcd.print(segundo);
  lcd.print("     "); }  
  
lcd.setCursor(13,0);   
lcd.print(temperatura); 
lcd.setCursor(15,0);
lcd.print("C"); 

// desabilita ajuste
ajuste=0;

if(saida == HIGH) {
  controle++; }
  
if(controle > 10) {
  lcd.clear();
  delay(1000);
  ajuste=1;
  menu=1;
  controle=0; }
  
// Leitura LDR
valorlido = analogRead(LDR);
pwm=(valorlido / 4.01176470588235);

// Liga luz display
if(movimento == HIGH || saida == HIGH){
  tempoluz=1;
  ativaluz=1;
  energiatemporizador=energia;
  energia=1; }
  
// Temporizador da Luz
if(ativaluz ==1 && tempoluz < 400){
  pwm=255;
  tempoluz++; }
  
  else {
   if(pwm > 255) {
     pwm=255; }

   if(pwm < 0) {
     pwm=0; }
  
   if(valorlido < 15) {
     pwm=0; }

   if(valorlido > 1000) {
     pwm=255; }
  }

// Contagem mudanca de tela
contadorflip++;
if(contadorflip > 500) {
  contadorflip=0;
  flip++; }
  
if(flip > 1) {
  flip=0; }

// Ajuste Energia
if (energiamenu == HIGH) {
  lcd.clear();
  energiaajuste=1; }
  
// Ajuste do alarme
if (alarme == HIGH) {
  lcd.clear();
  alarmeajuste=1;
  alarmemenu=1; }

// Dispara alarme
if (hora == alarmehora && minuto == alarmeminuto && alarmeon == 1) {
  freqbuzzer++;
  if(freqbuzzer > 100) {
    freqbuzzer=0; }
  if(freqbuzzer >= 0 && freqbuzzer < 51) {
    analogWrite(buzzer, 50); }
      if (freqbuzzer >= 51 && freqbuzzer < 100) {
        analogWrite(buzzer, 100); }

// Soneca e desligamento do alarme  
  if(movimento == HIGH || saida == HIGH){
    digitalWrite (buzzer, LOW);
    soneca++;
    if(soneca > 2){
     soneca=0; 
     alarmeon=0; }
     
    else {
      alarmeminuto = alarmeminuto + 9;
      if(alarmeminuto > 59){
        alarmeminuto = alarmeminuto - 59;
        alarmehora++;}
   }
}
}
// Desliga temporizador da Luz
if (ativaluz == 1 && tempoluz >= 400) {
  ativaluz=0;
  tempoluz=0;
  energia=energiatemporizador; }
}
}
