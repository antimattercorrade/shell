#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing ls
//////////////////////////////////////////

int myls(char** parsed_inp)
{
  DIR* direc;                                       //Pointer to directory
  struct dirent* file;                              //Structure storing attributes of each file in directory
  char* directory;                                  //Variable storing path where directory is to be opened
  int flag = 0;

  if(parsed_inp[1] == NULL)                         //If directory is not given
  {
    char arg[INT_MAX];
    if(getcwd(arg,sizeof(arg)) == NULL)             //Get current working directory using "getcwd"
    {
      perror("Cannot get path\n");
      return 1;
    }
    directory = malloc(INT_MAX*sizeof(char));
    strcpy(directory,arg);
    flag = 1;
  }
  else                                               //If directory is specified
  {
    directory = malloc(strlen(parsed_inp[1])*sizeof(char));
    strcpy(directory,parsed_inp[1]);
  }


  int i;
  if(flag == 0)                                   //Check where to start the iteration
  {
    i = 2;
  }
  else
  {
    i = 1;
  }

  while(directory != NULL)                              //While input directories are not exhausted
  {
    direc = opendir(directory);                        //Open directory in the given path
    if(direc == NULL)
    {
      perror("ls: No such file or directory\n");
      return 1;
    }
    while((file = readdir(direc)) != NULL)             //Read from directory all files and folders till every file is read
    {
      if(strcmp(file->d_name,".") != 0 && strcmp(file->d_name,"..") != 0)           //Ignore '.' and '..' directories
      {
        printf("%s    ",file->d_name);                 //Print name of the files/folders
      }
    }
    closedir(direc);                                   //Close the directory
    printf("\n");

    if(parsed_inp[i] == NULL)                          //Break if input directories are exhausted
      break;
    else
      strcpy(directory,parsed_inp[i]);
    i++;
  }

  free(directory);                                   //Free memory used by malloc

  return 1;
}
