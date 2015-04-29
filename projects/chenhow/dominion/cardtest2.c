//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              cardTest2.c

/*Description: This is a card test to test the cardSmithy() in dominion.c.
The test needs to determine whether the cardSmithy() draws 3 cards and then
discards the Smithy card.*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testCardSmithy(int currentPlayer, struct gameState *after)
{
  int i;
  int discard = 1;
  int failTests = 0;
  int handPos = floor(Random() * after->handCount[currentPlayer]);
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));
   
  //this is initializing stream for random number generation
  SelectStream(2);
  PutSeed(3);

  //+3 Cards
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, &before);
  }
  
  //discard card from hand
  discardCard(handPos, currentPlayer, &before, 0);
  
  cardSmithy(handPos, currentPlayer, after);
  
  //check to see if top discard pile is not the same
  if (after->playedCards[after->playedCardCount-1] != before.playedCards[before.playedCardCount-1])
	{
    //FAILED: discard card if not the same error message
		printf("cardSmithy() FAIL: DISCARD\n");
    printf("cardSmithy() INFO: Does NOT DISCARD Card\n");
    discard = 0;
    failTests += 1;
	}
  
  //if Smithy card was properly discarded,
  if (discard == 1)
  {
    //then check to see if hand counts don't match
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer])
    {
      //if they don't match, then cardSmithy() does not draw correct amount
      printf("cardSmithy() FAIL: +3 DRAW\n");
      printf("cardSmithy() INFO: Does NOT DRAW CORRECT # of Cards\n");
      failTests += 1;
    }
  }
  else
  { 
    //if Smithy card was not properly discarded, check is handcount has 1 extra
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer] + 1)
    {
      //if not, then cardSmithy() does not draw correct amount
      printf("cardSmithy() FAIL: +3 DRAW\n");
      printf("cardSmithy() INFO: Does NOT DRAW CORRECT # of Cards\n");
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
  int numTests = 2;
  int gameIterations = 1; //change for the number of test games
  struct gameState testGame;
  
  //display testing message for cardTest2
  printf ("----------------------------------------\n");
  printf ("FUNCTION cardSmithy() BEING TESTED...\n");
  printf ("RANDOM TESTS...cardtest2.c\n\n");

  //this is initializing stream for random number generation
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
    
    //function call to test cardSmithy() function
    outCome = testCardSmithy(j, &testGame);
  }
  if (outCome == 0)
  {
    printf("ALL TESTS PASSED\n");
  }
  else
  {
    printf("cardSmithy() FAILED %d out of %d TESTS\n\n", outCome, numTests);
  }
  return 0;
}