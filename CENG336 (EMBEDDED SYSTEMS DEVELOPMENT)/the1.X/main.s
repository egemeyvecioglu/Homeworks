PROCESSOR    18F4620

#include <xc.inc>

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
GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL var4
GLOBAL tmp
GLOBAL increase_amount
GLOBAL bar_length
GLOBAL prev_portb
GLOBAL curr_portb
GLOBAL pause_mode
GLOBAL prev_porta
; Define space for the variables in RAM
PSECT udata_acs
tmp:
    DS 1
var1:
    DS 1 
var2:
    DS 1 
var3:
    DS 1 
var4:
    DS 1 
increase_amount:
    DS 1
bar_length:
    DS 1
prev_portb:
    DS 1
curr_portb:
    DS 1
pause_mode:
    DS 1
prev_porta:
    DS 1
PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
    clrf PORTA
    clrf TRISA ; make PORTA an output
    setf TRISB ; make PORTB an input
    
    clrf var1 ; var1 = 0
    setf var2 ; var2 = 11111111B = 255
    clrf increase_amount
    incf increase_amount ; increase_amount = 1
    clrf pause_mode ; pause_mode = 0

    movlw 00000111B ; light up RA1, RA2, RA3
    movwf LATA
    call busy_wait
    
    clrf WREG
    clrf LATA
    clrf var1
    setf var2
    movlw 8
    movwf bar_length ; bar_length=0
    movff bar_length,var3
    
    movff PORTB, prev_portb
main_loop:
    call check_buttons
    call metronome_update
    goto main_loop

    
busy_wait:
    ; BUSY WAITING
    ; for(var2 = 255; var1 > 0; var2--) for(var1 = 0; var1 < 256; var1++)
    setf var2 ; var2 = 255
    clrf var1 ; var1 = 0
    movlw 0x5
    movwf var3
    most_outer_loop_start:
	outer_loop_start:
	    loop_start:
		incfsz var1 ; var1 += 1; if (var1 == 0) skip next
		goto loop_start
	    decf var2
	    bnz outer_loop_start
	; 8 bit
	; var1 = 255
	; var1 = 0
	decf var3
	bnz most_outer_loop_start
    return

check_buttons:
    movff PORTB, curr_portb
    
    ;If the current value of an input port is 1, then there is no way to be a click. Hence we can skip calling further checks
    
    btfss curr_portb, 0 ; check RB0
    call rb0_pressed 
    
    btfss curr_portb, 1 ; check RB1
    call rb1_pressed
    
    btfss curr_portb, 2 ; check RB2
    call rb2_pressed
    
    btfss curr_portb, 3 ; check RB3
    call rb3_pressed
    
    btfss curr_portb, 4 ; check RB4
    call rb4_pressed
    
    movff curr_portb,prev_portb  

    btfsc pause_mode,0 ; Keep checking buttons when metronome is paused
    goto check_buttons
    
    return

rb0_pressed:
    btfsc prev_portb, 0
    btg pause_mode,0 
    btfsc prev_portb, 0
    call arrange_ra2
    return

rb1_pressed:
    btfsc prev_portb, 1
    btg increase_amount,1
    return
    
rb2_pressed:
    movlw 8
    btfsc prev_portb, 2
    movwf bar_length
    return    
    
rb3_pressed:
    movlw 2
    btfsc prev_portb, 3
    subwf bar_length
    return    
        
rb4_pressed:
    movlw 2
    btfsc prev_portb, 4
    addwf bar_length
    return  

arrange_ra2:
    btfsc pause_mode,0
    goto light_ra2
    goto off_ra2
    
light_ra2:
    movff PORTA,prev_porta
    bsf PORTA,2
    return
off_ra2:
    movff prev_porta,PORTA
    bcf PORTA,2
    return      

  
metronome_update:
    movff increase_amount,WREG
    incf WREG
    addwf var1 ; var1 += increase_amount
    bc var1_overflown ; if var1 is overflown
    return ; otherwise return
var1_overflown:
    decf var2
    movlw 190
    cpfsgt var2
    call var2_overflown
    return
var2_overflown:
    clrf var4
    setf var2
    
    movff LATA,WREG
    incf WREG ; complement ra0
    btfsc WREG,0
    incf var4 ; var4 = new RA0
    
    incf var3
    movff bar_length,WREG
    cpfslt var3
    goto light_ra1 ; if var3 >= bar length
    
    movff var4,WREG
    movwf LATA ; LATA = var4
    
    return
light_ra1:
    movlw 00000011B
    movwf LATA 
    clrf var3
    return
end resetVec


busy_wait:
    ; BUSY WAITING
    ; for(var2 = 255; var1 > 0; var2--) for(var1 = 0; var1 < 256; var1++)
    setf var2 ; var2 = 255

    movlw 0x4
    movwf var3
    most_outer_loop_start:
	
	outer_loop_start:
	    nop
	    decf var2
	    bnz outer_loop_start
	decf var3
	bnz most_outer_loop_start
    return