#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char charArray[] = {'[', ']', '{', '}',
					'(', ')', ' ', 'a', 'x'};
	
	int index = rand() % 9;
	
    return charArray[index];
}

char *inputString()
{
	char charArray[] = {'r', 'e', 's', 't', '\0'};
	int indexArray[5];
	
	int counter = 0;
	int index;
	int i;
	int badIndex;
	while(counter < 5)
	{
		badIndex = 0;
		
		index = rand() % 5;
		indexArray[counter] = index;
		if(counter > 0)
		{
			for(i = counter-1; i > 0; i--)
			{
				if(indexArray[counter] == indexArray[i])
					badIndex = 1;
			}
		}
		if(badIndex != 1)
			counter++;
	}
	
	char *returnedString = malloc(6 * sizeof(char));
	
	returnedString[0] = charArray[indexArray[0]];
	returnedString[1] = charArray[indexArray[1]];
	returnedString[2] = charArray[indexArray[2]];
	returnedString[3] = charArray[indexArray[1]];
	returnedString[4] = charArray[indexArray[3]];
	returnedString[5] = charArray[indexArray[4]];

    return returnedString;
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
	
	free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
