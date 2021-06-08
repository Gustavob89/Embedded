ROUTINES code


initialize_interface_port; ------------------------------------------

	bcf INTERFACE_PORT_TRIS, OUTPUT0
	bcf INTERFACE_PORT_TRIS, OUTPUT1
	bcf INTERFACE_PORT_TRIS, OUTPUT2
	bcf INTERFACE_PORT_TRIS, OUTPUT3
	bsf INTERFACE_PORT_TRIS, INPUT0
	bsf INTERFACE_PORT_TRIS, INPUT1
	bsf INTERFACE_PORT_TRIS, INPUT2
	bsf INTERFACE_PORT_TRIS, INPUT3
	
 return; End of initialize_interface_port ---------------------------
 

configure_TMER0; ----------------------------------------------------

	bsf T0CON, TMR0ON; Enable TIMER0
	movlw b'01001000'
	movwf T0CON
	bsf T0CON, TMR0ON; Enable TIMER0
	
 return; End of configure_TMER0 -------------------------------------
 

configure_oscillator; -----------------------------------------------

	clrf OSCTUNE
	SETF OSCCON
	bcf OSCCON, 7
	bcf OSCCON, 3
 return; End of configure_oscillator --------------------------------
 
 
configure_interrupts; -----------------------------------------------

	clrf INTCON
	movlw b'0000100'
	movwf INTCON2
	clrf INTCON3
	clrf PIE1
	clrf PIE2
	clrf PIE3
	clrf IPR1
	clrf IPR2
	clrf IPR3
	clrf RCON
	bsf RCON, IPEN
	
 return; End of configure_interrupts ---------------------------------
 
 
configure_motor_control_PWM; --------------------------------------------

	movlw b'00001010'
	movwf PTCON0
	movlw b'00000000'
	movwf PTCON1
	movlw b'01010000'
	movwf PWMCON0
	movlw b'00000000'
	movwf PWMCON1
	movlw b'00010100'
	movwf DTCON
	
	; Set PTPER
	movlw b'0000'
	movwf PTPERH
	movlw b'00111111'
	movwf PTPERL
	
	; Enable:
	bsf PTCON1, PTEN; Enable PWM Time Base
	bsf PIE3, PTIE; Enable PWM time base interrupt
	bcf PIR3, PTIF; Clear PWM time baae interrupt flag.
	
 return; End of configure_motor_control_pwm -------------------------
 
 
initialize_duty_cycles; ---------------------------------------------

	; Initialize variables
	LFSR 0, p_phase0
	movlw 0x00; 0.(85)
	movwf INDF0
	LFSR 0, p_phase1
	movlw 0x55; 1.(85)
	movwf INDF0
	LFSR 0, p_phase2
	movlw 0xAA; 2.(85)
	movwf INDF0
	
 return; End of start_motor -----------------------------------------
 
 
 check_button_increase; ----------------------------------------------
 
	; Check buttons
	lfsr 0, p_button_buffer
	lfsr 1, p_sine_offset
	
	btfsc INTERFACE_PORT, INPUT1
	bsf INDF0, INPUT1
	
	btfss INDF0, INPUT1
	goto end_button_check_increase
	
	btfsc INTERFACE_PORT, INPUT1
	goto no_increase
	
test_increase
	incf INDF1
	clrf INDF0
	
	no_increase
end_button_check_increase
 return; End of check_button_increase -------------------------------
 
 
	check_button_decrease; ----------------------------------------------
	
	; Check buttons
	lfsr 0, p_button_buffer
	lfsr 1, p_sine_offset
	
	btfsc INTERFACE_PORT, INPUT0
	bsf INDF0, INPUT0
	
	btfss INDF0, INPUT0
	goto end_button_check_decrease
	
	btfsc INTERFACE_PORT, INPUT0
	goto no_decrease
	
test_decrease
	decf INDF1, 1
	clrf INDF0
	
no_decrease
	end_button_check_decrease
	
 return; End of check_button_decrease --------------------------------
 
 
 
 