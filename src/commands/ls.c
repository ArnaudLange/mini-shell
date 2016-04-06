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
    
#include "../../include/commands/ls.h"

int ls_lib(int argc, char *argv[]){

	// -----------------------------------
    // Declaration tableau deux dimensions pour les options

    char* options = NULL;
    options = (char*) calloc(2,sizeof(*options));
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
    /*
    files[0] = malloc(sizeof(char*));
    if (files[0] == NULL)
    {
        perror("files[x]");
        exit(1);
    }
	*/
    // -----------------------------------

    int nbFiles = 0;
    int i, c;

    // -----------------------------------
    // parcourt des arguments de la fonction

    if (argc >1) {
        while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help",     no_argument,       0, 'h'},
            {"l",  no_argument,       0, 'l'},
            {"directory",  no_argument,       0, 'd'}
        };

       c = getopt_long(argc, argv, "hld", long_options, &option_index);

        if (c == -1) break;

       switch (c) {

         case 'h':

           	printf("Usage: ls [OPTION]... [FILE]...\n");
			printf("List information about the FILEs (the current directory by default).\n");
			printf("\n  -l\t\tuse a long listing format\n");
			printf("\n  -d, --directory\t\tlist directory entries instead of content.\n");
           	exit(0);
           	break;

         case 'l':
           options[0]=1; 
           break;

         case 'd':
           options[1]=1; 
           break;

       default:
            printf("Try 'ls --help' for more information.\n");
            exit(1);
      }
    }

        for (i=1; i<argc; i++)
        {
            if(argv[i][0] != '-')
            {
            	files[nbFiles]=argv[i];
                nbFiles++;
                files = realloc(files, (nbFiles +1)*sizeof(char*));
            }
        }
        // if there are 2 files
        if (nbFiles == 0)
        {
            ls("./",options);
        }
        else
        {
            int k;
            for(k=0; k<nbFiles ; k++)
            {
            	printf("%s\n",files[nbFiles]);
            	ls(files[nbFiles],options);
            }
        }
        free(files);
        free(options);


    }
    //SI pas d'arguments => on affiche une erreur
    else
    {
        ls("./","");
    }

    return 0;
	/*
        char *optionTest = "";

        char *options = NULL;
        options = malloc(sizeof(char));
        if (options == NULL)
        {
                perror("options");
                exit(-1);
        }

        int iOptions = -1;
        int iParam = -1;
        int i;

        if (argc >0)
        {
                for (i=0; i<argc; i++)
                {
                        if(argv[i][0] == '-')
                        {
                                iOptions = i;
                                printf("test");
                                concatenateTables(options,argv[i]);
                        }
                        else {
                                iParam = i;
                        }
                }

                if (iOptions == -1)
                {
                        if (iParam == -1)
                        {
                                ls("./","");
                        }
                        else
                        {
                                ls(argv[iParam],"");
                        }
                }
                else {
                        if (iParam == -1)
                        {
                                ls("./",options);
                        }
                        else
                        {
                                ls(argv[iParam],options);
                        }
                }
        }
        //SI pas d'arguments => on execute dans le dossier courant
        else
        {
                ls("./",optionTest);
        }
        return 0;

    */
}

