#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../src/cStrUtils.c"

int main(int argc, char **argv[])
{
    struct cString  *s = new_cString("NEW_STRING_HERE");

    long lines = s->countLines(s);
    long chars = count_Char(s, 'c');

    /*
    *
    * Remove chars using an array
    */
    char rm_chars[] = { '(', ')', '\'' };
    for(int i = 0; i <= sizeof(rm_chars); i++)
    {
        if(rm_chars[i] == '\0') break;
        s->rmChar(s, rm_chars[i]);
    }

    /*
    *   Remove a string the buffer
    */
    char *t = s->rmString(s, "substr");
    printf("\x1b[32mnew_cString(cF->content)->data\x1b[39m =>\r\n%s \r\n", s->data);

    return 0;
}