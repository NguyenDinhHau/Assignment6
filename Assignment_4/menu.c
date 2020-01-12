#include<stdio.h>
#include<stdbool.h>
#include"head.h"
/* this is menu */
void Menu()
{
    while(true)
    {
        char number = 0;
        
        printf("****************MENU****************\n");
        printf("Enter 1: Add a Sinh Vien in list\n");
        printf("Enter 2: Delete a Sinh Vien in List\n");
        printf("Enter 3: Show Sinh Vien in List\n");
        printf("Enter 4: Exit\n");
        printf("Enter your number :");
        scanf("%d",&number);
    
        if(number == 1)
        {
           EnterStudent();
        }
        else if(number == 2)
        {
            DelStudent();
        }
        else if(number == 3)
        {
            Show_Student();
        }
        else if(number == 4)
        {
            break;
        }
        else
        {
            printf("Your Number was wrong\n");
        }
    }
}
