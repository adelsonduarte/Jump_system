#include "comunicacao.h"
#include "Bluetooth_module.h"

extern unsigned char botaoAvancar;
extern unsigned char botaoConfirmar;
extern unsigned char botaoParar;
extern unsigned char botaoMenu;
extern unsigned char botaoInserir;

unsigned char bluetooth_main()
{
    if(botaoAvancar) set_bluetooth();
    else delete_bluetooth();
}


unsigned char set_bluetooth()
{
    //if(USART2_IRQn) HAL_NVIC_EnableIRQ(USART2_IRQn);
    //Habilita a UART
    //HAL_NVIC_EnableIRQ(USART2_IRQn);
}

unsigned char delete_bluetooth()
{
    //if(USART2_IRQn) HAL_NVIC_DisableIRQ(USART2_IRQn);
 //Desabilita UART
 //

}

