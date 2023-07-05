/* 
 * File:   data_definitions.h
 * Author: e2449783
 *
 * Created on May 24, 2023, 3:36 PM
 */

#ifndef DATA_DEFINITIONS_H
#define	DATA_DEFINITIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#define TMR1_H 0x85 // 100 ms
#define TMR1_L 0xEE // 100 ms
#define TMR0_400MS_H 0xC2
#define TMR0_400MS_L 0xF7
#define TMR0_800MS_H 0x85
#define TMR0_800MS_L 0xEE
#define TMR0_1200MS_H 0x48
#define TMR0_1200MS_L 0xE5
#define TMR0_1600MS_H 0x0B
#define TMR0_1600MS_L 0xDC
#define TMR2_VAL 0x64 // 0.25 ms
    

unsigned short game_times[4][2] = 
{
    {TMR0_400MS_H,TMR0_400MS_L},
    {TMR0_800MS_H,TMR0_800MS_L},
    {TMR0_1200MS_H,TMR0_1200MS_L},
    {TMR0_1600MS_H,TMR0_1600MS_L}
};
    
typedef enum {
    A1,
    A2,
    B1,
    B2
}player_names;    
    
typedef enum {
    ACTIVE_MODE,
    INACTIVE_MODE
} MODE ;

typedef struct {
    unsigned short x;
    unsigned short y;
} pos;

typedef struct{
    char team;
    pos position;
    unsigned short selected;
    unsigned short holding_frisbee;
} player;

byte digits[6] = {
    //7-Segment Display of:
    0b00111111,         //0
    0b00000110,         //1
    0b01011011,         //2
    0b01001111,         //3
    0b01100110,         //4
    0b01101101          //5
};

#ifdef	__cplusplus
}
#endif

#endif	/* DATA_DEFINITIONS_H */

