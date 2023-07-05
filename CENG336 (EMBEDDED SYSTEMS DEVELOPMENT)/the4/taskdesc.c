
#include "define.h"

/**********************************************************************
 * --------------------- COUNTER & ALARM DEFINITION -------------------
 **********************************************************************/
Counter Counter_list[] = 
  {
   /*******************************************************************
    * -------------------------- First counter ------------------------
    *******************************************************************/
   {
     {
       200,                                /* maxAllowedValue        */
        10,                                /* ticksPerBase           */
       100                                 /* minCycle               */
     },
     0,                                    /* CounterValue           */
     0                                     /* Nbr of Tick for 1 CPT  */
   }
  };

Counter Counter_kernel = 
  {
    {
      65535,                              /* maxAllowedValue        */
          1,                              /* ticksPerBase           */
          0                               /* minCycle               */
    },
    0,                                    /* CounterValue           */
    0                                     /* Nbr of Tick for 1 CPT  */
  };

AlarmObject Alarm_list[] = 
  {
   /*******************************************************************
    * -------------------------- Active task ---------------------------
    *******************************************************************/
   {
     OFF,                                  /* State                   */
     0,                                    /* AlarmValue              */
     0,                                    /* Cycle                   */
     &Counter_kernel,                      /* ptrCounter              */
     ACTIVE_ID,                             /* TaskID2Activate         */
     ALARM_EVENT,                          /* EventToPost             */
     0                                     /* CallBack                */
   },
   /*******************************************************************
    * ---------------------- Alarm LCD task ---------------------------
    *******************************************************************/
   {
     OFF,                                  /* State                   */
     0,                                    /* AlarmValue              */
     0,                                    /* Cycle                   */
     &Counter_kernel,                      /* ptrCounter              */
     LCD_ID,                               /* TaskID2Activate         */
     LCD_EVENT,                          /* EventToPost             */
     0                                     /* CallBack                */
   }
 };

#define _ALARMNUMBER_          sizeof(Alarm_list)/sizeof(AlarmObject)
#define _COUNTERNUMBER_        sizeof(Counter_list)/sizeof(Counter)
unsigned char ALARMNUMBER    = _ALARMNUMBER_;
unsigned char COUNTERNUMBER  = _COUNTERNUMBER_;
unsigned long global_counter = 0;

/**********************************************************************
 * --------------------- COUNTER & ALARM DEFINITION -------------------
 **********************************************************************/
Resource Resource_list[] = 
  {
   {
      10,                                /* priority           */
       0,                                /* Task prio          */
       0,                                /* lock               */
   }
  };
  
#define _RESOURCENUMBER_       sizeof(Resource_list)/sizeof(Resource)
unsigned char RESOURCENUMBER = _RESOURCENUMBER_;

/**********************************************************************
 * ----------------------- TASK & STACK DEFINITION --------------------
 **********************************************************************/
#define DEFAULT_STACK_SIZE      256
DeclareTask(IDLE);
DeclareTask(ACTIVE);
DeclareTask(HASH);
DeclareTask(LCD);

// to avoid any C18 map error : regroup the stacks into blocks
// of 256 bytes (except the last one).
#pragma		udata      STACK_A   
volatile unsigned char stack_idle[DEFAULT_STACK_SIZE];
#pragma		udata      STACK_B
volatile unsigned char stack_lcd[DEFAULT_STACK_SIZE];
#pragma		udata      STACK_C
volatile unsigned char stack_active[DEFAULT_STACK_SIZE];
#pragma		udata      STACK_D
volatile unsigned char stack_hash[DEFAULT_STACK_SIZE];
#pragma		udata

/**********************************************************************
 * ---------------------- TASK DESCRIPTOR SECTION ---------------------
 **********************************************************************/
#pragma		romdata		DESC_ROM
const rom unsigned int descromarea;
/**********************************************************************
 * -----------------------------  idle ------------------------------
 **********************************************************************/
rom_desc_tsk rom_desc_idle = {
	IDLE_PRIO,                       /* prioinit from 0 to 15       */
	stack_idle,                           /* stack address (16 bits)     */
	IDLE,                            /* start address (16 bits)     */
	READY,                            /* state at init phase         */
	IDLE_ID,                         /* id_tsk from 0 to 15         */
	sizeof(stack_idle)                    /* stack size    (16 bits)     */
};

/**********************************************************************
 * -----------------------------  active ------------------------------
 **********************************************************************/
rom_desc_tsk rom_desc_active = {
	ACTIVE_PRIO,                       /* prioinit from 0 to 15       */
	stack_active,                           /* stack address (16 bits)     */
	ACTIVE,                            /* start address (16 bits)     */
	SUSPENDED,                            /* state at init phase         */
	ACTIVE_ID,                         /* id_tsk from 0 to 15         */
	sizeof(stack_active)                    /* stack size    (16 bits)     */
};

/**********************************************************************
 * -----------------------------  hash ------------------------------
 **********************************************************************/
rom_desc_tsk rom_desc_hash = {
	HASH_PRIO,                       /* prioinit from 0 to 15       */
	stack_hash,                           /* stack address (16 bits)     */
	HASH,                            /* start address (16 bits)     */
    READY,                            /* state at init phase         */
	HASH_ID,                         /* id_tsk from 0 to 15         */
	sizeof(stack_hash)                    /* stack size    (16 bits)     */
};


/**********************************************************************
 * -------------------------------  LCD  ------------------------------
 **********************************************************************/
rom_desc_tsk rom_desc_LCD = {
    LCD_PRIO,                       /* prioinit from 0 to 15       */
    stack_lcd,                      /* stack address (16 bits)     */
    LCD,                            /* start address (16 bits)     */
    READY,                          /* state at init phase         */
    LCD_ID,                         /* id_tsk from 0 to 15         */
    sizeof(stack_lcd)               /* ctx address   (16 bits)     */
};

/**********************************************************************
 * --------------------- END TASK DESCRIPTOR SECTION ------------------
 **********************************************************************/
rom_desc_tsk end = {
	0x00,                              /* prioinit from 0 to 15       */
	0x0000,                            /* stack address (16 bits)     */
	0x0000,                            /* start address (16 bits)     */
	0x00,                              /* state at init phase         */
	0x00,                              /* id_tsk from 0 to 15         */
	0x0000                             /* stack size    (16 bits)     */
};

volatile rom unsigned int * taskdesc_addr = (&(descromarea)+1);
	
/* End of File : taskdesc.c */