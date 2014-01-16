// $Id: jgrep2.java,v 1.1 2012-10-14 12:15:46-07 - - $

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
      while (input.hasNextLine()) {
         String line = input.nextLine();
         boolean matches = pattern.matcher (line).find();
         if (matches) {
            out.printf ("%s:%s%n", filename, line);
         }
      }
   }
   
   public static void optionflag (String x){

   Pattern insensitive = Pattern.compile ("i");
   Pattern printfilename = Pattern.compile ("l");
   Pattern linenumber = Pattern.compile ("n");
   Pattern allbutpattern = Pattern.compile ("v");

   boolean insensitivematches = insensitive.matcher (x).find();
   boolean printfilenamematches = printfilename.matcher (x).find();
   boolean linenumbermatches = linenumber.matcher (x).find();
   boolean allbutpatternmatches = allbutpattern.matcher (x).find();

   if (insensitivematches){
      System.out.println("This wont be case sensitive");
   }
   if (printfilenamematches){
      System.out.println("This will print only file name");
   }
   if (linenumbermatches){
      System.out.println("This will print line numbers");
   }
   if (allbutpatternmatches){
      System.out.println("This will print all but lines with the pattern");
   }

   }

   public static void main (String[] args) {

      options opts = new options (args);
      if (args.length == 0) {
         err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
         exit (messages.EXIT_FAILURE);
      }

      String options = args[0];
      Pattern optionpattern = Pattern.compile ("-");
      boolean optionmatches = optionpattern.matcher (options).find();
      if (optionmatches) {
         optionflag(options);
      }

      try {
         String regex = args[0];
         Pattern pattern = Pattern.compile (regex);
         if (args.length == 1) {
            scanfile (new Scanner (in), "<stdin>", pattern);
         }else {
            for (int argi = 1; argi < args.length; ++argi) {
               try {
                  String filename = args[argi];
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

