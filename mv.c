#include "mv.h"


int main(int argc, char *argv[])
{
    // -----------------------------------
    // Declaration tableau deux dimensions pour les options

    char* options = NULL;
    options = (char*) malloc(15*sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char** files = NULL;
    files = malloc(sizeof(char**));
    if (files == NULL)
    {
        perror("files");
        exit(1);
    }
    files[0] = malloc(sizeof(char*));
    if (files[0] == NULL)
    {
        perror("files[x]");
        exit(1);
    }

    // -----------------------------------

    int nbOptions = 0;
    int nbFiles = 0;
    int i, c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {
        while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'}
        };

       c = getopt_long(argc, argv, "hv", long_options, &option_index);

        if (c == -1) break;

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
    }

        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files[nbFiles] = malloc(16*sizeof(char*));

                concatenateTables(files[nbFiles],argv[i]);


            }
        }
        // if there are 2 files
        if (nbFiles == 2)
        {
            myMv(files[1],files[2], options, nbOptions);   
        }
        else
        {
            printf("mv : invalid number of arguments\n");
            printf("Try 'mv --help' for more information.\n");
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("mv : invalid number of arguments\n");
    }

    return 0;
}

void myMv(char* arg1, char* arg2, char* options, int iOptions)
{    
    // ----------------------------------
    // Lecture des options
    // ----------------------------------
    if(strcmp(options, "v") == 0){
        printf("Renaming %s to %s\n", arg1, arg2);
    }
    // ----------------------------------
    // Initialisation
    // ----------------------------------
    struct stat statbuf;

    if (stat(arg1, &statbuf) == -1) { //si il n'existe aucun fichier déjà nommé comme celui qu'on essaye de déplacer
        printf("mv : '%s' invalid path\n", arg1);
    }
    else if(stat(arg2, &statbuf) != -1) { //si le fichier dest existe déjà
        printf("mv : '%s' already exists\n", arg2);
    }
    else{
        rename(arg1, arg2);
    }
    
}

void concatenateTables(char *tab1, const char *tab2)
{
    /**
     * Gets the size of each table
     *
     */
    int taille1=0, taille2=0;

    while(tab1[taille1] != '\0')
    {
        taille1++;
    }

    while(tab2[taille2] != '\0')
    {
        taille2++;
    }

    /**
     * Resets the memory of the table 
     * Sets it to the addition of both tables' size
     */
    tab1 = realloc(tab1, (taille1 + taille2)*sizeof(char));

    int i = taille1;
    int j = 0;


    while(tab2[j] != '\0')
    {
        tab1[i] = tab2[j];
        i++;
        j++;
    }
}

