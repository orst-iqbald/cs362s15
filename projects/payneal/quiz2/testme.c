//
//  main.c
//  randomTesterQuiz2
//
//  Created by Ali Payne on 4/23/15.
//  Copyright (c) 2015 Ali Payne. All rights reserved.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    
    //asic tabel hold sare test case chars and some
    int number = rand() % (126-32) + 32;

    //check number in correct range
    //printf("%c",number);
    
    return (char)number ;
}

char *inputString()
{
    // TODO: rewrite this function
    
    // rest is what we want and thats one 6 char includeing '\0'
    // we make length 5 becuase we dont need to mess with '\0'
    // i is the index used for loop below
    int i,length= 5;
    
    // this is the string we will mess with to reach all test casses
    char string[]= "reset";
    char *reset = malloc(length+1);
    
    
    for( i = 0; i< length + 1; i++)
    {
            if (rand() % 3> 1)
            {
                string[i] = inputChar();
            }
        
        reset[i] = string[i];
        //printf(" string = %s \n", string );
    }
  //  printf(" string = %s \n", string);
    return reset;
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
    
    // for loop to make sure letter was being created and string
   // int i;
    //char *s;
    //for (i = 0; i< 200; i++)
    //{
     //   inputChar();
        //s= inputString();
        //printf(" string is: %s", s);
        //printf("\n");
    //}
    
    testme();
    
    return 0;
}












