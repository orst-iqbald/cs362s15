//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              cardTest3.c

/*Description: This is a card test to test the cardVillage() in dominion.c.
The test needs to determine whether the cardVillage() draws 1 card, adds 2
actions, and then discards Village card.*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testCardVillage(int currentPlayer, struct gameState *after)
{
  int discard;
  int failTests = 0;
  int handPos = floor(Random() * after->handCount[currentPlayer]);
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));

  SelectStream(2);
  PutSeed(3);

  //+1 Card
  drawCard(currentPlayer, &before);
  
  //+2 Actions
  before.numActions = before.numActions + 2;
        
  //discard card from hand
  discardCard(handPos, currentPlayer, &before, 0);

  cardVillage(handPos, currentPlayer, after);
        
  if (after->playedCards[after->playedCardCount-1] != before.playedCards[before.playedCardCount-1])
	{
    //FAILED: discard card if not the same error message
		printf("cardVillage() FAIL: DISCARD\n");
    printf("cardVillage() INFO: Does NOT DISCARD Card\n");
    discard = 0;
    failTests += 1;
	}
  
  if (after->numActions > before.numActions)
  {
    //FAILED: adding too many actions
    printf("cardVillage() FAIL: +2 ACTIONS\n");
    printf("cardVillage() INFO: Adding TOO MANY ACTIONS\n");
    failTests += 1;
  }
  else if (after->numActions < before.numActions)
  {
    //FAILED: adding not enough actions
    printf("cardVillage() FAIL: +2 ACTIONS\n");
    printf("cardVillage() INFO: Adding NOT ENOUGH ACTIONS\n");
    failTests += 1;
  }
  
  //if Village card was properly discarded,
  if (discard == 1)
  {
    //then check to see if hand counts don't match
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer])
    {
      //FAILED: +1 draw
      printf("cardVillage() FAIL: +1 DRAW\n");
      printf("cardVillage() INFO: Does NOT DRAW CORRECT # of Cards\n");
      failTests += 1;
    }
  }
  else
  { 
    //if Village card was not properly discarded, check is handcount has 1 extra
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer] + 1)
    {
      //FAILED: +1 Draw
      printf("cardVillage() FAIL: +1 DRAW\n");
      printf("cardVillage() INFO: Does NOT DRAW CORRECT # of Cards\n");
      failTests += 1;
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
  int numTests = 3;
  int gameIterations = 1;
  struct gameState testGame;

  printf ("----------------------------------------\n");
  printf ("FUNCTION cardVillage BEING TESTED...\n");
  printf ("RANDOM TESTS...cardtest3.c\n\n");

  SelectStream(3);
  PutSeed(3);

  for (n = 0; n < gameIterations; n++)
  {
    SelectStream(3);
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&testGame)[i] = floor(Random() * 256);
    }

    j = floor(Random() * MAX_PLAYERS);
    testGame.whoseTurn = j;
    testGame.deckCount[j] = floor(Random() * MAX_DECK);
    testGame.discardCount[j] = floor(Random() * MAX_DECK);
    testGame.handCount[j] = floor(Random() * MAX_HAND);
    testGame.playedCardCount = floor(Random() * MAX_DECK);

    outCome = testCardVillage(j, &testGame);
  }
  if (outCome == 0) 
  {
    printf("ALL TESTS PASSED\n");
  }
  else
  {
    printf("cardVillage() FAILED %d out of %d TESTS\n\n", outCome, numTests);
  }
  return 0;
}