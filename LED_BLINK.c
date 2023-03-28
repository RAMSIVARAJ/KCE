#include <AT89S52.h>	/* include header for AT89S52 */ 

void wait(void);      /* declare wait function */

void main()
{
  P2_0=0;    	/*Turn ON the LED */
  while(1)  	/* Super loop (Infinite loop) */
  {
  }
}

void wait()
{
  int i;
  for(i=0;i<10;i++) /* generate a dummy loop with 10 counts */
  {
  }
}