void ls(char *directory, char *options)
{
	Options etat;
	readLsOptions(options, &etat);

	DIR *repertoire;

	struct dirent *flux;
	struct stat statbuf;
	int file;

	//POUR etatColonne
	//int ligne = -1;
	
	//POUR etatDetails
	struct passwd *userInfo;
	struct group *groupInfo;
	struct tm *timeInfo;


	if ((repertoire = opendir(directory)) == NULL)
	{
		perror(directory);
		exit(-1);
	}

	while ((flux = readdir(repertoire)))
	{
		file = openFile(flux->d_name);
		if (file == -1)
		{
			perror(flux->d_name);
			exit(-1);
		}

		if (fstat(file,&statbuf) == -1)
		{
			perror("stat");
			exit(-1);
		}

		//-----------------SWITCH AVEC LES DIFFERENTES OPTIONS-----------------//

		switch (etat)
		{

			case etatNormal:

				//SI DOSSIER = COULEUR BLEUE
				if (S_ISDIR(statbuf.st_mode))
				{
					//SET bleue puis PRINTF le nom puis SET couleur normale
					printf("%s%s%s  ",BLUE,flux->d_name,NORMAL);
				}
				else
				{	
					printf("%s  ",flux->d_name);
				}
				break;

			case etatDetails:

				// AFFICHAGE MODE
				if ((statbuf.st_mode & S_IFSOCK)==S_IFSOCK) printf("s");
				else if ((statbuf.st_mode & S_IFLNK)==S_IFLNK) printf("l");
				else if ((statbuf.st_mode & S_IFREG)==S_IFREG) printf("-");
				else if ((statbuf.st_mode & S_IFBLK)==S_IFBLK) printf("b");
				else if ((statbuf.st_mode & S_IFDIR)==S_IFDIR) printf("d");
				else if ((statbuf.st_mode & S_IFCHR)==S_IFCHR) printf("c");	
				else if ((statbuf.st_mode & S_IFIFO)==S_IFIFO) printf("p");	
			    printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
			    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
			    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
			    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
			    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
			    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
			    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
			    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
			    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");

			    printf(" %d\t",(int)statbuf.st_nlink);

				userInfo=getpwuid(statbuf.st_uid);
				printf("%s",userInfo->pw_name);

				groupInfo=getgrgid(statbuf.st_gid);
				printf(" %s",groupInfo->gr_name);

				printf(" %8d",(int)statbuf.st_size);

				timeInfo=localtime(&statbuf.st_mtime);
				printf(" %4d-%02d-%02d %02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min);

				if ((statbuf.st_mode & S_IFDIR)==S_IFDIR)
				{
					printf(" %s%s%s\n",BLUE,flux->d_name,NORMAL);
				}
				else if ((statbuf.st_mode & S_IXUSR))
				{
					printf(" %s%s%s\n",GREEN,flux->d_name,NORMAL);
				}
				else {
					printf(" %s\n",flux->d_name);
				}
				

				break;

			case etatDossiers:

				if (S_ISDIR(statbuf.st_mode))
				{
					//SET bleue puis PRINTF le nom puis SET couleur normale
					printf("%s%s%s  ",BLUE,flux->d_name,NORMAL);
				}
				break;

			case etatDetailsDossiers:

				if (S_ISDIR(statbuf.st_mode))
				{
					printf("d");
					printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
				    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
				    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
				    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
				    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
				    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
				    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
				    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
				    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");

				    printf(" %d\t",(int)statbuf.st_nlink);

					userInfo=getpwuid(statbuf.st_uid);
					printf("%s",userInfo->pw_name);

					groupInfo=getgrgid(statbuf.st_gid);
					printf(" %s",groupInfo->gr_name);

					printf(" %8d",(int)statbuf.st_size);

					timeInfo=localtime(&statbuf.st_mtime);
					printf(" %4d-%02d-%02d %02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min);


					printf(" %s%s%s\n",BLUE,flux->d_name,NORMAL);

					break;

			}
		}



	}
	//SAUT DE LIGNE A LA FIN
	printf("\n");

}

void readLsOptions(char *options, Options *etat)
{
        /**
         * Compares options and different types of options handled
         * And updates etat accordingly
         */
        if (strcmp(options, "-l")==0)
        {
                *etat=etatDetails;
        }
        else if (strcmp(options, "-d")==0)
        {
                *etat=etatDossiers;
        }
        else if (strcmp(options, "")==0)
        {
                *etat=etatNormal;
        }
        else if ((strcmp(options, "-dl")==0) || (strcmp(options, "-ld")==0) || (strcmp(options, "-d-l")==0) || (strcmp(options, "-l-d")==0))
        {
                *etat=etatDetailsDossiers;
        }
        else
        {
                /**
                 * Error if the options isn't handled
                 * Precise which options were at fault
                 * And quits the program
                 */
                printf("ls: invalid option -- \"%s\"\n",options);
                printf("Get more information on the README.md document.");
                exit(-1);
        }

}