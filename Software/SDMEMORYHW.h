#ifndef SDMEMORYHW_H_INCLUDED
#define SDMEMORYHW_H_INCLUDED

unsigned char HW_EXT_MEMORY_CHECK();
<<<<<<< HEAD
unsigned char HW_EXT_MEMORY_READ();
=======
unsigned char HW_EXT_MEMORY_READ(unsigned char* loadName,unsigned char numSamples, unsigned char* loadPointer);
>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f
unsigned char HW_EXT_MEMORY_WRITE(unsigned char* saveString, unsigned char idxTest);



#endif // SDMEMORYHW_H_INCLUDED
