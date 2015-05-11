/* Author: Jon Derderian
*  Class: CS 362
*  Assignment: Quiz 2
*  File: testme.c
*  Date: Spring 2015, Week 4
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //gets random ASCII character between the values of 32-125,
    //which is in the range we want to test
    char testChar = (char)((rand() % 94) + 32);
    return testChar;
}

char *inputString()
{
    //the letters that we want in the inputString being tested
    char testString[] = {'r', 'e', 's', 't'};
    //create memory allocation for randomString
    char *randomString = malloc(sizeof(char) * 6);
    int i;
    for(i = 0; i < 5; i++){
        //randomly generating the position in the letter array to choose
        int r = rand() % 4;
        //place the letter into the string that's being returned to testme()
        randomString[i] = testString[r];
    }
    randomString[5] = '\0';

    return randomString;
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


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
