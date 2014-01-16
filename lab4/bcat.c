// $Id: bcat.c,v 1.50 2012-11-03 23:41:55-07 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439


//
// NAME
//    bcat - concatenate and display files
//
// SYNOPSIS
//    bcat [filename...]
//
// DESCRIPTION
//    The bcat utility reads each file in sequence and writes it
//    to stdout.  If any filename is given as the single character
//    "-", stdin is read at that point.  If no filenames are given
//    then stdin is read as the only file.
//

#include <errno.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *progname = NULL;          // Name of the program being run.
int exit_status = EXIT_SUCCESS; // Assume successful completion.

struct options {                // Structure to hold options.
   bool moretitles;             // Print titles in more-style
   bool numberlines;            // Output line numbers for each line.
   bool squeeze;                // Squeeze multiple empty lines.
};


//
// cat -
// Copy the contents of an already-opened file to stdout.
//

void catfile (FILE *input, char *filename, struct options *opts) {
   char buffer[4096];
   char prevbuffer[4096];
//   char *prevbuffer_ptr = &prevbuffer;
   int linenumber = 0;
   if (opts->moretitles){
      printf("\n");
      for (int i = 0; i<64; i++){
         printf(":");
      }
      printf("\n%s\n", filename);
      for (int i = 0; i<64; i++){
         printf(":");
      }
      printf("\n\n");
   }
   for (;;) {
      char *bufrc = fgets (buffer, sizeof buffer, input);
      linenumber++;
      if (bufrc == NULL) break;
      if (opts->squeeze){
         if (*prevbuffer == '\n' && *buffer == '\n') continue;
      }
      if (opts->numberlines)
          printf("%6d  ",linenumber);
      printf ("%s", buffer);
      strcpy(prevbuffer,buffer);
   };
}


// scanoptions -
// Scan the options and initialize a struct options.
//

void scan_options (int argc, char **argv, struct options *opts) {
   memset (opts, 0, sizeof (struct options));
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "mns");
      if (opt == EOF) break;
      switch (opt) {
         case 'm':
            opts->moretitles = true;
            break;
         case 'n':
            opts->numberlines = true;
            break;
         case 's':
            opts->squeeze = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     progname, optopt);
            fflush (NULL);
            exit_status = EXIT_FAILURE;
       }
   }
}


//
// main -
// Loop over files, if any, and cat each of them to stdout.
// Print error messages if appropriate.
//

int main (int argc, char **argv) {
   exit_status = EXIT_SUCCESS;
   progname = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (optind == argc) {
      catfile (stdin, "-", &opts);
   }else{
      for (int argi = optind; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, "-") == 0) {
            catfile (stdin, "-", &opts);
         }else{
            FILE *input = fopen (filename, "r");
            if (input == NULL) {
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", progname,
                        argv[argi], strerror (errno));
               fflush (NULL);
               exit_status = EXIT_FAILURE;
            }else{
               catfile (input, filename, &opts);
               fclose (input);
            };
         };
      };
   };
   return exit_status;
}

