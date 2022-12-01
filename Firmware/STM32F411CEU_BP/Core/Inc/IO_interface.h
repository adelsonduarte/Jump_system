#ifndef IO_INTERFACE_H_INCLUDED
#define IO_INTERFACE_H_INCLUDED

struct results;
struct samples;
union vooTime;
union soloTime;
union totalTime;
union alturaSalto;
//TIMERS
void startTM1(void);
void stopTM1(void);
void startTM2(void);
void stopTM2(void);

//RESET
void rstHardware(void);

//DISPLAY
//void printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData);
void eraseDataDisplay();
//void updateDataDisplay(unsigned char col, unsigned char linha);
void homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
//void insertDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData);
//MEMORIA EXTERNA
//unsigned char check_SD_card();
unsigned char* load_SD_card(unsigned char numTeste);
void save_SD_card(unsigned char* dataToSave, unsigned char numTeste);
//COMUNICAÇÃO
void startCOMM();
void stopCOMM();
void transmissionCOMM();
void receiveCOMM();
void statusCOMM();

#endif // IO_INTERFACE_H_INCLUDED
