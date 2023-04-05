#include <AT89S52.h>
#define FOSC 11059200
#define TCLK FOSC/12
#define SCLK TCLK/32
#define LED P2_0
void baud_rate(int);
void send_msg(char*);
void wait (char);

void main()
{
 baud_rate(9600);
 LED=1;/*LED OFF*/
 while(1)
 {
  if(RI==1)
  {
   RI=0;
   if(SBUF=='1')
   {
    send_msg("LED TURNED ON\n\n");
    LED=0;/*LED ON*/
   }
   else if(SBUF=='0')
   {
    send_msg("LED TURNED OFF\n\n");
    LED=1;/*LED OFF*/
   }
   else
   {
    send_msg("CHECK INPUT\n\n");
   }
  }
 }
}

void baud_rate(int baud)
{
 char b;
 SCON=0X50;
 TMOD=0x20;
 b=(0xFF-(SCLK/baud))+1;
 TH1=b;
 TL1=b;
 TR1=1;
}

void send_msg(char *m)
{
 while(*m!=0)
 {
  SBUF=*m;
  *m++;
  while(TI==0)
  {}
  TI=0;
 }
}

void wait (char d)
{
 char i;
 int j;
 for(i=0;i<d;i++)
 {
  for(j=0;j<1275;j++)
  {}
 }
}
