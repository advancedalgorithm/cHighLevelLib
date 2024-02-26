#pragma

#ifndef CFILE_H
#define CFILE_H


typedef struct cFile;

long line_count(cFile *cF);
void clean_up(cFile *cF);

#endif