#include <stdio.h>
#include <stdlib.h>
#include <p18f2550.h>
#include <delays.h>
#include <timers.h>
#include <portb.h>


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
 long timems = 0;
 int aff = 0;
 long chiffre = 0;

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
     if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
    timems++;
    WriteTimer0(65535-1000); // 1000 cycles corresponds to 1ms
    INTCONbits.TMR0IF = 0;
    }


}

#pragma interrupt low_isr
void low_isr(void)
{

if (PIE1bits.TMR2IE && PIR1bits.TMR2IF) {
    caract(chiffre);
    if (timems >= 10000) timems = 0;
    if (aff) {
        PORTBbits.RB2 = 1; //transitors pins for multiplexing
        PORTBbits.RB3 = 0;

        chiffre = (timems%1000)/100;
    }
    else {
        PORTBbits.RB2 = 0; //transitors pins for multiplexing
        PORTBbits.RB3 = 1;

        chiffre = (timems)/1000;
    }

    aff = aff^1;

    PIR1bits.TMR2IF = 0;
    }

  if (INTCON3bits.INT1IE && INTCON3bits.INT1IF)
    {
        INTCONbits.TMR0IE = INTCONbits.TMR0IE^1;

        INTCON3bits.INT1IF = 0;
    }

}


#pragma code
void main (void)
{
//initialisations
    CMCON   = 0b00000111; /* Désactive les comparateurs. */
    ADCON0  = 0b00000000;
    ADCON1  = 0b00001111;
    WDTCON  = 0 ;
    OSCCON  = 0b01101111;  //oscillator to 4mhz
    UCON    = 0 ;           /* Désactive l'USB. */
    UCFG    = 0b00001000 ;
    TRISA   = 0b01000000 ;  // segments leds in output
    TRISBbits.RB0 = 0 ;

    TRISBbits.RB1 = 1; //pin of the button

    TRISBbits.RB2 = 0;
    TRISBbits.RB3 = 0; // multiplexing with transistors in output

    RCONbits.IPEN = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.GIEH = 1;




   OpenTimer0( TIMER_INT_ON &
               T0_16BIT &
               T0_SOURCE_INT &
               T0_PS_1_1 );

    INTCON2bits.TMR0IP = 1;     //Set the Timer0 interrupts as high

   OpenTimer2( TIMER_INT_ON &
               T2_PS_1_16 &
               T2_POST_1_1);

   IPR1bits.TMR2IP = 0;

  OpenRB1INT( PORTB_CHANGE_INT_ON &
               RISING_EDGE_INT &
               PORTB_PULLUPS_OFF);

    INTCON3bits.INT1IP = 0;

//Variables Globales



//Début Programme

    while(1){

    }
}


/*FONCTIONS*/

void caract(char i)
{
    switch(i) {
         case 0 : PORTA = 0b00000000;
                  PORTBbits.RB0 = 1;
        break;
         case 1 : PORTA = 0b00111001;
                  PORTBbits.RB0 = 1;
        break;
         case 2 : PORTA = 0b00100100;
                  PORTBbits.RB0 = 0;
        break;
         case 3 : PORTA = 0b00110000;
                  PORTBbits.RB0 = 0;
        break;
         case 4 : PORTA = 0b00011001;
                  PORTBbits.RB0 = 0;
        break;
         case 5 : PORTA = 0b00010010;
                  PORTBbits.RB0 = 0;
        break;
         case 6 : PORTA = 0b00000010;
                  PORTBbits.RB0 = 0;
        break;
         case 7 : PORTA = 0b00111000;
                  PORTBbits.RB0 = 1;
        break;
         case 8 : PORTA = 0b00000000;
                  PORTBbits.RB0 = 0;
        break;
         case 9 : PORTA = 0b00010000;
                  PORTBbits.RB0 = 0;
        break;
        /* case 'o' : PORTA = 0b00011100;
                  PORTBbits.RB0 = 1;
        break; */
    }
}