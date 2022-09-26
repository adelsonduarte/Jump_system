#ifndef UARTHW_H_INCLUDED
#define UARTHW_H_INCLUDED

unsigned char SET_HW_UART(unsigned char* instance);

unsigned char RESET_HW_UART(unsigned char* instance);

unsigned char TRANSMISSION_HW_UART(unsigned char* instance, unsigned char TX[10]);

unsigned char RECEIVE_HW_UART2(void);

unsigned char STATUS_HW_UART2(void);

#endif // UARTHW_H_INCLUDED
