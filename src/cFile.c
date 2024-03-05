#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/cFile.h"

#pragma once

typedef struct cFile
{
    int     status;
    FILE    *fd;
    char    *filepath;
    char    *content;
    long    content_count;
    char    *buffer;

    long    (*lineCount)(struct cFile *cF);
    void    (*trim)(struct cFile *cF);
    void*   (*cpyData)(struct cFile *cF, char *dest);
    void    (*die)(struct cFile *cF);
} cFile;


cFile *cFileInit(char *file)
{
    cFile *cF = (cFile *)malloc(sizeof(cFile));
    cF->lineCount   = line_count;
    cF->trim        = _trim;
    cF->cpyData     = cpy_Data;
    cF->die         = clean_up;

    cF->filepath = (char *)malloc(sizeof(char *) * (strlen(file) + 1));
    memset(cF->filepath, 0, sizeof(char *) * (strlen(cF->filepath) + 1));
    strcpy(cF->filepath, file);

    cF->fd = fopen(file, "r");
    if(cF->fd == NULL) return cF;

    fseek(cF->fd, 0L, SEEK_END);
    long sz = ftell(cF->fd);
    fseek(cF->fd, 0L, SEEK_SET);

    cF->content = (char *)malloc(sizeof(char *) * (sz + 1));

    fread(cF->content, sizeof(char), sz, cF->fd);
    cF->content_count = strlen(cF->content);

    return cF;
}

long line_count(struct cFile *cF)
{
    long c = 0;
    for(int i = 0; i < strlen(cF->content); i++)
    {
        if(cF->content[i] == '\n')
            c++;
    }

    return c;
}

/*
*   [@DOC]
*   void _trim(cFile *cF)
*
*   Trim whitespaces
*/
void _trim(struct cFile *cF)
{
    cF->buffer = (char *)malloc(sizeof(char *) * strlen(cF->content));
    memset(cF->buffer, 0, strlen(cF->buffer));

    for(int i = 0; i < strlen(cF->content); i++)
    {
        if(cF->content[i] != '\r' && cF->content[i] != '\n' && cF->content[i] != '\t')
            strcat(cF->buffer, &cF->content[i]);
    }

    memset(cF->content, 0, (strlen(cF->content) + 1));
    strcpy(cF->content, cF->buffer);
}

void *cpy_Data(struct cFile *cF, char *dest)
{
    dest = strdup(cF->content);
}

void clean_up(struct cFile *cF)
{
    fclose(cF->fd);
    free(cF->buffer);
    free(cF->content);
    free(cF->filepath);
}