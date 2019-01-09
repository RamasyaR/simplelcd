#ifndef SIMPLE_LCD_H
#define SIMPLE_LCD_H

#include "GPIOClass.h"

using namespace std;

struct lcdPins {GPIOClass EN; GPIOClass RS; GPIOClass D4; GPIOClass D5; GPIOClass D6; GPIOClass D7;};

void Lcd_SetBit(lcdPins &pin, char data_bit);
void Lcd_Cmd(lcdPins &pin, char a);
void Lcd_Clear(lcdPins &pin);
void Lcd_Set_Cursor(lcdPins &pin, char a, char b);
void Lcd_Start(lcdPins &pin);
void Lcd_Print_Char(lcdPins &pin, char data);
void Lcd_Print_String(lcdPins &pin, const char *a);

#endif
