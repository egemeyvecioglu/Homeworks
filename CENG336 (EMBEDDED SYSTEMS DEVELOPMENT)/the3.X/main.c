/*
 * File:   main.c
 * Author: e2449783
 *
 * Created on May 23, 2023, 3:31 PM
 */
#include <xc.h>
#include "pragmas.h"
#include "adc.h"
#include "lcd.h"
#include "the3.h" 
#include "data_definitions.h"
#include <stdio.h>
#include <string.h>

volatile char CONVERT = 0;

MODE mode = INACTIVE_MODE;

short timer3_ctr;
short debounce;
byte prev_portb;
byte light_target = 1;

unsigned short teamA_score;
unsigned short teamB_score;
unsigned short number_of_steps;
unsigned short frisbee_step;
unsigned short turn; //0 means A's turn, 1 means B's turn
byte game_mode;

player players[4];

unsigned short selected_player;
unsigned short frisbee_owner;

pos frisbee_pos;
pos frisbee_target_pos;

    //TODO:
//    -(YAPTIM) Frisbi hedefinin 100 ms de 1 yan?p sönmesi için 
//    timer1 kullan (ba?lang?ç de?eri olan makro data_defitions.h da)
//    int0 interrupt?na girildi?inde di?er ko?ullar do?ruysa timer? ba?lat. 
//    Bundan sonra periyodik olarak timer1 interruptlar?nda frisbi ?eklini veya bo? string bast?r.
//    
//    -(YAPTIM)Oyun h?z?n? kontrol etmek için ADC Conversion implement et. 
//    400-800-1200-1600 ms seçenekleri için 
//    ba?lang?ç de?erleri yine data_definitions.h ta 

//    -(YAPTIM)Ayarlanan oyun h?z?na göre random fonksiyonunu da kullanarak 
//    di?er 3 oyuncuyu random hareket ettir.
//      NOT: ADC olmadan oyunculari suan hareket ettirmek için fonksiyon yazd?m (perform_random_moves_for_players)
//      sadece adc ile onun de?er araligini pdfteki gibi 4e bölerek 0-1-2-3 
//      de?erlerinden birini verip game_mode degiskenine atmak ve dogru timer initini
//      game_times[game_mode][0] game_times[game_mode][1] diyerek almak 

//    -(YAPAMADIM)7 Segmentte RBlere basarken ve active moddayken flicker oluyor. 
//    Ek olarak Gamepad deki 4 tus, özellikle yukar? ve sa? dogru düzgün çalismiyor.Bir basiyor bis basmiyor.
//      Buradaki hatalari çözmeye çalis.

//    -(YAPTIM) Frisbi hareketini gerçeklestiren kod yaz. ADC ve Timer0 interrput kullanarak bunu bast?r.
//    Frisbi 1 oyuncu tarafindan tutuldugunda veya hedefine ulastiginda INACTIVE_MODE a geç.
//    Bir tak?m frisbiyi tutabildiyse kontrolü tutan oyuncuda birak. Kimse utamad?ysa kar??dan 1 oyuncuya rastgele ver.

