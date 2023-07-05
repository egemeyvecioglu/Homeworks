#include "define.h"
#include <stdio.h>
#include <string.h>
/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
extern char unhashed_string[8];
extern char hashed_string[16];

extern char hash_done;

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
char hexDigits[] = "0123456789abcdef";
void compute_hash(unsigned char *inp, unsigned char *out) {
  unsigned long hash_L;
  unsigned long hash_H;
  unsigned long tmp, tmp_L, tmp_H;
  unsigned char c, *cp;
  unsigned int i;
  char j;

  cp = inp;
  for (i = 0; i < 200; i++) {
    hash_L = 5381;
    hash_H = 0;
    while ((c = *cp++)) {
      // hash_HL << 5 //
      tmp_H = (hash_H << 5) + ((hash_L & 0xF8000000) >> 27);
      tmp_L = hash_L << 5;
      // tmp_HL + hash_HL //
      tmp = hash_L + tmp_L;
      if ((tmp < hash_L) || (tmp < tmp_L)) // 4 byte unsigned int overflow !
        tmp_H += 1;
      tmp_L = tmp;
      tmp_H = hash_H + tmp_H;
      // tmp_HL + c //
      tmp = tmp_L + c;
      if ((tmp < c) || (tmp < tmp_L)) // 4 byte unsigned int overflow !
        tmp_H += 1;
      tmp_L = tmp;
      // update hash_HL with tmp_HL //
      hash_L = tmp_L;
      hash_H = tmp_H;
    }

    //write hex values of each byte
    for(j = 7; j >= 0;j--) {
      out[j] = hexDigits[hash_H & 0xF];
      hash_H >>= 4;
    }
    for(j = 15; j >= 8;j--) {
      out[j] = hexDigits[hash_L & 0xF];
      hash_L >>= 4;
    }
    out[16] = '\0';
    //repeat algo for new str
    cp = out;
    
  }
}

/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 *
 * Task t
 *
 **********************************************************************/
TASK(HASH)
{
    
	while(1)
    {
        WaitEvent(HASH_EVENT);
        ClearEvent(HASH_EVENT);
        compute_hash(unhashed_string, hashed_string);
        hash_done = 1;
    }
    TerminateTask();
	
}


/* End of File : tsk_task0.c */



