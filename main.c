#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/cStrUtils.c"

int main()
{
    struct cString *s = new_cString("Testing\n");
    printf("%s", s->data);
    return 0;
}