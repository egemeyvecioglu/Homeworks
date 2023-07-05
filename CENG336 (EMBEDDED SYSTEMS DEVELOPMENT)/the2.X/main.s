PROCESSOR    18F4620

#include <xc.inc>

;Work done by Group 62 : Hasan Ege Meyvecioğlu and Mert Cenk Yediparmak

; CONFIGURATION (DO NOT EDIT)
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = ON        ; Power-up Timer Enable bit (PWRT enabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
CONFIG BORV = 3         ; Brown Out Reset Voltage bits (Minimum setting)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG PBADEN = OFF     ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))


; GLOBAL SYMBOLS
; You need to add your variables here if you want to debug them.
GLOBAL temp_portb ; Used to read PORTB before clearing interrupt flag
GLOBAL speed_level 
GLOBAL prev_portb ; Used to hold previous value of PORTB to detect clicking.
GLOBAL pause_mode
GLOBAL bar_length
GLOBAL current_beat
GLOBAL display_number ; Used to hold the number to be displayed.
GLOBAL var2 ; Used to wait after displaying
GLOBAL var1 ; Used to wait after displaying
GLOBAL temp_latc ; Used to make operations on LATC, and write to LATC only on 1 step.



    
    
; Define space for the variables in RAM
PSECT udata_acs
temp_latc:
    DS 1
temp_portb:
    DS 1
speed_level:
    DS 1
bar_length:
    DS 1
current_beat:
    DS 1
prev_portb:
    DS 1
pause_mode:
    DS 1
var1:
    DS 1
var2:
    DS 1
display_number:
    DS 1
  
PSECT CODE
; Reset vector
org 0x0000
  goto main

org 0x0008
interrupt_service_routine:
    ; WREG, STATUS and BSR registers are automatically saved to shadow registers
    ; They can be restored with retfie 1 command
    ; Check each interrupt flag. If it matches, go to its interrupt handler
    btfsc INTCON, 2           ; Check Timer0 flag, skip if clear
    goto  timer0_interrupt
    
    btfsc PIR1, 0 ; Check Timer1 flag, skip if clear
    goto  timer1_interrupt
    
    btfsc INTCON, 0 ; Check RBIF, skip if clear
    goto rb_interrupt
    
    movff PORTB, prev_portb
    retfie  1                 ; No match

rb_interrupt:
    movff PORTB,temp_portb ; Read PORTB before clearing I.F.
    
    btfss temp_portb, 4 ;Check if RB4 is pressed.
    call rb4_interrupt
    
    btfss temp_portb, 5 ;Check if RB5 is pressed.
    call rb5_interrupt
    
    btfss temp_portb, 6 ;Check if RB6 is pressed.
    call rb6_interrupt
    
    btfss temp_portb, 7 ;Check if RB7 is pressed.
    call rb7_interrupt
    
    movff temp_portb, prev_portb
    bcf     INTCON, 0
    retfie 1
    
rb4_interrupt: ;start/stop button
    bcf     INTCON, 0 ;clear RBIF 
    btfss prev_portb, 4 ; Check if there is a click 
    retfie 1
    
    btg pause_mode, 0 ; Change pause mode
    
    movff temp_portb, prev_portb
    
    btfss pause_mode, 0
    goto start_mode  ;If metronome is started, make arrangements.
    
   
    return
    
start_mode:
    movlw 00000011B ; Start with lightning RC0-1
    movwf LATC
    call start_timers ; Start timers from the beginning.
    return
    
rb5_interrupt: ; Increase 
    bcf     INTCON, 0 ;clear RBIF 
    btfss prev_portb, 5 ; Check if there is a click 
    retfie 1
    btfsc pause_mode,0  ; Check the mode, if in pause mode increase speed level else increase bar length.
    goto increase_speed_level
    goto increase_bar_length

increase_speed_level:
    movlw 9
    subwf speed_level, 0
    btfss STATUS, 2   ;If speed level < 9, increase.
    incf speed_level
    movff temp_portb, prev_portb
    return
    
increase_bar_length:
    movlw 8
    subwf bar_length, 0
    btfss STATUS, 2 ;If bar length < 8, increase.
    incf bar_length
    movff temp_portb, prev_portb
    return

rb6_interrupt:	;Decrease
    bcf     INTCON, 0 ;clear RBIF 
    btfss prev_portb, 6 ; Check if there is a click 
    retfie 1
    btfsc pause_mode,0  ; Check the mode, if in pause mode decrease speed level else decrease bar length.
    goto decrease_speed_level
    goto decrease_bar_length
    
decrease_speed_level:
    movlw 1
    subwf speed_level, 0
    btfss STATUS, 2  ;If speed level > 1, decrease.
    decf speed_level 
    movff temp_portb, prev_portb
    return
    
decrease_bar_length:
    movlw 2
    subwf bar_length, 0
    btfss STATUS, 2 ;If bar length > 2, decrease.
    decf bar_length
    movff temp_portb, prev_portb
    return
    
