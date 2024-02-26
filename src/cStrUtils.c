#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/cStrUtils.h"

#pragma once

typedef struct cString
{
    char    *data;
    char    *buffer;
    char*   (*rmChar)(struct cString *s, char ch);
    long    (*countChar)(struct cString *s, char ch);
} cString;

cString *new_cString(char *data)
{
    cString *c      = (cString *)malloc(sizeof(cString *)*255);

    /* Copy the data into the buffer */
    c->data         = (char *)malloc(sizeof(char *) * strlen(data));
    strcpy(c->data, data);
    c->buffer       = strdup(data);

    c->rmChar       = rm_Char;
    c->countChar    = count_Char;
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
    s->buffer = (char *)malloc(sizeof(char *) * strlen(s->data));
    memset(s->buffer, 0, strlen(s->buffer));

    for(int i = 0; i < strlen(s->data); i++)
    {
        if(s->data[i] != ch) strcat(s->buffer, &s->data[i]);
    }

    memset(s->data, 0, strlen(s->data));
    strcpy(s->data, s->buffer);

    return s->buffer;
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

void clean_up_string(struct cString *s)
{
    free(s->data);
    free(s->buffer);
}