void __interrupt(high_priority) FNC()
{
    

    if(INTCONbits.INT0IF) 
    {
        INTCONbits.INT0IF = 0;

        for(int i = 0; i < 300; i++);
        if( (PORTBbits.RB0 == 1 && !(prev_portb & 0b00000001)) && mode == INACTIVE_MODE)
        {
            int i;
            for(i = 0 ; i < 4; i++)
            {
                if(players[i].position.x == frisbee_pos.x && players[i].position.y == frisbee_pos.y)
                {
                    mode = ACTIVE_MODE;
                    
                    number_of_steps = compute_frisbee_target_and_route(frisbee_pos.x,  frisbee_pos.y);
                    frisbee_target_pos.x = frisbee_steps[number_of_steps-1][0];
                    frisbee_target_pos.y = frisbee_steps[number_of_steps-1][1];
                    
                    printTarget();
                    TMR0H = game_times[game_mode][0];
                    TMR0L = game_times[game_mode][1];
                    T0CONbits.TMR0ON = 1;
                    break;
                }
            }
        }
        prev_portb = PORTB;
        INTCONbits.INT0IF = 0;
    }
    else if(INTCON3bits.INT1IF) 
    {
        INTCON3bits.INT1IF = 0;

        for(int i = 0; i < 300; i++);
        if(PORTBbits.RB1 == 1 && !(prev_portb & 0b00000010))
        {
            if( !  (mode == INACTIVE_MODE && players[selected_player].holding_frisbee == 1)  )
            {
                players[selected_player].selected = 0;
                selected_player = (selected_player + 1) % 4;
                players[selected_player].selected = 1;
                if(players[selected_player].team == 'A') turn = 0;
                else turn = 1; 

                printInstances();
            }            
        }

        prev_portb = PORTB;
    }
    else if(INTCONbits.RBIF)
    {
        INTCONbits.RBIF = 0;
        if(debounce == 0)
        {
            return;
        }
        LATA = 0;
        debounce = 0;
        if(PORTBbits.RB4 == 0 && (prev_portb & 0b00010000)) //up
        {
            if(players[selected_player].position.y != 1)
            {  
              
                if(selected_player == frisbee_owner)
                {
                    players[selected_player].holding_frisbee = 0;
                    frisbee_owner = 5;
                }
                    
                LCDGoto(players[selected_player].position.x,players[selected_player].position.y);
                LCDStr(" ");
                (players[selected_player].position.y)--;
                
                if(players[selected_player].position.x == frisbee_pos.x && players[selected_player].position.y == frisbee_pos.y)
                {
                    players[selected_player].holding_frisbee = 1;
                    frisbee_owner = selected_player;
                }
                    
            }
        }
        else if(PORTBbits.RB5 == 0 && (prev_portb & 0b00100000)) // right
        {
            if(players[selected_player].position.x != 16)
            {
                if(selected_player == frisbee_owner)
                {
                    players[selected_player].holding_frisbee = 0;
                    frisbee_owner = 5;
                }
                LCDGoto(players[selected_player].position.x,players[selected_player].position.y);
                LCDStr(" ");
                (players[selected_player].position.x)++;        
                
                if(players[selected_player].position.x == frisbee_pos.x && players[selected_player].position.y == frisbee_pos.y)
                {
                    players[selected_player].holding_frisbee = 1;
                    frisbee_owner = selected_player;
                }
            }     
        }
        else if(PORTBbits.RB6 == 1 && !(prev_portb & 0b01000000)) //down
        {
            if(players[selected_player].position.y != 4)
            {
                if(selected_player == frisbee_owner)
                {
                    players[selected_player].holding_frisbee = 0 ;
                    frisbee_owner = 5;
                }
                LCDGoto(players[selected_player].position.x,players[selected_player].position.y);
                LCDStr(" ");
                (players[selected_player].position.y)++;
                
                if(players[selected_player].position.x == frisbee_pos.x && players[selected_player].position.y == frisbee_pos.y)
                {
                    players[selected_player].holding_frisbee = 1;
                    frisbee_owner = selected_player;
                }
            }
        }
        else if(PORTBbits.RB7 == 1 && !(prev_portb & 0b10000000)) //left
        {
            if(players[selected_player].position.x != 1)
            {
                if(selected_player == frisbee_owner)
                {
                    players[selected_player].holding_frisbee = 0;
                    frisbee_owner = 5;
                }
                LCDGoto(players[selected_player].position.x,players[selected_player].position.y);

                LCDStr(" ");
                (players[selected_player].position.x)--;     
                
                if(players[selected_player].position.x == frisbee_pos.x && players[selected_player].position.y == frisbee_pos.y)
                {
                    players[selected_player].holding_frisbee = 1;
                    frisbee_owner = selected_player;
                }
            }
        }        
        display_score();
        printInstances();
        display_score();
        prev_portb = PORTB;
    }
    else if(PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        T2CONbits.TMR2ON = 0;
        
        timer3_ctr = (timer3_ctr + 1 ) % 3;
        if(timer3_ctr == 2) debounce = 1;
                
        TMR2 = TMR2_VAL;
        T2CONbits.TMR2ON = 1;
    }
    else if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        T1CONbits.TMR1ON = 0;
        
        if(mode == ACTIVE_MODE) printTarget();
        
        TMR1H = TMR1_H;
        TMR1L = TMR1_L;
        T1CONbits.TMR1ON = 1;
    }
    else if(INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;
        T0CONbits.TMR0ON = 0;
        
        //perform frizbi move gibi bi fonksiyon laz?m
        move_frisbee();
        perform_random_moves_for_players();
        
        unsigned short convertion = 0;
        convertion = readADCChannel(0);

        if(convertion >= 0 && convertion <= 255)
        {
            game_mode = 0;
            
//            LCDGoto(1,1);
//            LCDStr("0");
        }
        else if(convertion >=256 && convertion <=511 )
        {
            game_mode = 1;
            
//                LCDGoto(1,1);                  
//            LCDStr("1");
        }
        else if(convertion >=512 && convertion <=767 )
        {
            game_mode = 2;           
            
//            LCDGoto(1,1);         
//            LCDStr("2");
        }
        else if(convertion >=768 && convertion <=1023 )
        {
            game_mode = 3;        
            
//            LCDGoto(1,1);   
//            LCDStr("3");
        }
        
        TMR0H = game_times[game_mode][0];
        TMR0L = game_times[game_mode][1];

        if(mode == ACTIVE_MODE) T0CONbits.TMR0ON = 1;
    }
    return;
}

