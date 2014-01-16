// $Id: options.java,v 1.3 2012-11-12 00:10:25-08 - - $
//Jacky Wong - jagwong@ucsc.edu
//ID: 1281439
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class options {
   boolean count_only = false;
   boolean dump_tree = false;
   boolean fold_cases = false;
   String[] filenames = null;

   options (String[] args) {
      int argi = 0;
      String notoption = "Not an available option";
      if (args.length > 0){
      if (args[argi].startsWith("-")){
         ++argi;
         for (int i = 1; i<args[0].length();++i){
             switch (args[0].charAt(i)){
                 case 'c': count_only = true;
                           break;
                 case 'd': dump_tree = true;
                           break;
                 case 'f': fold_cases = true;
                           break;
                 default: err.printf ("jxref: %c (%s) %n",
                               args[0].charAt(i), notoption);
                 exit (messages.EXIT_FAILURE);
                 break;
             }
         }
      }
      }
      if (args.length-argi == 0){
          filenames = new String[1];
          filenames[0] = "-";
      } else if (args.length-argi > 0){
          filenames = new String[args.length-argi];
          for( int i = 0;argi<args.length;argi++){
             filenames[i++] = args[argi];
          }
        }
   }
}
