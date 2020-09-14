///////////////////////////////////////////
//  Function for implementing cd
//////////////////////////////////////////

int mycd(char** parsed_inp)
{
  int temp = chdir(parsed_inp[1]);                //Change directory using chdir
  if(temp < 0)
    perror("Cannot change directory\n");

  return 1;
}
