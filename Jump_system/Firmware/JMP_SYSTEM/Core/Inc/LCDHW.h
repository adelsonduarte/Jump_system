#ifndef LCDHW_H_INCLUDED
#define LCDHW_H_INCLUDED

unsigned char HW_PRINT_DATA(unsigned char col, unsigned char linha,unsigned char* userData);
unsigned char HW_ERASE_DATA();
unsigned char HW_UPDATE_DATA(unsigned char position, unsigned char linha);
unsigned char HW_HOME_DISP();
unsigned char HW_INSERT_DATA(unsigned char col, unsigned char linha,unsigned char* userData);
#endif // LCDHW_H_INCLUDED
