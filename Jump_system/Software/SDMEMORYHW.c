#include "SDMEMORYHW.h"

unsigned char HW_EXT_MEMORY_CHECK()
{
    //    FATFS *pfs;
    //    DWORD fre_clust;
    //    uint32_t totalSpace, freeSpace;
    //    f_getfree("", &fre_clust, &pfs);
    //    totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    //    freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
    //    return freeSpace;
}

unsigned char HW_EXT_MEMORY_READ(unsigned char* loadName,unsigned char numSamples, unsigned char* loadPointer)
{
//     unsigned char line = numSamples;
//     unsigned char column = 0;
//    unsigned char (*loadDataHW)[MAX_LINES][MAX_LEN] = loadPointer;
//    f_open(&fil, loadName, FA_READ);
//   Reads line by line until the end
//    for(line=0;line<numSamples;line++)
//    {
//        for(column=0;column<4;column++)
//        {
//            fscanf(&fil,"%d",&loadDataHW[line][column]);
//            if(feof(&fil)) break;
//        }
//    }
//    f_close(&fil);
//    return loadDataHW;
}

unsigned char HW_EXT_MEMORY_WRITE(unsigned char* saveString, unsigned char idx)
{
//    FATFS fs;
//    FIL fil;
//    HAL_Delay(500);
//    f_mount(&fs, "", 0);
//    f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//    f_lseek(&fil, fil.fsize);
//    f_puts(saveString, &fil);
//    f_close(&fil);
//    return 1;
}
