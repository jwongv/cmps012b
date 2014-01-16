#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

#include "inssort.h"

void inssort (void *base, size_t nelem, size_t size, 
              int (*compar) (const void *, const void *)){
   
   for (size_t index = 1; index < nelem; ++index){
      int slot = index;
      void *copy[size];
      memcpy (copy,  base + slot * size, size);
      for (;slot > 0; --slot){
         int cmp = compar(copy, base + (slot - 1) * size);
         if (cmp > 0) break;
         memcpy ((char*)base + slot * size,  
                base + (slot - 1) * size, size);
      }
      memcpy (base + slot * size, copy, size);
   }


}
