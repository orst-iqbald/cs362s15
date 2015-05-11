#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // randomly return one of the printable ascii key codes from 32 to 126
    char ret_char = (rand() % 95) + 32;
    return ret_char;
}

char *inputString()
{   
	// setup return string to hold up to five chars
    char tempStr[6];
    memset(tempStr, '\0', 6);
    
    // randomly choose length of string from 1 to 5 
    int str_length = (rand() % 5) + 1;
    
    // get random char and add to str
    for (int i=0; i < str_length; i++) {
      tempStr[i] = inputChar();
    }
    
    // return random length/content string
    char *retStr = malloc((str_length+1) * sizeof(char));
    strcpy(retStr, tempStr);
    
    return retStr;
    
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
      free(s);  // added to counter malloc from inputString()
      exit(200);
    }
    free(s);  // added to counter malloc from inputString()
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
