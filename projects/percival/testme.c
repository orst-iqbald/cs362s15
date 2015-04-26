#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int NUM_POSSIBLE_CHARS = 35;
int NUM_POSSIBLE_STRINGS = 10;
char POSSIBLE_CHARS[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'[', '{', '(', ' ', '}', ')', ']', '.', ',' };
char *POSSIBLE_STRINGS[] = { "reset", "string", "count", "store", "rest", "start",
	"stop", "refresh", "update", "char"};

char inputChar()
{
	int idx;
	
    // generate a random index in the POSSIBLE_CHARS array
	idx = rand() % NUM_POSSIBLE_CHARS;
	
    return POSSIBLE_CHARS[idx];
}

char *inputString()
{
	int idx;
	
    // generate a random index in the POSSIBLE_STRINGS array
	idx = rand() % NUM_POSSIBLE_STRINGS;
	
    return POSSIBLE_STRINGS[idx];
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
