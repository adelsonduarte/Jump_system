#include <stdio.h>
#include <stdlib.h>
#include "menu_module.h"
#include "main.h"

struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
    };


struct Menu menuMain ={IDDLE,IDDLE,IDDLE,IDDLE};


unsigned char getNextMain(unsigned char nextState)
{

    menuMain.menuNext = nextState;
//    printf("menuMain.menuNext = %d\n",menuMain.menuNext);
    return menuMain.menuNext;
}

unsigned char setSelectMain(unsigned char *selectedState)
{
//    printf("endereco menuMain = %d\n",&menuMain);
    unsigned char state = *selectedState;
    menuMain.menuSelect = state;
//    printf("menuMain.menuSelect = %d\n",menuMain.menuSelect);
    return menuMain.menuSelect;
}


unsigned char getDisplayMain(unsigned char *data)
{

    unsigned char state = *data;
    return state;
    //chama a fun��o display
}

unsigned char getStateMain(unsigned char *currentState)
{
    return menuMain.menuState;
}

unsigned char setStateMain(unsigned char *currentState)
{
    unsigned char state = *currentState;
    return menuMain.menuState = state;
}

unsigned char* getDataMainMenuTest()
{
    unsigned char* ptr_menuMain = &menuMain;
    printf("endereco menuMain = %d\n",&menuMain);
    return ptr_menuMain;
}










