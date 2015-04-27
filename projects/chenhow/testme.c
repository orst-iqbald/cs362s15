//AUTHOR:                HOWARD CEHN
//CLASS/Assignment:      CS362/Quiz2
//TERM:                  Spring 2015
//Filename:              testme.c

/*Description:  Implement a random tester for the function testme() in 
    testme.c that is capable of printing the error message.  You should
    implement inputChar() and inputString() to produce random values.
    Write up the development of your random tester and how it finds the
    error message as randomstring.txt.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  //generating the number of ASCII character randomly; 
  int ascNum = rand() % (126-32) + 32; 
  //returning the type casted (char) ASCII number
  return (char)ascNum ;
}

char *inputString()
{
  //these are letters we are concerned with in the string
  char testChar[] = {'e', 'r', 's', 't'};
  //memory allocation of randStr
  char *randStr = malloc(sizeof(char)*5);
  int i = 0;
  
  //loop to create randStr array
  for(i = 0; i < 5; i++)
  {
    //randomly generates array index for testChar[]
    int j = rand() % 4;
    //sets the value of each randStr index with a random value from 
    //the testChar array
    randStr[i] = testChar[j];
  }
  //return the character string 
  return randStr;
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
  }
}


int main()
{
  srand(time(NULL));
  testme();
  return 0;
}