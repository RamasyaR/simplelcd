#include "simplelcd.h"

using namespace std;

simplelcd::simplelcd (string pinEN, string pinRS, string pinD4, string pinD5, string pinD6, string pinD7){
	EN = new GPIOClass(pinEN);
	EN->setdir_gpio("out");
	RS = new GPIOClass(pinRS);
	RS->setdir_gpio("out");
	D4 = new GPIOClass(pinD4);
	D4->setdir_gpio("out");
	D5 = new GPIOClass(pinD5);
	D5->setdir_gpio("out");
	D6 = new GPIOClass(pinD6);
	D6->setdir_gpio("out");
	D7 = new GPIOClass(pinD7);
	D7->setdir_gpio("out");
}

simplelcd::~simplelcd(){
	EN->setval_gpio("0"); delete EN; 
	RS->setval_gpio("0"); delete RS; 
	D4->setval_gpio("0"); delete D4; 
	D5->setval_gpio("0"); delete D5; 
	D6->setval_gpio("0"); delete D6; 
	D7->setval_gpio("0"); delete D7; 
} 

void simplelcd::setBit(char data_bit){
	if(data_bit& 1) D4->setval_gpio("1");
	else D4->setval_gpio("0");
	if(data_bit& 2) D5->setval_gpio("1");
	else D5->setval_gpio("0");
	if(data_bit& 4) D6->setval_gpio("1");
	else D6->setval_gpio("0");
	if(data_bit& 8) D7->setval_gpio("1");
	else D7->setval_gpio("0");
}

void simplelcd::cmd(char a){
	RS->setval_gpio("0");           
	setBit(a);				//Incoming Hex value
	EN->setval_gpio("1");         
	usleep(4000);
	EN->setval_gpio("0");        
}

void simplelcd::clear(){
	cmd(0);					//Clear the LCD
	cmd(1); 				//Move the cursor to first position
}

void simplelcd::setCursor(char a, char b){
	char temp,z,y;
	if(a== 1){
		temp = 0x80 + b - 1;		//80H is used to move the cursor
		z = temp>>4;			//Lower 8-bits
		y = temp & 0x0F;		//Upper 8-bits
		cmd(z);				//Set Row
		cmd(y);				//Set Column
	}
	else if(a== 2){
		temp = 0xC0 + b - 1;
		z = temp>>4;			//Lower 8-bits
		y = temp & 0x0F;		//Upper 8-bits
		cmd(z);				//Set Row
		cmd(y);				//Set Column
	}  
}

void simplelcd::start(){
	setBit(0x00);
	usleep(100); 
	cmd(0x03);
	usleep(5000); 
	cmd(0x03);
	usleep(11000); 
	cmd(0x03); 
	cmd(0x02); 				//  02H is used for Return 
						//     home -> Clears the RAM and initializes the LCD
	cmd(0x02);
	cmd(0x08); 				//Select Row 1
	cmd(0x00);				//Clear Row 1 Display
	cmd(0x0C);				//Select Row 2
	cmd(0x00);				//Clear Row 2 Display
	cmd(0x06);
}

void simplelcd::printChar(char data){
	char Lower_Nibble,Upper_Nibble;
	Lower_Nibble = data&0x0F;
	Upper_Nibble = data&0xF0;
	RS->setval_gpio("1");			// => RS = 1
	setBit(Upper_Nibble>>4);		//Send upper half by shifting by 4
	EN->setval_gpio("1");
	usleep(200);  
	EN->setval_gpio("0");
	setBit(Lower_Nibble);			//Send Lower half
	EN->setval_gpio("1");
	usleep(200); 
	EN->setval_gpio("0");
	usleep(3000);
}

void simplelcd::printString(const char *a){
	int i;
	for(i=0;a[i]!='\0';i++)
	   printChar(a[i]);			//Split the string using pointers and call the Char function 
}
