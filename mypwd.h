#define INT_MAX 1024

///////////////////////////////////////////
//  Function for implementing pwd
//////////////////////////////////////////

int mypwd(char** parsed_inp)
{
    char pwd[INT_MAX];                              //Buffer to store path
    if(getcwd(pwd,sizeof(pwd)) == NULL)             //Get current working directory using "getcwd"
    {
      perror("Cannot get working directory\n");
    }
    else
    {
      printf("%s\n",pwd);
    }
    return 1;
}
