#include <AT89S52.h>
#define DATA P2
#define RS P3_0
#define EN P3_2
#define RW P3_1


void lcd_init(void);
void lcd_data(char);
void lcd_cmd(char);
void lcd_busy(void);
void lcd_print(char*);

void main()
{
 EN=0;
 lcd_init();
 lcd_print("Welcome to");
 lcd_cmd(0xC0);
 lcd_print("KCE - ECE Dept.");
 while(1)
 {
  //lcd_cmd(0x1C);
 }
}

void lcd_init(void)
{
 lcd_busy();
 lcd_cmd(0x38);
 lcd_cmd(0x01);
 lcd_cmd(0x0C);
 lcd_cmd(0x06);
 lcd_cmd(0x80);
}

void lcd_cmd(char c)
{
 DATA=c;
 RS=0;//COMMAND
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_data(char d)
{
 DATA=d;
 RS=1;//DATA
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_busy()
{
 char s;
 RS=0;
 RW=1;
 DATA=0xFF;//ALL 8 BITS ARE INPUT
 EN=1;
 s=DATA&0x80;//MASK THE NON MSB BITS
 EN=0;
 while(s!=0x00)
 {
  EN=1;
  s=DATA&0x80;
  EN=0;
 }
}

void lcd_print(char*msg)
{
 while(*msg!=0x00)
 {
  lcd_data(*msg);
  *msg++;
 }
}

