#ifndef SDMEMORYHW_H_INCLUDED
#define SDMEMORYHW_H_INCLUDED

unsigned char HW_EXT_MEMORY_CHECK();
unsigned char HW_EXT_MEMORY_READ(unsigned char* loadName,unsigned char numSamples, unsigned char* loadPointer);
unsigned char HW_EXT_MEMORY_WRITE(unsigned char* saveString, unsigned char idxTest);



#endif // SDMEMORYHW_H_INCLUDED
