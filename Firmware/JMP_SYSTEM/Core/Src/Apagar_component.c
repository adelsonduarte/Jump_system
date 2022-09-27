#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Exportar_component.h"
#include "SubMenu.h"
#include "DisplayMessages.h"
#include "DataProcessing.h"
#include "Data.h"
#include "Display_module.h"


struct samples{
    unsigned char sampleNum;
    unsigned int uiVooTime;
    unsigned int uiSoloTime;
};
struct results{
    unsigned char resultTestNum;
    unsigned char resultTestAcquiredSamples;
    struct samples Measurement[MEASUREMENT_SIZE];
};
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

unsigned char eraseStateMachine(struct Menu* subMenu)
{
    struct Menu* subMenuErase = subMenu;
    unsigned char key = 0;
    unsigned char index = 0;
    unsigned char displayUpdateStatus = IDDLE;
    unsigned char* ptr_eraseString;
    while(key != MENU)
    {
        switch(subMenuErase->menuState)
        {
            case IDDLE:
                subMenuErase->menuState = getNextSub(VERFICA_APAGAR);
            break;

            case VERFICA_APAGAR:
                updateUserMsg(3,2,eraseselectUserMsg,&displayUpdateStatus);
                ptr_eraseString = getEraseTestString();
                printDataDisplay(0,0,ptr_eraseString);
                key = getKeyPressed();

                if(key == INSERIR)
                {
                	resetKeyPressed();
                    setUserErase(&index);
                    subMenuErase->menuState = getNextSub(VERFICA_APAGAR);
                }
                else if(key == CONFIRMAR)
                {
                	resetKeyPressed();
                    if(*ptr_eraseString == '5')
                    {
                        updateUserMsg(3,2,erasingUserMsg,&displayUpdateStatus);
                        resetMyResults();
                        subMenuErase->menuSelect = setSelectSub(&subMenuErase->menuState);
                        subMenuErase->menuState = getNextSub(CONFIRMA_APAGAR);
                    }
                    else if(*ptr_eraseString == '2')
                    {
                     subMenuErase->menuState = getNextSub(IDDLE);
                      key = MENU;
                    }
                }

            break;

            case CONFIRMA_APAGAR:
                updateUserMsg(3,2,erasedUserMsg,&displayUpdateStatus);
                subMenuErase->menuState = getNextSub(IDDLE);
                key = MENU;
                break;
        }
    }
}
