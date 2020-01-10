#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#include"fat.h"
#include"hal.h"

const char *filePath = "floppy.img";

int main()
{
    
    uint8_t buff[512];
    if(fat_init(filePath))
    {
        fat12_read_bootsector();
       // fap12_read_entry_direct(0);
        fat12_read_folder(19);
    }
    return 0;
}
