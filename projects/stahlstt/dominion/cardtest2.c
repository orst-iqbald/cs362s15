/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four Dominion cards implemented in dominion.c. These tests 
should be checked in as cardtest1.c, cardtest2.c,cardtest3.c, and cardtest4.c. 
(For example, create a test for smithy card.). 
It is mandatory to test smithy and adventurer card. 

test of Adventurer (refactored card)
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int checkAdventurer(int card, struct gameState *post, int handPos) 
{
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  r = cardEffect(card, 0, 0, 0, post, handPos, 0);
  
  int treasure = 0;
  int newcard;
  int z = 0;
  int temp[MAX_HAND];
  int currPlayer = whoseTurn(&pre);
  
  // draw cards until 2 treasures cards are drawn; discard the other cards
  while (treasure < 2) {
    if(pre.deckCount[currPlayer]<1){
      shuffle(currPlayer, &pre);
    }
    drawCard(currPlayer, &pre);
    newcard = pre.hand[currPlayer][(pre.handCount[currPlayer])-1];
    if (newcard == copper || newcard == silver || newcard == gold) {
      treasure++;
    } 
    else {
      temp[z] = newcard;
      pre.handCount[currPlayer]--;
      z++;
    }
  }
  while (z-1>=0){
    pre.discard[currPlayer][pre.discardCount[currPlayer]++] = temp[z-1];
    z=z-1;
  }
  
  //Check that pre and post gameStates are equivalent
  assert (r == 0);
  assert (pre.numBuys == post->numBuys);
  assert (pre.discardCount[pre.whoseTurn] == post->discardCount[pre.whoseTurn]);
  assert (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn]);
  assert (pre.deckCount[currPlayer] == post->deckCount[currPlayer]);
  return 0;
}

int main (int argc, char** argv) {

  int i, pos, player;

  struct gameState G;

  printf ("Testing Adventurer....\n");

    // Initialize the gameState with random bytes
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 255);
    }

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
    
    //Test adventurer function
    checkAdventurer(adventurer, &G, pos);
  
  printf ("End adventurer test...\n");

  return 0;
}