rb7_interrupt: ; Reset
    bcf     INTCON, 0 ;clear RBIF 
    btfss prev_portb, 7 ; Check if there is a click 
    retfie 1
    btfsc pause_mode,0 ; Check the mode, if in pause mode reset speed level else reset bar length.
    goto reset_speed_level
    goto reset_bar_length
    
reset_speed_level:
    movlw 6
    movwf speed_level ; Assign default value of speed level
    movff temp_portb, prev_portb
    return

reset_bar_length:
    movlw 4
    movwf bar_length  ; Assign default value of bar length
    movff temp_portb, prev_portb 
    return
    
timer0_interrupt:
    bcf     INTCON, 2         ; Clear Timer0 flag
    bcf     T0CON, 7        ; Disable timer 0
    
    clrf temp_latc
    
    btfsc pause_mode, 0 ; If in pause mode, LATC will be 0. Directly skip the below part.
    goto here
    
    movff current_beat, WREG
    subwf bar_length, 0
    btfsc STATUS, 2 ;if current_beat = bar_length, restart it.
    clrf current_beat    
    btfsc STATUS, 4 ;if current_beat > bar_length, restart it.
    clrf current_beat  
    
    incf current_beat ; Increase the current beat
    
    movlw 00000001B
    movwf temp_latc ;Light RC0
    
    movlw 1
    subwf current_beat, 0
    btfsc STATUS, 2
    bsf temp_latc, 1 ; If current beat = 1, then a new bar starts. Light RC1

here:    
    movff temp_latc, LATC ; Change LATC

    call start_timers ;Start timers again.

    retfie 1

timer1_interrupt:
    
    bcf  PIR1, 0         ; Clear Timer1 flag
    bcf  T1CON, 0        ; Disable time1 0
    
    clrf LATC ; Clear the LATC.
   
    retfie 1

    


main:
    ; Initialize variables
   
    movlw 0x6
    movwf speed_level ;speed_level = 6 by default.
    movlw 0x4
    movwf bar_length ; bar_length = 4 by default.
    
    clrf current_beat
    incf current_beat ; current_beat starts with 1
    
    clrf TRISA ; PORTA<0:3> will be output, others are not connected.
    setf TRISB ; PORTB<4:7> will be input, others are not connected.
    clrf TRISC ; PORTC<0:1> will be output, others are not connected.
    clrf TRISD ; PORTD will be output.
    
    clrf LATA ;clear output values
    clrf LATC
    
    ; Enable Timer1 interrupt
    bsf     PIE1, 0
    
    ; Enable global and peripheral interrupts by setting GIE and PEIE bits to 1
    clrf INTCON
    bsf INTCON,3 ; Enable BIT3: RBIE
    bsf INTCON,5 ; Enable BIT5: TMR0IE
    bsf INTCON,6 ; Enable BIT6:PEIE
    bsf INTCON,7 ; Enable BIT7:GIE 
    
    
    clrf pause_mode
    btg pause_mode, 0 ;starting on pause mode
 
    movff PORTB, prev_portb
    
    call start_timers
    

main_loop:
    call display ; Keep displaying numbers unless there is an interrupt
    bra main_loop

    
display:
    ;Display each RA<0:3> and wait for a bit for each.
    call display_ra0
    call busy_wait
    
    call display_ra1
    call busy_wait
    
    call display_ra2
    call busy_wait
    
    call display_ra3
    call busy_wait
    
display_ra0:
    movlw 1B
    movwf LATA ;Select RA0
    clrf WREG ; W = 0
    btfsc pause_mode,0
    movlw 01110011B ; 7-segment display for P
    movwf LATD ; If in pause mode display P else display nothing
    return

display_ra1:
    movlw 10B
    movwf LATA ;Select RA1
    clrf LATD
    clrf WREG ; W = 0
    btfss pause_mode,0
    call display_current_beat ; If in pause mode display nothing else display the current beat
    movwf LATD
    return
display_ra2:
    movlw 100B
    movwf LATA ;Select RA2
    clrf LATD
    bsf LATA, 2  
    clrf WREG ; W = 0
    btfss pause_mode,0
    movlw 01000000B ; If in pause mode display nothing else display dash
    movwf LATD
    return
display_ra3:
    movlw 1000B
    movwf LATA ;Select RA3
    clrf LATD
    clrf WREG ; W = 0
    btfss pause_mode,0 ; If in pause mode display speed level else dispaly bar length
    call display_bar_length
    btfsc pause_mode,0
    call display_speed_level
    movwf LATD
    return
    

start_timers:
    
    ;Initialize timers with correct starting values
    call init_tmr0   
    call init_tmr1
    
    ; Bit 6 T08BIT = 0, 16 bit configuration
    ; Bit 7 TMR0ON = 1, enable timer0 now.
    ; Bit 3 PSA = 0, prescaler will be used.
    ; Bits 2:0 T0PS2:0 = 011, 1:16 prescaling
    movlw   10000011B
    movwf   T0CON
    
    ;Enable Timer1 with no prescaling and 16 bit mode and T1RUN = 1
    movlw 11001001B
    movwf T1CON   
    
    return

init_tmr1:
    clrf TMR1
    movlw 0x3C ; Load 15536 to the timer1
    movwf TMR1H
    movlw 0xB0
    movwf TMR1L
    
    
