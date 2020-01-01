#ifndef _HEADER_FILENAME_
#define _HEADER_FILENAME_

void DisplayAfSwap(int n);
void DisplayBfSwap(int n);
#define SWAPBYTE(NUMBER)\
   ((NUMBER &0XFF)<< 24)|((NUMBER &0XFF00)<<8)|((NUMBER & 0XFF0000)>>8)|((NUMBER & 0XFF000000)>>24)   

#endif /* _HEADER_FILENAME_ */