void move_frisbee()
{
    LATA = 0;
    if(selected_player == frisbee_owner)
    {
        players[selected_player].holding_frisbee = 0;
        frisbee_owner = 5;
    }
    LCDGoto(frisbee_pos.x,frisbee_pos.y);
    LCDStr(" ");
    frisbee_pos.x = frisbee_steps[frisbee_step][0];
    frisbee_pos.y = frisbee_steps[frisbee_step][1];
    frisbee_step++;
    LCDGoto(frisbee_pos.x,frisbee_pos.y);
    LCDGoto(frisbee_pos.x,frisbee_pos.y);
    LCDDat(6);
    if(frisbee_step == number_of_steps)
    {
        players[selected_player].selected = 0;
        short flag = 0;
        for(int i = 0; i < 4 ; i++)
        {
            if(players[i].position.x == frisbee_pos.x && players[i].position.y == frisbee_pos.y)
            {
                selected_player = i;
                frisbee_owner = i;
                players[i].holding_frisbee = 1;
                players[i].selected = 1;
                if(players[i].team == 'A') 
                {
                    turn = 0;
                    teamA_score++;
                } 
                    
                else
                {
                    turn = 1;
                    teamB_score++;
                } 
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            if(turn == 0)
            {
                turn = 1;
                players[B1].selected = 1;
                selected_player = B1;
            }
            else
            {
                turn = 0;
                players[A1].selected = 1;
                selected_player = A1;
            } 
        }
        T0CONbits.TMR0ON = 0;
        frisbee_step = 0;
        mode = INACTIVE_MODE;
    }
    printInstances();
    display_score();
    return;
}

void perform_random_moves_for_players()
{
    byte tmp = LATA;
    LATA = 0;
    for(unsigned short i = 0; i < 4; i++)
    {
        if(i != selected_player)
        {
            unsigned short move = random_generator(9);
            if(i == frisbee_owner)
            {
                players[i].holding_frisbee = 0;
                frisbee_owner = 5;
            }
            switch(move)
            {
                case 0: //up
                if(players[i].position.y != 1)
                {

                    LCDGoto(players[i].position.x,players[i].position.y);
                    LCDStr(" ");
                    (players[i].position.y)--;        
                }  
                case 1: //right
                    if(players[i].position.x != 16)
                    {
                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.x)++;          
                    }
                    break;
                case 2: // down
                    if(players[i].position.y != 14)
                    {
                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.y)++;          
                    }
                    break;
                case 3: //left
                    if(players[i].position.x != 1)
                    {
                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.x)--;          
                    }
                    break;
                case 4: //up-right
                    if(players[i].position.y != 1 && players[i].position.x != 16)
                    {

                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.y)--;        
                        (players[i].position.x)++;    
                    }  
                    break;
                case 5: //down-right
                    if(players[i].position.y != 4 && players[i].position.x != 16)
                    {

                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.y)++;        
                        (players[i].position.x)++;    
                    }  

                    break;
                case 6: //down-left
                    if(players[i].position.y != 4 && players[i].position.x != 1)
                    {

                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.y)++;        
                        (players[i].position.x)--;    
                    }  
                    break;
                case 7: //up-left
                    if(players[i].position.y != 1 && players[i].position.x != 1)
                    {

                        LCDGoto(players[i].position.x,players[i].position.y);
                        LCDStr(" ");
                        (players[i].position.y)--;        
                        (players[i].position.x)--;    
                    }  
                    break;
                case 8: // no move
                    break;
            }
            LATA = tmp;
            if(players[i].position.x == frisbee_pos.x && players[i].position.y == frisbee_pos.y)
            {
                players[i].holding_frisbee = 1;
                frisbee_owner = i;
            }            

        }
        printInstances();
    }
    return;
}

void initGame()
{
    teamA_score = 0;
    teamB_score = 0;
    
    game_mode = 0; //Corresponds to 400ms see game_times array in "data_definitions.h"
    frisbee_step = 0;
    selected_player = A1;
    frisbee_owner = 5;
    
    players[A1] = (player) {'A', {3,2}, 1, 0};
    players[A2] = (player) {'A', {3,3}, 0, 0};
    players[B1] = (player) {'B', {14,2},0, 0};
    players[B2] = (player) {'B', {14,3},0, 0};
    
    frisbee_pos = (pos) {9,2};
        
}

