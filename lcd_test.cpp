#include "src/GPIOClass.h"
#include "src/simplelcd.h"
#include <signal.h>



using namespace std;

int i = 0;
volatile sig_atomic_t flag = 0;
void my_function(int sig){ 
	flag = 1;
}


int main (void){
	signal(SIGINT, my_function);
 
	GPIOClass* gpio228 = new GPIOClass("228");
	(*gpio228).setdir_gpio("out");
	GPIOClass* gpio117 = new GPIOClass("117");
	(*gpio117).setdir_gpio("out");
	GPIOClass* gpio118 = new GPIOClass("118");
	(*gpio118).setdir_gpio("out");
	GPIOClass* gpio73 = new GPIOClass("73");
	(*gpio73).setdir_gpio("out");
	GPIOClass* gpio72 = new GPIOClass("72");
	(*gpio72).setdir_gpio("out");
	GPIOClass* gpio71 = new GPIOClass("71");
	(*gpio71).setdir_gpio("out");
	
	//EN RS D4 D5 D6 D7
	lcdPins lcd {*gpio228, *gpio117, *gpio118, *gpio73, *gpio72, *gpio71};
 
	Lcd_Start(lcd);
	Lcd_Clear(lcd);
	Lcd_Set_Cursor(lcd,1,5);
	Lcd_Print_String(lcd,"Hello");
	while(!flag){
		Lcd_Clear(lcd);
		Lcd_Set_Cursor(lcd,1,3);
		Lcd_Print_String(lcd,"Don't worry");
		Lcd_Set_Cursor(lcd,2,4);
		Lcd_Print_String(lcd,"Be happy!");
		usleep(1000000);
	}

	/*(*gpio228).setval_gpio("0");
 	delete gpio228;
 	gpio228 = NULL;
	(*gpio117).setval_gpio("0");
 	delete gpio117;
 	gpio117 = NULL;
	(*gpio118).setval_gpio("0");
 	delete gpio118;
 	gpio118 = NULL;
	(*gpio73).setval_gpio("0");
 	delete gpio73;
 	gpio73 = NULL;
	(*gpio72).setval_gpio("0");
 	delete gpio72;
 	gpio72 = NULL;
	(*gpio71).setval_gpio("0");
	delete gpio71;
 	gpio71 = NULL;*/
    
	return 0;
}
