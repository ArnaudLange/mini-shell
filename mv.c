#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void myMv(char const *arg1, char const *arg2);

int main(int argc, char const *argv[])
{
    if(argc == 3){
        myMv(argv[1], argv[2]);
    }
    else{
        printf("Erreur : nombre d'arguments incorrect !\n");
    }
    return 0;
}
void myMv(char const *arg1, char const *arg2)
{
    struct stat statbuf;

    if (stat(arg1, &statbuf) == -1) { //si il n'existe aucun fichier déjà nommé comme celui qu'on essaye de créer 
        printf("Erreur : le chemin vers '%s' est introuvable !\n", arg1);
    }
    else{
        rename(arg1, arg2);
    }
    
}
