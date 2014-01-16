// $Id: keyvalue.java,v 1.7 2012-10-29 00:11:20-07 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

import java.io.*;
import java.util.Scanner;
import java.util.Iterator;
import static java.lang.System.*;

class keyvalue {

   static void scanfile (Scanner input, String filename){
      int numberline = 1;
      while (input.hasNextLine()) {
         String line = input.nextLine();
         line = line.trim();
         out.printf("%s:%d:%s%n",filename,numberline++,line);
         String [] parts = line.split("=",2);
         if(parts[0].length()>0){
         if(parts[0].charAt(0) == '#'){
            input.nextLine();
            continue;
         }
         }
         if(parts.length == 1){
           if (list.get(parts[0]) != null)
              out.printf("%s=%s%n",parts[0],list.get(parts[0]));
           if (list.get(parts[0]) == null)
              out.printf("%s: not found%n", parts[0]);
         }
         if(line.equals("=")){
           list.printAll(); 
         }
         if(parts.length == 2){
            if(parts[0].equals("") && !parts[1].equals("")){
               list.printValueMatches(parts[1]);
            }
            if(!parts[0].equals("") && parts[1].equals("")){
              if (list.get(parts[0]) == null)
                 out.printf("%s: not found%n", parts[0]);
              else if (list.get(parts[0]) != null){
                 out.printf("%s=%s%n",parts[0],list.get(parts[0]));
                 list.delete(parts[0]);
              }
            }
            if(!parts[0].equals("") && !parts[1].equals("")){
              if(list.get(parts[0]) != null)
                out.printf("%s=%s%n", parts[0],
                              list.put(parts[0], parts[1]));
              list.put(parts[0], parts[1]);
            }
         }
      }
   }

static linkedlist list;

   public static void main (String[] args) {
      list = new linkedlist();
         if(args.length == 0)
            scanfile (new Scanner (in), "<stdin>");
         else{
            for (int argi = 0; argi < args.length; ++argi) {
               try {
                  if(args[argi].equals("-"))
                      scanfile (new Scanner (in), "<stdin>");
                  else{
                     String filename = args[argi];
                     Scanner input = new Scanner (new File (filename));
                     scanfile (input, filename);
                     input.close();
                  }
               }catch (IOException error) {
                  messages.warn (error.getMessage());
               }
            }
         }

      exit (messages.exit_status);

   }
/*
      ////////// delete these loops and replace with prog //////////
      for (pair item : list) {
         out.printf ("%s = %s%n", item.key, item.value);
      }
      for (Iterator<pair> itor = list.iterator();
           itor.hasNext (); ) {
         pair item = itor.next ();
         out.printf ("%s = %s%n", item.key, item.value);
      }
*/


}

