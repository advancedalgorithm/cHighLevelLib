#pragma once
#ifndef CFILE_H
#define CFILE_H


typedef struct cFile *czz;

long line_count(struct cFile *cF);
void _trim(struct cFile *cF);
void *cpy_Data(struct cFile *cF, char *dest);
void clean_up(struct cFile *cF);
void clean_up(struct cFile *cF);

#endif