init_tmr0:
    clrf TMR0
    clrf WREG ; Load a value to the timer0 according to the speed level 
    goto init_tmr_1000_ms
    
init_tmr_1000_ms:
    movlw 1
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_900_ms
    ;TMR0 will begin from 3036 = 0xBDC, load TMR0H and TMR0L according to this.
    movlw 0x0B
    movwf TMR0H
    movlw 0xDC
    movwf TMR0L
    return

init_tmr_900_ms:
    movlw 2
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_800_ms
    ;TMR0 will begin from 9286 = 0x2446, load TMR0H and TMR0L according to this.
    movlw 0x24
    movwf TMR0H 
    movlw 0x46
    movwf TMR0L
    return

init_tmr_800_ms:
    movlw 3
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_700_ms
    ;TMR0 will begin from 15536 = 0x3CB0, load TMR0H and TMR0L according to this.
    movlw 0x3C
    movwf TMR0H
    movlw 0xB0
    movwf TMR0L
    return

init_tmr_700_ms:
    movlw 4
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_600_ms
    ;TMR0 will begin from 21786 = 0X551A, load TMR0H and TMR0L according to this.
    movlw 0x55
    movwf TMR0H
    movlw 0x1A
    movwf TMR0L
    return
    
init_tmr_600_ms:
    movlw 5
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_500_ms
    ;TMR0 will begin from 28036 = 0x6D84, load TMR0H and TMR0L according to this.
    movlw 0x6D
    movwf TMR0H
    movlw 0x84
    movwf TMR0L
    return

init_tmr_500_ms:
    movlw 6
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_400_ms
    ;For 500 ms counter should start at 34286 = 0x85ee

    movlw 0x85
    movwf TMR0H
    movlw 0xEE
    movwf TMR0L
    return

init_tmr_400_ms:
    movlw 7
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_300_ms
    ;For 400 ms counter should start at 40536 = 0x9e58

    movlw 0x9E
    movwf TMR0H
    movlw 0x58
    movwf TMR0L
    return
    
init_tmr_300_ms:
    movlw 8
    subwf speed_level, 0
    btfss STATUS, 2
    goto init_tmr_200_ms
    ;For 300 ms counter should start at 46786 = 0xb6c2
    movlw 0xB6
    movwf TMR0H
    movlw 0xC2
    movwf TMR0L
    return

init_tmr_200_ms:
    movlw 9
    subwf speed_level, 0
    btfss STATUS, 2
    return
    ;For 200 ms counter should start at 53036 = 0xcf2c
    movlw 0xCF
    movwf TMR0H
    movlw 0x2C
    movwf TMR0L
    return


display_speed_level: ; Load speed_level to display_number
    movff speed_level, display_number
    goto display_digit
    
display_current_beat: ; Load current_beat to display_number
    movff current_beat, display_number
    goto display_digit
    
display_bar_length: ; Load bar length to display_number
    movff bar_length, display_number
    goto display_digit
    
display_digit:
    goto display_0

display_0:
    clrf WREG
    subwf display_number, 0
    btfss STATUS, 2
    goto display_1
    movlw 00111111B ;7-segment display for 0
    return

display_1:
    movlw 1
    subwf display_number, 0
    btfss STATUS, 2
    goto display_2
    movlw 00000110B ;7-segment display for 1
    return

display_2:
    movlw 2
    subwf display_number, 0
    btfss STATUS, 2
    goto display_3
    movlw 01011011B ;7-segment display for 2
    return

display_3:
    movlw 3
    subwf display_number, 0
    btfss STATUS, 2
    goto display_4
    movlw 01001111B ;7-segment display for 3
    return
    
display_4:
    movlw 4
    subwf display_number, 0
    btfss STATUS, 2
    goto display_5
    movlw 01100110B ;7-segment display for 4
    return

display_5:
    movlw 5
    subwf display_number, 0
    btfss STATUS, 2
    goto display_6
    movlw 01101101B ;7-segment display for 5
    return

display_6:
    movlw 6
    subwf display_number, 0
    btfss STATUS, 2
    goto display_7
    movlw 01111101B ;7-segment display for 6
    return

display_7:
    movlw 7
    subwf display_number, 0
    btfss STATUS, 2
    goto display_8
    movlw 00000111B ;7-segment display for 7
    return
    
display_8:
    movlw 8
    subwf display_number, 0
    btfss STATUS, 2
    goto display_9
    movlw 01111111B ;7-segment display for 8
    return

display_9:
    movlw 9
    subwf display_number, 0
    btfss STATUS, 2
    return
    movlw 01101111B ;7-segment display for 9
    return
    
busy_wait:
    ; BUSY WAITING ~1 ms to create output delay

    setf var2 
    movlw 0x3 ; should be <4
    movwf var1 
    most_outer_loop_start: ; for(var1 = 1; var1 > 0; var1--)
	outer_loop_start: ; for(var2 = 255; var2 > 0; var2--)
	    nop
	    decf var2
	    bnz outer_loop_start
	decf var1
	bnz most_outer_loop_start
    return

