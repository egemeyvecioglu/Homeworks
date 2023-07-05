#include "define.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
extern char game_mode;
extern char receive_buffer[32];
extern char send_buffer[32];

extern char sending;
extern char receiving;

char hash_done = 0;

unsigned short money_earned = 0;

char customer_num,customer_num2,ingr_count;


char unhashed_string[9];
char hashed_string[17];

customer customers[3];
ingredient ings[4];

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 *
 * Task t
 *
 **********************************************************************/
TASK(ACTIVE)
{
    int cycle = 1;
    char fj_index;
    char cooking_for[3] = {0,0,0};
    char send_cook_for_someone;
    SetRelAlarm(ACTIVE_ALARM_ID, 100, 50);
	while(1)
    {
        int i;
        send_cook_for_someone = 0;
        fj_index = 4;
        customer_num = 0;
        ingr_count = 0;
        game_mode = 1;
 
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        
        if(receive_buffer[0] == '$' && receive_buffer[1] == 'E' )
        {
            break;
        }
        
        else if(hash_done)
        {
            int byte_pos;
            hash_done = 0;
            send_buffer[0] = 'H';
            byte_pos = 1;
            for(i = 0; hashed_string[i] != '\0'; i++)
            {
                send_buffer[byte_pos++] = hashed_string[i];
            }
            send_buffer[byte_pos] = ':';
            
            sending = 1;
            TXREG = '$';
            
            continue;
        }
        

        else if(receive_buffer[0] == '$' && receive_buffer[1] == 'H')
        {
            int byte_pos = 2;
            int i;
            for(i = 0; i < 8 ; i++)
            {
                unhashed_string[i] = receive_buffer[byte_pos++];
            }
            unhashed_string[8] = '\0';
            hashed_string[16] = '\0';
            
            SetEvent(HASH_ID,HASH_EVENT);

        }

        else if(receive_buffer[0] == '$' && receive_buffer[1] == 'R' )
        {
            int byte_pos = 2;
            int i;
            for(i = 0; i < 3 ; i++) // READ MSG
            {
                customers[i].customer_id = receive_buffer[byte_pos++];
                customers[i].ing1 = receive_buffer[byte_pos++];
                customers[i].ing2 = receive_buffer[byte_pos++];
                customers[i].patience = receive_buffer[byte_pos++];
                
                customers[i].num_of_inr = (customers[i].ing1 != 'N') + (customers[i].ing2 != 'N');
                
                if(customers[i].ing1 == 'F' && customers[i].ing2 == 'J') fj_index = i;
                
                if(customers[i].customer_id != 0x00) customer_num++;
                
                     
            }

            for(i = 0 ; i < 3 ; i++) //FORGET PEOPLE WHO LEFT
            {
                if(
                    cooking_for[i] != 0 &&
                    cooking_for[i] != customers[0].customer_id &&
                    cooking_for[i] != customers[1].customer_id &&
                    cooking_for[i] != customers[2].customer_id
                )
                {
                    cooking_for[i] = 0;
                }
            }

            for(i = 0; i < 4 ; i++) // INGREDIENT STATUS
            {
                ings[i].ingr = receive_buffer[byte_pos++];
                switch(ings[i].ingr)
                {
                    case 'C':
                        ings[i].status = COOKING;
                        ingr_count++;
                        break;
                    case 'S':
                        ings[i].status = SLOW_COOKING;
                        ingr_count++;
                        break;
                    case 'N':
                        ings[i].status = NONE;
                        break;
                    default:
                        ings[i].status = UNUSED;
                        ingr_count++;
                        break;
                        
                }
            }
                
            money_earned = (((unsigned short)(receive_buffer[18]) << 8) | ((unsigned short)(receive_buffer[19]))); 
        }
        
        
        if(cycle++ % 8 != 0) // just send wait 
        {
            
            send_buffer[0] = 'W';
            send_buffer[1] = ':';

            sending = 1;
            
            TXREG = '$';
            
            if(cycle % 8 == 5) // UPDATE LCD EVERY 250 MS
            {
                customer_num2 = 0;
                if(customers[2].customer_id != 0x00) customer_num2++;
                if(customers[1].customer_id != 0x00) customer_num2++;
                if(customers[0].customer_id != 0x00) customer_num2++;
                SetEvent(LCD_ID,LCD_EVENT2);
            }
            
            
            continue;
        }
        
        
        
        if(fj_index < 3) // IF THERE IS FOOD JUDGE
        {
            char jjj,mm;
            char already_cooked_for = 0;
            for(mm = 0 ; mm < 3 ; mm++) // DO NOTHING IF I AM ALREADY COOKING FOR HIM
            {
                if(cooking_for[mm] == customers[fj_index].customer_id)
                {
                    already_cooked_for = 1;
                    break;
                }
            }

            if(!already_cooked_for)
            {
                send_cook_for_someone = 1;

                for(jjj = 0 ; jjj < 4; jjj++)
                {
                    if(ings[jjj].status == UNUSED && ings[jjj].ingr != 'N') // FIND FIRST UNUSED INGREDIENT
                    {
                        int jm;
                        for(jm = 0 ; jm < 3 ; jm++)
                        {
                            if(cooking_for[jm] == 0) // ADD TO THE CUSTOMERS THAT I AM COOKING FOR
                            {
                                cooking_for[jm] = customers[fj_index].customer_id;
                                break;
                            }
                        }

                        ings[jjj].status = SLOW_COOKING;

                        send_buffer[0] = 'S';
                        send_buffer[1] = customers[fj_index].customer_id;
                        send_buffer[2] = jjj;
                        send_buffer[3] = ':';

                        sending = 1;
                        TXREG = '$';

                        break;
                    }
                }
            }
            
            
            continue;
        }
        else if(customer_num > 0) // IF THERE IS A CUSTOMER
        {
            int i,j;
            char found;
            char ing1, ing2;
            
            for(j = 0; j < 3; j++) // SEARCH VALID CUSTOMER
            {
                int mm;
                int flag=0;
                int already_cooked_for = 0;
                if(customers[j].customer_id == 0x00 || fj_index == j) continue;

                for(mm = 0 ; mm < 3 ; mm++)
                {
                    if(cooking_for[mm] == customers[j].customer_id)
                    {
                        already_cooked_for = 1;
                        break;
                    }
                }
                
                if(already_cooked_for)continue;
                
                found = 0;
                ing1 = 'N';
                ing2 = 'N';
                
                for(i = 0; i < 4; i++) // SEARCH AVAILABLE INGREDIENTS FOR A CUSTOMER
                {
                    if(ings[i].ingr == 'N' || ings[i].ingr == 'S' || ings[i].ingr == 'C') continue;
                    
                    
                    if(customers[j].ing1 == ings[i].ingr && ing1 == 'N')
                    {
                        ing1 = i;
                        found++;
                    }
                    else if(customers[j].ing2 == ings[i].ingr && ing2 == 'N')
                    {
                        ing2 = i;
                        found++;
                    }
                    
                    if(found==customers[j].num_of_inr) // IF A CUSTOMER CAN BE COOKED FOR, COOK FOR HER/HIM
                    {
                        int mm ;
                        flag = 1;
                        
                        for(mm = 0 ; mm < 3 ; mm++)
                        {
                            if(cooking_for[mm] == 0)
                            {
                                cooking_for[mm] = customers[j].customer_id;
                                break;
                            }
                        }
                        
                        ings[ing1].status = ing1 == 'N' ? ings[ing1].status :COOKING;
                        ings[ing2].status = ing2 == 'N' ? ings[ing2].status :COOKING;
                        
                        break;
                    }
                }
                
                
                if(flag == 1) // SEND THE COOK COMMAND HERE
                {
                    send_cook_for_someone = 1;
                    
                    send_buffer[0] = 'C';
                    send_buffer[1] = customers[j].customer_id;
                    send_buffer[2] = ing1;
                    send_buffer[3] = ing2;
                    send_buffer[4] = ':';
                    
                    sending = 1;
                    TXREG = '$';
                    
                    break;
                }

            }       
        }
        if(customer_num > 0 && ingr_count == 4 && send_cook_for_someone == 0) // IF THERE IS 4 INGREDIENTS AND WE STILL CAN'T COOK FOR SOMEONE TOSS ONE UNUSED INGREDIENT
        {
            char jjj;
            for(jjj = 0 ; jjj < 4; jjj++)
            {
                if(ings[jjj].status == UNUSED && ings[jjj].ingr != 'N')
                {
                    send_buffer[0] = 'T';
                    send_buffer[1] =  jjj;
                    send_buffer[2] = ':';

                    sending = 1;
                    TXREG = '$';

                    break;
                }
            }
            
        } 
    }
    TerminateTask();
	
}


/* End of File : tsk_task0.c */

