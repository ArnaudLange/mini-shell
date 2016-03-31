#include "parametre.h"


int getlogin_r(char *buf, size_t bufsize);

char* formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}

void lectureParam(char * param, Parametres *etat)
{
	if (strcmp(param, "l")==0)
	{
		*etat=etatDetails;
	}
	else if (strcmp(param, "d")==0)
	{
		*etat=etatDossiers;
	}
	else if (strcmp(param, "c")==0)
	{
		*etat=etatColonnes;
	}
	else 
		*etat=etatNormal;
		printf("Pas de parametre valide.\n");
}

void tabulation(int nb)
{
	int i;
	for (i=0;i<nb;i++)
	{
		printf("\t");
	}
}

void testParam()
{
	char *parametre = "c";
	Parametres etat = etatNormal;

	lectureParam(parametre,&etat);
	if (etat == etatDetails)
	{
		printf("Etat -l\n");
	}
	else if (etat == etatDossiers)
	{
		printf("Etat -d\n");
	}
	else if (etat == etatColonnes)
	{
		printf("Etat -c\n");
	}
	printf("Done.\n");
}

void ls(char *input, char *param)
{
	Parametres etat = etatNormal;	//definition de l'etat
	lectureParam(param,&etat);

	DIR *repertoire;

	struct dirent *flux;
	struct stat statbuf;
	int file;
	int ligne = -1;

	if( (repertoire = opendir(input)) ==NULL)
	{
		printf("Error\n");
	}

	while((flux=readdir(repertoire)))
	{	
		//pour -l
		char * buf;
		/*
		struct stat *file_info = malloc(sizeof(struct stat));
	    if (lstat(flux->d_name, file_info) != 0) {
	            perror("Error");
	            exit(1);
	    }*/
	    //char date[36];
		
		file = openFile(flux->d_name);
		
		fstat(file,&statbuf);
		switch (etat)
		{
		case etatNormal:

			//printf("%d",statbuf.st_mode.S_IXUSR);

			if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
			{
				printf("%s%s",BLUE,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel
				printf("%s  ",NORMAL);	//puis on remet la couleur normale
			}
			else
			{	
				printf("%s  ",flux->d_name);	//sinon on ecrit normalement
			}
			break;
		
		case etatDetails:
			// MODE DU FILE
			


			printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
		    printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
		    printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
		    printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
		    printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
		    printf("\t");

		    

		    printf("%d\t",statbuf.st_nlink);
		    
		    getlogin_r(buf,statbuf.st_size);
		    printf("%s\t",buf);
		    /*
		    printf("Access: %s\n", formatdate(date, statbuf.st_atime));
    		printf("Modify: %s\n", formatdate(date, statbuf.st_mtime));
    		printf("Change: %s\n", formatdate(date, statbuf.st_ctime));
			*/
		    printf("%d\t",statbuf.st_gid);
		    printf("%d\t",statbuf.st_size);


			printf("%s\n",flux->d_name);
		    
		    
			break;

		case etatColonnes:
			ligne++;
			if (ligne >= 4)
			{
				printf("\n");
				ligne=0;
			}
			if (S_ISDIR(statbuf.st_mode))	//CHECK si c'est un dossier
			{
				int taille=0;
				taille = parcourirChaine(flux->d_name);

				printf("%s%s",BLUE,flux->d_name);		//si oui on l'ecrit en bleu pour que ce soit visuel

				printf("%s",NORMAL);	//puis on remet la couleur normale
				if(taille > 8)
				{
					tabulation(2);
				}
				else
					tabulation(3);
			}
			else
			{	
				int taille=0;
				taille = parcourirChaine(flux->d_name);

				printf("%s",flux->d_name);	//sinon on ecrit normalement
				if(taille >= 8)
				{
					tabulation(2);
				}
				else
					tabulation(3);
			}
			break;
		
		case etatDossiers:
			printf("Case -c\n.");
			break;
		}
	}
	printf("\n"); //saut de ligne
	closedir(repertoire);	//on ferme le dossier
}

int main(int argc, char *argv[])
{
	char *param = "l";
	int i;
	if (argc >1)
		for (i=1;i<argc;i++)
		{
			ls(argv[i],param);
		}	
	else	//si il n'y a pas d'arguments on lance ls dans le fichier courant
	{
		ls("./",param);
	}
	return 0;
}