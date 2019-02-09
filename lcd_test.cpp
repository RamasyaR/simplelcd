#include "src/GPIOClass.h"
#include "src/simplelcd.h"
#include <signal.h>

using namespace std;

volatile sig_atomic_t flag = 0;
void my_function(int sig){ 
	flag = 1;
}

int main (void){
	signal(SIGINT, my_function);
 
	simplelcd lcd("228","117","118","73","72","71");	//EN RS D4 D5 D6 D7

	lcd.start();
	lcd.clear();
	lcd.setCursor(1,3);
	lcd.printString("Hello World");
	while(!flag){
		lcd.setCursor(2,4);
		lcd.printString("Don't worry");
		usleep(1000000);
	}
    	return 0;
}
