#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing cp
//////////////////////////////////////////

int mycp(char** parsed_inp)
{
  if(parsed_inp[1] == NULL || parsed_inp[2] == NULL)        //If files not specified return
  {
    printf("cp: missing operand\n");
    return 1;
  }

  ///////////////////////////////////////////
  //  Copy multiple files to a directory
  //////////////////////////////////////////

  if(strcmp(parsed_inp[1],"-r") != 0 && parsed_inp[3] != NULL)  //Copy number of files to a directory
  {
    int i;
    for(i=1;parsed_inp[i]!=NULL;i++);                   //Find the number of files
    int j = 1;
    char* ptr;                                          //Pointer to the name of the file

    while(j < (i-1))                                    //While all files are not copied
    {
      char filename[INT_MAX];                           //String to store path of new file
      strcpy(filename,parsed_inp[i-1]);                 //Copy new directory path
      ptr = strrchr(parsed_inp[j],'/');                 //Find pointer to file name
      if(ptr != NULL)
      {
        strcat(filename,ptr);                           //Concatenate file name
      }
      else
      {
        strcat(filename,"/");
        strcat(filename,parsed_inp[j]);                 //Concatenate file name
      }

      int fd1,n;
      if((fd1 = open(parsed_inp[j],O_RDONLY)) == -1)               //If file cannot be opened return
      {
        perror("cp: cannot open file\n");
        return 1;
      }

      int fd2;
      mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;        //S_IRUSR for ruser ead, S_IWUSR for user write, S_IRGRP for group read, S_IROTH for others read permissions
      if((fd2 = creat(filename,mode)) == -1)                 //If new file cannot be created return
      {
        perror("cp: cannot create file\n");
        return 1;
      }

      char buf[1];                                                //Buffer to read from original file
      while((n = read(fd1,buf,sizeof(buf))) > 0)                  //Read while end of file is not encountered
      {
        write(fd2,buf,sizeof(buf));                               //Write into new file
      }
      close(fd1);                                                 //Close original file
      close(fd2);                                                 //Close new file

      j++;
    }

    return 1;
  }

  ///////////////////////////////////////////
  //  Copy one directory to another
  //////////////////////////////////////////

  if(strcmp(parsed_inp[1], "-r") == 0)                                //If "-r" flag is passed
  {
    char dir[INT_MAX];                                                //Store new directory path
    int flag = 0;                                                     //Check for absolute or relative path
    char* ptr;                                                        //Pointer to directory name in absolute path
    ptr = strrchr(parsed_inp[2],'/');

    char pwd_init[INT_MAX],pwd_temp[INT_MAX];                         //Buffer for directory paths
    getcwd(pwd_init,sizeof(pwd_init));                                //Get path to original directory

    if(chdir(parsed_inp[3]) < 0)                                      //chdir to destination directory to get absolute path
    {
      perror("Cannot change directory\n");
    }
    getcwd(pwd_temp,sizeof(pwd_temp));                                //Get path to destination directory

    if(chdir(pwd_init) < 0)                                           //Return to original directory
    {
      perror("Cannot change directory\n");
    }

    strcpy(dir,pwd_temp);                                             //Prepare path to copy files
    strcat(dir,"/");

    if(ptr != NULL)
    {
      flag = 1;
      ptr++;

      if(chdir(parsed_inp[2]) < 0)                                  //Change directory to the source directory
      {
        perror("Cannot change directory\n");
      }
      if(chdir("..") < 0)
      {
        perror("Cannot change directory\n");
      }
    }

    int copy(const char* path, const struct stat* stat, int flags, struct FTW* ftw)
    {
      char filename[INT_MAX];                         //String to store path of new file
      strcpy(filename,dir);                           //Copy new directory path
      strcat(filename,path);                          //Concatenate file name

      if(flags == FTW_D || flags == FTW_DP)           //If the given path in traversal is a directory
      {
          if(mkdir(filename, 0777) < 0)                 //Create a directory in the new path
          {
            printf("Cannot create directory\n");
            return -1;
          }

      }

        if(flags == FTW_F)                              //If the given path in traversal is a file copy file to the new path
        {
          int fd1,n;
          if((fd1 = open(path,O_RDONLY)) == -1)               //If file cannot be opened return
          {
            perror("cp: cannot open file\n");
            return 1;
          }

          int fd2;
          mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;        //S_IRUSR for ruser ead, S_IWUSR for user write, S_IRGRP for group read, S_IROTH for others read permissions
          if((fd2 = creat(filename,mode)) == -1)                      //If new file cannot be created return
          {
            perror("cp: cannot create file\n");
            return 1;
          }

          char buf[1];                                                //Buffer to read from original file
          while((n = read(fd1,buf,sizeof(buf))) > 0)                  //Read while end of file is not encountered
          {
            write(fd2,buf,sizeof(buf));                               //Write into new file
          }
          close(fd1);                                                 //Close original file
          close(fd2);                                                 //Close new file

        }
        return 0;
    }
    if(flag == 0)                                                       //If relative path of source directory
    {
      if (nftw(parsed_inp[2], copy, 10, FTW_MOUNT|FTW_PHYS) == -1)      //Call nftw to traverse the old directory recursively
      {
          perror("nftw");
      }
    }
    else                                                          //If absolute path of source directory
    {
      char dirname[INT_MAX];                                      //Buffer for source directory name
      strcpy(dirname,ptr);

      if (nftw(dirname, copy, 10, FTW_MOUNT|FTW_PHYS) == -1)      //Call nftw to traverse the directory recursively
      {
          perror("nftw");
      }

      if(chdir(pwd_init) < 0)                                          //Change directory to original directory
      {
        perror("Cannot change directory\n");
      }
    }

    return 1;
  }


  ///////////////////////////////////////////
  //  Copy one file to another
  //////////////////////////////////////////

  int fd1,n;
  if((fd1 = open(parsed_inp[1],O_RDONLY)) == -1)               //If file cannot be opened return
  {
    perror("cp: cannot open file\n");
    return 1;
  }

  int fd2;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;        //S_IRUSR for ruser ead, S_IWUSR for user write, S_IRGRP for group read, S_IROTH for others read permissions
  if((fd2 = creat(parsed_inp[2],mode)) == -1)                 //If new file cannot be created return
  {
    perror("cp: cannot create file\n");
    return 1;
  }

  char buf[1];                                                //Buffer to read from original file
  while((n = read(fd1,buf,sizeof(buf))) > 0)                  //Read while end of file is not encountered
  {
    write(fd2,buf,sizeof(buf));                               //Write into new file
  }
  close(fd1);                                                 //Close original file
  close(fd2);                                                 //Close new file

  return 1;
}
