#pragma once
#ifndef CSTRUTILS_H
#define CSTRUTILS_H

typedef struct cString *cStr;

char *rm_Char(struct cString *s, char ch);
long count_Char(struct cString *s, char ch);

#endif