// $Id: list4.c,v 1.12 2012-11-06 11:48:29-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ref;
struct node {
   char *word;
   node_ref link;
};

int main (int argc, char **argv) {
   node_ref head=NULL;
   for (int argi = 0; argi < argc; ++argi) {
      node_ref node = malloc (sizeof (struct node));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   for (node_ref curr = head; curr->link != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->word, curr->link);
   }

   while(head!=NULL){
      node_ref tmp = head;
      head = head->link;
      free(tmp);
   }
   return 9;
}
