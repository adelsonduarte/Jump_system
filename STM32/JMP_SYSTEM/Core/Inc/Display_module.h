#ifndef DISPLAY_MODULE_H_INCLUDED
#define DISPLAY_MODULE_H_INCLUDED

unsigned char startUserInterface(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
unsigned char updateUserInterface(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status);
unsigned char IOStatus(unsigned char* displayStatus, unsigned char* buttonStatus);
#endif // DISPLAY_MODULE_H_INCLUDED
