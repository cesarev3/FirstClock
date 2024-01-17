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
int segundo,minuto, hora, dia, mes, ano; 
int ADClido = 0;
int contador = 0;
int ajuste = 1;
int movimento = 0;
int saida = 0;
int menu = 1;
int controle = 0;
int valorlido = 0;
int pwm = 0;

// definindo variaveis numerias decimais
float temperatura = 0;

// definindo constantes inteiras para portas Arduino
const int botao1 = 9;
const int botao2 = 8;
const int LDR = 1;
const int LM35 = 0;
const int Led = 10;

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
pinMode (botao1, INPUT);
pinMode (botao2, INPUT);
pinMode (Led, OUTPUT);

// definindo conteudo das variaveis  
UtlTime=0;   
minuto=-1;   
hora=-1;   
dia=0;   
mes=0;   
ano=14;
contador = 0;

// definindo comunicacao serial
Serial.begin(9600);

// especificando tensao de referencia das portas analogicas para o LM35
analogReference(INTERNAL); //Se estiver usando Arduino Mega, use INTERNAL1V1

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
movimento = digitalRead(botao1);
saida = digitalRead(botao2);

// Preparando leitura do LM35
ADClido = analogRead(LM35);
temperatura = ADClido * 0.1075268817204301;

// Leitura LDR
valorlido = analogRead(LDR);
pwm=(valorlido/3.5);

if (pwm > 255) {
  pwm=255; }

if (pwm < 0) {
  pwm=0; }
  
if (valorlido < 50) {
  pwm=0; }

if (valorlido > 1000) {
  pwm=255; }

analogWrite(Led, pwm);

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
  lcd.clear();

    if(menu > 6) {
      menu=0;
      ajuste=0; }
}

//Serial.print("Valor Menu:");
//Serial.print(menu);
//Serial.print(" Contador: ");
//Serial.print(contador);
//Serial.print(" Ajuste: ");
//Serial.print(ajuste);
//Serial.print(" Controle: ");
//Serial.print(controle);
Serial.print(" PWM LDR: ");
Serial.print(pwm);
Serial.print(" Valor LDR: ");
Serial.println(valorlido);


// Chave de selecao de calculo ou ajuste
if(ajuste == 0) {
  
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
}
}
