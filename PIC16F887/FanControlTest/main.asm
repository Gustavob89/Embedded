#include <p16f887.inc>

; CONFIG1
; __config 0xE4F4
 __CONFIG _CONFIG1, _FOSC_INTRC_NOCLKOUT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_ON & _FCMEN_OFF & _LVP_OFF
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF    


; Reset and Interrupt Vectors ==================================================
org 0x00; start code at 0
goto Start      
    
    
org  0x04 ; Interrupt vector
goto _Interrupt

 
; Interrupt Subroutine =========================================================
_Interrupt; --------------------------------------------------------------------
 
 
 ; ADC acquisition from AN0:
 banksel ADCON0
 ;MOVLW b'11000001' ;ADC Frc clock,
 ;MOVWF ADCON0 ;AN0, On
 bcf ADCON0, 5
 bcf ADCON0, 4
 bcf ADCON0, 3
 bcf ADCON0, 2
 
 bsf ADCON0, 0
 
 nop; Acquisition delay
 nop
 nop
 nop
 nop
 nop
 
 
 banksel PORTD
 bsf PORTD, 0 
    
 bsf ADCON0, GO; Start conversion
 
 conversion_AN0:
 btfsc ADCON0, GO; Is conversion done?
 goto conversion_AN0; No, test again
 
 banksel PORTD
 bcf PORTD, 0
 
 ; Update PWM duty cycle
 banksel ADRESH
 movfw ADRESH
 
 banksel CCPR1L
 movwf CCPR1L

 ;banksel CCPR1L
 ;movlw b'00001111'
 ;movwf CCPR1L
 
 banksel PIR1
 bcf PIR1, ADIF
 
 
banksel INTCON
bcf INTCON, TMR0IF
bsf INTCON, GIE
bsf INTCON, TMR0IE
 
retfie; End of _Interrupt ------------------------------------------------------
    
_config_interrupt; -------------------------------------------------------------
     
   banksel OPTION_REG
   bcf OPTION_REG, T0CS
   bcf OPTION_REG, PSA
   bsf OPTION_REG, 2
   bsf OPTION_REG, 1
   bsf OPTION_REG, 0 
    
return; End of _config_interrupt -----------------------------------------------        
    
_config_PWM1; ------------------------------------------------------------------
   
   banksel TRISC
   bcf TRISC, 2
   
   banksel TRISD
   bcf TRISD, 0
   
   ; PWM initial duty cycle:
   banksel CCPR1L
   movlw b'1110000'
   movwf CCPR1L
   
   banksel CCP1CON
   bcf CCP1CON, 5
   bcf CCP1CON, 4
   
   banksel CCP1CON
   bcf CCP1CON, 7;  Single output, P1A (RC2) modulated
   bcf CCP1CON, 6
   bsf CCP1CON, 3; PWM mode, P1A (RC2) active high 
   bsf CCP1CON, 2
   bcf CCP1CON, 1
   bcf CCP1CON, 0
   
   banksel PIE1 
   bcf PIE1, TMR2IE; Timer 2 will not cause interrupt
   
   banksel T2CON
   bcf T2CON, 6 ; 1:1 Postcaler
   bcf T2CON, 5
   bcf T2CON, 4
   bcf T2CON, 3
   bcf T2CON, 1; Prescaler is 4
   bsf T2CON, 0
   
   bsf T2CON, 2; Timer 2 on
   
return; End of _config_PWM1 ----------------------------------------------------   
   
_config_ADC; -------------------------------------------------------------------
   
   ; Configure PORTA
   banksel PORTA; Initialize PORTA
   clrf PORTA
   banksel TRISA
   bsf TRISA, 0; Set RA0/AN0 as input
   banksel ANSEL
   bsf ANSEL, 0; RA0/AN0 as analog input
   
   ;
   banksel ADCON1
   movlw b'00000000'; Left justify, Vdd and Vss as Vref
   movwf ADCON1
   
   ; ADC conversion clock:
   banksel ADCON0
   bcf ADCON0, 7 ; Fosc/2
   bcf ADCON0, 6
   
   bsf ADCON0, 0; ADC Enabled
   
return; End of _config_ADC -----------------------------------------------------   
   
    
MAIN_PROGRAM code; =============================================================
Start:
   
    call  _config_interrupt; Configure Interrupt
    call _config_PWM1; Configure PWM1
    call _config_ADC; Configure ADC
    
    ; Enable Interrupt:
    banksel INTCON
    bcf INTCON, TMR0IF
    bsf INTCON, GIE
    bsf INTCON, TMR0IE
    
    MainLoop:
    
	nop
	nop
	nop
	
    goto MainLoop
    
end; End of MAIN_PROGRAM =======================================================
    
    
    