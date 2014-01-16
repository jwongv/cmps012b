// $Id: jbox.java,v 1.3 2012-11-07 18:17:54-08 - - $

// Java equivalent of the intx example.
// For brevity we put all of the classes on one file.

import static java.lang.System.*;

class jbox_main {
   public static void main (String[] args) {
      jbox box = new jbox_code();
      out.printf ("box = %s%n", box);
      box.put (1024);
      out.printf ("box value is %d\n", box.get());
   }
}

interface jbox {
   public int get();
   public void put (int value);
}

class jbox_code implements jbox {
   private int value;

   jbox_code() {
      this (0);
   }

   jbox_code (int _value) {
      value = _value;
   }

   public int get() {
      return value;
   }

   public void put (int _value) {
      value = _value;
   }

}

