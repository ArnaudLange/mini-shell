#include "mv.h"


int main(int argc, char const *argv[])
{
    // -----------------------------------
    // Declaration tableau deux dimensions pour les options

    char **options = NULL;
    options = (char**) malloc(sizeof(*options));
    if (options == NULL)
    {
        perror("options");
        exit(1);
    }
    options[0] = malloc(sizeof(char));
    if (options[0] == NULL)
    {
        perror("options[x]");
        exit(1);
    }
    options[0]="";


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char **files = NULL;
    files = malloc(sizeof(char*));
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

    int iOptions = 0;
    int iFiles = 0;
    int i;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1)
    {
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] == '-')
            {
                iOptions++;
                options[iOptions] = malloc(sizeof(char*));
                concatenateTables(options[iOptions],argv[i]);
                printf("ceci est un tasty test : %s\n", options[i]);


            }
            else {
                iFiles++;
                files[iFiles] = malloc(sizeof(char*));

                concatenateTables(files[iFiles],argv[i]);
            }
        }
        // if there are 2 files
        if (iFiles == 2 || iOptions > 0)
        {
            myMv(files[0],files[1], options, iOptions);   
        }
        else
        {
            printf("mv : invalid number of arguments\n");
        }
        printf("test2 %d\n", iOptions);
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

void myMv(char* arg1, char* arg2, char**options, int iOptions)
{    
    // ----------------------------------
    // Lecture des options
    // ----------------------------------
    int h;
    for (h = 0; h <= iOptions; h++)
    {
        readOptions(options[h]);
    }
    // ----------------------------------
    // Initialisation
    // ----------------------------------
    struct stat statbuf;

    if (stat(arg1, &statbuf) == -1) { //si il n'existe aucun fichier déjà nommé comme celui qu'on essaye de déplacer
        printf("mv : '%s' invalid path\n", arg1);
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

void readOptions(char *options)
{
    /**
     * Compares options and different types of options handled
     * And updates etat accordingly
     */

    if (strcmp(options, "--help")==0){

        printf("Usage: mv SOURCE... DEST...\n");
        printf("Rename SOURCE to DEST\n");
        exit(0);
    }

    else{
        /**
         * Error if the options isn't handled
         * Precise which options were at fault
         * And quits the program
         */
        printf("mv: invalid option %s\n", options);
        printf("Try 'mv --help' for more information.\n");
        exit(1);
    }

}


