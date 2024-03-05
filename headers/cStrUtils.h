#pragma once
#ifndef CSTRUTILS_H
#define CSTRUTILS_H

typedef struct cString *cz;


/*
*   String Modification Functions
*/
char *rm_String(struct cString *s, char *str);
char *rm_Char(struct cString *s, char ch);
void cString_trim(struct cString *s);
char *replace_String(struct cString *s, char *str, char *substr);

/*
*   String Counting Functions
*/
long count_Lines(struct cString *s);
long count_Char(struct cString *s, char ch);
void clean_up_string(struct cString *s);

#endif