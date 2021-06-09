
#include "device_configuration.h"
#include <xc.h>
#include <pic16f887.h>

void __interrupt() Timer0Interrupt(){
    
    int localCounter0;
    
    PORTDbits.RD0 = 1;
 
    if(PORTDbits.RD1 == 0){ // Toggle led 
        PORTDbits.RD1 = 1;
    }
    else{
        PORTDbits.RD1 = 0;
    }
    
    // ADC acquisition from AN0:
    ADCON0bits.CHS3 = 0; // Select analog channel AN0
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    
    ADCON0bits.ADON = 1; // Enable ADC
    
    for(localCounter0 = 0; localCounter0 < 20 ; localCounter0++){
        // Acquisition delay
    }
    
    ADCON0bits.GO = 1; // Start conversion
    
    while(ADCON0bits.GO_DONE == 1){
        // Conversion is not complete yet
    }
    
    // Update PWM duty cycle:
    CCPR1L = ADRESH;
    
    PIR1bits.ADIF = 0;
    
    
    PORTDbits.RD0 = 0;
    
    INTCONbits.T0IF = 0; // Clear Timer0 interruption 
    INTCONbits.T0IE = 1;// Enable Timer0 interruption
}


void main(void) {
    
    // Internal oscillator configuration:
    OSCCON = 0b01110001;
    
    
    // PORTA configuration:
    PORTA = 0; // Initialize PORTA
    TRISA0 = 1; // RA0/AN0 as input
    ANSELbits.ANS0 = 1; // RA0/AN0 as analog input
    
    
    // PORTD configuration:
    PORTD = 0x00;   // Initialize PORTD
    TRISD0 = 0;     // PORTD RD0 and RDD as outputs
    TRISD1 = 0;
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    
    
    // Timer0 configuration:
    OPTION_REGbits.T0CS = 0; // Use internal instruction cycle clock (Fosc/4)
    OPTION_REGbits.PSA = 0; // Preescaler assigned to Timer0
    OPTION_REGbits.PS2 = 0; // Preescaler rate: 1:8
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS1 = 0;
    
    
    // PWM1 configuration:
    TRISC2 = 0; // RC2 as digital output
    
    CCPR1L = 0b1110000; // Initial duty cycle
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0;
    
    CCP1CONbits.P1M1 = 0; // Single output, P1A (RC2) modulated
    CCP1CONbits.P1M0 = 0;
    CCP1CONbits.CCP1M3 = 1; // PWM mode, P1A (RC2) active high
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M1 = 0;
    CCP1CONbits.CCP1M0 = 0;       

    PIE1bits.TMR2IE = 0; // Timer2 will not cause interruption
    
    T2CONbits.TOUTPS3 = 0; // Timer2 with 1:1 postscaler
    T2CONbits.TOUTPS2 = 0;
    T2CONbits.TOUTPS1 = 0;
    T2CONbits.TOUTPS0 = 0;
    T2CONbits.T2CKPS1 = 0; // Preescaler is 4
    T2CONbits.T2CKPS0 = 2;        
    
    T2CONbits.TMR2ON = 1; // Enable Timer2
    
    
    // ADC configuration:
    ADCON1 = 0; // Left justify, Vdd and Vss as Vref
    
    ADCON0bits.ADCS1 = 0; // ADC frequency is Fosc/2
    ADCON0bits.ADCS0 = 0;
    
    
    // Interruption configuration:
    INTCONbits.T0IF = 0; // Clear Timer0 interrupt flag
    INTCONbits.T0IE = 1; // Enable Timer0 interruption
    INTCONbits.PEIE = 1; // Enavle peripheral interruptions
    INTCONbits.GIE = 1; // Enable all interruptions
    
    while(1){
    }
        
    
    return;
}
