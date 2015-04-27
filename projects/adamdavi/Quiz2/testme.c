/******************************************************************************
* testme.c
* David Adams
* CS 362
* Spring 2015
* Quiz 2
******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar()
{
  //return a random character out of the below set of possible characters
  char charOptions[] = "[({ ax})]";
  return charOptions[rand() % 9];
}

char *inputString()
{
  //return a random string
  char charOptions[] = "reset";
  char *testWord = malloc(sizeof(char) * 6);
  int i, randRet;

  for (i = 0; i < 5; i++) {
    randRet = rand() % 5;
    testWord[i] = charOptions[randRet];
  }

  testWord[5] = '\0';

  return testWord;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();  
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
    
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
