#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "main.h"


/*Cart�o de mem�ria -> OK SD_module.c TESTAR
transmiss�o/recep��o bluetooth -> OK DMA_exemplo TESTAR
Rel� -> Rele_module.c TESTAR
Display 16x4; -> LiquidCrystal.c TESTAR*/

//Variaveis global, interrupcoes
unsigned char botaoAvancar;
unsigned char botaoConfirmar;
unsigned char botaoParar;
unsigned char botaoMenu;
unsigned char botaoInserir;

unsigned char key = 0;
unsigned char* ptr_key = &key;

void main(void)
{

    unsigned char menuSub = IDDLE;
    //display
    printf("05.Jump System NG\nCEFISE Versao 0.1 0.1\n");
    *ptr_key = getchar();
    while( getchar() != '\n' );
    while(*ptr_key != AVANCAR);


    //Esse while � s� pra teste. Na aplica��o real teremos interrup��o para chamar o menu_module.c
    while(1)
    {
        switch(menuSub)
        {
            case IDDLE:
                menuSub = menuStateMachine(&menuSub);
            break;
            case START_TEST:
//                printf("chama .c com a maquina de estado do START_TEST\n");
                menuSub = initStateMachine(&menuSub);
            break;

            case CONSULT_DATA:
                printf("chama .c com a maquina de estado do CONSULT_DATA\n");
            break;

            case CONFIG_SENSOR:
                printf("chama .c com a maquina de estado do CONFIG_SENSOR\n");
            break;

            case EXPORT_DATA:
                printf("chama .c com a maquina de estado do EXPORT_DATA\n");
            break;

            case ERASE_DATA:
                printf("chama .c com a maquina de estado do ERASE_DATA\n");
            break;
        }

    }


}
