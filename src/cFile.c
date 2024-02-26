#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/cFile.h"

typedef struct cFile
{
    int     status;
    FILE    *fd;
    char    *filepath;
    char    *content;
    long    content_count;

    long    (*lineCount)(cFile *cF);
} cFile;


cFile *__cFile(char *file)
{
    cFile *cF = (cFile *)malloc(sizeof(cFile *) * 255);
    cF->lineCount = line_count;

    cF->filepath = (char *)malloc(sizeof(char *) * strlen(file));
    memset(cF->filepath, 0, sizeof(cF->filepath));

    cF->fd = fopen(file, "r");
    if(cF->fd == NULL) return cF;

    fseek(cF->fd, 0L, SEEK_END);
    long sz = ftell(cF->fd);
    fseek(cF->fd, 0L, SEEK_SET);

    cF->content_count = (char *)malloc(sizeof(char *) * sz);
    fread(cF->content, 0, sz, cF->fd);

    cF->content_count = strlen(cF->content);
}

long line_count(cFile *cF)
{
    long c = 0;
    for(int i = 0; i < strlen(cF->content); i++)
    {
        if(cF->content[i] == '\n')
            c++;
    }

    return c;
}

void clean_up(cFile *cF)
{
    fclose(cF->fd);
    free(cF->filepath);
    free(cF->content);
}