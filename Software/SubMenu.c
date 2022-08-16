#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"


struct dataInsert{
    unsigned char userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned char userAlturaMin;
    unsigned char userAlturaMax;
    unsigned char userNumSaltos;
    unsigned char userIntervalSaltos;
    unsigned char userCMJ;
    unsigned char userAlturaDJ;
    unsigned char userNumSeries;
    unsigned char userIntervalSeries;
    unsigned char userCommConfig;
    unsigned char userSelectTapete;
    unsigned char userSelectSensorChannel;
};
struct Menu{
        unsigned char menuNext;
        unsigned char menuSelect;
        unsigned char menuDisplay;
        unsigned char menuState;
        struct dataInsert menuInsert;
    };


struct Menu menuSub ={IDDLE,IDDLE,IDDLE,IDDLE};


unsigned char getNextSub(unsigned char nextState)
{
    menuSub.menuNext = nextState;
//    printf("menuSub.menuNext = %d\n",menuSub.menuNext);
    return menuSub.menuNext;
}

unsigned char setSelectSub(unsigned char *selectedState)
{
//    printf("endereco menuSub = %d\n",&menuSub);
    unsigned char state = *selectedState;
    menuSub.menuSelect = state;
    return menuSub.menuSelect;
}

unsigned char setInsertSub(struct dataInsert* dataToInsert)
{
    //AQUI DEVO COLOCAR UMA FUNCAO PARA CHAMAR UM .C RELACIONADO A DADOS, PARA FAZER A CÓPIA DAS INFORMAÇÕES
    //POR ENQUANTO VOU FAZER CONFORME ABAIXO:
    menuSub.menuInsert.userTime = dataToInsert->userTime;
    menuSub.menuInsert.userMass = dataToInsert->userMass;
    menuSub.menuInsert.userOverMass = dataToInsert->userOverMass;
    menuSub.menuInsert.userConsultTest = dataToInsert->userConsultTest;
    menuSub.menuInsert.userAlturaMin = dataToInsert->userAlturaMin;
    menuSub.menuInsert.userAlturaMax = dataToInsert->userAlturaMax;
    menuSub.menuInsert.userNumSaltos = dataToInsert->userNumSaltos;
    menuSub.menuInsert.userIntervalSaltos = dataToInsert->userIntervalSaltos;
    menuSub.menuInsert.userCMJ = dataToInsert->userCMJ;
    menuSub.menuInsert.userAlturaDJ = dataToInsert->userAlturaDJ;
    menuSub.menuInsert.userNumSeries = dataToInsert->userNumSeries;
    menuSub.menuInsert.userIntervalSeries = dataToInsert->userIntervalSeries;
    menuSub.menuInsert.userCommConfig = dataToInsert->userCommConfig;
    menuSub.menuInsert.userSelectTapete = dataToInsert->userSelectTapete;
    menuSub.menuInsert.userSelectSensorChannel = dataToInsert->userSelectSensorChannel;

    printf("menuSub.menuInsert.userCommConfig = %d\n",menuSub.menuInsert.userCommConfig);
    printf("menuSub.menuInsert.userSelectTapete = %d\n",menuSub.menuInsert.userSelectTapete);
}

unsigned char getInsertSub(struct dataInsert* getData)
{

//    static unsigned char data[USER_SIZE];
//
//    for(unsigned char i=0;i<USER_SIZE;i++)
//    {
//        data[i] = menu.menuInsert[i];
//    }
//    return data;
}

unsigned char getDisplaySub(unsigned char *data)
{
    unsigned char state = *data;
    //chama a função display
}

unsigned char getStateSub(unsigned char *currentState)
{
    return menuSub.menuState;
}

unsigned char setStateSub(unsigned char *currentState)
{
    unsigned char state = *currentState;
    return menuSub.menuState = state;
}


unsigned char* getDataSubMenuTest()
{
    unsigned char* ptr_menuSub = &menuSub;
//    printf("endereco menuSub = %d\n",&menuSub);
    return ptr_menuSub;
}





