#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing cat
//////////////////////////////////////////

int mycat(char** parsed_inp)
{
  if(parsed_inp[1] == NULL)                         //Return if file not specified
  {
    printf("File not specified\n");
    return 1;
  }

  int i = 1;
  while(parsed_inp[i] != NULL)                      //Run while all input files specified are not printed
  {
    char buf[10];                                   //Buffer to read characters from file
    FILE* file;                                     //Pointer to file
    int n;
    file = fopen(parsed_inp[i],"r");                //Open file in read mode

    if(file == NULL)                                //Return if error encountered
    {
      perror("cat: cannot open file\n");
      return 1;
    }
    while(fgets(buf,sizeof(buf),file) != NULL)      //Read from file while end of file is not encountered
    {
      printf("%s",buf);
    }
    printf("\n");
    fclose(file);                                   //Close the file
    i++;
  }

  return 1;
}
