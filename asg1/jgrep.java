//Name: Jacky Wong
//Username: jagwong@ucsc.edu
//ID: 1281439

// $Id: jgrep.java,v 1.5 2012-10-14 18:41:35-07 - - $

//
// This program is a stub showing how to create a pattern from a
// regular expression.  It does not handle options or files, and
// has some other bugs which you must discover and fix.
//

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;


class jgrep {


   static void scanfile (Scanner input, String filename,
                         Pattern pattern) {
      int nl_counter = 1;
      int numberofmatches = 0;
      while (input.hasNextLine()) {
         String line = input.nextLine();
         boolean matches = pattern.matcher (line).find();
         if (flags.reverse_match){
             matches = !matches;
         }
         if (matches) {
              if(flags.filename_only){
                   out.println(filename);
                   ++numberofmatches;
                   break;
              }
         if(flags.filenames.length>1) out.printf("%s:",filename);
         if(flags.number_lines) out.printf("%d:", nl_counter);
         out.println(line);
         ++numberofmatches;
         }
         ++nl_counter;
      } 
     if(numberofmatches == 0){
        messages.nomatch();
     }
   }
static int numberofmatches;
static options flags;

   public static void main (String[] args) {

      if (args.length == 0) {
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
         exit (messages.EXIT_FAILURE);
      }
       flags = new options (args);

      try {
         Pattern pattern = Pattern.compile (flags.regex);
         if (flags.insensitive){
               pattern = Pattern.compile (flags.regex,
                    Pattern.CASE_INSENSITIVE);
         }
         else{
               pattern = Pattern.compile (flags.regex);
         }
         if (flags.filenames.length == 0) {
            scanfile (new Scanner (in), "<stdin>", pattern);
         }else {
            for (int flagi=0; flagi<flags.filenames.length; ++flagi){
               try {
                  String filename = flags.filenames[flagi];
                  Scanner input = new Scanner (new File (filename));
                  scanfile (input, filename, pattern);
                  input.close();
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }
      }catch (PatternSyntaxException error) {
         messages.die (error.getMessage());
      }
          exit (messages.exit_status);
   }
}

