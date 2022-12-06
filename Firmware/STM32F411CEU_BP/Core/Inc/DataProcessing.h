#ifndef DATAPROCESSING_H_INCLUDED
#define DATAPROCESSING_H_INCLUDED

unsigned char indexTime(unsigned char* index);
unsigned long stringToLong(unsigned char* string);
unsigned int stringToInt(unsigned char* string);
unsigned char indexMass(short* index);
unsigned char stringToFloat(unsigned char* string);
unsigned char stringLenght(unsigned char* str);
unsigned int* param_1_toString(unsigned int* string);
unsigned int* param_2_toString(unsigned int* string);
unsigned int* param_3_toString(unsigned int* string);


unsigned char* getAltMinString();
unsigned char* getAltMaxString();
unsigned char* getNumSaltosString();
unsigned char* getIntervalSaltosString();
unsigned char* getTypeJumpString();
unsigned char* getAltDJString();
unsigned char* getNumSeriesString();
unsigned char* getIntervalSeriesString();
unsigned char* getNumTestString();
unsigned char* getEraseTestString();
unsigned char* getStringToSave();

unsigned char* getTimeStruct();
unsigned char* getMassArray();
unsigned char setUserOverMass(unsigned char* idx);
unsigned char setUserMass(unsigned char* idx);
unsigned char setUserAltMin(unsigned char* idx);
unsigned char setUserAltMax(unsigned char* idx);
unsigned char setUserNumSaltos(unsigned char* idx);
void setUserIntervalSaltosTime(unsigned char* idx);
void setUserIntervalSeriesTime(unsigned char* configInputTimer);
unsigned char setUserTypeJump(unsigned char* idx);
unsigned char setUserAltDJ(unsigned char* idx);
unsigned char setUserNumSeries(unsigned char* idx);
unsigned char setUserIntervalSeries(unsigned char* idx);
unsigned char setUserErase(unsigned int* idx);
void setUserTime(unsigned char* inputUserTimer);

unsigned char indexChange(short* index, unsigned char size);
//unsigned long milisecondsTime(unsigned char* ptr_inputTime);



#endif // DATAPROCESSING_H_INCLUDED
