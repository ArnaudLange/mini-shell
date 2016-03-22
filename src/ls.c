#include "../include/commands.h"

int ls_lib(int argc, char* argv[]){
      DIR* dirp;
      struct dirent *dir_ptr;
      if((dirp=opendir(argv[0]))==NULL){
            printf("error");
            return -1;
      }
      while(dir_ptr=readdir(dirp)){
            printf("%s\n", dir_ptr->d_name);
      }
      closedir(dirp);
      return 1;
}