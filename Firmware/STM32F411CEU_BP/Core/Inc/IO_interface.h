#ifndef IO_INTERFACE_H_INCLUDED
#define IO_INTERFACE_H_INCLUDED

struct dataInsert;
struct results;
struct samples;
union vooTime;
union soloTime;
union totalTime;
union alturaSalto;
//TIMERS
void startTM3(void);
void stopTM3(void);
void startTM2(void);
void stopTM2(void);

//RESET
void rstHardware(void);

//DISPLAY
void eraseDataDisplay();
void homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);
//MEMORIA EXTERNA
unsigned char* load_SD_card(unsigned char numTeste);
void save_SD_card(unsigned char* dataToSave, unsigned char numTeste);
//COMUNICAÇÃO
void startCOMM();
void stopCOMM();
void transmissionCOMM();
void receiveCOMM();
void statusCOMM();
unsigned int wflashConfigData(struct dataInsert* dataToFlash);
void rflashConfigData(void);


#endif // IO_INTERFACE_H_INCLUDED
