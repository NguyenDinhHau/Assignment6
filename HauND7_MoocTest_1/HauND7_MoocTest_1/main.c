#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include "HAL.h"
#include "FAT12.h"
#include "Menu.h"

static const char * filePath = "floppy.img";

int main()
{
    if(fat_init(filePath))
    {
        MenuFat12();
    }
    fat_deinit();
  
    return 0;
}
