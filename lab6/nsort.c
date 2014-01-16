// $Id: nsort.c,v 1.3 2012-11-16 00:18:31-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439


#include <errno.h>
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct node *node_ref;
typedef struct list *list_ref;
int EXIT_STATUS = EXIT_SUCCESS;

struct node {
   double item;
   node_ref link;
};

struct options {
   bool debug;
};

void scan_options (int argc, char **argv,
                    struct options *opts, char *progname) {
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->debug = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     progname, optopt);
            fflush (NULL);
            EXIT_STATUS = EXIT_FAILURE;
       }
   }
}

void printlist (node_ref head, struct options *opts){
   if(opts->debug){
       for (node_ref curr = head; curr != NULL; curr = curr->link){
           printf ("%p -> struct node {item= %.15g, link= %p}\n",
              (void*) curr, curr->item, (void*) curr->link);
       }
   }
   else {
       for (node_ref curr = head; curr != NULL; curr = curr->link){
           printf ("%24.15g\n", curr->item);
       }
   }
}

int main (int argc, char **argv) {

   char *progname = basename (argv[0]);
   char err_buffer [256];
   char err_buf_fmt[16];
   sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer -1);
   node_ref head = NULL;
   struct options opts;
   scan_options (argc, argv, &opts, progname);

   for (;;){
      double number;
      int check = scanf ("%lg", &number);

      if (check == EOF){
         printf ("%s: EOF\n", progname);
         break;
      }else if (check == 1) {
          node_ref curr = head;
          node_ref prev = NULL;
          while (curr != NULL){
              if (curr->item > number) break;
              prev = curr;
              curr = curr->link;
          }
          node_ref tmp = malloc (sizeof (struct node));
          assert (tmp != NULL);
          tmp->item = number;
          tmp->link = curr;
          if (prev == NULL) head = tmp;
                       else prev->link = tmp;
      }else {
         check = scanf (err_buf_fmt, err_buffer);
         assert (check == 1);
         printf ("%s: bad number \"%s\"\n", progname, err_buffer);
         EXIT_STATUS = EXIT_FAILURE;
      }
   }

   printlist(head, &opts);
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free (old);
   }
   return EXIT_STATUS;
}

