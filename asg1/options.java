//Name: Jacky Wong
//Username: jagwong@ucsc.edu
//ID: 1281439
// $Id: options.java,v 1.4 2012-10-14 18:41:35-07 - - $

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;

class options {
   boolean insensitive = false;
   boolean filename_only = false;
   boolean number_lines = false;
   boolean reverse_match = false;
   String regex;
   String[] filenames;

  public options (String[] args) {

       int argi = 0;
       String notoption = "Not an available option";
       if (args[argi].startsWith("-")){
           ++argi;
           for(int i = 1; i<args[0].length(); ++i){
                switch (args[0].charAt(i)){
                     case 'i': insensitive = true;
                               break;
                     case 'l': filename_only = true;
                               break;
                     case 'n': number_lines = true;
                               break;
                     case 'v': reverse_match = true;
                               break;
                     default: err.printf ("jgrep: %c (%s) %n",
                                args[0].charAt(i),notoption);
                     exit (messages.EXIT_FAILURE);
                     break;


                }
           }
       }

       if(args.length<argi+1){
           err.printf ("Usage: %s [-ilnv] regex [filename...]%n",
                       messages.program_name);
           exit (messages.EXIT_FAILURE);
       }

       regex = args[argi++];

       filenames = new String[args.length-argi];
       int i = 0;
       for( ;argi<args.length;++argi){
           filenames[i++] = args[argi];
       }

   }
}

