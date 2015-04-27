#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    //values from 32-126 on the ASCII table
    char random_char = (char)((rand() % 95)+32);
    return random_char;
}

char *inputString()
{
    // TODO: rewrite this function
    char *reset = "reset";
    char *random_string = malloc(6 * sizeof(char));
    int i;

    //create a 1/1000 chance to be the string reset which will trigger
    //error message
    //else we use inputChar to generate a totally random string
    if ((rand() % 1000) == 7)
      return reset;
    else {
      for (i = 0; i < 5; i++){
        random_string[i] = inputChar();
      }
      random_string[5] = '\0'; //explicitly null terminate string
    }

    return random_string;
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
