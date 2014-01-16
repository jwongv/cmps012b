#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

#include "inssort.h"

typedef char *cstring;

static int compar (const void *copy, const void *original){
    return strcmp(*(char* const*) copy, *(char* const*) original);
}

int main (){
    char* array[1000];
    char buffer[1000];
    int max = 0;
    for (int i = 0;i < 999; ++i){
       cstring line;
       line = fgets (buffer, sizeof buffer, stdin);
       if (line == NULL) break;
       cstring nlpos = strchr (buffer, '\n');
       if (nlpos != NULL){
          *nlpos = '\0';
       }

       array [i] = strdup(buffer);
       ++max;
    }

    inssort (&array[0], max, sizeof(char *) ,compar);

    for (int i = 0; i < max; i++){
       printf ("%s\n", array[i]);
       free (array[i]);
    }
}
