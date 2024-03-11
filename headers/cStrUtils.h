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
char *c_replace(struct cString *s, char *substr, char *replacement);
char **split_char(struct cString *s, char delim);
int str_starts_with(struct cString *s, char *data);

/*
*   String Counting Functions
*/
long count_Lines(struct cString *s);
long count_Char(struct cString *s, char ch);
int count_String(struct cString *s, char *delim);
void clean_up_string(struct cString *s);

#endif