#ifndef SENSORHW_H_INCLUDED
#define SENSORHW_H_INCLUDED

struct dataInsert;
unsigned char readingSensor();
unsigned char* getMeasureState();
unsigned int calcAltura(float TimeVoo);
float calcPotencia(unsigned int alturaSalto,unsigned int massaCorpo);

#endif // SENSORHW_H_INCLUDED
