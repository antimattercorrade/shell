////////////////////////////////////////////
//  Standard Library header files
///////////////////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/wait.h>
#include<unistd.h>
#include<dirent.h>
#include<fcntl.h>
#define __USE_XOPEN_EXTENDED 1
#include<ftw.h>

////////////////////////////////////////////
//  Header file for implementing commands
///////////////////////////////////////////

#include"mybuiltin.h"

#define INT_MAX 1024

// Initialising parent pid with arbritrary value
pid_t val = INT_MAX;

////////////////////////////////////////////
//  Function for parsing input
///////////////////////////////////////////

char** parseinput(char* inp, char** parsed_inp)
{
  char* token;
  int i = 0;
  token = strtok(inp," ");  //Temporary variable to get the space delimited strings
  parsed_inp[i] = token;    //Storing the delimited strings into 2D character array

  while(1)                  //Loop runs till the input is delimited
  {
    i++;
    token = strtok(NULL," ");

    if(token != NULL && strcmp(token,"&") == 0)  //Check for background process,i.e, if input contains '&'
    {
      val = fork();
       if(val > 0)                              //Parent process
       {
          return NULL;                          //Return prompt to execute next command
       }
      else if(val == 0)                         //Child process(background)
      {
          parsed_inp[i] = NULL;                 //Terminate the parsed input with NULL
          break;
      }
      else                                      //Fork failed
      {
          perror("Cannot Fork\n");
      }
    }

    //If not a background process store the delimited strings
    parsed_inp[i] = token;

    if(token == NULL)                           //If input string is consumed, break
      break;
  }

return parsed_inp;
}

////////////////////////////////////////////
//  Main function
///////////////////////////////////////////

int main()
{
  char* inp;                      //Buffer to store input from prompt
  int rc;

  while(1)                        //Process input while the program is not terminated
  {
    inp = readline("shell> ");                                //Read input from the prompt
    char** parsed_inp = malloc(INT_MAX*sizeof(char *));       //Buffer to store parsed input

    if(parsed_inp == NULL)                                    //Exit if memory allocation failed
    {
      printf("Memory allocation failed\n");
      exit(1);
    }

    parsed_inp = parseinput(inp,parsed_inp);                  //Store the parsed input in buffer

    if(parsed_inp == NULL)                                    //If empty string then continue to next iteration
    {
      continue;
    }

    if(builtin(parsed_inp))                                   //Check for builtin commands
    {
      if (val == 0)                                           //If it is background process terminate it since the command has been executed
      {
        kill(getpid(),SIGKILL);
      }
      continue;                                               //If builtin command found then continue to next iteration
    }

    rc = fork();                                             //Else execute the command using fork and execute
    if(rc < 0)                                               //Exit if fork failed
    {
      printf("Fork Failed\n");
      exit(1);
    }
    else if(rc == 0)                                        //If child process then execute the command
    {
      execvp(parsed_inp[0],parsed_inp);
      printf("%s execution failed\n",parsed_inp[0]);
    }
    else                                                    //If parrent process wait for the child to execute
    {
      wait(NULL);
    }

    free(parsed_inp);                                       //Free allocated memory

    if(val == 0)                                            //If it is background process terminate it since the command has been executed
    {
      kill(getpid(),SIGKILL);
    }
  }


return 0;
}
