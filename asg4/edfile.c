// $Id: edfile.c,v 1.101 2012-11-27 02:40:02-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "debugf.h"
#include "list.h"

bool want_echo = false;
int currentlines = 0;
void badline (int stdincount, char *stdinline) {
   fflush (NULL);
   fprintf (stderr, "Bad input line %d: %s\n", stdincount, stdinline);
   fflush (NULL);
}

void putinlist (list_ref list, FILE *input, char *filename) {
   char buffer[1024];
   for (int linenr = 1; ; ++linenr) {
      char *linepos1 = fgets (buffer, sizeof buffer, input);
      if (linepos1 == NULL) break;
      linepos1 = strchr (buffer, '\n');
      if (linepos1 == NULL) {
         fflush (NULL);
         fprintf (stderr, "%s: %s[%d]: unterminated line\n",
                  Exec_Name, filename, linenr);
         fflush (NULL);
         Exit_Status = EXIT_FAILURE;
      }else {
         *linepos1 = '\0';
      }
      linepos1 = strdup (buffer);
      assert (linepos1 != NULL);
      insert_list (list, linepos1);
      ++currentlines;
      set_curr (list, currentlines);
   }
   printf("%d lines read from %s\n", currentlines, filename);
}

void putfileinlist (list_ref list, char *filename) {
   FILE *input = fopen (filename, "r");
   if (input == NULL) {
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n",
               Exec_Name, filename, strerror (errno));
      fflush (NULL);
      Exit_Status = EXIT_FAILURE;
   }else {
      putinlist (list, input, filename);
      fclose (input);
   }
}

void putinlist1 (list_ref list, FILE *input, char *filename){
   char buffer[1024];
   int newfilelines = 0;
   for (int linenr = 1; ; ++linenr) {
      char *linepos1 = fgets (buffer, sizeof buffer, input);
      if (linepos1 == NULL) break;
      linepos1 = strchr (buffer, '\n');
      if (linepos1 == NULL) {
         fflush (NULL);
         fprintf (stderr, "%s: %s[%d]: unterminated line\n",
                  Exec_Name, filename, linenr);
         fflush (NULL);
         Exit_Status = EXIT_FAILURE;
      }else {
         *linepos1 = '\0';
      }
      linepos1 = strdup (buffer);
      assert (linepos1 != NULL);
      insert_fileline_list (list, linepos1);
      ++newfilelines;
   }
   printf("%d lines read from %s\n", newfilelines, filename);
}

void writefile (list_ref list, char *newfile, char *filename ){
   FILE *output;
   if (newfile[0] == '\0')
      output = fopen(filename, "w");
   else 
      output = fopen(newfile, "w");
   set_curr_head(list);
   while (!is_null(list)){
   char *oldline = itoratetowrite(list);
   fprintf(output, "%s\n", oldline);
   }
   fclose(output);

}

void insertfile (list_ref list, char *filename){
   FILE *input = fopen (filename, "r");
   if (input == NULL) {
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n",
               Exec_Name, filename, strerror (errno));
      fflush (NULL);
      Exit_Status = EXIT_FAILURE;
   }else {
      putinlist1 (list, input, filename);
      fclose (input);
   }
}


void editfile (list_ref list, char *filename) {
   char stdinline[1024];
   int stdincount = 0;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if (linepos == NULL) break;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      }else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '$': setmove_list(list, MOVE_LAST, stdinline); break;
            case '*': print_all(list, stdinline); break;
            case '.': viewcurr_list(list, stdinline); break;
            case '0': setmove_list(list, MOVE_HEAD, stdinline); break;
            case '<': setmove_list(list, MOVE_PREV, stdinline); break;
            case '>': setmove_list(list, MOVE_NEXT, stdinline); break;
            case '@': debugdump_list (list, stdinline); break;
            case 'a': insert_line_after (list, stdinline+1); break;
            case 'd': delete_list(list, stdinline); break;
            case 'i': insert_line_before(list, stdinline+1); break;
            case 'r': insertfile(list, stdinline+1); break;
            case 'w': writefile (list, stdinline+1, filename); break;
            default : badline (stdincount, stdinline);
         }
      }
   }
   printf("%s\n", "^D");
}



void usage_exit() {
   fflush (NULL);
   fprintf (stderr, "Usage: %s filename\n", Exec_Name);
   fflush (NULL);
   exit (EXIT_FAILURE);
}

int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   if (argc != 2) usage_exit();
   want_echo = ! (isatty (fileno (stdin)) && isatty (fileno (stdout)));
   list_ref list = new_list();
   putfileinlist (list, argv[1]);
   editfile (list, argv[1]);
   set_curr_head(list);
   while (!empty_list(list)){
      delete_list(list, "");
   }
   free_list (list); list = NULL;
   return Exit_Status;
}
