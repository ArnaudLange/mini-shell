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

//** à décommenter et à completer une fois la fonction finies **//
//#include "../../include/commands/fonction.h"

#include "../../include/commands/chmod.h" //à virer une fois les tests effectués


int chmod_lib(int argc, char *argv[]){


    // -----------------------------------
    int i, c;
    int option=0;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {

        //Boucle pour parcourir les options, exemple avec les options verbose et help
        while (1) {
        int option_index = 0;

        //structure donnant les options gérées par la commande
            //si l'option peut prendre un argument (ex : --port:8080) à la place de no_argument on mettra required_argument
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"verbose",  no_argument,       0, 'v'},
            {"example",  no_argument,       0, 'e'}
        };

        //dans le getopt_long, changer le troisième argument et rajouter les options attendues, ici "hv"
            //si l'option peut prendre un argument on mettra ":" après la lettre (ex: "hvp:")
        c = getopt_long(argc, argv, "hve", long_options, &option_index);

        if (c == -1) break;

        //switch en fonction des options rentrées par l'user
        switch (c) {

         case 'h': 
           printf("\n-----------------------------------------------------------\n");
           printf("Usage: chmod [OPTION]... MODE[,MODE]... FILE...\n");
           printf("Change the mode of each FILE to MODE.\n\n");
           printf("    -v, --verbose        output a diagnostic for every file processed\n");
           printf("    -e, --example        shows an example\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

         case 'v':
           option=1;
           break;

         case 'e':
           printf("\n-----------------------------------------------------------\n");
           printf("chmod: example\n");
           printf("\tchmod [OPTION]... MODE[,MODE]... FILE...\n");
           printf("\tchmod -v u+x,g-r file1 file2\n");
           printf("\nHere, the option 'verbose' is activated\n");
           printf("chmod will add the right to execute for the user, and remove\n");
           printf("for the group, the right to read.\n");
           printf("And this, on both files : file1 and file2.\n");
           printf("\nYou can also do :\n");
           printf("chmod 777 file1\n");
           printf("If you know directly the octal modes\n");
           printf("\n-----------------------------------------------------------\n\n");
           exit(0);
           break;

        //message par défaut quand l'option rentrée n'est pas gérée par la commande
        default:
            printf("chmod : invalid option.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
        }
    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        printf("chmod : invalid number of arguments.\n");
        printf("Try 'chmod --help' for more information.\n");
        exit(1);
    }

    if (argc>2 && option != 1){
        for (i=2; i<argc && *argv[i]!='-'; i++){
            myChmod(0, argv[1], argv[i]);
        }
    }
    else if (argc > 3 && option){
        int iOption=0;
        int k;
        for (i=1; i<argc; i++){
            if (*argv[i] == '-'){
                iOption=i+1;
            }
        }
        if (argc-2<iOption){
            printf("chmod : invalid number of arguments.\n");
            printf("Try 'chmod --help' for more information.\n");
            exit(1);
        }
        else{
            for(k = iOption+1; k<argc; k++){
                myChmod(option,argv[iOption],argv[k]);
            }
        }
    }
    else{
        printf("chmod : invalid number of arguments.\n");
        printf("Try 'chmod --help' for more information.\n");
        exit(1);
    }

    return 0;
}

char* lectureMode(char* mode){

    char* tabMode=calloc(9,sizeof(char));

    int n;

    for(n=0;n<9;n++){
        tabMode[n]=' ';
    }

    int u[3]={0,1,2};
    int g[3]={3,4,5};
    int o[3]={6,7,8};

    int taille = strlen(mode);

    char which=' ';
    char etat=' ';
    int h;

    typedef enum{
        etatDebut,
        etatOpe,
        etatFin,
        etatVirgule
    } Etat;

    Etat curEtat = etatDebut;

    for(h=0;h<taille;h++){

        switch (curEtat){
            case etatDebut:
                if(mode[h]=='o' || mode[h]=='g' || mode[h]=='u'){
                    which=mode[h];
                    curEtat=etatOpe;
                    break;
                }
                else{
                    printf("chmod: invalid mode: '%c'\n",mode[h]);
                    printf("Try 'chmod --help' for more information.\n");
                    exit(0);
                }
            case etatOpe:
                if(mode[h]=='=' || mode[h]=='+' || mode[h]=='-'){
                    etat=mode[h];
                    curEtat=etatFin;
                    break;
                }
                else{
                    printf("chmod: invalid mode: '%c'\n",mode[h]);
                    printf("Try 'chmod --help' for more information.\n");
                    exit(0);
                }
            case etatFin:
                if(mode[h]=='x'){
                    if(which == 'u'){
                        tabMode[u[2]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'g'){
                        tabMode[g[2]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'o'){
                        tabMode[o[2]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else{
                        printf("Error while parsing.\n");
                        exit(1);
                    }
                }
                else if(mode[h]=='w'){
                    if(which == 'u'){
                        tabMode[u[1]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'g'){
                        tabMode[g[1]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'o'){
                        tabMode[o[1]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else{
                        printf("Error while parsing.\n");
                        exit(1);
                    }
                }
                else if(mode[h]=='r'){
                    if(which == 'u'){
                        tabMode[u[0]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'g'){
                        tabMode[g[0]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else if(which == 'o'){
                        tabMode[o[0]]=etat;
                        curEtat=etatVirgule;
                        break;
                    }
                    else{
                        printf("Error while parsing.\n");
                        exit(1);
                    }
                }
                else{
                    printf("chmod: invalid mode: '%c'\n",mode[h]);
                    printf("Try 'chmod --help' for more information.\n");
                    exit(0);
                }
            case etatVirgule:
                if (mode[h]==','){
                    which=' ';
                    etat=' ';
                    curEtat=etatDebut;
                    break;
                }
                else{
                    curEtat=etatFin;
                    h=h-1;
                }
        }
    }
    return (char*)tabMode;
}

void myChmod(int option, char* mode, char* file){

    int sf;
    struct stat statbuf;
    char modeAvant[9];
    char modeApres[9];
    char *modeApr=NULL;

    modeApr=calloc(9,sizeof(char));
    if(modeApr==NULL){
        perror("modeApr");
        exit(1);
    }

    //initialisation des tableaux
    int w;

    for (w=0; w<9; w++){
        modeAvant[w]='-';
        modeApres[w]='-';
    }
    modeAvant[9]='\0';
    modeApres[9]='\0';

    // Prise des donnees avant changement
    sf = openFile(file);
    if(sf == -1){
        perror(file);
        exit(1);
    }
    
    if (fstat(sf,&statbuf)==-1){
        perror("fstat");
        exit(1);
    }

    if (atoi(mode)==0){
        modeApr = lectureMode(mode);
    }

    //Recuperation du mode
    //Tout d'abord le mode User
    int valUsr=0;
    int valUsrApr=0;
    //on voit si il a le droit 'Read'
    if (statbuf.st_mode & S_IRUSR){
        valUsr+=4;
        modeAvant[0]='r';

        //On regarde aussi si le mode etait en String si il n'y a pas le droit '-'
        if(modeApr[0]!='-'){
            valUsrApr+=4;
            modeApres[0]='r';
        }
    }
    //ou encore le droit +
    else if (modeApr[0]=='+'){
        valUsrApr+=4;
        modeApres[0]='r';
    }

    //On fait de meme pour les autres droits
    if (statbuf.st_mode & S_IWUSR){
        valUsr+=2;
        modeAvant[1]='w';

        if(modeApr[1]!='-'){
            valUsrApr+=2;
            modeApres[1]='w';
        }
    }
    else if (modeApr[1]=='+'){
        valUsrApr+=2;
        modeApres[1]='w';
    }

    if (statbuf.st_mode & S_IXUSR){
        valUsr+=1;
        modeAvant[2]='x';

        if(modeApr[2]!='-'){
            valUsrApr+=1;
            modeApres[2]='x';
        }
    }
    else if (modeApr[2]=='+'){
        valUsrApr+=1;
        modeApres[2]='x';
    }

    //Ensuite on repete le meme pattern pour les autres users : Group et Other
    int valGrp=0;
    int valGrpApr=0;
    if (statbuf.st_mode & S_IRGRP){
        valGrp+=4;
        modeAvant[3]='r';

        if(modeApr[3]!='-'){
            valGrpApr+=4;
            modeApres[3]='r';
        }
    }
    else if (modeApr[3]=='+'){
        valGrpApr+=4;
        modeApres[3]='r';
    }

    if (statbuf.st_mode & S_IWGRP){
        valGrp+=2;
        modeAvant[4]='w';

        if(modeApr[4]!='-'){
            valGrpApr+=2;
            modeApres[4]='w';
        }
    }
    else if (modeApr[4]=='+'){
        valGrpApr+=2;
        modeApres[4]='w';
    }

    if (statbuf.st_mode & S_IXGRP){
        valGrp+=1;
        modeAvant[5]='x';

        if(modeApr[5]!='-'){
            valGrpApr+=1;
            modeApres[5]='x';
        }
    }
    else if (modeApr[5]=='+'){
        valGrpApr+=1;
        modeApres[5]='x';
    }

    //Et enfin, other
    int valOth=0;
    int valOthApr=0;
    if (statbuf.st_mode & S_IROTH){
        valOth+=4;
        modeAvant[6]='r';

        if(modeApr[6]!='-'){
            valOthApr+=4;
            modeApres[6]='r';
        }
    }
    else if (modeApr[6]=='+'){
        valOthApr+=4;
        modeApres[6]='r';
    }

    if (statbuf.st_mode & S_IWOTH){
        valOth+=2;
        modeAvant[7]='w';

        if(modeApr[7]!='-'){
            valOthApr+=2;
            modeApres[7]='w';
        }
    }
    else if (modeApr[7]=='+'){
        valOthApr+=2;
        modeApres[7]='w';
    }
    if (statbuf.st_mode & S_IXOTH){
        valOth+=1;
        modeAvant[8]='x';

        if(modeApr[8]!='-'){
            valOthApr+=1;
            modeApres[8]='x';
        }
    }
    else if (modeApr[8]=='+'){
        valOthApr+=1;
        modeApres[8]='x';
    }

    int intMAvant=0;
    intMAvant=100*valUsr+10*valGrp+valOth;

    //On check si il y a des egales
    int e;
    int first=1;
    int modes[9]={'r','w','x','r','w','x','r','w','x'};
    int modesChiffre[9]={4,2,1,4,2,1,4,2,1};
    for(e=0;e<3;e++){
        if(modeApr[e]=='=' && first){
            modeApres[0]='-';
            modeApres[1]='-';
            modeApres[2]='-';
            modeApres[e]=modes[e];
            valUsrApr=modesChiffre[e];
            first=0;
        }
        else if(modeApr[e]=='='){
            modeApres[e]=modes[e];
            valUsrApr+=modesChiffre[e];
        }
    }
    first=1;
    for(e=3;e<6;e++){
        if(modeApr[e]=='=' && first){
            modeApres[3]='-';
            modeApres[4]='-';
            modeApres[5]='-';
            modeApres[e]=modes[e];
            valGrpApr=modesChiffre[e];
            first=0;
        }
        else if(modeApr[e]=='='){
            modeApres[e]=modes[e];
            valGrpApr+=modesChiffre[e];
        }
    }
    first=1;
    for(e=6;e<9;e++){
        if(modeApr[e]=='=' && first){
            modeApres[6]='-';
            modeApres[7]='-';
            modeApres[8]='-';
            modeApres[e]=modes[e];
            valOthApr=modesChiffre[e];
            first=0;
        }
        else if(modeApr[e]=='='){
            modeApres[e]=modes[e];
            valOthApr+=modesChiffre[e];
        }
    }

    int intMApres=0;
    intMApres=100*valUsrApr+10*valGrpApr+valOthApr;

    char str[4];
    sprintf(str, "%d", intMApres);


    mode_t modeConv=strtol(mode,NULL,8);
    mode_t modeConvString=strtol(str,NULL,8);

    if (atoi(mode)==0){
        if(intMAvant==intMApres){
            if (option){
                printf("mode of '%s' retained as %d (%s)\n",file, intMAvant,modeAvant);
            }
        }
        else{
            chmod(file,modeConvString);
            if (option){
                printf("mode of '%s' changed from %d to %o (%s)\n",file,intMAvant,modeConvString,modeApres);
            }
        }
        
    }
    else{
        if(intMAvant == atoi(mode)){
            if (option){
                printf("mode of '%s' retained as %d (%s)\n",file, intMAvant,modeAvant);
            }
        }
        else{
            chmod(file,modeConv);
            if (option){
                printf("mode of '%s' changed from %d to %o\n",file,intMAvant,modeConv);
            }
        }
    }

}
