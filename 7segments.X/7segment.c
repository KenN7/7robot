#include <stdio.h>
#include <stdlib.h>
#include <p18f2550.h>
#include <delays.h>


/////*CONFIGURATION*/////
#pragma config FOSC = HS
#pragma config FCMEN = ON
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = ON
#pragma config BORV = 2
#pragma config VREGEN = ON
#pragma config WDT = OFF
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = ON
#pragma config LVP = OFF
#pragma config DEBUG = ON
#pragma config PLLDIV = 2

 int i;
/////*PROTOTYPES*/////

void high_isr(void);
void low_isr(void);
void caract(char i);


/////*VARIABLES GLOBALES*/////


/////*INTERRUPTIONS*/////

#pragma code high_vector=0x08
void high_interrupt(void)
{
     _asm GOTO high_isr _endasm
}
#pragma code low_vector=0x18
void low_interrupt(void)
{
     _asm GOTO low_isr _endasm
}

#pragma code

#pragma interrupt high_isr
void high_isr(void)
{
   
}

#pragma interrupt low_isr
void low_isr(void)
{


}

#pragma code
void main (void)
{
//initialisations
    CMCON   = 0b00000111; /* Désactive les comparateurs. */
    ADCON0  = 0b00000000;
    ADCON1  = 0b00001111;
    WDTCON  = 0 ;
    OSCCON  = 0b01111111;
    UCON    = 0 ;           /* Désactive l'USB. */
    UCFG    = 0b00001000 ;
    TRISA   = 0b01000000 ;
    TRISBbits.RB0 = 0 ;
   
//Variables Globales
//Début Programme
    while(1){
        for (i = 0; i<10; i++) {
           caract(i);
           Delay10KTCYx(200);

        }
    }
}


/*FONCTIONS*/

void caract(char i)
{
    switch(i) {
         case 0 : PORTA = 0b00111111;
                  PORTBbits.RB0 = 0;
        break;
         case 1 : PORTA = 0b00000110;
                  PORTBbits.RB0 = 0;
        break;
         case 2 : PORTA = 0b00011011;
                  PORTBbits.RB0 = 1;
        break;
         case 3 : PORTA = 0b00001111;
                  PORTBbits.RB0 = 1;
        break;
         case 4 : PORTA = 0b00100110;
                  PORTBbits.RB0 = 1;
        break;
         case 5 : PORTA = 0b00101101;
                  PORTBbits.RB0 = 1;
        break;
         case 6 : PORTA = 0b00111101;
                  PORTBbits.RB0 = 1;
        break;
         case 7 : PORTA = 0b00000111;
                  PORTBbits.RB0 = 0;
        break;
         case 8 : PORTA = 0b00111111;
                  PORTBbits.RB0 = 1;
        break;
         case 9 : PORTA = 0b00101111;
                  PORTBbits.RB0 = 1;
        break;
        /* case o : PORTA = 0b00011100;
                  PORTBbits.RB0 = 1;
        break; */
    }
}