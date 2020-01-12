#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "HAL.h"
#include "FAT12.h"
/*Show folder */
static void show_directories(linkedList_ptr head)
{   
    linkedList_ptr current = NULL;
    uint32_t count = 1;
    current = head;
    printf("\n Number\t\t   File Name\t\t   Type\t\t   Date Time\t\t  Size   \n");
    while(current!= NULL)
    {
        printf("%d\t\t   %s\t\t   %s\t\t   %d   %d  %d\t\t   %d\t\t \n",count,current->entry_direct->name,current->entry_direct->type,current->entry_direct->day,current->entry_direct->month,current->entry_direct->year,current->entry_direct->size);
        current = current->next;
        count++;
    }
}
/* return current head when we chosse */
static linkedList_ptr return_head(uint32_t number,linkedList_ptr head)
{
    linkedList_ptr current = NULL;
    uint32_t count = 1;
    
    current = head;
    while(current != NULL && count != number )
    {
        current = current->next;
        count++;
    }
    
    return current;
}
/* Menu of Fat12 */
void MenuFat12()
{
    fat12_read_bootsector_struct_t *bootsector =NULL;
    linkedList_ptr head = NULL;
    linkedList_ptr cur = NULL;
    uint32_t count_number = 1;
    uint8_t first_cluser = 0;
    uint32_t number_choose = 0;
    
    fat12_read_bootsector();
    head = fap12_read_entry_direct(0,head);
    show_directories(head);
    
    while(1)
    {
        printf("\nEnter your number you want ");
        scanf("%d",&number_choose);
        cur = return_head(number_choose,head);
        first_cluser = cur->entry_direct->first_cluster;
        if(cur->entry_direct->attribute == 0x10)
        {
            head = fap12_read_entry_direct(first_cluser,head);
            show_directories(head);
        }
        else
        {
            fat12_read_file(first_cluser);
        }
    }
    
}

