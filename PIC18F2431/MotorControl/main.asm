; Includes ===============================================
#include "p18f2431.inc"
#include "configurations_and_definitions.inc"
#include "sinedata.inc"
#include "routines.inc"


; Reset and Interrupt Vectors ============================
RST code 0x00; Reset vector.

	goto Start
	HP_INTERRUPT code 0x08;
	goto high_priority_interrupt
	
	LP_INTERRUPT code 0x18
	goto low_priority_interrupt
	
	
; Main Code ==============================================
MAIN_PROGRAM code
	Start:
	; Initialize sine offset:
	lfsr 0, p_sine_offset
	movlw b'00000001'
	movwf INDF0
	; Initialize button buffer:
	lfsr 0, p_button_buffer
	movlw b'00000000'
	movwf INDF0
	; Configure and initialze modules:
	call load_sine
	call configure_interrupts
	call configure_TMER0
	call initialize_interface_port
	call initialize_duty_cycles
	call configure_motor_control_PWM
	; Initialize interrupts
	bsf INTCON, GIEH; Enable high priority interrupts.
	bsf INTCON, GIEL; Enable low priority interrupts.
	
	; Enable Timer 0 and interrupts:
	bsf T0CON, TMR0ON
	bcf INTCON, TMR0IF;
	bsf INTCON, TMR0IE

Main_loop:; Program main loop ---------------------

 goto Main_loop; -----------------------------------


high_priority_interrupt:; ------------------------------

	btg INTERFACE_PORT, OUTPUT0
	
	call check_button_increase
	call check_button_decrease
	
	; Increase pointers:
	lfsr 0, p_phase0
	lfsr 1, p_sine_offset
	clrf WREG
	movff INDF1, WREG
	addwf INDF0
	
	lfsr 0, p_phase1
	lfsr 1, p_sine_offset
	clrf WREG
	movff INDF1, WREG
	addwf INDF0
	
	lfsr 0, p_phase2
	lfsr 1, p_sine_offset
	movff INDF1, WREG
	addwf INDF0

	; Transfer values
	lfsr 0, p_phase0
	movff INDF0, FSR1L
	clrf FSR1H
	
	movff INDF1, PDC0L
	
	lfsr 0, p_phase1
	movff INDF0, FSR1L
	clrf FSR1H
	
	movff INDF1, PDC1L
	
	lfsr 0, p_phase2
	movff INDF0, FSR1L
	clrf FSR1H
	
	movff INDF1, PDC2L

	; Enable interruptions
	bsf INTCON, GIEL
	bcf INTCON, TMR0IF
 retfie; Return from interrupt ----------------------

low_priority_interrupt:; ----------------------------
	btg INTERFACE_PORT, OUTPUT1
	bcf PIR3, PTIF
 retfie; Return from interrupt ----------------------


END; Program End ===================================


