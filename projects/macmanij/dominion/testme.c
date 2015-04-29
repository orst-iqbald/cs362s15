#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char characters[33] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
				'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
				's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[',
				'(', '{', ' ', '}', ')', ']' };
	int randochar = rand()%34;
	printf("characters[randochar] = %c\n", characters[randochar]);
    return characters[randochar];
}

char *inputString()
{
    // TODO: rewrite this function
	int randostring = rand()%10;
	printf("randostring = %i\n", randostring);
	if (randostring == 0) {
		return "avocado";
	} else if (randostring == 1) {	
		return "asparagus";
	} else if (randostring == 2) {
		return "turtles";
	} else if (randostring == 3) {
		return "endersgame";
	} else if (randostring == 4) {
		return "iplantedatreetoday";
	} else if (randostring == 5) {
		return "vegansareawesome";
	} else if (randostring == 6) {
		return "waterbottle";
	} else if (randostring == 7) {
		return "plugsnotdrugs";
	} else if (randostring == 8) {
		return "guitarallday";
	} else if (randostring == 9) {
		return "reset";
	}
    
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
