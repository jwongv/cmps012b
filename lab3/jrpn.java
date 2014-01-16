//# $Id: jrpn.java,v 1.8 2012-10-24 22:56:02-07 - - $

// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jrpn{

   public static void main (String[] args){

      final int EMPTY = -1;
      int top = EMPTY;
      double[] stack = new double[16];
      char operator = 'a';

      if (args.length >= 0){
        Scanner input = new Scanner (in);
        int i = 0;
        while (input.hasNext()){
            boolean isoperator = false;
            double userinputd = 1;
            String userinput = input.next();
            if (userinput.startsWith("#")){
               input.nextLine();
               continue;
            }
            try{
               userinputd = Double.parseDouble(userinput);
            }catch(NumberFormatException error){
                 isoperator = true;
                 operator = userinput.charAt(0);
            }

            if(isoperator){
                switch (operator){
                   case '+':
                        if (top-1 > EMPTY){
                        stack [top-1] = stack[top-1] + stack[top];
                        top = top - 1;
                        }else
                           err.printf("Error: Stack underflow!%n");
                        break;
                   case '-':
                        if (top-1 > EMPTY){
                        stack [top-1] = stack[top-1] - stack[top];
                        top = top - 1;
                        }else
                           err.printf("Error: Stack underflow!%n");
                        break;
                   case '*':
                        if (top-1 > EMPTY){
                        stack [top-1] = stack[top-1] * stack[top];
                        top = top - 1;
                        }else
                           err.printf("Error: Stack underflow!%n");
                        break;
                   case '/':
                        if (top-1 >EMPTY) {
                        stack [top-1] = stack[top-1] / stack[top];
                        top = top - 1;
                        }else
                           err.printf("Error: Stack underflow!%n");
                       break;
                   case ';':
                        for (i = top; i > -1; i--){
                           out.printf("%22.15g\n", stack[top-i]);
                        }
                        break;
                   case '~':
                        top = EMPTY;
                        break;
                   default:
                        err.printf ("%s is not a valid operator!%n", userinput);
                        continue;
                }
            }
            else{
                if (top < stack.length-1)
                   stack[++top] = userinputd;
                else
                  err.printf("Error: Stack overflow!%n");
            }
        }
      }
   }
}
