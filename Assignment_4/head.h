#ifndef _HEADER_FILENAME_HEAD
#define _HEADER_FILENAME_HEAD

typedef struct
{
    int codeStudent;
    char nameStudent[20];
}Student_str_t;


typedef struct linkList
{
    Student_str_t values;
    struct linkList *next;
} node_str_t;

void EnterStudent();
void DelStudent();
void Show_Student();
#endif /* _HEADER_FILENAME_HEAD */
