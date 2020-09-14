#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing grep
//////////////////////////////////////////

int mygrep(char** parsed_inp)
{
  if(parsed_inp[1] == NULL)                           //Return if no search term specified
  {
    printf("grep: searchterm [file...]\n");
    return 1;
  }

  if(parsed_inp[1][0] == '"' && parsed_inp[1][1] == '"')  //If search term is empty string
  {
    printf("No match found\n");
    return 1;
  }

  if(parsed_inp[2] == NULL)                               //If file is not specified read from standard input
  {
      char* line;                                         //Buffer to store input
      int n;
      size_t len = 0;
      while((n = getline(&line,&len,stdin)) > 0)          //While input can be read from stdin store it in buffer
      {
        if(strstr(line,parsed_inp[1]) != NULL)            //Check if input has the search term as a substring, then print
          printf("%s\n",line);
      }

    return 1;
  }

  char* search;                                       //Buffer for search term                                 
  search = malloc(strlen(parsed_inp[1])*sizeof(char));  //Else copying search term into search variable
  strcpy(search,parsed_inp[1]);


  int i = 2;
  while(parsed_inp[i] != NULL)                         //Run while all input files are not checked
  {
    char* line;                                         //Buffer for reading lines from file
    FILE* file;                                         //Pointer to file
    int n;
    size_t len = 0;
    file = fopen(parsed_inp[i],"r");                    //Open file in read mode
    if(file == NULL)                                    //Return if file cannot be opened
    {
      perror("Cannot open file\n");
      return 1;
    }
    while((n = getline(&line,&len,file)) > 0)           //Read from file till end of file is encountered
    {
      if(strstr(line,search) != NULL)                   //Check if input has the search term as a substring, then print
        printf("%s\n",line);
    }
    printf("\n");
    fclose(file);                                       //Close file
    i++;
  }

  free(search);                                         //Free memory allocated by malloc

  return 1;
}
