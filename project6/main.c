#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"sourcefile.h"

uint8_t assignment3[20] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uint32_t next[20] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

uint32_t AddLinkedList(uint32_t head,uint32_t position, uint32_t value );

uint32_t enterElementOfArr(uint32_t head)
{
	uint32_t i = 0;
	uint32_t position = 0;
	uint32_t values = 0;
	uint32_t compare = 0;

	printf("\nEnter position of arr ");
	scanf("%d",&position);
	if(position <= 19 && position >= 0)
		{
			if(assignment3[position] == 0xff)
			{
				printf("\nEnter value of Array ");
				scanf("%d",&values);
				if(values  >= 0 && values<= 100 )
				{
					for(i=0; i<= 19; i++)
					{
						if(assignment3[i]== values)
						{
							compare = assignment3[i];
							break;
						}
						else
						{
							compare = 0;
						}
					}
					if(compare != values)
					{
						assignment3[position] = values;
						head = AddLinkedList(head,position,values);
						printf("\n Insert value successfull");
					}
					else
					{
						printf("\nValue has existed");
					}
				}
				else
				{
					printf("\nValue Error");
				}
			}
			else
			{
				printf("\nPosition is not Null");
			}
		}
	else 
	{
		printf("\nPosition was wrong! ");
	}
	
	return head;
}
void PrintSwap(uint32_t head)
{
	uint32_t current = head;
	while(current!= 0xff)
	{
		printf("%d ",assignment3[current]);
		current = next[current];
	}
}
void printElementofArr(uint8_t *ptr)
{
	uint32_t i=0;
	
	for(i=0;i<=19; i++)
	{
		if(ptr[i] != 0xff)
		{
		printf("%d ",*(ptr+i));	
		}
	}

}
uint32_t DelHead(uint32_t head)
{
	if(head == 0xff)
	{
		printf("Linked list Null");
	}
	else
	{
		head = next[head];
		next[head] = '\0';
	}
	
	return head;
}

uint32_t DelValue(uint32_t head, uint32_t position)
{
	uint32_t current = head;
	
	if(position == 0||head == 0xff)
	{
		head = DelHead(head);
	}
	else
	{
		while(next[current] != position)
		{
			current = next[current];
		}
		next[current] = next[position];
		next[position] = '\0';
	}
	return head;
}
uint32_t delElementOfArr(uint32_t head)
{
	uint32_t values = 0;
	uint32_t position = 0;
	uint32_t compare = 0;
	uint32_t i=0;
	
	printf("\n Enter value of arr you want to delete: ");
	scanf("%d",&values);
	if(values <=100 && values>=0)
	{
		for(i=0;i<=19;i++)
		{
			if(assignment3[i]== values)
			{
				compare = values;
				position = i;
				break;
			}
			else
			{
				compare = 0;
			}
		}
		if(compare == values)
		{
			assignment3[i] = 0xff;
			position = i;
			head = DelValue(head,position);
			printf("\n delete value %d successful ",values);
		}
		else
		{
			printf("\nvalue had not existed!");
		}	
	}
	else
	{
		printf("\n You have to enter a value is bigger than 0 and less than 100 ");
	}
	
	return head;
}

uint32_t AddLinkedList(uint32_t head,uint32_t position, uint32_t value )
{
	uint32_t cur =0;
	uint32_t pev = 0;
	
	if(head == 0xff)
	{
		head = position;
	}
	else
	{
		cur = head;
		pev = head;
		while(cur!= 0xff)
		{
			if(assignment3[cur] > value)
			{
				break;
			}
			else
			{
				pev = cur; 
				cur = next[cur];
			}
		}
		if(cur == pev)
		{
			head = position;
			next[head] = cur;	
		}
		else
		{
			next[pev] = position;
			next[position] = cur; 
		}
	}
	return head;
}
int main(){
	
	uint32_t head = 0xff;
	uint32_t choose_main =0;
	uint32_t choose_3 = 0;
	
	while(1)
	{
		
	printf("\n Enter 1: Enter a value to array ");
	printf("\n Enter 2: Delete a value from array ");
	printf("\n Enter 3: Print values from array ");
	printf("\n Enter 4: Exit ");
	printf("\n Enter your choose: ");
	scanf("%d",&choose_main);
	if(choose_main == 1)
	{
		head = enterElementOfArr(head);
			printf("%d",head);
	}
	if(choose_main == 2)
	{
		head = delElementOfArr(head);
	}
	if(choose_main == 3)
	{
		printf("\n Enter 1: Print unsorted array ");
		printf("\n Enter 2: Print sorted array ");
		printf("\n Enter number you want");
		scanf("%d",&choose_3);
		if(choose_3 == 1)
		{
			printElementofArr(assignment3);
		}
		if(choose_3 == 2)
		{
			PrintSwap(head);
		}
	}
	if(choose_main == 4)
	{
		exit(1);
	}
}
	return 0;
}
