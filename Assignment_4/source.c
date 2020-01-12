#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "head.h"

static node_str_t * g_head;
/* create note to save data */
static node_str_t * CreateNode()
{
    node_str_t * temp = NULL;
    
    temp = (node_str_t * )malloc(sizeof(node_str_t));
    temp->next = NULL;
    
    return temp;
}
/* add note to linked list */
static void AddNode(node_str_t * node)
{   
    if(!g_head)
    {
        g_head = node;
    }
    else
    {
        node->next = g_head;
        g_head = node;
    }
}
/* show list student */
void Show_Student()
{
    node_str_t * current = NULL;
    int count = 0;
    
    current = g_head;
    printf("Count                  Code                   Name                  \n");
    while(current != NULL)
    {
        printf("%10d  %10d  %10s  \n",count, current->values.codeStudent,current->values.nameStudent);
        current = current->next;
        count++;
    }
}
/*check code student */
static bool CheckCode(int code)
{
    node_str_t * current = NULL;
    bool check = false;
    
    current = g_head;
    
    while(current != NULL)
    {
        if(current->values.codeStudent == code)
        {
            check = true;
            break;
        }
        current = current->next;
    }
    
    return check;
}

void *DelHead()
{
    if(g_head== NULL)
    {
        printf("Student Lists are null \n");
    }
    else
    {
        g_head = g_head->next;
    }
}
/*delete a note from linked list */
void DelAt(int position)
{
    int count = 0;
    node_str_t * current = NULL;
    node_str_t * pre = NULL;
    
    if(position == 0 || g_head == NULL)
    {
        g_head = DelHead(g_head);
    }
    else
    {
        current = g_head;
        while(current->next != NULL && count != position)
        {
            pre = current;
            current = current->next;
            count++; 
        }  
        if(position > count)
        {
            printf("Your position is wrong! \n");
        }
        else
        {
            printf("%s \n",pre->values.nameStudent);
            pre->next = current->next;
            printf("%s \n",pre->values.nameStudent);
            printf("delete successful \n");
        }
    }
}
/* add a student to linked list */
void EnterStudent()
{
     node_str_t * node;
     Student_str_t student;
     int code;
     char name[20];
     int i =0;
     
     printf("Enter code student. Please! \n ");
     scanf("%d",&code);
     
     if(!CheckCode(code))s
     {
         node = CreateNode();
         student.codeStudent = code;
         printf("Enter name of student. Please \n");
         fflush(stdin);
         gets(name);
         for(i=0;i<20;i++)
         {
             student.nameStudent[i] = name[i];
         }
         node->values = student;
         AddNode(node);
     }
     else
     {
         printf("Your code has existed!\n");
     }
     
}
/* delete a student */
void DelStudent()
{
    int position = 0;
    
    printf("Enter position you want to delete: \n");
    scanf("%d",&position);
    DelAt(position);
}
