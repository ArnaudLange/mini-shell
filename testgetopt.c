#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int c;
    char* options = (char*) calloc(15, sizeof(*options));
    int nbOptions = 0;

   while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'}
        };

       c = getopt_long(argc, argv, "hv", long_options, &option_index);

        if (c == -1)
            break;

       switch (c) {

         case 'h':
           printf("Usage: mv [OPTION]... SOURCE DEST\n");
           printf("Rename SOURCE to DEST\n");
           printf("-v, --verbose : explain what is being done\n");
           exit(0);
           break;

         case 'v':
           options[nbOptions] = c; 
           nbOptions++;
           break;

       default:
            printf("Try 'mv --help' for more information.\n");
            exit(1);
      }
      free(options);
    }

   return 0;
}