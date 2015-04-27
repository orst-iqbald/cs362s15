#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // 50% chance of returning one of the characters
    // that will eventually be needed
    char arr[] = "[({ ax})]";
    int randomGenerator;
    randomGenerator = rand() % 2;
    if ( randomGenerator == 1 ) 
	return ( rand() % 128 ); // returns ASCII number for some char
    else 
	return arr[ (rand() % 9) ];
}

char *inputString()
{
    // we'll give this random generator about
    // a 1 in 64 shot at hitting the string
    // 'reset' with a null at end
    static char arr[6];
    char guide[6];
    guide[0] = 'r';
    guide[1] = 'e';
    guide[2] = 's';
    guide[3] = 'e';
    guide[4] = 't';
    guide[5] = '\0';

    int i;
    for ( i =0; i < 6; i++ ) {
	if ( rand() % 2 == 0 ) {
	    arr[i] = guide[i];
	}
	else {
	    arr[i] = rand() % 128; // some random ASCII char
	}
    }	
    return arr;
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
