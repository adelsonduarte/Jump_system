#include <String.h>
#include "SD_module.h"

unsigned char check_SD_card()
{
//    FATFS *pfs;
//    DWORD fre_clust;
//    uint32_t totalSpace, freeSpace;
//    f_getfree("", &fre_clust, &pfs);
//    totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
//    freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
//    return freeSpace;
}

unsigned char read_SD_card()
{
//    static char buffer[100];
//    f_open(&fil, "read.txt", FA_READ);
//  // Reads line by line until the end
//    while(f_gets(buffer, sizeof(buffer), &fil))
//    {
//    // Can use the buffer for something useful
//        memset(buffer,0,sizeof(buffer));
//    }
//    f_close(&fil);
//    return *buffer;
}

unsigned char write_SD_card()
{
//    FATFS fs;
//    FIL fil;
//    HAL_Delay(500);
//    f_mount(&fs, "", 0);
//    f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
//    f_lseek(&fil, fil.fsize);
//    f_puts("Hello from Nizar\n", &fil);
//    f_close(&fil);
//    return 1;
}

unsigned char save_data()
{

}
