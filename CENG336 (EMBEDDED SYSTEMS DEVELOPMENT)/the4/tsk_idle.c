#include "define.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
char game_mode = 0;
extern char receiving;
extern char send_buffer[32];
/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 *
 * Task t
 *
 **********************************************************************/
TASK(IDLE)
{
	while(1)
    {
        game_mode = 0;
        
        WaitEvent(GO_EVENT);
        ClearEvent(GO_EVENT);
        
        
        ActivateTask(ACTIVE_ID);
        SetEvent(LCD_ID,LCD_EVENT2);

        TerminateTask();
        
    }
	
}


/* End of File : tsk_task0.c */

