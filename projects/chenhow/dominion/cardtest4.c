//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 3
//Term:                   Spring 2015
//File Name:              cardTest4.c

/*Description: This is a card test to test the cardGreatHall() in dominion.c.
The test needs to determine whether the cardGreatHall() draws 1 card, adds 1
action, and then discards Village card.*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

int testCardGreatHall(int currentPlayer, struct gameState *after)
{
  int discard = 1;
  int failTests = 0;
  int handPos = floor(Random() * after->handCount[currentPlayer]);
  struct gameState before;
  memcpy(&before, after, sizeof(struct gameState));

	//+1 Card
	drawCard(currentPlayer, &before);
  
	//+1 Actions
	before.numActions = before.numActions + 1;

	//discard card from hand
	discardCard(handPos, currentPlayer, &before, 0);
  
  cardGreatHall(handPos, currentPlayer, after);
  
   //check to see if top discard pile is not the same
  if (after->playedCards[after->playedCardCount-1] != before.playedCards[before.playedCardCount-1])
	{
    //FAILED: discard card
		printf("cardGreatHall() FAIL: DISCARD\n");
    printf("cardGreatHall() INFO: Does NOT DISCARD Card\n");
    discard = 0;
    failTests += 1;
	}
  
  //check to see whether too many actions were added
  if (after->numActions > before.numActions)
  {
    //FAILED: adding too many actions
    printf("cardGreatHall() FAIL: +1 ACTIONS\n");
    printf("cardGreatHall() INFO: Adding TOO MANY ACTIONS\n");
    failTests += 1;
  }
  //check to see whether not enough actions were added
  else if (after->numActions < before.numActions)
  {
    //FAILED: adding not enough actions
    printf("cardGreatHall() FAIL: +1 ACTIONS\n");
    printf("cardGreatHall() INFO: Adding NOT ENOUGH ACTIONS\n");
    failTests += 1;
  }
  
  //if Great Hall card was properly discarded,
  if (discard == 1)
  {
    //then check to see if hand counts don't match
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer])
    {
      //if they don't match, then cardGreatHall() does not draw correct amount
      printf("cardGreatHall() FAIL: +1 DRAW\n");
      printf("cardGreatHall() INFO: Does NOT DRAW CORRECT # of Cards\n");
      failTests += 1;
    }
  }
  else
  { 
    //if Great Hall card was not properly discarded, check is handcount has 1 extra
    if (before.handCount[currentPlayer] != after->handCount[currentPlayer] + 1)
    {
      //if not, then cardGreatHall() does not draw correct amount
      printf("cardGreatHall() FAIL: +1 DRAW\n");
      printf("cardGreatHall() INFO: Does NOT DRAW CORRECT # of Cards\n");
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
  int gameIterations = 1; //change for the number of test games
  int numTests = 3;
  struct gameState testGame;
  
  //display testing message for cardTest2
  printf ("----------------------------------------\n");
  printf ("FUNCTION cardAdventurer() BEING TESTED...\n");
  printf ("RANDOM TESTS...cardtest4.c\n\n");

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
    
    //function call to test cardAdventurer() function
    outCome = testCardGreatHall(j, &testGame);
  }
  if (outCome == 0)
  {
    printf("ALL TESTS PASSED\n");
  }
  else
  {
    printf("cardGreatHall() FAILED %d out of %d TESTS\n\n", outCome, numTests);
  }
  return 0;
}
