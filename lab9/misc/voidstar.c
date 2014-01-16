// $Id: voidstar.c,v 1.33 2012-11-16 14:59:17-08 - - $

//
// Simple example of void* processing in C.
// The function process takes an array and a function and
// processes the array according to the rules given by a
// function.
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

//
// Process an array by applying a function to each element.
//
void process (void *base,   // of the array
              size_t nelem, // number of elements
              size_t size,  // size of one element
              void (*function) (void *)) {
   for (size_t index = 0; index < nelem; ++index) {
      void *element = (char *) base + index * size;
      function (element);
   }
}

//
// Array of strings with two processing functions.
//
char *strings[] = {
   "hello", "world", "foo", "bar", "baz", "qux",
   "this", "is", "a", "test", 
};

void strdupthem (void *string) {
   char **chars = (char **) string;
   *chars = strdup (*chars);
}

void capitalize (void *string) {
   for (char *chars = * (char **) string; *chars != '\0'; ++chars) {
      *chars = toupper (*chars);
   }
}

void printstr (void *string) {
   (void) printf (" %s", * (char **) string);
}

void freestr (void *string) {
   char *str = * (char **) string;
   free (str);
   str = NULL;
}


//
// Array of doubles with two processing functions.
//

double numbers[] = {6.02e23, 287, -472, 0, 6e-22, MAXDOUBLE};

void exponent (void *number) {
   double *value = (double *) number;
   *value = log10 (*value);
}

void printnum (void *number) {
   (void) printf (" %10.3e", * (double *) number);
}

//
// Main function to exercise them.
//

int main (void) {

   size_t stringdim = sizeof strings / sizeof *strings;
//   printf ("%f\n", stringdim);
   process (strings, stringdim, sizeof *strings, printstr);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, strdupthem);
   process (strings, stringdim, sizeof *strings, capitalize);
   process (strings, stringdim, sizeof *strings, printstr);
   process (strings, stringdim, sizeof *strings, freestr);
   (void) printf ("\n");

   size_t numberdim = sizeof numbers / sizeof *numbers;
   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");
   process (numbers, numberdim, sizeof *numbers, exponent);
   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");

   return EXIT_SUCCESS;
}

//TEST// runprog -x voidstar.lis valgrind --leak-check=full voidstar
//TEST// mkpspdf Listing.ps voidstar.c voidstar.c.log voidstar.lis

