// $Id: spellchk.c,v 1.46 2012-12-07 17:07:47-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// Michael Ungerer - mungerer@ucsc.edu

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME "/afs/cats.ucsc.edu/courses/cmps012b-wm/usr/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2



void print_error (char *object, char *message) {
   fflush (NULL);
   fprintf (stderr, "%s: %s: %s\n", Exec_Name, object, message);
   fflush (NULL);
   Exit_Status = EXIT_FAILURE;
}

FILE *open_infile (char *filename) {
   FILE *file = fopen (filename, "r");
   if (file == NULL) print_error (filename, strerror (errno));
   DEBUGF ('m', "filename = \"%s\", file = 0x%p\n", filename, file);
   return file;
}

void spellcheck (char *filename, hashset_ref hashset) {
   yylineno = 1;
   DEBUGF ('m', "filename = \"%s\", hashset = 0x%p\n",
                filename, hashset);
   for (;;) {
      int token = yylex ();
      if (token == 0) break;
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
      bool initialword = has_hashset(hashset,yytext);
      int i = 0;
      char *originalword = strdup(yytext);
      while (yytext[i] != '\0'){
         yytext[i] = tolower (yytext[i]);
         i++;
      }
      bool lowerword = has_hashset(hashset, yytext);
      if (!initialword && !lowerword){
         fflush(NULL);
         fprintf (stderr, "%s is mispelled!\n", originalword);
         fflush(NULL);
         Exit_Status = EXIT_FAILURE;
      }
         free (originalword);
   }
}

typedef char *cstring;

void load_dictionary (char *dictionary_name, hashset_ref hashset) {
   char buffer [1000];
   if (dictionary_name == NULL) return;
   DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
           dictionary_name, hashset);
   FILE *dictionary = open_infile (dictionary_name);
   if (dictionary != NULL){
      for (;;){
          cstring line;
          line = fgets(buffer, sizeof buffer, dictionary);
          if (line == NULL) break;
          cstring nlpos = strchr (buffer, '\n');
          if (nlpos != NULL)
             *nlpos = '\0';
          put_hashset (hashset, line);
      }
   fclose (dictionary);
   }else Exit_Status = 2;
      
}
 

int main (int argc, char **argv) {
   bool clusteropt = false;
   Exec_Name = basename (argv[0]);
   char *default_dictionary = DEFAULT_DICTNAME;
   char *user_dictionary = NULL;
   hashset_ref hashset = new_hashset ();
   yy_flex_debug = false;

   // Scan the arguments and set flags.
   opterr = false;
   int xopt_counter = 0;
   for (;;) {
      int option = getopt (argc, argv, "nxyd:@:");
      if (option == EOF) break;
      switch (option) {
         char optopt_string[16]; // used in default:
         case 'd': user_dictionary = optarg;
                   break;
         case 'n': default_dictionary = NULL;
                   break;
         case 'x': clusteropt = true;
                   ++xopt_counter;
                   break;
         case 'y': yy_flex_debug = true;
                   break;
         case '@': set_debugflags (optarg);
                   if (strpbrk (optarg, "@y")) yy_flex_debug = true;
                   break;
         default : sprintf (optopt_string, "-%c", optopt);
                   print_error (optopt_string, "invalid option");
                   break;
      }
   }
   if (default_dictionary == NULL && user_dictionary == NULL){
      printf("failed!");
      exit(EXIT_FAILURE);
   }
   // Load the dictionaries into the hash table.
   load_dictionary (default_dictionary, hashset);
   load_dictionary (user_dictionary, hashset);

   if (clusteropt) clusters(hashset, xopt_counter);
   // Read and do spell checking on each of the files.
   if (optind >= argc) {
      yyin = stdin;
      spellcheck (STDIN_NAME, hashset);
   }else {
      int fileix = optind;
      for (; fileix < argc; ++fileix) {
         DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
         char *filename = argv[fileix];
         if (strcmp (filename, STDIN_NAME) == 0) {
            yyin = stdin;
            spellcheck (STDIN_NAME, hashset);
         }else {
            yyin = open_infile (filename);
            if (yyin == NULL) continue;
            spellcheck (filename, hashset);
            fclose (yyin);
         }
      }
   }
   free_hashset(hashset);
   yycleanup ();
   return Exit_Status;
}

