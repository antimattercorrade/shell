#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing mkdir
//////////////////////////////////////////

int mymkdir(char** parsed_inp)
{
  if(parsed_inp[1] == NULL)                           //If input not specified return
  {
    printf("mkdir: missing operand\n");
    return 1;
  }

  int i = 1;

  while(parsed_inp[i] != NULL)                        //Run while all directories are not created
  {
    if(mkdir(parsed_inp[i], 0777) < 0)                //Create new directory using mkdir
    {
      printf("Cannot create directory\n");
      return 1;
    }
    i++;
  }

  return 1;
}
