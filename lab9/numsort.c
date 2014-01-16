#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

#include "inssort.h"

static int compar (const void *copy, const void *original){
    if (*(double* const*)copy < *(double* const*)original) return -1;
    if (*(double* const*)copy > *(double* const*)original) return 1;
    return 0;
}

int main (){
    double array[1000];
    int max = 0;
    for (int i = 0;i < 999; ++i){
       double number;
       int check = scanf ("%lg", &number);

       if (check == EOF){
          printf ("EOF\n");
          break;
       }else if (check == 1) {
          array [i] = number;
          ++max;
       }
    }

    inssort (&array[0], max, sizeof(double) ,compar);

    for (int i = 0; i < max; i++){
       printf ("%20.15g\n", array[i]);
    }
}
