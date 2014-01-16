// $Id: treemap.java,v 1.3 2012-11-12 00:10:36-08 - - $
//Jacky Wong - jagwong@ucsc.edu
//ID: 1281439
import java.io.*;
import static java.lang.System.*;

class treemap <key_t extends Comparable<key_t>, value_t> {

   private class bstree {
      key_t key;
      value_t value;
      bstree left;
      bstree right;
   }
   private bstree root = null;

   public value_t put (key_t key, value_t value) {
      value_t oldvalue;
      bstree curr = root;
      bstree prev = null;
      int side = 0;
      while (curr != null){
         int cmp = curr.key.compareTo (key);
         if (cmp == 0){
            oldvalue = curr.value;
            curr.value = value;
            return oldvalue;
         }
         prev = curr;
         if (cmp < 0){
            curr = curr.right;
            side = 1;
         } else{
              curr = curr.left;
              side = 2;
           }
      }
      bstree tmp = new bstree();
      tmp.key = key;
      tmp.value = value;
      if (root == null) root = tmp;
      else{
      if (side == 1) prev.right = tmp;
         else if (side == 2) prev.left = tmp;
      }
      return null;
   }

   public value_t get (key_t key) { 
       bstree curr = root;
       while (curr != null){
          int cmp = curr.key.compareTo (key);
          if (cmp == 0) return curr.value;
          if (cmp < 0) curr = curr.right;
             else curr = curr.left;
       }
       return null;
   }

   public value_t remove (key_t key) {
      throw new UnsupportedOperationException ();
   }

   public void visit_all (visitor <key_t, value_t> visitor_fn) {
      visit_all_inorder (root, visitor_fn);
   }

   private void visit_all_inorder (bstree tree,
                  visitor <key_t, value_t> visitor_fn) {
      if(tree != null){
      visit_all_inorder(tree.left, visitor_fn);
      visitor_fn.visit (tree.key, tree.value);
      visit_all_inorder(tree.right, visitor_fn);   
      }
   }

   public void debug_dump () {
      debug_dump_inorder (root, 0);
   }

   private void debug_dump_inorder (bstree tree, int depth) {
      if (tree == null) return;
      debug_dump_inorder (tree.left, depth + 1);
      String sfmt = "%" + (depth > 0 ? depth * 3 : "") + "s";
      out.printf (sfmt + "%d: %s => %s%n",
                  "", depth, tree.key, tree.value);
      debug_dump_inorder (tree.right, depth + 1);
   }

}
