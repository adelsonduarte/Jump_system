//User interface module: Aqui ser� possivel setar os parametros de entrada do usuario
#include "main.h"
#include "Display_module.h"
#include "LiquidCrystal.h"

static LiquidCrystal lcdDisplay;

unsigned char startUserInterface(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion)
{
	begin(&lcdDisplay,16,4,LCD_5x10DOTS);
	setCursor(&lcdDisplay, 0, 0);
	print(&lcdDisplay,appName);
	setCursor(&lcdDisplay, 0, 1);
	print(&lcdDisplay,companyName);
	setCursor(&lcdDisplay, 0, 3);
	print(&lcdDisplay,appVersion);
	return 1;
//	return &(lcdDisplay);
}


unsigned char updateUserInterface(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{
	if(*status == IDDLE)
	{
		*status = TRUE;
		clear(&lcdDisplay);
		setCursor(&lcdDisplay, col, linha);
		print(&lcdDisplay,userMessage);
	}

}

unsigned char eraseUserInterface()
{
	clear(&lcdDisplay);
}

unsigned char IOStatus(unsigned char* displayStatus, unsigned char* buttonStatus)
{
	*displayStatus = IDDLE;
	*buttonStatus = IDDLE;
}


