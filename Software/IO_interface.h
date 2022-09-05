#ifndef IO_INTERFACE_H_INCLUDED
#define IO_INTERFACE_H_INCLUDED

unsigned char* start_encoder();

unsigned char* stop_encoder();

unsigned char* start_timer();

unsigned char* stop_timer();

unsigned char reset_hardware();


unsigned char printDataDisplay(unsigned char col, unsigned char linha,unsigned char* userData);
unsigned char eraseDataDisplay();
unsigned char updateDataDisplay(unsigned char col, unsigned char linha, unsigned char *userMessage, unsigned char* status);
unsigned char homeDataDisplay(unsigned char* appName,unsigned char* companyName,unsigned char* appVersion);

unsigned char check_SD_card();
unsigned char read_SD_card();
unsigned char write_SD_card();

#endif // IO_INTERFACE_H_INCLUDED
