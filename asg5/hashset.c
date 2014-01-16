// $Id: hashset.c,v 1.119 2012-12-07 17:17:22-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// Michael Ungerer - mungerer@ucsc.edu

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   for (size_t i = 0; i < hashset->length; i++){
      free (hashset->array[i]);
   }
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   if (too_full_hash (hashset)) double_array_hash (hashset);
   hashcode_t index = strhash (item) % hashset->length;
   while (hashset->array[index] != NULL) {
      if (strcmp (hashset->array[index], item) == 0) return;
      index = (index + 1) % hashset->length;
   }
   hashset->array[index] = strdup (item);
   ++hashset->load;
}

void double_array_hash (hashset_ref hashset){
   size_t newlength = hashset->length * 2 + 1;
   char **tmparray = malloc ((newlength) * sizeof (char*));
   assert (tmparray != NULL);
   for (size_t index = 0; index < newlength ; ++index){
      tmparray[index] = NULL;
   }
   for (size_t i = 0; i < hashset->length  ; ++i){
      if (hashset->array[i] != NULL){
         hashcode_t newindex = strhash (hashset->array[i]) % newlength;
         while (tmparray[newindex] != NULL){
            newindex = (newindex +1) % newlength;
         }
      tmparray[newindex] = strdup (hashset->array[i]);
      }
   }
   for (size_t i = 0; i < hashset->length; i++){
      free(hashset->array[i]);
   }
   free(hashset->array);
   hashset->array = tmparray;
   hashset->length = newlength;
}


void clusters (hashset_ref hashset, int xoptcounter){
   int *clusterarray = malloc (hashset->length/4 * (sizeof (int)));
   for (int i = 0; i < (int32_t) (hashset->length/4 ); ++i){
      clusterarray[i] = 0;
   }
   int cindex = 0;
   int cindex2 = 0;
   while (cindex2 < (int32_t)hashset->length - 1){
      int counter = 0;
      for (;hashset->array[cindex] == NULL; ++cindex){      
      ++cindex2;
      }
      for (;hashset->array[cindex] != NULL;
            cindex = (cindex +1) % (int32_t)hashset->length){
         ++counter;
         ++cindex2;
      }
   ++clusterarray[counter];
   }
   for (int i = 0; i< (int32_t)(hashset->length/4 ); ++i){
      if (clusterarray[i] > 0)
         printf ("%10d clusters of size %d\n", clusterarray[i], i);
   }
   if (xoptcounter > 1){
      for (int i = 0; i < (int32_t)hashset->length; i++){
         if (hashset->array[i] != NULL)
            printf ("array[%10d] = %12u \"%s\"\n", i,
                    strhash(hashset->array[i]), hashset->array[i] );
      }
   }
   free(clusterarray);
}

bool too_full_hash (hashset_ref hashset){
   if (hashset->load * 4 > (int32_t) hashset->length) return true;
   return false;
}

bool has_hashset (hashset_ref hashset, char *item) {
   hashcode_t index = strhash (item) % hashset->length;
   while (hashset->array[index] != NULL){
      if (strcmp(hashset->array[index], item) == 0)
         return true;
      index = (index + 1) % hashset->length;
   }
   return false;
}

