#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

int
main(int argc, char **argv)
{
    int c;
    char* options = (char*) malloc(sizeof(*options));
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
           printf("Usage: mv [OPTIONS] SOURCE... DEST...\n");
           printf("Rename SOURCE to DEST\n");
           exit(0);
           break;

         case 'v':
           nbOptions++;
           break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

   if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
   printf("%d\n", nbOptions);
   exit(EXIT_SUCCESS);
}