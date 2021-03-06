//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              unittest1.c

/*Description: This is a unit test to test the scoreFor() in dominion.c. Each
player will have 3 attributes to calculate (hand, deck, and discard). The test
needs to be able to random create hands, decks, discards, and number of
players. It will the test to see if the function calculates those scores
correctly.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testScoreFor(int player, struct gameState *after)
{
  int i;
  int outCome = 0;
  int score = 0;
  int failTests = 0;
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));
  outCome = scoreFor(player, after);

  //this is the score from hand
  for (i = 0; i < before.handCount[player]; i++)
  {
    //curse gets -1 to score
    if (before.hand[player][i] == curse)
    { 
      score = score - 1;
    }
    //estate gets +1 to score
    if (before.hand[player][i] == estate)
    {
      score = score + 1;
    }
    //duchy gets +3 to score
    if (before.hand[player][i] == duchy)
    {
      score = score + 3; 
    }
    //province gets +6 to score
    if (before.hand[player][i] == province)
    {
      score = score + 6;
    }
    //great hall gets + 1 to score
    if (before.hand[player][i] == great_hall)
    {
      score = score + 1;
    }
    //gardens gets +1 for every 10 cards in deck
    if (before.hand[player][i] == gardens)
    {
      score = score + ( fullDeckCount(player, 0, &before) / 10 );
    }
  }

  //this is the score from discard (same descriptions for cards below)
  for (i = 0; i < before.discardCount[player]; i++)
  {
    if (before.discard[player][i] == curse)
    {
      score = score - 1;
    }
    if (before.discard[player][i] == estate)
    {
      score = score + 1;
    }
    if (before.discard[player][i] == duchy)
    {
      score = score + 3;
    }
    if (before.discard[player][i] == province)
    {
      score = score + 6;
    }
    if (before.discard[player][i] == great_hall)
    {
      score = score + 1;
    }
    if (before.discard[player][i] == gardens)
    {
      score = score + ( fullDeckCount(player, 0, &before) / 10 );
    }
  }

  //this is the score from the deck (same descriptions for cards below)
  for (i = 0; i < before.discardCount[player]; i++)
  {
    if (before.deck[player][i] == curse) 
    { 
      score = score - 1;
    }
    if (before.deck[player][i] == estate)
    {
      score = score + 1;
    }
    if (before.deck[player][i] == duchy) 
    {
      score = score + 3;
    }
    if (before.deck[player][i] == province)
    {
      score = score + 6;
    }
    if (before.deck[player][i] == great_hall)
    {
      score = score + 1;
    }
    if (before.deck[player][i] == gardens)
    {
      score = score + ( fullDeckCount(player, 0, &before) / 10 );
    }
  }
  
  if (outCome != score)
  {
    printf("scoreFor() FAIL: SCORE FOR\n");
    printf("scoreFor() INFO: NOT CALCULATING CORRECT SCORE\n");
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
  int gameIterations = 100; //change for the number of test games
  struct gameState testGame;

  //display testing message for unittest1
  printf ("----------------------------------------\n");
  printf ("FUNCTION scoreFor() BEING TESTED...\n");
  printf ("RANDOM TESTS...unittest1.c\n\n");

  //this is initializing stream for random number generation
  SelectStream(2);
  PutSeed(3);

  //testing for 2000 iterations
  for(n = 0; n < gameIterations; n++)
  {
    for(i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&testGame)[i] = floor(Random() * 256);
    }
    //initializing random number of players up to largest integral value
    j = floor(Random() * MAX_PLAYERS);
    //initializing random decks up to the largest integral value
    testGame.deckCount[j] = floor(Random() * MAX_DECK);
    //initializing random discards up to the largest integral value
    testGame.discardCount[j] = floor(Random() * MAX_DECK);
    //initializing random hands up to the largest integral value
    testGame.handCount[j] = floor(Random() * MAX_HAND);

    //initializing random hands for each player
    for (i = 0; i < testGame.handCount[j]; i++)
    {
      testGame.hand[j][i] = floor(Random() * MAX_DECK);
    }
    //initializing random discards for each player
    for (i = 0; i < testGame.discardCount[j]; i++)
    {
      testGame.discard[j][i] = floor(Random() * MAX_DECK);
    }
    //initializing random deck for each player
    for (i = 0; i < testGame.discardCount[j]; i++)
    {
      testGame.deck[j][i] = floor(Random() * MAX_DECK);
    }

    //call to test scoreFor()
    outCome = testScoreFor(j, &testGame);
  }
  
  if (outCome == 0)
  {
    printf("TEST PASSED\n\n");
    printf("scoreFor() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  else
  {
    printf("scoreFor() FAILED %d out of %d TEST\n\n", outCome, numTests);
  }
  return 0;
}