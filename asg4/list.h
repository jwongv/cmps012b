// $Id: list.h,v 1.5 2012-11-14 21:35:53-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// ID: 1281439
#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>

//
// NAME
//    list - maintain a doubly linked list of elements.
//
// DESCRIPTION
//    A doubly linked list of elements is maintained, with the
//    ability to insert, delete, and view elements of the list
//    and to move up and down the list one step at a time.
//

typedef enum {MOVE_HEAD, MOVE_PREV, MOVE_NEXT, MOVE_LAST} list_move;
   //
   // Type:  enumeration code for moving up and down the list.
   //        Used as second argument to `setmove_list':
   //
   // MOVE_HEAD - set the cursor position to the null node at the
   //             beginning of the list.
   //
   // MOVE_LAST - set the cursor position to the last node in the
   //             list.
   //
   // MOVE_PREV - set the cursor position to the node immediately
   //             before it in the list.
   //
   // MOVE_NEXT - set the cursor position to the node immediately
   //             after the current position.
   //

typedef struct list *list_ref;
   //
   // Type:  the handle returned by the constructor and passed to
   //        the other functions.
   //

void debugdump_list (list_ref list, char*);
   //
   // Accessor:       Prints out a debug dump of the list to stderr.
   // Precondition:   valid list.
   // Postcondition:  none.
   //


list_ref new_list (void);
   //
   // Constructor:    return a new valid empty list.
   // Precondition:   none;
   // Postcondition:  returns a properly constituted empty list.
   //

void free_list (list_ref);
   //
   // Destructor:     frees up the list and its internal headers.
   // Preconditions:  list must be valid and empty.
   // Postcondition:  memory is freed and its argument is dangling.
   // Asserts:        that the precondition is met.
   //

bool setmove_list (list_ref, list_move, char*);
   //
   // Mutator:        moves the current position to another position
   //                 in the list (see `typedef list_move' above).
   // Precondition:   list must be valid.
   //                 MOVE_PREV may not be used in the head position.
   //                 MOVE_NEXT may not be used in the last position.
   // Postcondition:  returns TRUE if successful and FALSE if failed.
   //

char *viewcurr_list (list_ref, char*);
   //
   // Accessor:       returns the data item in the current node in the
   //                 list.  Does not release space, this pointer's
   //                 target may not be changed or freed.
   // Precondition:   valid list and current not in the head position.
   // Postcondition:  returns NULL if called from the head positin.
   //

void print_all(list_ref, char*);

char* itoratetowrite (list_ref);


void insert_list (list_ref, char *);
   //
   // Mutator:        inserts new char* into the list immediately
   //                 after the current position.
   // Precondition:   valid list.
   // Postcondition:  char* passed in is now property of list and
   //                 not the client.
   //

void insert_fileline_list (list_ref, char *);

void insert_line_after (list_ref, char *);

void insert_line_before (list_ref, char *);

void set_curr (list_ref, int);

void set_curr_head (list_ref);

bool is_null(list_ref);

void delete_list (list_ref, char*);
   //
   // Mutator:        deletes the current line from the list.
   // Precondition:   valid list and not empty.
   // Postcondition:  same list with one line removed.
   //

bool empty_list (list_ref);
   //
   // Accessor:       checks to see if the list is empty.
   // Precondition:   list is valid.
   // Postcondition:  returns TRUE iff the only node is the head node.
   //

bool is_list (list_ref);
   //
   // Accessor:       checks to see if its argument is a list.
   // Precondition:   none.
   // Postcondition:  returns TRUE if is not null and is a list.
   //

#endif

