/* $Id: queue.c,v 1.20 2012-11-23 22:50:15-08 - - $ */
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

static char *queue_tag = "struct queue";
static char *queuenode_tag = "struct queuenode";

typedef struct queuenode *queuenode_ref;

struct queuenode {
   char *tag;
   queue_item_t item;
   queuenode_ref link;
};

struct queue {
   char *tag;
   queuenode_ref front;
   queuenode_ref rear;
};

queue_ref new_queue (void) {
   queue_ref new = malloc (sizeof (struct queue));
   assert (new != NULL);
   new->tag = queue_tag;
   new->front = NULL;
   new->rear = NULL;
   return new;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   queuenode_ref newnode = malloc (sizeof (struct queuenode));
   newnode->tag = queuenode_tag;
   newnode->item = item;
   newnode->link = NULL;
   if (isempty_queue(queue)){
      queue->front = newnode;
      queue->rear = newnode;
   }
   else{
      queue->rear->link = newnode;
      queue->rear = newnode;
   }
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   queue_item_t olditem  = queue->front->item;
   queuenode_ref oldnode = queue->front;
   queue->front = queue->front->link;
   free(oldnode);
   return olditem;
}

bool isempty_queue (queue_ref queue) {
   assert (is_queue (queue));
   return queue->front == NULL;
}

bool is_queue (queue_ref queue) {
   return queue != NULL && queue->tag == queue_tag;
}

