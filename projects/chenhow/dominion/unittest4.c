//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              unittest4.c

/*Description: This is a unit test to test the isGameOver() in dominion.c.
Each supply card will have its count randomly generated. Check to see 
whether provinces are 0 or three supply card categories are 0.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testIsGameOver(struct gameState *after)
{
  int i;
  int j = 0;
  int failTests = 0;
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));
  int outCome = isGameOver(after);

  //check to see if there no provinces left
  if (before.supplyCount[province] == 0)
  {
    if (outCome != 1)
    {
      printf("isGameOver() FAIL: PROVINCE # Test\n");
      printf("isGameOver() INFO: Not Calculating Correct # of Provinces\n");
      failTests += 1;
    }
  }
  //check to see if there are any empty supply card categories
  for (i = 0; i < 25; i++)
  {
    if (before.supplyCount[i] == 0)
    {
      j++;
    }
    //check to see if there are 3 or more supply card categories empty
    if (j >= 3)
    {
      if (outCome != 1)
      {
        printf("isGameOver() FAIL: GAME OVER Test\n");
        printf("isGameOver() INFO: Not Calculating Correct # of Supply Cards\n");
        failTests += 1;
      }
    }
  }
  
  if (failTests == 0)
  {
    //return 0 if no errors
    return 0;
  }
  else
  {
    //return 1 if there were errors
    return failTests;
  }
}

int main()
{
  int i; 
  int n; 
  int j;
  int outCome;
  int numTests = 2;
  int gameIterations = 100; //change for the number of test games
  struct gameState testGame;

  //check if supply pile is empty or card not used in game
  printf ("----------------------------------------\n");
  printf ("FUNCTION isGameOver() BEING TESTED...\n");
  printf ("RANDOM TESTS...unittest4.c\n\n");

  //this is initializing stream for random number generation
  SelectStream(2);
  PutSeed(3);
  
  //testing for 2000 iterations
  for (n = 0; n < gameIterations; n++)
  {
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&testGame)[i] = floor(Random() * 256);
    }
    //randomly generate each supplyCards count
    for (j = 0; j < 25; j++)
    {
      testGame.supplyCount[j] = floor(Random() * (25 + 1));
    }
    //call to test isGameOver()
    outCome = testIsGameOver(&testGame);
  }
  
  if (outCome == 0)
  {
    printf("ALL TESTS PASSED\n\n");
    printf("isGameOVer() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  else
  {
    printf("isGameOVer() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  return 0;
}