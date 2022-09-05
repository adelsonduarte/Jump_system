#include <String.h>
#include "SD_module.h"
#include "Data.h"

struct dataSave{
    unsigned long int userTime;
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

unsigned char save_data()
{
    static struct dataSave myDataSave;
    struct dataSave* userDataSave = &myDataSave;
    //salvar os dados medidos também -> criar outra estrutura
    userDataSave->userTime = getUserTime();
    userDataSave->userMass = getUserMass();
    userDataSave->userOverMass = getUserOverMass();
    userDataSave->userConsultTest = getUserConsultTest();
    userDataSave->userAlturaMin = getUserAlturaMin();
    userDataSave->userAlturaMax = getUserAlturaMax();
    userDataSave->userIntervalSaltos = getUserIntervalSaltos();
    userDataSave->userNumSaltos = getUserNumSaltos();
    userDataSave->userCMJ = getUserCMJ();
    userDataSave->userAlturaDJ = getUserAlturaDJ();
    userDataSave->userNumSeries = getUserNumSeries();
    userDataSave->userIntervalSeries = getUserIntervalSeries();
    userDataSave->userCommConfig = getUserCommConfig();
    userDataSave->userSelectTapete = getUserSelectTapete();
    userDataSave->userSelectSensorChannel = getUserSelectSensorChannel();
    //ENVIA userDataSave PARA IO_INTERFACE PARA SALVAR NO CARTAO SD
}
