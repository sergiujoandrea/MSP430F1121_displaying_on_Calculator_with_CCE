//P1.0 la P1.7 conectati la pinii D0 la D7 ai afisorului
//P2.3 -> RS (afisor)
//P2.4 -> RW (afisor)
//P2.5 -> E (afisor)
#include "io430.h"

#define ON_E 0x20
#define OFF_E 0xDF
#define ON_RW 0x10
#define OFF_RW 0xEF
#define ON_RS 0x08
#define OFF_RS 0xF7
#define DIR_DAT P1DIR
#define DAT_DAT P1OUT
#define DIR_COM P2DIR
#define DAT_COM P2OUT

void LCD8b_Tcom (char com){
  __delay_cycles(100);         //intarziere initiala
  DAT_COM = DAT_COM & OFF_RS;       //RS = 0 => instructiune
  DAT_COM = DAT_COM & OFF_RW;       //RW = 0 => scriere
  DAT_COM = DAT_COM & OFF_E;        //E = 0 => comunicatie inactiva
  DIR_DAT = 0xFF; //pini P1 -> iesiri
  DAT_COM = DAT_COM | ON_E;         //E = 1 => comunicatie activa
  DAT_DAT = com;
  __delay_cycles(1);   //intarziere
  DAT_COM = DAT_COM & OFF_E;        //E = 0 => comunicatie inactiva
  }

void LCD8b_Tdat (char dat){
  __delay_cycles(100);         //intarziere initiala
  DAT_COM = DAT_COM | ON_RS;       //RS = 0 => instructiune
  DAT_COM = DAT_COM & OFF_RW;       //RW = 0 => scriere
  DAT_COM = DAT_COM & OFF_E;        //E = 0 => comunicatie inactiva
  DIR_DAT = 0xFF; //pini P1 -> iesiri
  DAT_COM = DAT_COM | ON_E;         //E = 1 => comunicatie activa
  DAT_DAT = dat;
  __delay_cycles(1);   //intarziere
  DAT_COM = DAT_COM & OFF_E;        //E = 0 => comunicatie inactiva
}

void LCD8b_init(void){
  DIR_DAT = 0xFF;
  DIR_COM = 0X3C;
  LCD8b_Tcom(0x30);     //interfata 8 biti, afisare pe o linie
  LCD8b_Tcom(0x0C);     //0Ch display on, cursor off, blinking off
  LCD8b_Tcom(0x03);     //incrementare adresa
  LCD8b_Tcom(0x01);     //stergere continut display
}