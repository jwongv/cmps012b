// $Id: list.c,v 1.118 2012-11-27 02:34:11-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugf.h"
#include "list.h"

static char *list_tag = "struct list";
static char *listnode_tag = "struct listnode";
int currentline = 1;
int totallines = 1;
typedef struct listnode *listnode_ref;

struct list {
   //
   // INVARIANT:  Both head and last are NULL or neither are NULL.
   // If neither are null, then following listnode next links from
   // head will get to last, and prev links from last gets to head.
   //
   char *tag;
   listnode_ref head;
   listnode_ref curr;
   listnode_ref last;
};

struct listnode {
   char *tag;
   char *line;
   listnode_ref prev;
   listnode_ref next;
};

void debugdump_list (list_ref list, char *stdinline) {
   if (strlen(stdinline)>1){
      fflush(NULL);
      fprintf(stderr, "%s: %s: invalid command\n",Exec_Name, stdinline);
      fflush(NULL);
      Exit_Status = EXIT_FAILURE;
   }else{
     listnode_ref itor = NULL;
     assert (is_list (list));
     fflush (NULL);
     fprintf (stderr,
              "\n[%p]->struct list {tag=[%p]->[%s];"
              " head=[%p]; curr=[%p]; last=[%p]; }\n",
              list, list->tag, list->tag,
              list->head, list->curr, list->last);
     for (itor = list->head; itor != NULL; itor = itor->next) {
        fprintf (stderr,
                 "[%p]->struct listnode {tag=[%p]->[%s];"
                 " line=[%p]=[%s]; prev=[%p]; next=[%p]; }\n",
                 itor, itor->tag, itor->tag, itor->line, itor->line,
                 itor->prev, itor->next);
     }
     fflush (NULL);
   }
}


list_ref new_list (void) {
   //
   // Creates a new struct list.
   //
   list_ref list = malloc (sizeof (struct list));
   assert (list != NULL);
   list->tag = list_tag;
   list->head = NULL;
   list->curr = NULL;
   list->last = NULL;
   return list;
}

void free_list (list_ref list) {
   assert (is_list (list));
   assert (empty_list (list));
   memset (list, 0, sizeof (struct list));
   free (list);
}

bool setmove_list (list_ref list, list_move move, char *stdinline) {
   assert (is_list (list));
   if (strlen(stdinline)>1){
      fflush(NULL);
      fprintf(stderr, "%s: %s: invalid command\n",Exec_Name, stdinline);
      fflush(NULL);
      Exit_Status = EXIT_FAILURE;
   }else{
   switch (move) {
      case MOVE_HEAD:
           list->curr = list->head;
           currentline = 1;
           viewcurr_list(list, "");
           break;
      case MOVE_PREV:
           if (list->curr->prev != NULL){
              list->curr = list->curr->prev;
              --currentline;
           }
           viewcurr_list(list, "");
           break;
      case MOVE_NEXT:
           if (list->curr->next != NULL){
              list->curr = list->curr->next;
              ++currentline;
           }
           viewcurr_list(list, "");
           break;
      case MOVE_LAST:
           list->curr = list->last;
           currentline = totallines;
           viewcurr_list(list, "");
           break;
      default: assert (false);
   }
   }
   return false;
}

char *viewcurr_list (list_ref list, char *stdinline) {
   assert (is_list (list));
   if (strlen(stdinline)>1){
      fflush(NULL);
      fprintf(stderr, "%s: %s: invalid command\n",Exec_Name, stdinline);
      fflush(NULL);
      Exit_Status = EXIT_FAILURE;
   }else{
     if(list->head != NULL)
     printf ("%6d:%s\n",currentline, list->curr->line);
       else{
          fflush (NULL);
          fprintf (stderr, "%s: %s\n", Exec_Name, "no lines in file");
          fflush (NULL);
          Exit_Status = EXIT_FAILURE;
       }
   }
     return NULL;
}

void print_all(list_ref list, char *stdinline){
   assert (is_list(list));
   if (strlen(stdinline)>1){
      fflush(NULL);
      fprintf(stderr, "%s: %s: invalid command\n",Exec_Name, stdinline);
      fflush(NULL);
      Exit_Status = EXIT_FAILURE;
   }else{
   list->curr = list->head;
   currentline = 1;
   while(list->curr != NULL){
      printf("%6d: %s\n",currentline, list->curr->line);
      list->curr = list->curr->next;
      ++currentline;
   }
   list->curr = list->last;
   }
}

