#include "UARTHW.h"
#include "main.h"


unsigned char SET_HW_UART(unsigned char* addr)
{
	UART_HandleTypeDef* instance = addr;
    __HAL_UART_ENABLE(instance);
}

unsigned char RESET_HW_UART(unsigned char* addr)
{
	UART_HandleTypeDef* instance = addr;
    __HAL_UART_DISABLE(instance);
}

unsigned char TRANSMISSION_HW_UART(unsigned long int* addr, unsigned char* TX)
{
	unsigned char buffer[50];
	for(unsigned char i=0;i<50;i++) buffer[i] = TX[i];
	UART_HandleTypeDef* instance = addr;
    HAL_UART_Transmit(instance, buffer, sizeof(buffer), HAL_MAX_DELAY);

}

unsigned char RECEIVE_HW_UART2(void)
{

}

unsigned char STATUS_HW_UART2(void)
{

}
