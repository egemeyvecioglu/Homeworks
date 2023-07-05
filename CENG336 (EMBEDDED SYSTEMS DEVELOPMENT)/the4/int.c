#include "define.h"

char rcv_value;
char snd_value;
extern char game_mode = 0;

char receive_buffer[32];
char receive_buffer_pos;

char send_buffer[32];
char send_buffer_pos = 0;

char sending = 0;
char receiving = 0;

/**********************************************************************
 * Function you want to call when an IT occurs.
 **********************************************************************/
  extern void AddOneTick(void);
/*extern void MyOwnISR(void); */
  void InterruptVectorL(void);
  void InterruptVectorH(void);

/**********************************************************************
 * General interrupt vector. Do not modify.
 **********************************************************************/
#pragma code IT_vector_low=0x18
void Interrupt_low_vec(void)
{
   _asm goto InterruptVectorL  _endasm
}
#pragma code

#pragma code IT_vector_high=0x08
void Interrupt_high_vec(void)
{
   _asm goto InterruptVectorH  _endasm
}
#pragma code

/**********************************************************************
 * General ISR router. Complete the function core with the if or switch
 * case you need to jump to the function dedicated to the occuring IT.
 * .tmpdata and MATH_DATA are saved automaticaly with C18 v3.
 **********************************************************************/
char hello = 0;
#pragma	code _INTERRUPT_VECTORL = 0x003000
#pragma interruptlow InterruptVectorL
void InterruptVectorL(void)
{
	EnterISR();
	
	if (INTCONbits.TMR0IF == 1)
		AddOneTick();
	/* Here are the other interrupts you would desire to manage */
	if (PIR1bits.TXIF == 1) 
    {

        if(sending)
        {
            snd_value = send_buffer[send_buffer_pos];
            send_buffer_pos++;
            
            if(snd_value == ':')
            {
                sending = 0;
                send_buffer_pos = 0;
            }
            
            TXREG = snd_value;
        }
        
        
	}
    
	if (PIR1bits.RCIF == 1)
    {
        // receiving is the same for both picsim and real life.
        
        rcv_value = RCREG;
        
        if (rcv_value == '$') 
        {
            receive_buffer_pos = 0;  // Reset buffer index
            receive_buffer[receive_buffer_pos] = rcv_value;
            receive_buffer_pos++;
            receiving = 1;  // Set reception flag
        }
        
        else if(receiving)
        {
            receive_buffer[receive_buffer_pos] = rcv_value;
            receive_buffer_pos++;
            
            if(rcv_value == ':') 
            {
                receive_buffer[receive_buffer_pos] = '\0';  
                receiving = 0;
                
                if(receive_buffer[0] == '$' && receive_buffer[1] == 'G' && receive_buffer[3] == ':')
                {
                    SetEvent(IDLE_ID, GO_EVENT);
                }
            }
        
        }
      
        
		PIR1bits.RCIF = 0;	// clear RC1IF flag
	}
    
    if (RCSTAbits.OERR)
    {
      RCSTAbits.CREN = 0;
      RCSTAbits.CREN = 1;
    }
	LeaveISR();
}
#pragma	code

/* BE CARREFULL : ONLY BSR, WREG AND STATUS REGISTERS ARE SAVED  */
/* DO NOT CALL ANY FUNCTION AND USE PLEASE VERY SIMPLE CODE LIKE */
/* VARIABLE OR FLAG SETTINGS. CHECK THE ASM CODE PRODUCED BY C18 */
/* IN THE LST FILE.                                              */
#pragma	code _INTERRUPT_VECTORH = 0x003300
#pragma interrupt InterruptVectorH nosave=FSR0, TBLPTRL, TBLPTRH, TBLPTRU, TABLAT, PCLATH, PCLATU, PROD, section(".tmpdata"), section("MATH_DATA")
void InterruptVectorH(void)
{
  if (INTCONbits.INT0IF == 1)
    INTCONbits.INT0IF = 0;
}
#pragma	code



extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x003400
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code


/* End of file : int.c */

