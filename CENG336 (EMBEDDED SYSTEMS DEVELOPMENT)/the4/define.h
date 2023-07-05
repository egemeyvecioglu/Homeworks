#ifndef _DEFINE_H
#define _DEFINE_H

#include "device.h"

#define _XTAL_FREQ   10000000

/***********************************************************************
 * ------------------------ Timer settings -----------------------------
 **********************************************************************/
#define _10MHZ	63055
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/***********************************************************************
 * ----------------------------- Events --------------------------------
 **********************************************************************/
#define ALARM_EVENT       0x80
#define GO_EVENT          0x40
#define HASH_EVENT        0x10
#define HASH_DONE         0x08
#define LCD_EVENT         0x01
#define LCD_EVENT2        0x02


/***********************************************************************
 * ----------------------------- Alarms --------------------------------
 **********************************************************************/
#define ACTIVE_ALARM_ID     0       /* Alarm ID (index) in tascdesc.c */
#define LCD_ALARM_ID        1       /* Alarm ID (index) in tascdesc.c */

/***********************************************************************
 * ---------------------- Task ID & Priorities -------------------------
 **********************************************************************/
#define IDLE_ID            1
#define ACTIVE_ID          2
#define HASH_ID            4
#define LCD_ID             5

#define IDLE_PRIO          10
#define ACTIVE_PRIO        8
#define LCD_PRIO           6
#define HASH_PRIO          7

typedef enum
{
    COOKING,
    SLOW_COOKING,
    UNUSED,
    NONE
}stat;

typedef struct
{
    char customer_id;
    char ing1;
    char ing2;
    char patience;
    char num_of_inr;
}customer;

typedef struct
{
    char ingr;
    stat status;
}ingredient;

#endif /* _DEFINE_H */


/* End of File : define.h */