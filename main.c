#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/cStrUtils.c"
#include "src/cFile.c"

int main()
{
    struct cFile    *cF = cFileInit("../cnc/assets/users.gn");    
    struct cString  *s = new_cString(cF->content);
    printf("\x1b[32mnew_cString(cF->content)->data\x1b[39m =>\r\n%s \r\n", s->data);

    char *t = s->replaceString(s, "Jeff", "LawlzSec");
    printf("\x1b[32mnew_cString(cF->content)->data\x1b[39m =>\r\n%s \r\n", s->data);

    /* Clean up memory blocks */
    s->clean_up(s);
    cF->die(cF);
    free(s);
    free(cF);

    return 0;
}