
#include "simplelcd.h"

using namespace std;

void Lcd_SetBit(lcdPins &pin, char data_bit){
	if(data_bit& 1) pin.D4.setval_gpio("1");
	else pin.D4.setval_gpio("0");

	if(data_bit& 2) pin.D5.setval_gpio("1");
	else pin.D5.setval_gpio("0");

	if(data_bit& 4) pin.D6.setval_gpio("1");
	else pin.D6.setval_gpio("0");

	if(data_bit& 8) pin.D7.setval_gpio("1");
	else pin.D7.setval_gpio("0");
}

void Lcd_Cmd(lcdPins &pin, char a){
	pin.RS.setval_gpio("0");           
	Lcd_SetBit(pin, a); //Incoming Hex value
	pin.EN.setval_gpio("1");         
	usleep(4000);
	pin.EN.setval_gpio("0");         
}

void Lcd_Clear(lcdPins &pin){
	Lcd_Cmd(pin, 0); //Clear the LCD
	Lcd_Cmd(pin, 1); //Move the cursor to first position
}

void Lcd_Set_Cursor(lcdPins &pin, char a, char b){
	char temp,z,y;
	if(a== 1){
		temp = 0x80 + b - 1; //80H is used to move the cursor
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		Lcd_Cmd(pin, z); //Set Row
		Lcd_Cmd(pin, y); //Set Column
	}
	else if(a== 2){
		temp = 0xC0 + b - 1;
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		Lcd_Cmd(pin, z); //Set Row
		Lcd_Cmd(pin, y); //Set Column
	}   
}

void Lcd_Start(lcdPins &pin){
	Lcd_SetBit(pin, 0x00);
	usleep(100); 
	Lcd_Cmd(pin, 0x03);
	usleep(5000); 
	Lcd_Cmd(pin, 0x03);
	usleep(11000); 
	Lcd_Cmd(pin, 0x03); 
	Lcd_Cmd(pin, 0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
	Lcd_Cmd(pin, 0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
	Lcd_Cmd(pin, 0x08); //Select Row 1
	Lcd_Cmd(pin, 0x00); //Clear Row 1 Display
	Lcd_Cmd(pin, 0x0C); //Select Row 2
	Lcd_Cmd(pin, 0x00); //Clear Row 2 Display
	Lcd_Cmd(pin, 0x06);
}

void Lcd_Print_Char(lcdPins &pin, char data){
	char Lower_Nibble,Upper_Nibble;
	Lower_Nibble = data&0x0F;
	Upper_Nibble = data&0xF0;
	pin.RS.setval_gpio("1");             // => RS = 1
	Lcd_SetBit(pin, Upper_Nibble>>4);             //Send upper half by shifting by 4
	pin.EN.setval_gpio("1");
	usleep(200);  
	pin.EN.setval_gpio("0");
	Lcd_SetBit(pin, Lower_Nibble); //Send Lower half
	pin.EN.setval_gpio("1");
	usleep(200); 
	pin.EN.setval_gpio("0");
	usleep(3000);
}

void Lcd_Print_String(lcdPins &pin, const char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Print_Char(pin, a[i]);  //Split the string using pointers and call the Char function 
}
