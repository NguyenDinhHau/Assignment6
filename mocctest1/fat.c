#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#include "hal.h"
#include "fat.h"

static boot_sector_data_t  g_boot_sector_data_t;
static uint32_t g_indexSector_start_fat = 0;
static uint32_t g_indexSector_start_root = 0;
static uint32_t g_indexSector_start_data = 0;
static uint32_t g_numberSector_root = 0;
static linked_list *g_head = NULL;

uint32_t reverseByte(uint8_t* byte,uint8_t _count)
{
    uint32_t result = 0;
    int i = 0;
    
    for (i = _count-1; i >= 0; i--)
    {
         result = (result << 8) | byte[i];
    }
    
    return result;
}

bool fat12_read_bootsector()
{
    bool check = false;
    
    fat12_read_bootsector_struct_t *bootsector_ptr = NULL;     /*  bootsector_ptr is a adapter */
    bootsector_ptr = (fat12_read_bootsector_struct_t *)malloc(sizeof(fat12_read_bootsector_struct_t));   /*  allocate memory for bootsector_ptr */
    
    if(kmc_read_sector(0,(uint8_t*)bootsector_ptr))   /* check when read a sector */
    {
        g_boot_sector_data_t.byte_per_sector = reverseByte(bootsector_ptr->bytepersector,2);
        g_boot_sector_data_t.num_fat = bootsector_ptr->fatCopy;
        g_boot_sector_data_t.reservedSector = reverseByte(bootsector_ptr->reservedSector,2);
        g_boot_sector_data_t.num_root_entry = reverseByte(bootsector_ptr->numberrootEntry,2);
        g_boot_sector_data_t.sector_per_cluster = bootsector_ptr->sectorPerCluster;
        g_boot_sector_data_t.sector_per_fat = reverseByte(bootsector_ptr->sectorPerFAT,2);
        g_boot_sector_data_t.fat_number =  reverseByte(bootsector_ptr->fat_number_char,2);
        g_indexSector_start_fat = g_boot_sector_data_t.reservedSector*g_boot_sector_data_t.sector_per_cluster;
        g_indexSector_start_root = g_indexSector_start_fat + g_boot_sector_data_t.num_fat*g_boot_sector_data_t.sector_per_fat;
        g_indexSector_start_data = g_indexSector_start_root + g_boot_sector_data_t.num_root_entry*NB_PER_ENTRY_DIREC/NUMBER_BYTE_PER_SECTOR;
        g_numberSector_root = (g_boot_sector_data_t.num_root_entry*NB_PER_ENTRY_DIREC)/g_boot_sector_data_t.byte_per_sector;
        kmc_update_sector_size(g_boot_sector_data_t.byte_per_sector);   /* update byte per sector */
        check = true;
        
        printf("%d",g_numberSector_root);
    }
    free(bootsector_ptr);     /* free memory when not use apdater */
       
    return check;
}

linked_list *Create_node()
{
    linked_list * temp = NULL;
    
    temp = (linked_list *)malloc(sizeof(linked_list));
    temp->next = NULL;
    
    return temp;
}

linked_list * Add_node(linked_list * node)
{
    linked_list * temp = NULL;
    linked_list * current = NULL;
    
    temp = Create_node();
    if(g_head == NULL)
    {
        g_head = temp;
    }
    else
    {
        current = g_head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
    }
    return g_head;
}

linked_list *fat_free_list(linked_list *head)
{
    linked_list * temp = NULL;
    linked_list * current = NULL;
    
    temp = head;
    while(temp != NULL)
    {
        current = temp->next;
        free(current);   /* free heap memory */
    }
    head = current;
    
    return head;
}
linked_list * fat12_read_folder(uint32_t index_sector_direct)
{
    linked_list * node = NULL;
    entry_directory_data_t  entry_data_save_ptr;    /* create a value to save entry data for linked list */
    fat12_read_entryDirec_struct_t * entries_direct_ptr;  /* create a adapter to connect buff[32] and entry_data_save */
    uint32_t size = g_boot_sector_data_t.byte_per_sector;   /*size of buff */
    uint8_t buff_sector_direct[size];
    uint8_t buff_entry_direct[NB_PER_ENTRY_DIREC];    /* create a buff  32 to copy entry from buff_sector_direct */
    uint32_t i = 0;
    uint32_t j = 0;
    uint8_t count = 0;
    
    entries_direct_ptr = (fat12_read_entryDirec_struct_t *)malloc(sizeof(fat12_read_entryDirec_struct_t)); /* allocate memory for adapter*/
    kmc_read_multi_sector(index_sector_direct*g_boot_sector_data_t.sector_per_cluster,size,(uint8_t*)&buff_sector_direct[0]);
    
        for(i = 0; i< size/NB_PER_ENTRY_DIREC; i++)  /* size/32 */
        {
            for(j=0; j< NB_PER_ENTRY_DIREC; j++)
            {
                buff_entry_direct[j] = buff_sector_direct[j + i*NB_PER_ENTRY_DIREC]; /* copy entry direct from buff_sector_direct to buff_entry_direct*/
            }
            if(buff_entry_direct[11] != 0x0f && buff_entry_direct[0] != 0x00 )  /* check long file name */
            {
                node = (linked_list*)malloc(sizeof(linked_list)); /* allocate memory for entry_data_save_ptr */
                entries_direct_ptr = (fat12_read_entryDirec_struct_t *)&buff_entry_direct[0];
                
                for(count = 0; count <8;count++)
                {
                    entry_data_save_ptr.name[count] = entries_direct_ptr->fileName[count];
                    
                }
                entry_data_save_ptr.size = reverseByte(entries_direct_ptr->filesize,4);
                entry_data_save_ptr.hour = (reverseByte(entries_direct_ptr->creationTime,2)>>11);
                entry_data_save_ptr.minute = (reverseByte(entries_direct_ptr->creationTime,2)>>5)&0x3f;
                entry_data_save_ptr.year = ((reverseByte(entries_direct_ptr->lastWriteDate,2)>>9) + 1980);
                entry_data_save_ptr.month = (reverseByte(entries_direct_ptr->lastWriteDate,2)>>5) & 0x0f;
                entry_data_save_ptr.day = (reverseByte(entries_direct_ptr->lastWriteDate,2)&0x1f);
                entry_data_save_ptr.first_cluster = (reverseByte(entries_direct_ptr->firstLogiClu,2));
                entry_data_save_ptr.attribute = entries_direct_ptr->atributes;
                
                node->entry_direct = entry_data_save_ptr;
                printf("%X  ",entries_direct_ptr->filesize[0]);
                g_head = Add_node(node);
            }
        } 
   // printf("%d",g_head);
    return g_head;
}

