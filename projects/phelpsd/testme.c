#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//function that returns a random character
char inputChar()
{
    return rand() % 94 + 32;
}

//function that returns a random string
char *inputString()
{
    char values[4] = {'r','e','s','t'}; //array of the letters in the word 'reset' to select from "randomly"
    char *str;
    str = malloc(6 * sizeof(char));
    int i;
    //for loop to create string
    for(i = 0; i < 5; ++i) {
        /*this implementation produces a much more random string, but takes MUCH longer to run
        In my test, it took 526582 iterations to hit 'reset' with this method.*/
        //str[i] = rand() % 16 + 101;
        str[i] = values[rand() % 4]; //this implementation takes far fewer iterations to get 'reset'.       
    }
    str[5] = '\0'; //null terminates the string after randomly building it
    return str;
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