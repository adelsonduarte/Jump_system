#ifndef SD_MODULE_H_INCLUDED
#define SD_MODULE_H_INCLUDED

#define MSG_QTD 6
#define MSG_LEN 255

struct samples;
struct results;
struct config;
unsigned char save_data(unsigned char numTest);
unsigned char* savedDataToString(struct results* dataToSave, unsigned char sample);
unsigned char* load_data(unsigned char numTest);
unsigned char* savedHeaderToString(struct results* dataToSave);
unsigned char* getArqName(unsigned char numTeste);
<<<<<<< HEAD
unsigned char* getArquivoMsg();
=======
unsigned char lineCounter(unsigned char numTeste);
unsigned char* loadDataArrayToStruct(unsigned char* load);

>>>>>>> 86ffc1670df986741b7c1944748c75133f6cec1f





#endif // SD_MODULE_H_INCLUDED
