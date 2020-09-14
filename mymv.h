#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing mv
//////////////////////////////////////////

int mymv(char** parsed_inp)
{
  if(parsed_inp[1] == NULL || parsed_inp[2] == NULL)    //If source and destination not specified return
  {
    perror("mv: missing operand\n");
    return 1;
  }

  ///////////////////////////////////////////
  //  Move multiple files to a directory
  //////////////////////////////////////////

  if(parsed_inp[3] != NULL)                             //If multiple files are to be moved to a directory
  {
    int i;
    for(i=1;parsed_inp[i]!=NULL;i++);                   //Find the number of files
    int j = 1;
    char* ptr;                                          //Pointer to the name of the file

    while(j < (i-1))                                    //While all files are not moved
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

      if(rename(parsed_inp[j],filename) == -1)           //Move file
      {
        perror("Cannot move file\n");
        return 1;
      }

      j++;
    }

    return 1;
  }

  ///////////////////////////////////////////
  //  Move one file 
  //////////////////////////////////////////

  int fd1,n;
  if((fd1 = open(parsed_inp[1],O_RDONLY)) == -1)               //If file cannot be opened return
  {
    perror("mv: cannot open file\n");
    return 1;
  }

  int fd2;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;        //S_IRUSR for ruser ead, S_IWUSR for user write, S_IRGRP for group read, S_IROTH for others read permissions
  if((fd2 = creat(parsed_inp[2],mode)) == -1)                 //If new file cannot be created return
  {
    perror("mv: cannot create file\n");
    return 1;
  }

  char buf[1];                                                //Buffer to read from original file
  while((n = read(fd1,buf,sizeof(buf))) > 0)                  //Read while end of file is not encountered
  {
    write(fd2,buf,sizeof(buf));                               //Write into new file
  }
  remove(parsed_inp[1]);
  close(fd1);                                                 //Close original file
  close(fd2);                                                 //Close new file

  return 1;
}