linked_list * fap12_read_entry_direct(uint32_t first_cluster)
{
    uint32_t lastCluster_index_root = 0;
    uint32_t firstCluster_index_data = 0;
    uint32_t firstCluster_index_root = 0;
    
    lastCluster_index_root = (g_indexSector_start_root + g_numberSector_root)*g_boot_sector_data_t.sector_per_cluster;
    firstCluster_index_data = g_numberSector_root/g_boot_sector_data_t.sector_per_cluster;
    
    if(0 == first_cluster)
    {
        fat_free_list(g_head);
       while( firstCluster_index_data < lastCluster_index_root  )
        {
            g_head = fat12_read_folder(firstCluster_index_root);
            printf("%d",g_head);
            firstCluster_index_data = firstCluster_index_data + 1;
        }
       
    }
    else if(0xfff == first_cluster)
    {
        printf("folder was null");
    }
    else
    {
        fat_free_list(g_head);
        firstCluster_index_data =  g_indexSector_start_data/g_boot_sector_data_t.sector_per_cluster - 2 + first_cluster;
        g_head = fat12_read_folder(firstCluster_index_data);
    }
    printf("%d",g_head);
    return g_head;
}
//static uint32_t find_next_cluster(uint32_t next_cluster)
//{
//    uint32_t size = g_boot_sector_data_t.byte_per_sector * g_boot_sector_data_t.sector_per_cluster;
//    uint8_t buff[2 * size];
//    uint32_t offset = (boot_data.sector_per_cluster) * 512;
//    uint32_t num_sector = boot_data.sector_per_cluster;
//    uint32_t i = 0; 
//    uint32_t = next = next_cluster * 1.5;
//    uint32_t =  temp;
//    uint32_t s = 0, temp2 = 0;
//    if (next < 512) {
//        i = 0;
//    }
//    else if (next % 512 == 0 && next >= 512) {
//        i = next / 512;
//        next = 0;
//    }
//    else {
//        temp = next;
//        next = next % 512;
//        i = temp / 512;
//    }
//    if (next_cluster % 2 == 0 && next == 0x1FF) {
//        kmc_read_multi_sector(i + 1, 2 * num_sector, buff);
//        temp2 = buff[next + 1] << 28;
//        temp2 = temp2 >> 20;
//        s = temp2 | buff[next];
//    }
//    else if (next_cluster % 2 != 0 && next == 0x1FF) {
//        kmc_read_multi_sector(i + 1, 2 * num_sector, buff);
//        s = buff[next + 1] << 4 | buff[next] >> 4;
//    }
//    else if (next_cluster % 2 == 0) {
//        kmc_read_multi_sector(i + 1, num_sector, buff);
//        temp2 = buff[next + 1] << 28;
//        temp2 = temp2 >> 20;
//        s = temp2 | buff[next];
//    }
//    else if (next_cluster % 2 != 0) {
//        kmc_read_multi_sector(i + 1, num_sector, buff);
//        s = buff[next + 1] << 4 | buff[next] >> 4;
//    }
//    return s;
//}


uint32_t fat12_read_file(uint32_t first_cluster)
{
    uint32_t size = g_boot_sector_data_t.byte_per_sector * g_boot_sector_data_t.sector_per_cluster;
    uint32_t next_cluster = 0;
    uint32_t i = 0;
    uint32_t index_cluster = 0;
    uint8_t arr[size];
    
    
    index_cluster = g_indexSector_start_data/g_boot_sector_data_t.sector_per_cluster - 2;  /* -2 because we have 2 cluster to reverve*/
    next_cluster = first_cluster;
    while(0xff != next_cluster)
    {
        if(kmc_read_multi_sector((index_cluster + next_cluster)*g_boot_sector_data_t.sector_per_cluster,g_boot_sector_data_t.sector_per_cluster,(uint8_t*)&arr[0]))
        {
            
            for(i=0; i<size;i++)
            {
                printf("%c",arr[i]);
            }
            
        }
       // next_cluster = fat12_findnext_cluster(next_cluster,g_boot_sector_data_t.fat_number);
    }
}
