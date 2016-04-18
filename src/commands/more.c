/*
    This file is part of Binsh.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Binsh.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../../include/commands/more.h"

int more_lib(int argc, char *argv[]){


    // -----------------------------------
    // Declaration tableau deux dimensions pour les files

    char** files = NULL;
    files = calloc(1,sizeof(char*));
    if (files == NULL)
    {
        perror("files");
        exit(1);
    }
    files[0] = calloc(1,sizeof(char));
    if (files[0] == NULL)
    {
        perror("files[x]");
        exit(1);
    }

    // -----------------------------------

    int nbLigne = 1;
    int nbFiles = 0;
    int i, c, j;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "h", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: more [OPTION] FILE... \n\n");
           printf("press 'h' while the function is running to see the\n");
           printf("'in-function' options.\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("Try 'more --help' for more information.\n");
            exit(1);
      }
    }
        //Boucle pour parcourir les arguments qui ne sont pas des options
        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
                nbFiles++;
                files=realloc(files, (nbFiles+1)*sizeof(char*));
                if(files == NULL){
                    perror("files");
                    exit(1);
                }
                files[nbFiles] = calloc(1,sizeof(char));
                if (files[nbFiles] == NULL)
                {
                    perror("files[x]");
                    exit(1);
                }
                files[nbFiles-1]=concatenateTables(files[nbFiles-1], argv[i]);
            }
        }
        // if there are 2 files
        if (nbFiles >0)
        {
            for(j = 0; j < nbFiles; j++)
            {
                more(files[j], &nbLigne);
                free(files[j]);
            }   
        }
        else
        {
            more("",&nbLigne);
        }
        free(files);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("more : invalid number of parameters\n");
        printf("Try 'more --help' for more information.\n");
        exit(1);
    }

    return 0;
}

//Fonction qui etablit l'etat actuel
//On prend l'etat en entree, le char lu par la fonction a ce moment
//Ainsi que la taille du fichier et la ligne ou nous sommes rendus
void getEtat(Etat *curEtat, char c, int taille, int nbLigne){
   //On calcule le pourcentage de parcourt du fichier
   double pourcentage = (double)nbLigne/taille*100;
   //L'affichage pour que l'on rentre notre commande, avec les pourcentage
   printf("--More-- (%d%c)",(int)pourcentage,37);
   //On recupere l'entree de l'utilisateur
   char command=getchar();
   //On supprime la ligne du dessus pour que ca n'influe pas sur l'affichage du more
   printf("\033[A\33[2K");
   while('\n'!=getchar());

   //Si c'est un h, on affiche l'aide
    if (command == 'h'){
        printf("----------------------------------------\n");
        printf("<space> \t\t\tDisplay next k lines of text [current screen size]\n");
        printf("<return>\t\t\tDisplay next 1 line of text\n");
        printf("q or Q  \t\t\tExit from more\n");
        printf("s       \t\t\tSkip forward 1 line of text\n");
        printf("f       \t\t\tSkip forward k screenfuls of text\n");
        printf("=       \t\t\tDisplay current line number\n");
        printf("----------------------------------------\n");
        //Puis on reprend l'entree clavier
        command=getchar();
        //Et on efface l'aide
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
        printf("\033[A\33[2K");
    }

    //Si on a "Entree"
    //On efface la ligne du dessus, si le caractere en parametre n'est pas entree, on l'affiche (car sinon cela fera un saut de ligne intempestif)
    if (command == 10){
        printf("\033[A\33[2K");
        if (c!=10){
            printf("%c",c);
        }
        //On met l'etat sur etat entree
        *curEtat = etatEntree;
    }
    //Si on a "espace"
    else if (command == ' '){
        //Meme chose pour l'affichage du parametre en entree
        if(c!=10){
            printf("%c",c);
        }
        //On met l'etat a etat espace
        *curEtat = etatSpace;
    }
    //Pour les autres cas on change juste l'etat
    else if (command == 'q' || command == 'Q'){
        *curEtat = etatExit;
    }
    else if (command == 's'){
        *curEtat = etatSkipLignes;
    }
    else if (command == 'f'){
        *curEtat = etatSkipScreenLignes;
    }
    else if (command == '='){
        *curEtat = etatLigneNumber;
    }
}

//Fonction qui renvoie le nombre de ligne total d'un fichier
int getLength(char *file){
    int length=0;
    char c;

    //On va ouvrir le fichier et le parcourir normalement
    FILE *fichier = NULL;
    fichier = fopen(file,"r");
    if(fichier == NULL){
        perror(file);
        exit(1);
    }
    while((c=fgetc(fichier)) != EOF){
        if(c == 10){
            //En incrementatant la variable "length" a chaque ligne
            length++;
        }
    }
    fclose(fichier);
    return length;
}

void more(char *file, int *nbLigne){
    FILE *fichier = NULL;
    char character;

    int i=1;

    //On recupere la taille de la fenetre via ces commandes
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    //Cela permettra de gerer les commandes "espace" ainsi que "f"
    int ligneScreen = w.ws_row;
    int lengthFile;

    //puis on ouvre le fichier normalement
    if(strcmp(file,"")){
        fichier = fopen(file,"r");
        if(fichier == NULL){
            perror(file);
            exit(1);
        }
        lengthFile=getLength(file);
        Etat curEtat;
        //De base more effectue l'etat "space" au lancement
        curEtat=etatSpace;

        while((character=fgetc(fichier)) != EOF){

            switch (curEtat){
                case etatSpace:
                    //Pour faire l'etat space on affiche le fichier caractere par caractere,
                    //jusqu'a atteindre le nombre de ligne correspondant a la taille de la fenetre
                    if (i<ligneScreen){
                        printf("%c",character);

                        if (character == 10){
                            i++;
                            (*nbLigne)++;
                        }
                        break;
                    }
                    else{
                        //Si c'est le cas on appelle la fonction qui va reinitialiser l'etat avec l'entree de l'utilisateur
                        getEtat(&curEtat,character,lengthFile,*nbLigne);
                        //Sans oublier de remettre i a 1
                        i=1;
                        break;
                    }

                case etatEntree:
                    //On affiche une ligne de caracteres, donc jusqu'au caractere 10
                    if (character == 10){
                            printf("%c",character);
                            (*nbLigne)++;
                            getEtat(&curEtat,10,lengthFile,*nbLigne);
                            break;
                        }
                    else{
                        printf("%c",character);
                    }
                    break;

                case etatExit:
                    //on quitte le programme
                    exit(0);

                case etatSkipLignes:
                    //On fait comme etatEntree mais sans afficher
                    if (character == 10){
                            (*nbLigne)++;
                            printf("\n...skipping one line\n");
                            getEtat(&curEtat,10,lengthFile,*nbLigne);
                            break;
                        }
                    break;

                case etatSkipScreenLignes:
                    //On fait comment etatSpace mais sans afficher
                    if (i<ligneScreen){
                        if (character == 10){
                            i++;
                            (*nbLigne)++;
                        }
                        break;
                    }
                    else{
                        printf("\n...skipping %d line\n",ligneScreen);
                        getEtat(&curEtat,character,lengthFile,*nbLigne);
                        i=1;
                        break;
                    }
                    break;

                case etatLigneNumber:
                    //On affiche le numero de la ligne ou nous sommes rendus
                    printf("Ligne n° : %d | ",*nbLigne);
                    getEtat(&curEtat,character,lengthFile,*nbLigne);
                    break;


            }
        }
        fclose(fichier);
    }
    else{
        printf("\n-----------------------------------------------------------\n");
        printf("Usage: more [OPTION] FILE... \n\n");
        printf("press 'h' while the function is running to see the\n");
        printf("'in-function' options.\n");
        printf("\n-----------------------------------------------------------\n\n");
    }
}