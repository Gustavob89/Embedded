#include "configurations.h"  // Header file for Configuration Bits
#include <pic18f4550.h>      // Header file PIC18f4550 definitions
#include <xc.h>


void __interrupt(high_priority) HighPriorityInterrupt(void){
    
 return;   
}


void __interrupt(low_priority) Timer0Interrupt(void){
    INTCONbits.TMR0IE = 0;// Disable Timer0 interrupt
    
    if(LATDbits.LD0 == 0){  // Toggle RD0
        LATDbits.LD0 = 1;
    }
    else{
        LATDbits.LD0 = 0;
    }
    
    INTCONbits.INT0IF = 0;// Clear Timer0 interrupt flag
    INTCONbits.INT0IE = 1;// Enable Timer0 interrupt
 return;   
}


void main(){
    
    PORTD = 0x00;      // PORTD RD0 and RDD as outputs
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    LATDbits.LD0 = 0;
    LATDbits.LD1 = 0;

    
    // Configure Timer0:
    T0CONbits.T08BIT = 1;// Set as 8bit timer
    T0CONbits.T0CS = 0;// Internal instruction cycle clock
    T0CONbits.PSA = 1;// Preescaler not assigned
    T0CONbits.TMR0ON = 1;// Enable Timer0
    

    // Configure interruptions:
    RCONbits.IPEN = 1;// Enable interrupt priorities
    INTCON2bits.TMR0IP = 0;// Timer0 interrupt set as low priority
    
    INTCONbits.TMR0IF = 0;// Clear Timer0 interrupt flag
    
    INTCONbits.GIE = 1;// Enable all interrupts
    INTCONbits.PEIE_GIEL = 1;// Enable peripheral interrupts
    INTCONbits.TMR0IE = 1;// Enable Timer0 interrupt
    

    while(1){
    }
    
    return;
}