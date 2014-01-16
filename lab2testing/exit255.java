// $Id: exit1.java,v 1.2 2012-10-16 10:52:35-07 - - $
// Jacky Wong - jagwong@ucsc.edu

import java.io.*;
import static java.lang.System.*;


class exit255{

     public static void main (String[] args){

        String errmsg = "EXIT 255";
        err.printf("%s%n", errmsg);
        exit (255);

     }
}