void setLCD()
{
    InitLCD();  
    
    LCDAddSpecialCharacter(0, teamA_player);
    LCDAddSpecialCharacter(1, selected_teamA_player);
    LCDAddSpecialCharacter(2, selected_teamA_player_with_frisbee);

    LCDAddSpecialCharacter(3, teamB_player);
    LCDAddSpecialCharacter(4, selected_teamB_player);
    LCDAddSpecialCharacter(5, selected_teamB_player_with_frisbee);
    
    LCDAddSpecialCharacter(6, frisbee);
    LCDAddSpecialCharacter(7, frisbee_target);   
    
        
    return;
}

void printTarget()
{
    byte tmp = LATA;
    LATA = 0;
    LCDGoto(frisbee_target_pos.x, frisbee_target_pos.y);
    if(light_target)
    {
        LCDDat(7);
        light_target = 0;
    }
    else
    {
        LCDStr(" ");
        light_target = 1;
    }
    LATA = tmp;
    return;
}

void printInstances()
{
    byte tmp = LATA;
    LATA = 0;
            
    LCDGoto(players[A1].position.x, players[A1].position.y);
    LCDDat(players[A1].selected ? (players[A1].holding_frisbee ? 2 : 1) : 0);

    LCDGoto(players[A2].position.x, players[A2].position.y);
    LCDDat(players[A2].selected ? (players[A2].holding_frisbee ? 2 : 1) : 0);
            
    LCDGoto(players[B1].position.x, players[B1].position.y);
    LCDDat(players[B1].selected ? (players[B1].holding_frisbee ? 5 : 4) : 3);

    LCDGoto(players[B2].position.x, players[B2].position.y);
    LCDDat(players[B2].selected ? (players[B2].holding_frisbee ? 5 : 4) : 3);
    
    if(frisbee_owner == 5)
    {
        LCDGoto(frisbee_pos.x, frisbee_pos.y);
        LCDDat(6);        
    }
    LATA = tmp;

}

void set7Segment()
{
    TRISD = 0; // PORTD will be output
   
    TRISAbits.RA3 =  0;
    TRISAbits.RA4 =  0;  // RA 3-4-5 will be output
    TRISAbits.RA5 =  0;

    return;
}

void display_score()
{
    if(timer3_ctr  == 0)
    {
        LATA = 0b1000;
        LATD = digits[teamA_score]; // display team A score
    }
    else if(timer3_ctr  == 1)
    {
        LATA = 0b10000;
        LATD = 0b01000000; // display "-"
    }
    else if(timer3_ctr == 2)
    {
        LATA = 0b100000;
        LATD = digits[teamB_score]; // display team B score
    }
    return;

}

void main(void) { 
    
    initGame();
    setLCD();
    set7Segment();
    initADC();
    debounce = 0;
    

    TRISB= 0b11110011;
    LATB = 0;
    prev_portb = PORTB ;
    
    INTCONbits.INT0IE = 1; //Enable INT0 pin interrupt
    INTCONbits.INT0IF = 0;  

    RCONbits.IPEN = 1;
    
    INTCONbits.RBIE = 0;
    INTCON2bits.RBIP = 1;
     
    
    INTCON3bits.INT1IE = 1; // Enable INT1 pin interrupt
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT1IP = 1; // high-priority

    T3CON = 0;
    TMR3H = 0;
    TMR3L = 0;
    
    T3CONbits.TMR3ON = 1; // Enable timer3 for random generation
    
    PIE1bits.TMR2IE = 1; //ENable timer2 for 7-segment display
    PIR1bits.TMR2IF = 0;
    IPR1bits.TMR2IP = 1;
    
    TMR2 = TMR2_VAL;
    
    T2CON = 0b00000001;
    
    PIE1bits.TMR1IE = 1; // Enable Timer 1 to show frisbee target
    PIR1bits.TMR1IF = 0;
    IPR1bits.TMR1IP = 1;

    TMR1H = TMR1_H;
    TMR1L = TMR1_L;
    T1CON = 0b11110000; // 16 bit, 1:8 prescale
    
    TMR0H = TMR0_400MS_H;
    TMR0L = TMR0_400MS_L;
    
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    INTCON2bits.TMR0IP = 1;
    
    T0CON = 0b00000101;  // 16 bit, 1:64 prescale
    
    
    
    INTCONbits.GIE = 1;
    
    LATB = 0;
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1; 
    
    
    T2CONbits.TMR2ON = 1;
    T1CONbits.TMR1ON = 1;
    INTCONbits.PEIE = 1;
    
    printInstances();
    while(1)
    {
        display_score();    
    }

    
    return ;
}