/************************************
Michael Flath
CS362
Quiz2

*************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char c[] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
	int r = rand() % 9;
    return c[r];
}

char *inputString()
{
    // TODO: rewrite this function
	int i;
	int r;
	char s[] = {'r', 'e', 's', 't', '\0'};
	char str[6];
	for(i = 0; i < 6; i++) {
		if(i == 0)
			str[i] = s[rand() % 2];
		else if(i == 1)
			str[i] = s[rand() % 2];
		else if(i == 3)
			str[i] = s[rand() % 4];
		else if( i == 4)
			str[i] = s[rand() % 5];
		else if(i == 5)
			str[i] = s[rand() % 6];
	}
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