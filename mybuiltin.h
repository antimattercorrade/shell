////////////////////////////////////////////
//  Header files for each command
///////////////////////////////////////////
#include"mycd.h"
#include"mypwd.h"
#include"myls.h"
#include"mycat.h"
#include"mygrep.h"
#include"mymv.h"
#include"mycp.h"
#include"myrm.h"
#include"mymkdir.h"
#include"mychmod.h"

///////////////////////////////////////////
//  Function for implementing all commands
//////////////////////////////////////////

int builtin(char** parsed_inp)
{
  if(strcmp(parsed_inp[0],"cd") == 0)                    //If the command is "cd"
  {
    return mycd(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"pwd") == 0)              //If the command is "pwd"
  {
    return mypwd(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"ls") == 0)                //If the command is "ls"
  {
    return myls(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"cat") == 0)               //If the command is "cat"
  {
    return mycat(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"grep") == 0)              //If the command is "grep"
  {
    return mygrep(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"mv") == 0)                //If the command is "mv"
  {
    return mymv(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"cp") == 0)                //If the command is "cp"
  {
    return mycp(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"rm") == 0)                //If the command is "rm"
  {
    return myrm(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"mkdir") == 0)             //If the command is "mkdir"
  {
    return mymkdir(parsed_inp);
  }

  else if(strcmp(parsed_inp[0],"chmod") == 0)             //If the command is "chmod"
  {
    return mychmod(parsed_inp);
  }

return 0;
}
