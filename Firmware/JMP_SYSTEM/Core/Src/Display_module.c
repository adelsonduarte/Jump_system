//User interface module: Aqui ser� possivel setar os parametros de entrada do usuario
#include "main.h"
#include "stdio.h"
#include "Display_module.h"
#include "LiquidCrystal.h"
#include "DataProcessing.h"
#include "time.h"
#include "stdlib.h"


unsigned char updateUserMsg(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status)
{
	if(*status == IDDLE)
	{
	    printDataDisplay(col,linha,userMessage);
		*status = PRINTED;
		HAL_Delay(250);
	}
}

unsigned char readyUserInterface(unsigned char* displayStatus,unsigned char* cursorPosition)
{
	statusUserInterface(displayStatus);
	resetKeyPressed();
	resetCursorInterface(cursorPosition);
	eraseDataDisplay();
}

unsigned char statusUserInterface(unsigned char* displayStatus)
{
	*displayStatus = IDDLE;
}

unsigned char cursorChangeInterface(unsigned char col, unsigned char linha)
{
	unsigned char actualposition = col;
	actualposition++;
	if(actualposition == 15) actualposition=0;
	HW_UPDATE_DATA(actualposition,linha);
	return actualposition;
}

unsigned char resetCursorInterface(unsigned char* cursorPosition)
{
	cursorPosition[0] = 0;
	cursorPosition[1] = 0;
}
