/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "header.h"        /* Function / Parameters                           */
#include <libpic30.h>


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */


/******************************************************************************/
/* Configuartion                                                              */
/******************************************************************************/

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void Setup_Timer3()
{
	IEC0bits.T3IE = 0; //Disable timer2 interrupt
	T3CONbits.TON = 0; //Disable timer
	T3CONbits.TSIDL = 0; //Continue operation in idle mode
	T3CONbits.TGATE = 0; //Timer gate accumulation disabled
	T3CONbits.TCKPS = 0b01; //Timer prescale 1:1, 1:8, 1:64, 1:256
	//T3CONbits.T32 = 0; //32 bit timer disabled
	T3CONbits.TCS = 0; //Internal clock source


	PR3 = 65535; //Period register

	TMR3=0;	
}

void Setup_OC_Single_Shot()
{	
	_RP5R = 0b10010; //Tie OC1 to RP12
	_OC1IE = 0; //Disable OC1 interrupt
	_TRISB5 = 0;

	_OCSIDL = 0; //OC continues in idle mode
	_OCFLT = 0; //Fault status bit, N/A as fault pin is disabled
	_OCTSEL = 1; //Timer3 source
	_OCM = 0b000; //Disables OC for now
}

void enable_timer3()
{
	TMR3=0;
	T3CONbits.TON = 1;
}

void output_compare_fire()
{
	_OCM = 0b010;
	enable_timer3();
}	

void disable_timer3()
{
	TMR3=0;
	T3CONbits.TON = 0;
}


int16_t main(void)
{
    // Initialize IO ports and peripherals.
    ConfigureOscillator();
    InitApp();
    Setup_OC_Single_Shot();

    while (1)
    {
        OC1R = 700;
	output_compare_fire();
        __delay_ms(2);
        //  led = !led;
        //  __delay_ms(100);
    }
}

