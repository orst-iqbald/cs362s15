/* ****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four Dominion cards implemented in dominion.c. These tests 
should be checked in as cardtest1.c, cardtest2.c,cardtest3.c, and cardtest4.c. 
(For example, create a test for smithy card.). 
It is mandatory to test smithy and adventurer card. 

test of Smithy (refactored card)
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int checkSmithy(int card, struct gameState *post, int handPos) 
{
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  r = cardEffect(card, 0, 0, 0, post, handPos, 0);
  
  int i;
  int currPlayer = pre.whoseTurn;
  
  //draw 3 cards
  for (i = 0; i < 3; i++) 
    drawCard(currPlayer, &pre);
  
  discardCard(handPos, currPlayer, &pre, 0);
  
  //Check that pre and post gameStates are equivalent
  assert (r == 0);
  assert (pre.numBuys == post->numBuys);
  assert (pre.discardCount[pre.whoseTurn] == post->discardCount[pre.whoseTurn]);
  assert (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn]);
  assert (pre.deckCount[currPlayer] == post->deckCount[currPlayer]);

  return 0;
}

int main (int argc, char** argv) 
{
  int i, pos, player;

  struct gameState G;

  printf ("Testing Smithy....\n");
    // Initialize the gameState with random bytes
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 255);
    }
    //Set critical values for current test to be with in valid ranstatees
    //Set whoseTurn to a valid player number
    G.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
    player = floor(Random() * G.numPlayers);
    G.whoseTurn = player;
    //Set deck/hand/discard values to reasonable numbers
    for (i = 0; i < G.numPlayers; i++) {
      G.deckCount[i] = floor(Random() * (MAX_DECK));
      G.handCount[i] = floor(Random() * (MAX_DECK - 4));
      G.discardCount[i] = floor(Random() * (MAX_DECK));
    }
    G.playedCardCount = floor(Random() * MAX_DECK);
    G.numBuys = 1;//floor(Random() * 10);
    //Set position to within range of handCount[]
    pos = floor(Random() * (G.handCount[player]));
    //Test smithy function
    checkSmithy(smithy, &G, pos);

  printf("End smithy test...\n");
  //End the random tests
  return 0;
}