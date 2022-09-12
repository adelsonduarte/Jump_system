#ifndef DATAPROCESSING_H_INCLUDED
#define DATAPROCESSING_H_INCLUDED

unsigned char indexTime(unsigned char* index);
unsigned long stringToLong(unsigned char* string);
unsigned int stringToInt(unsigned char* string);
unsigned char indexMass(unsigned char* index);
unsigned char stringToFloat(unsigned char* string);
unsigned int* param_1_toString(unsigned char* string);
unsigned int* param_2_toString(unsigned char* string);
unsigned int* param_3_toString(unsigned char* string);


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
unsigned char setUserIntervalSaltos(unsigned char* idx);
unsigned char setUserTypeJump(unsigned char* idx);
unsigned char setUserAltDJ(unsigned char* idx);
unsigned char setUserNumSeries(unsigned char* idx);
unsigned char setUserIntervalSeries(unsigned char* idx);
unsigned char setUserErase(unsigned char* idx);

unsigned char indexChange(unsigned char* index, unsigned char size);



#endif // DATAPROCESSING_H_INCLUDED
