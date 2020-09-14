#define INT_MAX 1024

///////////////////////////////////////////
//  Remove files/directories using nftw
//////////////////////////////////////////

int visit(const char* path, const struct stat* stat, int flags, struct FTW* ftw)
{
    if(remove(path) < 0)            //Remove file/directory specified by the path
    {
        perror("Cannot Remove\n");
        return -1;                  //Return in case of error
    }
    return 0;                       //Return in case of success
}

///////////////////////////////////////////
//  Function for implementing rm
//////////////////////////////////////////

int myrm(char** parsed_inp)
{
  if(parsed_inp[1] == NULL)                               //If input not specified return
  {
    printf("rm: missing operand\n");
    return 1;
  }

  else if(strcmp(parsed_inp[1],"-r") == 0 && parsed_inp[2] == NULL)   //If input not specified return
  {
    printf("rm: missing operand\n");
    return 1;
  }

  if(strcmp(parsed_inp[1],"-r") == 0)                                 //If "-r" flag is passed
  {
    printf("Do you want to proceed with this operation?(Y/N)\n");     //Check for consent
    char inp;
    scanf("%c",&inp);
    if(inp == 'Y' || inp == 'y')
    {
      if (nftw(parsed_inp[2], visit, 10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) == -1)     //Remove files/directories recursively using nftw
      {
          perror("nftw");
      }
    }

  }
  else                                                                 //If "-r" flag is not passed
  {
    if (remove(parsed_inp[1]) < 0)                                     //Remove file/directory using remove
    {
        perror("Remove error\n");
    }
  }

  return 1;
}
