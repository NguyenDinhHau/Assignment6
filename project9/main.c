#include<stdio.h>
#include"macrofile.h"

int main()
{
    int n = 0;
    
    printf("Enter number you want to swap \n ");
    scanf("%d",&n);
    
    DisplayBfSwap(n);  /* call function to show number before swap */
    DisplayAfSwap(n);  /* call function to show number after swap */
    
    return 0;
}
