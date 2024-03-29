#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/cStrUtils.h"

#pragma once

typedef enum
{
    NEW_STRING = 0,
    APPEND_STRING = 1,
    REMOVE_STRING = 2,
    EMPTY_STRING = 3
} STRING_EDIT_T;

typedef struct cString
{
    char    *data;
    char    *buffer;

    char*   (*rmChar)(struct cString *s, char ch);
    char*   (*rmString)(struct cString *s, char *str);
    char*   (*replaceString)(struct cString *s, char *str, char *substr);
    char**  (*splitString)(struct cString *s, char delim);
    int   (*startsWith)(struct cString *s, char *data);
    long    (*countChar)(struct cString *s, char ch);
    long    (*countLines)(struct cString *s);
    void    (*trim)(struct cString *s);
    void    (*clean_up)(struct cString *s);
} cString;

/*
*   [@DOC]
*   cString *new_cString(char *data)
*
*   Create a new string
*/
cString *new_cString(char *data)
{
    cString *c          = (cString *)malloc(sizeof(cString *)*255);

    /* Copy the data into the buffer */
    c->data              = (char *)malloc(sizeof(char *) * strlen(data));
    c->buffer            = (char *)malloc(sizeof(char *) * strlen(data));
    strcpy(c->data, data);
    strcpy(c->buffer, data);

    c->rmChar           = rm_Char;
    c->rmString         = rm_String;
    c->replaceString    = c_replace;
    c->splitString      = split_char;
    c->startsWith       = str_starts_with;
    c->countChar        = count_Char;
    c->countLines       = count_Lines;
    c->trim             = cString_trim;
    c->clean_up         = clean_up_string;

    return c;
}

cString *edit_string(STRING_EDIT_T *mode, char *n)
{

}

/* 
*   [@DOC]
*   char *rm_Char(char *str, char ch)
*   
*   remove a single char from string
*/
char *rm_Char(struct cString *s, char ch)
{
    /* Allocate memory and set the block to 0s */
    s->buffer = (char *)malloc(sizeof(char *) * (strlen(s->data) + 1));
    memset(s->buffer, 0, sizeof(char *) * (strlen(s->data) + 1));

    int r = 0;

    for(int i = 0; i < strlen(s->data); i++)
    {
        if(s->data[i] != ch)
            strncat(s->buffer, &s->data[i], 1);
        r++;
    }
 
    s->buffer[r] = '\0';
    
    free(s->data);
    s->data = strdup(s->buffer);

    return s->buffer;
}

/*
*   [@DOC]
*   char *rm_String(struct cString *s, char *str)
*
*   Remove a string from the current buffer
*/
char *rm_String(struct cString *s, char *str)
{
    if(strlen(s->buffer) > 0)
        free(s->buffer);

    s->buffer = (char *)malloc(sizeof(char *) * (strlen(s->data) + 1));
    memset(s->buffer, 0, sizeof(char *) * (strlen(s->buffer) + 1));

    int i = 0;
    while(i < strlen(s->data))
    {
        if(s->data[i] == str[0] && s->data[i + strlen(str)-1] == str[strlen(str)-1])
            i += strlen(str); 

        strncat(s->buffer, &s->data[i], 1);
        i++;
    }

    free(s->data);
    s->data = strdup(s->buffer);

    return s->buffer;
}

/*
*   [@DOC]
*   char *replace_String(struct cString *s, char *str, char *substr)
*
*   Remove a string from the current buffer
*/
char *c_replace(struct cString *s, char *substr, char *replacement)
{
    if(strlen(s->buffer) > 0)
        free(s->buffer);

    s->buffer = (char *)malloc(sizeof(char *) * (strlen(s->data) + 1));
    memset(s->buffer, 0, sizeof(char *) * (strlen(s->data) + 1));

    for(int i = 0; i < strlen(s->data); i++)
    {
        if(substr[0] == s->data[i] && substr[1] == s->data[i+1])
        {
                strcat(s->buffer, replacement);
                i += strlen(substr);
        }
        strncat(s->buffer, &s->data[i], 1);
    }
    strncat(s->buffer, "\0", 1);

    
    free(s->data);
    s->data = strdup(s->buffer);

    return s->buffer;
}

/*
*   [@DOC]
*   char **split_char(struct cString *s, char delim)
*
*   - Split a string with a char
*/
char **split_char(struct cString *s, char delim)
{
    /* Initialize array and reset the memory block */
    char **arr = (char **)malloc(sizeof(char *) * (strlen(s->data) + 255));

    /* 
    *   Null-terminate all cells to avoid 
    *   doing it at the end of function
    */
    memset(arr, '\0', (sizeof(arr) + 1));
    int idx = 0 ;
    
    int sz = strlen(s->data) + 5; // get size for buffer
    char temp[sz]; // Create a temporary buffer
    memset(temp, '\0', strlen(temp)); // Empty the allocated memory block
    
    for(int i = 0; i <= strlen(s->data); i++)
    {
        if(s->data[i] == delim) 
        {
            arr[idx] = strdup(temp);
            memset(temp, '\0', strlen(temp));
            idx++;
            i++;
        }
        strncat(temp, &s->data[i], 1);
    }

    return arr;
}

int str_starts_with(struct cString *s, char *data)
{
    if(strlen(data) == 0) return -1;

    if(s->data[0] != data[0])
        return -1;

    if(s->data[0] == data[0] && s->data[1] == data[1]) return 1;

    return 0;
}


/*
*   [@DOC]
*   long count_Char(char *str, char ch)
*
*   Count char in the buffer
*/
long count_Char(struct cString *s, char ch)
{
    long i = 0;
    for(int g = 0; g < strlen(s->data); i++ )
    {
        if(s->data[g] == ch)
            i++;
    }

    return i;
}

/*
*   [@DOC]
*   long count_Lines(struct cString *s)
*
*   Count a the total of amount of a specific char in the buffer
*/
long count_Lines(struct cString *s)
{
    long c = 0;

    for(int i = 0; i < strlen(s->data); i++)
    { if(s->data[i] == '\n') c++; }

    return c;
}

/*
*   [@DOC]
*   void cString_trim(cFile *cF)
*
*   Trim whitespaces
*/
void cString_trim(struct cString *s)
{
    s->buffer = (char *)malloc(sizeof(char *) * strlen(s->data));
    memset(s->buffer, 0, strlen(s->buffer));

    long idx = 0;
    for(int i = 0; i < strlen(s->data); i++)
    {
        if(s->data[i] != '\r' && s->data[i] != '\n' && s->data[i] != '\t')
            strcat(s->buffer, &s->data[i]);
        idx++;
    }
    s->buffer[idx] = '\0';

    free(s->data);
    strcpy(s->data, s->buffer);
}

void clean_up_string(struct cString *s)
{
    free(s->data);
    free(s->buffer);
}