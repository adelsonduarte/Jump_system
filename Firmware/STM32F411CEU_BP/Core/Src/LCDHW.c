#include "LCDHW.h"
#include "LiquidCrystal.h"

static LiquidCrystal lcdDisplay;


unsigned char HW_PRINT_DATA(unsigned char col, unsigned char linha,unsigned char* userData)
{
    setCursor(&lcdDisplay, col, linha);
//    HAL_Delay(10);
    print(&lcdDisplay,userData);
}

unsigned char HW_ERASE_DATA()
{
	clear(&lcdDisplay);
}

unsigned char HW_UPDATE_DATA(unsigned char position, unsigned char linha)
{
	setCursor(&lcdDisplay, position, linha); /***/
	cursor(&lcdDisplay);
	HAL_Delay(175);
	noCursor(&lcdDisplay);
}

unsigned char HW_HOME_DISP(unsigned char* appName, unsigned char* companyName, unsigned char* appVersion)
{
	begin(&lcdDisplay,16,4,LCD_5x10DOTS);
	setCursor(&lcdDisplay, 0, 0);
	print(&lcdDisplay,appName);
	setCursor(&lcdDisplay, 0, 1);
	print(&lcdDisplay,companyName);
	setCursor(&lcdDisplay, 0, 3);
	print(&lcdDisplay,appVersion);
	return &(lcdDisplay);
}



