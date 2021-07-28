// Joandrea Sergiu-Catalin Grupa 2.2
#include "io430.h"
#include "LCD8B.h"
unsigned char var=0;

int main( void )
{
// Stop watchdog timer to prevent time out reset
WDTCTL = WDTPW + WDTHOLD;
TACCR0=4999; //TAR numara pâna la 4999
TACTL=0x110;
LCD8b_init();
__delay_cycles(2000);
//Nu am pus comanda LCD8b_Tcom pt ca programul incepe by default cu prima 
//coloana 
LCD8b_Tdat('J'); // cod ASCII pentru J
LCD8b_Tdat('o');// cod ASCII pentru o
LCD8b_Tdat('a');// cod ASCII pentru a
LCD8b_Tdat(' ');// cod ASCII pentru  
LCD8b_Tdat('S');// cod ASCII pentru S
LCD8b_Tdat('e');// cod ASCII pentru e
LCD8b_Tdat('r');// cod ASCII pentru r
var='A';
for(;;){
    LCD8b_Tcom(0x8D); // adresa locatie DD RAM pentru coloana 14
    LCD8b_Tdat(var); // cod ASCII pentru var
    __delay_cycles(200000); //200000 ciclii, un ciclu = 1 us 
    var=var+1;
    if(var=='N') //cand variabila noastra ar trebui sa ia valoarea N o resetam
      var='A';   // la vairabila A astfel oprim la M 
}
while((TACTL&0x0001)==0x0000); //asteapta ca TAIFG=1
TACTL=TACTL&0xFFFE; //sterge TAIFG

return 0;
}