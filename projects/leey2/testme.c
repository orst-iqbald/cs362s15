//Yong Lee
//leey2@onid.oregonstate.edu

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int chooser = rand() % 94 + 32;

	return (chooser);
}

char *inputString()
{
    char *word = malloc (sizeof (char) * 6);
	
	int chooser = rand() % 5 + 1;
	if (chooser == 1)
		word[1] = 'a';
	else if (chooser == 2)
		word[1] = 'e';
	else if (chooser == 3)
		word[1] = 'i';
	else if (chooser == 4)
		word[1] = 'o';
	else if (chooser == 5)
		word[1] = 'u';	

	chooser = rand() % 5 + 1;
	if (chooser == 1)
		word[3] = 'a';
	else if (chooser == 2)
		word[3] = 'e';
	else if (chooser == 3)
		word[3] = 'i';
	else if (chooser == 4)
		word[3] = 'o';
	else if (chooser == 5)
		word[3] = 'u';
		
	char chooser1 = 'A';
	char chooser2 = 'A';	
	char chooser3 = 'A';	
		
	chooser1 = rand() % 26 + 97;
	word[0] = chooser1;
	
	do{
		chooser2 = rand() % 26 + 97;
		word[2] = chooser2;
	}while(chooser2 == chooser1);	

	do{
		chooser2 = rand() % 26 + 97;
		word[4] = chooser2;
	}while(chooser3 == chooser1 || chooser3 == chooser2);	
	
    return word;
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
	  free (s);
      exit(200);
    }
	free (s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
