// $Id: lsort.c,v 1.2 2012-11-16 00:18:29-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID:1281439


#include <errno.h>
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct node *node_ref;
typedef struct list *list_ref;
int EXIT_STATUS = EXIT_SUCCESS;
typedef char *cstring;

struct node {
   cstring item;
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

void printlist (node_ref head, struct options *opts, char *progname){
   if(opts->debug){
       for (node_ref curr = head; curr != NULL; curr = curr->link){
          printf("%s: %p-> node {\n"
                 "    string= %p->\"%s\",\n"
                 "    link= %p}\n",
                 progname, (void*) curr, (void*) curr->item,
                 curr->item, (void*) curr->link);
       }
   }
   else {
       for (node_ref curr = head; curr != NULL; curr = curr->link){
           printf ("%s\n", curr->item);
       }
   }
}

int main (int argc, char **argv) {

   char *progname = basename (argv[0]);
   char buffer[72];
   node_ref head = NULL;
   int linenr;
   struct options opts;
   scan_options (argc, argv, &opts, progname);

   for (linenr = 1;; ++linenr){
      cstring number;
      number = fgets (buffer, sizeof buffer, stdin);
      if (number == NULL) break;

      cstring nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  progname, linenr, buffer);
      };

          node_ref curr = head;
          node_ref prev = NULL;
          while (curr != NULL){
              int cmp = strcmp(curr->item, number);
              if (cmp > 0) break;
              prev = curr;
              curr = curr->link;
          }
          node_ref tmp = malloc (sizeof (struct node));
          assert (tmp != NULL);
          tmp->item = strdup(buffer);
          assert (tmp->item != NULL);
          tmp->link = curr;
          if (prev == NULL) head = tmp;
                       else prev->link = tmp;
   }

   printlist(head, &opts, progname);
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free (old->item);
      free (old);
   }
   return EXIT_STATUS;
}

