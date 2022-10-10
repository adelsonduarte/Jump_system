#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "INICIAR_Component.h"
#include "SubMenu.h"
#include "Data.h"


struct dataInsert{
    unsigned char userTest;
    unsigned long int userTime;
    unsigned char userMass;
    unsigned char userOverMass;
    unsigned char userConsultTest;
    unsigned int userAlturaMin;
    unsigned int userAlturaMax;
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
    return menuSub.menuNext;
}

unsigned char setSelectSub(unsigned char *selectedState)
{
    unsigned char state = *selectedState;
    menuSub.menuSelect = state;
    return menuSub.menuSelect;
}

unsigned char setInsertData(struct dataInsert* dataToInsert)
{
    struct dataInsert* userDataInput = dataToInsert;
    setUserInputConfigData(userDataInput);
}

unsigned char setTest(unsigned char* numTest)
{
    *numTest = *numTest+1;
}

unsigned char getDisplaySub(unsigned char *data)
{
    unsigned char state = *data;
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

}





