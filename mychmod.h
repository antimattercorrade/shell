#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing chmod
//////////////////////////////////////////

int mychmod(char** parsed_inp)
{
  if(parsed_inp[1] == NULL || parsed_inp[2] == NULL)             //If permissions or files not specified then return
  {
    printf("chmod: missing operand\n");
    return 1;
  }

  char* ptr;

  long int oct = strtol(parsed_inp[1],&ptr,8);                  //Convert input string to octal number

  int i = 2;

  while(parsed_inp[i] != NULL)                                  //Run while permissions for all inputs are not changed
  {
    if(chmod(parsed_inp[i],oct) < 0)                            //Change permissions using chmod
    {
      printf("Cannot change permissions\n");
      return 1;
    }
    i++;
  }

  return 1;
}
