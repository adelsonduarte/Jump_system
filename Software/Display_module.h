#ifndef DISPLAY_MODULE_H_INCLUDED
#define DISPLAY_MODULE_H_INCLUDED

#define DEZENA_H    0
#define UNIDADE_H   1
#define DEZENA_M    3
#define UNIDADE_M   4
#define DEZENA_S    6
#define UNIDADE_S   7


#define PRINTED     1


unsigned char startUserInterface(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
unsigned char updateUserMsg(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status);
unsigned char statusUserInterface(unsigned char* displayStatus);
unsigned char eraseUserInterface();
unsigned char insertUserInterface(unsigned char col, unsigned char linha,unsigned char* userData);
unsigned char cursorChangeInterface(unsigned char col, unsigned char linha);
unsigned char readyUserInterface(unsigned char* displayStatus,unsigned char* cursorPosition);
unsigned char resetCursorInterface(unsigned char* cursorPosition);









#endif // DISPLAY_MODULE_H_INCLUDED
