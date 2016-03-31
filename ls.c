#include "parametre.h"

void readOptions(char *options, Parametres *etat)
{
	if (strcmp(options, "l")==0)
	{
		*etat=etatDetails;
	}
	else if (strcmp(options, "d")==0)
	{
		*etat=etatDossiers;
	}
	else 
		*etat=etatNormal;
}

void ls(char *directory, char *options)
{
	Parametres etat;
	readOptions(options, &etat);

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
		perror("Error\n");
		exit(-1);
	}

	while ((flux = readdir(repertoire)))
	{
		file = openFile(flux->d_name);
		if (file == -1)
		{
			perror("Error\n");
			exit(-1);
		}

		if (fstat(file,&statbuf) == -1)
		{
			perror("Error");
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
					printf("%s  ",flux->d_name);
				}
				break;
		}



	}
	//SAUT DE LIGNE A LA FIN
	printf("\n");

}

int main(int argc, char *argv[])
{
	char *optionTest = "";

	if (argc >1)
	{
		if (argc > 2)
		{
			ls(argv[2], argv[1]);
		}
		else{
			ls("./",argv[1]);
		}
	}
	//SI pas d'arguments => on execute dans le dossier courant
	else
	{
		ls("./",optionTest);
	}
	return 0;
}