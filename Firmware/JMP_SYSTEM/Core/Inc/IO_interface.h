#ifndef IO_INTERFACE_H_INCLUDED
#define IO_INTERFACE_H_INCLUDED

struct results;
struct samples;
//TIMERS
unsigned char startTM1(void);
unsigned char stopTM1(void);
unsigned char startTM2(void);
unsigned char stopTM2(void);

//RESET
unsigned char rstHardware(void);

//DISPLAY
unsigned char printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData);
unsigned char eraseDataDisplay();
//unsigned char updateDataDisplay(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status);
unsigned char updateDataDisplay(unsigned char col, unsigned char linha);
unsigned char homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
unsigned char insertDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData);
//MEMORIA EXTERNA
unsigned char check_SD_card();
unsigned char* load_SD_card(unsigned char numTeste);
unsigned char save_SD_card(unsigned char* dataToSave, unsigned char numTeste);
//COMUNICAÇÃO
unsigned char startCOMM();
unsigned char stopCOMM();
unsigned char transmissionCOMM();
unsigned char receiveCOMM();
unsigned char statusCOMM();

#endif // IO_INTERFACE_H_INCLUDED
