// $Id: linkedlist.java,v 1.5 2012-10-29 00:12:06-07 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

import java.io.*;
import java.util.Scanner;
import java.util.Iterator;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class linkedlist implements Iterable<pair> {

   private class node {
      pair item;
      node link;
   }


   private node head = null;

   public String get (String key) {
      itor pairiterator = new itor();      
      while(pairiterator.hasNext()){
         pair thispair = pairiterator.next();
         if (key.equals(thispair.key))
             return thispair.value;
      }
      return null;
   }

   public String put (String key, String value) {
      node curr = head;
      node prev = null;
      int cmp = 1;
      String oldvalue = "";
      while (curr!=null){
         cmp = curr.item.key.compareTo(key);
         if(cmp >=0) break;
         prev = curr;
         curr = curr.link;
      }
      if (cmp != 0){
         node tmp = new node();
         pair tmppair = new pair(key, value);
         tmp.item = tmppair;
         tmp.link = curr;
         if(prev == null)
           head = tmp;
         else
           prev.link = tmp;
      }
      if (cmp == 0){
         oldvalue = curr.item.value;
         curr.item.value = value;
         return oldvalue;
      }
      return null;
   }

   public String delete (String key) {
      node curr = head;
      node prev = null;
      String oldvalue = "";
      while (curr!=null){
         if(curr.item.key.equals(key)){
            oldvalue = curr.item.value;
            if(prev == null) head = curr.link;
            else prev.link = curr.link;
            return oldvalue;
         }
         prev = curr;
         curr = curr.link;
      }
      return null;
   }

   public void printAll(){
      itor pairiterator = new itor();
      while(pairiterator.hasNext()){
         pair thispair = pairiterator.next();
         out.printf("%s=%s%n", thispair.key, thispair.value);
      }
   }

   public void printValueMatches(String value){
      itor pairiterator = new itor();
      while(pairiterator.hasNext()){
         pair thispair = pairiterator.next();
         if (thispair.value.equals(value))
           out.printf("%s=%s%n", thispair.key, thispair.value);
      }
   }

   public Iterator<pair> iterator () {
      return new itor ();
   }

   private class itor implements Iterator<pair> {
      private node nextnode = head;

      public boolean hasNext () {
         return nextnode != null;
      }

      public pair next () {
         if (! hasNext()) throw new NoSuchElementException ();
         pair result = nextnode.item;
         nextnode = nextnode.link;
         return result;
      }

      public void remove () {
         throw new UnsupportedOperationException ();
      }
   }
}