char* itoratetowrite (list_ref list){
   assert (is_list (list));
   assert (!empty_list (list));
   char *oldline = list->curr->line;
   list->curr = list->curr->next;
   return oldline;
}



void insert_list (list_ref list, char *line) {
   assert (is_list (list));
   listnode_ref newnode = malloc (sizeof (struct listnode));
   newnode->tag = listnode_tag;
   newnode->line = line;
   newnode->prev = NULL;
   newnode->next = NULL;
   if (empty_list(list)){
     list->head = newnode;
     list->last = newnode;
   }
   else{
     list->last->next = newnode;
     newnode->prev = list->last;
     list->last = newnode;
   }
}

void insert_fileline_list( list_ref list , char *line) {
   assert (is_list (list));
   listnode_ref newnode = malloc (sizeof (struct listnode));
   newnode->tag = listnode_tag;
   newnode->line = line;
   if (empty_list(list)){
      list->head = newnode;
      list->last = newnode;
      list->curr = newnode;
      list->curr->next = NULL;
      list->curr->prev = NULL;
   }else{
   newnode->prev = list->curr;
   newnode->next = list->curr->next;
   if (list->curr->next != NULL)
      list->curr->next->prev = newnode;
   list->curr->next = newnode;
   list->curr = newnode;
   }
   ++totallines;
   ++currentline;
}

void insert_line_after (list_ref list, char *line){
   assert (is_list (list));
   listnode_ref newnode = malloc (sizeof (struct listnode));
   newnode->tag = listnode_tag;
   newnode->line = strdup(line);
   if (empty_list(list)){
      list->head = newnode;
      list->last = newnode;
      list->curr = newnode;
      list->curr->next = NULL;
      list->curr->prev = NULL;
   }else{
   newnode->prev = list->curr;
   newnode->next = list->curr->next;
   if (list->curr->next != NULL)
      list->curr->next->prev = newnode;
   list->curr->next = newnode;
   list->curr = newnode;
   }
   ++currentline;
   ++totallines;
   viewcurr_list (list, "");
}

void insert_line_before (list_ref list, char *line){
   assert (is_list (list));
   listnode_ref newnode = malloc (sizeof (struct listnode));
   newnode->tag = listnode_tag;
   newnode->line = strdup(line);
   if (empty_list(list)){
      list->head = newnode;
      list->last = newnode;
      list->curr = newnode;
      list->curr->next = NULL;
      list->curr->prev = NULL;
      ++currentline;
   }else{
   newnode->prev = list->curr->prev;
   newnode->next = list->curr;
   if (list->curr->prev != NULL)
      list->curr->prev->next = newnode;
   list->curr->prev = newnode;
   list->curr = newnode;
   }
   ++totallines;
   viewcurr_list (list, "");
}

void set_curr (list_ref list, int currentlines ){
   assert (is_list (list));
   list->curr = list->last;
   currentline = currentlines;
   totallines = currentlines;
}

void set_curr_head (list_ref list){
   assert (is_list (list));
   list->curr = list->head;
   currentline = 0;
}

bool is_null(list_ref list){
  assert (is_list(list));
  if(list->curr == NULL){
     list->curr = list->last;
     return true;
  }
  else
     return false;
}

void delete_list (list_ref list, char *stdinline) {
   assert (is_list (list));
    if (strlen(stdinline)>1){
      fflush(NULL);
      fprintf(stderr, "%s: %s: invalid command\n",Exec_Name, stdinline);
      fflush(NULL);
      Exit_Status = EXIT_FAILURE;
   }else{
  
     if (empty_list(list)){
        fflush (NULL);
        fprintf (stderr, "%s: %s\n",Exec_Name, "no lines in file");
        fflush (NULL);
        Exit_Status = EXIT_FAILURE;
     }
     else{
     listnode_ref oldnode = list->curr;
     if(list->curr->next != NULL){
        list->curr->next->prev = list->curr->prev;
        if (list->curr->prev == NULL)
           list->head=list->curr->next;
        else
           list->curr->prev->next = list->curr->next;
        list->curr = list->curr->next;
     }
     else{
        if (list->curr->prev != NULL){
        list->last = list->curr->prev;
        list->curr = list->last;
        list->curr->next = NULL;
        }
        else{
        list->head = NULL;
        list->last = NULL;
        }
        --currentline;
     }
     free (oldnode->line);
     free (oldnode);
     --totallines;
     }

   }
}

bool empty_list (list_ref list) {
   assert (is_list (list));
   return list->head == NULL;
}

bool is_list (list_ref list) {
   return list != NULL && list->tag == list_tag;
}

