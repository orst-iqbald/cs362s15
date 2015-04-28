//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              unittest3.c

/*Description: This is a unit test to test the gainCard() in dominion.c.
Each player will randomly be assign decks, discards, and hands. Also the
amount of players, supplyCards, and toFlag will also be determined 
randomly.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testGainCard(int supplyPos, struct gameState *after, int toFlag, int player)
{
  int outCome;
  int failTests = 0;
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));

  outCome = gainCard(supplyPos, after, toFlag, player);

  //check if supply pile is empty or card not used in game
  if (supplyCount(supplyPos, &before) < 1)
  {
    return -1;
  }

  if (toFlag == 1)
  {
    before.deck[player][before.deckCount[player]] = supplyPos;
    before.deckCount[player]++;
  }
  else if (toFlag == 2)
  {
    before.hand[player][before.handCount[player]] = supplyPos;
    before.handCount[player]++;
  }
  else
  {
    before.discard[player][before.discardCount[player]] = supplyPos;
    before.discardCount[player]++;
  }

  //decrease number in supply pile
  before.supplyCount[supplyPos]--;

  if (outCome != 0)
  {
    printf("gainCard() FAIL: GAIN CARD\n");
    printf("gainCard() INFO: Not Working Properly!\n");
    failTests = 1;
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
  int numTests = 1;
  int supplyPos; 
  int toFlag;
  int gameIterations = 100; //change for number of test games
  struct gameState testGame;

  //display testing message for unittest1
  printf ("----------------------------------------\n");
  printf ("FUNCTION gainCard() BEING TESTED...\n");
  printf ("RANDOM TESTS...unittest3.c\n\n");

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

    //initializing random amount of players
    j = floor(Random() * MAX_PLAYERS);
    //initializing random decks
    testGame.deckCount[j] = floor(Random() * MAX_DECK);
    //initializing random discards
    testGame.discardCount[j] = floor(Random() * MAX_DECK);
    //initializing random hands
    testGame.handCount[j] = floor(Random() * MAX_HAND);
    //initializing random supply cards
    supplyPos = floor(Random() * 25);
    toFlag = floor(Random() * 3);
    //call to test gainCard()
    outCome = testGainCard(supplyPos, &testGame, toFlag, j);
  }

 if (outCome == 0)
  {
    printf("TEST PASSED\n\n");
    printf("gainCard() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  else
  {
    printf("gainCard() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  return 0;
}