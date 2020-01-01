#include<stdio.h>
#include"macrofile.h"
/* Number after we swap */
void DisplayAfSwap(int n)
{
    printf("Number after Swap \n");
    printf("%X  \n",SWAPBYTE(n));
}
/* Number before we swap */
void DisplayBfSwap(int n)
{
    printf("Number before Swap \n");
    printf("%X  \n",n);
}
