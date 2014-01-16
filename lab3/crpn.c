// $Id: crpn.c,v 1.4 2012-10-24 22:56:05-07 - - $

// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   assert (argc == 1);
   printf ("%s:\n", argv[0]);

   #define STACK_SIZE 16
   #define EMPTY (-1)
   double stack[STACK_SIZE];
   int top = EMPTY;
   int i = 0;

   for (;;) {
      char buffer[4096];

      int scanct = scanf ("%4095s", buffer);
      if (scanct == EOF) {
         printf ("EOF\n");
         break;
      }
      assert (scanct == 1);

      if (buffer[0] == '#') {
         scanf ("%4095[^\n]", buffer);
         continue;
      }

      char *endptr = NULL;
      double number = strtod (buffer, &endptr);
      char operator = buffer[0];
      if (*endptr == '\0') { 
        if (top < STACK_SIZE-1){
            stack[++top] = number;
        }else
           fprintf(stderr, "Error: Stack overflow!\n");
        }
      else{
         switch (operator){
            case '+' :
               if (top-1 > EMPTY) {
                 stack [top-1] = stack[top-1] + stack[top];
                 top = top - 1;
               }else
                  fprintf(stderr, "Error: Stack underflow!\n");
               break;
            case '-' :
               if (top-1 > EMPTY) {
                 stack [top-1] = stack[top-1] - stack[top];
                 top = top - 1;
               }else
                  fprintf(stderr, "Error: Stack underflow!\n");
               break;
            case '*' :
               if (top-1 > EMPTY) {
                 stack [top-1] = stack[top-1] * stack[top];
                 top = top - 1;
               }else
                  fprintf(stderr, "Error: Stack underflow!\n");
               break;
            case '/' :
               if (top-1 > EMPTY) {
                 stack [top-1] = stack[top-1] / stack[top];
                 top = top - 1;
               }else
                  fprintf(stderr, "Error: Stack underflow!\n");
               break;
            case ';' :
               for (i =top; i > -1; i--){
                   printf("%22.15g\n", stack[top-i]);
               }
               break;
            case '~' :
               break;
            default:
               fprintf (stderr, "%s is not a valid operator!\n", buffer);
               continue;

         }
      }
   }
    return EXIT_SUCCESS;
}
