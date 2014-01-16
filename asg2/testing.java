import static java.lang.System.*;

class testing{

   public static void main (String [] args){
      String rawr = "";
      rawr = rawr.trim();
      String [] parts = rawr.split("=",2);
      
      System.out.println(parts.length + "is the length!");

      if (!parts[0].equals(""))
      System.out.println(parts[0] + "rawr");
      else if(rawr.equals("="))
          System.out.println("print out the dictionary!");
      if (!parts[0].equals("") && rawr.charAt(0) == '=' && !parts[1].equals(""))
           System.out.println ("print out all key and value pairs whos value field match!");
      
//      System.out.println(part[1]);

   }


}
