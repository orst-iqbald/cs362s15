#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// the randomness is guided by including only a subset of ASCII
// CITE: https://piazza.com/class/i7qs7yqg42v4ez?cid=59
char charset[] = { ' ', '(', ')', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '{', '}', '[', ']' };
int charset_size = 33;

// set the size of the input string to 6, anything longer would be  waste since
// "reset" is 5 characters long + the null terminating character.
int input_string_length = 6;

char inputChar()
{
    // DONE: rewrite this function

    // This function just pulls a random character from the character set
    // defined above
    char c = rand() % charset_size;
    return charset[c];
}

char *inputString()
{
    // DONE: rewrite this function

    // set the input string to begin as "reset"
    char input_string[] = "reset\0";

    // replace characters in the string with a random character 1/3 of the time
    int i = 0;
    for (i = 0; i < input_string_length; i++)
    {
      if (rand() % 3 == 0)
      {
        input_string[i] = inputChar();
      }
    }
    return input_string;
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
