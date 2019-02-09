#ifndef SIMPLE_LCD_H
#define SIMPLE_LCD_H

#include "GPIOClass.h"

using namespace std;

class simplelcd {
	public:
		simplelcd (string, string, string, string, string, string);
		~simplelcd();
		void clear();
		void setCursor(char, char);
		void start();
		void printChar(char);
		void printString(const char *);
	private:
		GPIOClass* RS;
		GPIOClass* EN;
		GPIOClass* D4;
		GPIOClass* D5;
		GPIOClass* D6;
		GPIOClass* D7;
		void setBit(char);
		void cmd(char);		
};

#endif
