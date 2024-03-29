// $Id: hashset.h,v 1.1 2012-11-16 18:05:22-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// Michael Ungerer - mungerer@ucsc.edu

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset *hashset_ref;

//
// Create a new hashset with a default number of elements.
//
hashset_ref new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset_ref);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset_ref, char*);

void double_array_hash (hashset_ref hashset);

void clusters (hashset_ref hashset, int xoptcounter);

bool too_full_hash (hashset_ref hashset);

//
// Looks up the string in the hashset and returns true if found,
// false if not found.
//
bool has_hashset (hashset_ref, char*);

#endif

