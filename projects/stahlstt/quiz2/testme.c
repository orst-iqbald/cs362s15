#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// compiled with 'gcc -Wall testme.c -o testme'

char inputChar()
{
    // TODO: rewrite this function
    // r = (rand() % (max+1-min))+min

    // create random char from ascii characters 32 -126 
    // create random char from known set [,(, {, ' ', a, x, }, ), ]
    
//     int max = 126;
//     int min = 32;
//     int r = rand() % (max+1-min)+min;
//     char fluffy = r;

    char fluffy[] = "{[( ax)]}";
    char thisOne = fluffy[rand() % 9];
    return thisOne;
}

char *inputString()
{
    // TODO: rewrite this function
    // r = (rand() % (max+1-min))+min

    // create random string from lowercase characters  97 -122 
    // create random string from r,e,s,e,t
     
    char *testStr = malloc(sizeof(char)*6);
    int i;    
//     int min = 97;
//     int max = 122;
    
//     for(i = 0; i < 5; i++) {
//         testStr[i] = (char)(rand() % (max+1-min)+min);
//     }
//     testStr[6] = '\0';  
    
    char reset[6] = "reset";
    for(i=0; i < 5; i++){
        testStr[i] = reset[rand() % 5];
    }
    testStr[6] = '\0';        
    return testStr;
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
    if (c == ' ' && state == 3) state = 4;
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
      printf("error \n");
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
