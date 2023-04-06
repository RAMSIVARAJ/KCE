#include <AT89S52.h>
#define FOSC 11059200
#define TCLK FOSC/12
#define SCLK TCLK/32
#define TRIG P2_7
#define ECHO P2_6

void baud_rate(int);
void send_byte(char);
void send_msg(char*);
void wait (char);
int get_distance(void);

const char ASCII[11]="0123456789";
void main()
{
 baud_rate(9600);
 while(1)
 {
  char dist,hun,ten,one;
  dist=get_distance();
  one=(dist%10);
  dist= dist/10;
  ten = dist%10;
  hun=(dist/10);
  send_msg("Distance = ");
  send_byte(ASCII[hun]);
  send_byte(ASCII[ten]);
  send_byte(ASCII[one]);
  send_msg(" Cm\n\n");
 }
}

void baud_rate(int baud)
{
 char b;
 SCON=0X50;
 TMOD=(TMOD&0X0F)|0x20;
 b=(0xFF-(SCLK/baud))+1;
 TH1=b;
 TL1=b;
 TR1=1;
}

void send_byte(char m)
{
 SBUF=m;
 while(TI==0)
 {}
 TI=0;
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

int get_distance(void)
{
 int ultra_dist;
 char ultra_q;
 TRIG=0;
 ECHO=1;
 TR0=0;
 TMOD=(TMOD&0xF0)|(0x01);
 TH0=0x00;
 TL0=0x00;

 TRIG=1;
 for(ultra_q=0;ultra_q<10;ultra_q++)
 {}
 TRIG=0;
 
 while(ECHO==0)
 {
 }
 TR0=1;
 while(ECHO==1)
 {
 }
 TR0=0;
 ultra_dist=((TH0*256)+TL0)/54;
 return ultra_dist;
}
