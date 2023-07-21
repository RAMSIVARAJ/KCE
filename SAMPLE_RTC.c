#include <AT89S52.h>
#define SCL P0_0
#define SDA P0_1

#define DATA P2
#define RS P0_2
#define RW P0_3
#define EN P0_4

void lcd_init(void);
void lcd_data(char);
void lcd_cmd(char);
void lcd_busy(void);
void lcd_print(char*);

void i2c_start(void);
void i2c_stop(void);
void i2c_write(char);
char i2c_read(void);
void i2c_ack(void);
void i2c_nack(void);

void main()
{
 SCL=0;
 SDA=0;
 lcd_init();
 lcd_print("Seconds = ");
 i2c_start();
 i2c_write(0xD0);
 i2c_write(0x00);
 i2c_write(0x40);
 i2c_write(0x10);
 i2c_write(0x17);
 i2c_write(0x05);
 i2c_write(0x21);
 i2c_write(0x07);
 i2c_write(0x23);
 i2c_write(0x10);
 i2c_stop();
 while(1)
 {
  char sec;
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);
  i2c_start();
  i2c_write(0xD1);
  sec=i2c_read();
  i2c_nack();
  i2c_stop();
  lcd_cmd(0x8A);
  lcd_data((sec>>4)|0x30);
  lcd_data((sec&0x0F)|0x30);
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
 RS=0;
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_data(char d)
{
 DATA=d;
 RS=1;
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
 DATA=0xFF;
 EN=1;
 s=DATA&0x80;
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

void i2c_start()
{
 SDA=1;
 SCL=1;
 SDA=0;
 SCL=0;
}

void i2c_stop()
{
 SCL=1;
 SDA=1;
 SCL=0;
 SDA=0;
}

void i2c_write(char b)
{
 char n;
 __bit ack=1;
 while(ack==1)
 {
  for(n=0;n<8;n++)
  {
    if((b&(0x80>>n))!=0)
   {
     SDA=1;
     SCL=1;
     SCL=0;
     SDA=0;
    }
    else
   {
    SDA=0;
    SCL=1;
    SCL=0;
   }
  }
  SDA=1;
  SCL=1;
  ack=SDA;
  SCL=0;
  SDA=0;
 }
}

char i2c_read(void)
{
 char m,val=0x00;
 SDA=1;
 for(m=0;m<8;m++)
 {
  SCL=1;
  if(SDA!=0)
  {
   val=val|(0x80>>m);
  }
  else
  {
  }
  SCL=0;
 }
 SDA=0;
 return val;
}

void i2c_ack()
{
 SDA=0;
 SCL=1;
 SCL=0;
}

void i2c_nack()
{
 SDA=1;
 SCL=1;
 SCL=0;
 SDA=0;
}
