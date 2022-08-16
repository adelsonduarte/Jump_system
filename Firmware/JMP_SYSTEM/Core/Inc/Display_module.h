#ifndef DISPLAY_MODULE_H_INCLUDED
#define DISPLAY_MODULE_H_INCLUDED

unsigned char startUserInterface(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
unsigned char updateUserMsg(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status);
unsigned char statusUserInterface(unsigned char* displayStatus);
unsigned char eraseUserInterface();
unsigned char insertUserInterface(unsigned char col, unsigned char linha,unsigned char* userData);
unsigned char cursorChangeInterface(unsigned char col, unsigned char linha);
#endif // DISPLAY_MODULE_H_INCLUDED
