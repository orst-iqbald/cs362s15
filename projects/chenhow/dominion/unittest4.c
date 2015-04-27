//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              unittest4.c

/*Description: This is a unit test to test the isGameOver() in dominion.c.
Each supply card will have its count randomly generated.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testIsGameOver(struct gameState *testGame) {
  int i;
  int j = 0;
  int outCome = isGameOver(testGame);

  //check to see if there no provinces left
  if (testGame->supplyCount[province] == 0)
  {
    assert (outCome == 1);
    return outCome;
  }
  //check to see if there are any empty supply card categories
  for (i = 0; i < 25; i++)
  {
    if (testGame->supplyCount[i] == 0)
    {
      j++;
    }
    //check to see if there are 3 or more supply card categories empty
    if (j >= 3)
    {
      assert(outCome == 1);
      return outCome;
    }
  }

  assert(outCome == 0);
  return outCome;
}

int main()
{
  int i; 
  int n; 
  int j;
  struct gameState testGame;

  //check if supply pile is empty or card not used in game
  printf ("----------------------------------------\n");
  printf ("FUNCTION isGameOver() BEING TESTED...\n");
  printf ("RANDOM TESTS...\n");

  //this is initializing stream for random number generation
  SelectStream(2);
  PutSeed(3);
  
  //testing for 2000 iterations
  for (n = 0; n < 2000; n++)
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
    testIsGameOver(&testGame);
  }

  printf ("ALL TESTS OK!\n\n");
  return 0;
}