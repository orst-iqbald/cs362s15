#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // get a random char between ASCII values 32-125
  char c = (char)(32 + rand() % 94);
  return c;
}

char *inputString()
{

  char *reset = malloc(sizeof(char) * 6);  //malloc size of 6 chars
  reset[0] = 'r';
  reset[1] = 'e';
  reset[2] = 's';
  reset[3] = 'e';
  reset[4] = 't';
  reset[5] = '\0';
  
  int i;
  int len = 6;
  
  //replace a char (not '\0') in reset with a random char ~1/3 of the time
  for(i = 0; i < len-1; i++) {
    if(rand() % 3 == 0) {
      reset[i] = inputChar();
    }
  }
  return reset;   
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