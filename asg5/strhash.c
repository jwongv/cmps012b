// $Id: strhash.c,v 1.2 2012-12-07 16:39:18-08 - - $
// Jacky Wong - jagwong@ucsc.edu
// Michael Ungerer - mungerer@ucsc.edu

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "strhash.h"

hashcode_t strhash (char *string) {
   assert (string != NULL);
   hashcode_t hashcode = 0;
   for (int index = 0; string[index] != '\0'; ++index) {
      hashcode = hashcode * 31 + (unsigned char) string[index];
   }
   return hashcode;
}

