#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#include"HAL.h"

static FILE *s_file = NULL;
static uint32_t g_byte_per_sector = FAP12_NUMBER_BYTE_PER_SECTOR;

/* function to init*/
bool fat_init(const char * filePath)
{
    bool _check = false;
    s_file = fopen(filePath,"rb");
    if(s_file)
    {
        _check = true;
    }
    
    return _check;
}

void fat_deinit(void)
{
    fclose(s_file);
}
/* function to read a sector */
uint32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    uint32_t _size_t = 0;
    
    if(!fseek(s_file,index*g_byte_per_sector,SEEK_SET))  /* g_byte_per_sector are number bytes of a sector in fat12 */
    {  
        _size_t = fread(&buff[0],g_byte_per_sector,1,s_file);
    }
    
    return _size_t;
}
/* function to read multi sector */
uint32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    uint32_t _size_t = 0;
    
    if(!fseek(s_file,index*g_byte_per_sector,SEEK_SET))
    {
        _size_t = fread(buff,g_byte_per_sector*num,1,s_file);   /* 512 are number bytes of a sector in fat12 */
    }
    
    return _size_t;
}
void kmc_update_sector_size(uint32_t sector_size)
{
    if(0 == sector_size % FAP12_NUMBER_BYTE_PER_SECTOR)
    {
        g_byte_per_sector = sector_size;
    }
    else
    {
        g_byte_per_sector = sector_size ;
        printf("byte per sector > 512 byte");
    }
}
