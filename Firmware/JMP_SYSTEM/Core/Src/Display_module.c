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


unsigned char updateUserMsg(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{
	if(*status == IDDLE)
	{
		*status = TRUE;
//		clear(&lcdDisplay);
		setCursor(&lcdDisplay, col, linha);
		print(&lcdDisplay,userMessage);
	}

}

unsigned char eraseUserInterface()
{
	clear(&lcdDisplay);
}

unsigned char statusUserInterface(unsigned char* displayStatus)
{
	*displayStatus = IDDLE;
}

unsigned char insertUserInterface(unsigned char col, unsigned char linha,unsigned char* userData)
{
	unsigned char buffer[2];
	setCursor(&lcdDisplay, col, linha);
	cursor(&lcdDisplay);
	HAL_Delay(250);
	noCursor(&lcdDisplay);
	HAL_Delay(250);
	sprintf(buffer,"%d",*userData);
	print(&lcdDisplay,buffer);
}

unsigned char cursorChangeInterface(unsigned char col, unsigned char linha)
{
	unsigned char actualposition = col;
	actualposition++;
	if(actualposition == 15) actualposition=0;
	setCursor(&lcdDisplay, actualposition, linha);
	return actualposition;
}

unsigned char resetCursorInterface(unsigned char* cursorPosition)
{
	cursorPosition[0] = 0;
	cursorPosition[1] = 0;
}


