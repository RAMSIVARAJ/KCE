#ifndef LED_H
#define LED_H

void led_on(void)
{
 LED=0;
}

void led_off(void)
{
 LED=1;
}

void led_toggle(void)
{
 LED=!LED;
}

#endif
