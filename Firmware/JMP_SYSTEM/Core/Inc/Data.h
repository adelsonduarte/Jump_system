#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <string.h>
#include<stdint-gcc.h>

struct results;
struct dataInsert;
unsigned char* getMassArray();
unsigned char* getOverMassArray();
unsigned char* getTimeStruct();
unsigned char* getAltMinArray();
unsigned char* getAltMaxArray();
unsigned char* getNumSaltosArray();
unsigned char* getIntervalSaltosArray();
unsigned char* getTypeJumpArray();
unsigned char* getAltDJArray();
unsigned char* getNumSeriesArray();
unsigned char* getIntervalSeriesArray();
unsigned char* getNumTestArray();
unsigned int* getUserResultData(unsigned char);
unsigned char* getintervalSeriesTimeStruct();

unsigned long int getUserTest();
unsigned long int getUserTime();
unsigned char getUserMass();
unsigned char getUserOverMass();
unsigned char getUserConsultTest();
unsigned char getUserAlturaMin();
unsigned char getUserAlturaMax();
unsigned char getUserNumSaltos();
unsigned char getUserIntervalSaltos();
unsigned char getUserCMJ();
unsigned char getUserAlturaDJ();
unsigned char getUserNumSeries();
unsigned char getUserIntervalSeries();
unsigned char getUserCommConfig();
unsigned char getUserSelectSensorChannel();
unsigned char getUserSelectTapete();

unsigned char setUserInputConfigData(struct dataInsert* dataToInsert);
unsigned char* getUserConfigStruct();
unsigned int* getUserResultData(unsigned char numTest);

unsigned char setUserResultData(struct results* , unsigned char);


void resetMyResults();

















#endif // DATA_H_INCLUDED
