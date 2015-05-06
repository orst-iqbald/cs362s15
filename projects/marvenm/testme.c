/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: testme.c
 *           Overview: Program for Random Testing Quiz 2
 *
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


/*   *   *   *   *   *   *
 * 
 * Function: rand_range()
 * 
 *    Entry: The parameters are ints for the minimum and maximum range values
 *
 *     Exit: The function returns an int in the range, inclusive of the stated
 *           limits
 *
 *  Purpose: The function generates a number within a range without some 
 *           numbers generating more than others and output skewing toward those
 *           values; More information available at the link below;
 *           Adapted from the Stack Overflow answer located at:
 *           http://stackoverflow.com/questions/2999075/generate-a-random-
 *           number-within-range/2999130#2999130
 *
 *
 *   *   *   *   *   *   */
int rand_range(int min, int max)
{
    // Generate a divisor for the rand() function
    int divisor = RAND_MAX / ((max - min) + 1);
    int output;

    do
    {
        output = rand() / divisor;
    }while (output > (max - min));

    return (output + min);
}

char inputChar()
{
    // TODO: rewrite this function
    
    // Initialize a char for output
    char output;
    
    // Initialize ints for range of ASCII char values from 32 to 126, which
    // include the space character and the closing curly brace character which
    // are needed for the testme() function
    int min = 32;
    int max = 126;
    
    output = rand_range(min, max);
    
    return (output);
    
}

char *inputString()
{
    // TODO: rewrite this function
    
    // Uncomment the line below and comment the rest of the random generation 
    // code to hard code the "reset" string and provide it every iteration
    // char output_string[6] = {'r', 'e', 's', 'e', 't', 0};
    
    // Initialize a char array for output 
    char output_string[6] = {0};
    
    
    
    // Initialize ints for the min and max values of 97 and 122, corresponding
    // to the lowercase letters of the ASCII character set
    int min = 97;
    int max = 122;
    
    // Use loop to fill the array with random char values
    char random;
    int i;
    
    for (i = 0; i < 5; i++)
    {
        // Call the rand_range function to generate a char value
        random = rand_range(min, max);
        
        // Assign the char to the array
        output_string[i] = random;
    }
    
    // The array was originally filled with null characters, so the last array
    // index is left unchanged and contains the null character
    
    return (output_string);
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
