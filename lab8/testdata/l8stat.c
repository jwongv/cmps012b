//$Id: 
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int Exit_Status = EXIT_SUCCESS;
char *Exec_Name;

int main (int argc, char **argv){
   Exec_Name = basename (argv[0]);
   char cwd[1024];
   int i;
   if (argc == 1)
      getcwd(cwd, sizeof(cwd));
   else
      i = 1;
   for (; i < argc ; ++i){
      char buffer[1024];
      char readlink[1024];
      struct stat buf;
      struct tm *tmp;

      if (argc == 1){
         lstat(cwd, &buf);
         time_t t = buf.st_mtime;
         tmp = localtime(&t);
         off_t size = buf.st_size;
         mode_t mode = buf.st_mode;
         if ((time(NULL)-buf.st_mtime)/86400 < 180)
            strftime (buffer, sizeof(buffer), "%b %e %R", tmp);
         else
            strftime (buffer, sizeof(buffer), "%b %e  %Y", tmp);
      printf ("%lo   %d  %s  %s  \n", mode, size, buffer, cwd);
      break;

      }

      if (realink(argv[i], readlink, sizeof (readlink)) != -1){
         printf ("%s\n", readlink);
         continue;
      }


      FILE *file = fopen (argv[i], "r");
      if (file == NULL){
         fflush (NULL);
         fprintf (stderr, "%s: %s: %s\n",
                  Exec_Name, argv[i], strerror (errno));
         fflush (NULL);
         Exit_Status = EXIT_FAILURE;
         continue;
      }

      lstat(argv[i], &buf);
      time_t t = buf.st_mtime;
      tmp = localtime(&t);
      off_t size = buf.st_size;
      mode_t mode = buf.st_mode;
      if ((time(NULL)-buf.st_mtime)/86400 < 180)
         strftime (buffer, sizeof(buffer), "%b %e %R", tmp);
      else
         strftime (buffer, sizeof(buffer), "%b %e  %Y", tmp);
      printf ("%lo   %d  %s  %s  \n", mode, size, buffer, argv[i]);
   
   }
   return Exit_Status;
}
