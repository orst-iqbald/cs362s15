#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int checkDiscardEndTurn(struct gameState *post, int player) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int i;

  endTurn(post);
  
    // Make sure player whose turn ended discards all cards in play
	// discard hand
    for (i = 0; i < pre.handCount[player]; i++) {
	pre.discardCount[player]++;
    }
    pre.handCount[player] = 0;
      // discard played cards
    for (i = 0; i < pre.playedCardCount; i++) {
	pre.discardCount[player]++;
    }
    pre.playedCardCount = 0;
    if (post->discardCount[player] != pre.discardCount[player]) {
	return -1;
    } 
    return 0;
}

int checkHandEndTurn(struct gameState *post, int player) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  endTurn(post);
  
    // Make sure the previous player drew a new hand of cards
    pre.handCount[player] = 0;
    int i;
    for (i = 0; i < 5; i++){
      drawCard(player, &pre);
    }
    assert(pre.handCount[player] == 5);
    if (pre.handCount[player] != post->handCount[player]) {
	return -1;
     }
	return 0;
}

int checkResetEndTurn(struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  endTurn(post); 

  // Make sure setup for new player is good
	// unpdate current player
    pre.whoseTurn = (pre.whoseTurn + 1) % pre.numPlayers;
	// unpdate gameState values
    pre.numActions = 1;
    pre.numBuys = 1;
    pre.phase = 0;

 if (pre.whoseTurn != post->whoseTurn || pre.numActions != post->numActions || pre.numBuys != post->numBuys || pre.phase != post->phase) {
    return -1;
  } 
  return 0;
}

int checkCoinsEndTurn(struct gameState *post, int correct) {
  
   endTurn(post); 
 
 // update coins
    if (post->coins != correct) {
	return -1;
    }
    return 0;
} 

void printCoinsTestResult(int r, int coinCount) {
  if (r == 0) {	
    printf("PASSES when coin count in hand is %d\n", coinCount);
  } else {	
    printf("FAILS when coin count in hand is %d\n", coinCount);
  }
}

void printResetTestResult(int r, int data[4]) {
  if (r == 0) {	
    printf("PASSES with old player %d, actions %d, buys %d, and phase %d\n", data[0], data[1], data[2], data[3]);
  } else {	
     printf("FAILS with old player %d, actions %d, buys %d, and phase %d\n", data[0], data[1], data[2], data[3]);
  }
}

void printHandTestResult(int r, int handCount) {
  if (r == 0) {	
    printf("PASSES with old handCount %d\n", handCount);
  } else {	
    printf("FAILS with old handCount %d\n", handCount);
  }
}

void printDiscardTestResult(int r, int handCount, int discardCount, int playedCount) {
  if (r == 0) {	
    printf("PASSES with handCount %d, discardCount %d and playedCardCount %d\n", handCount, discardCount, playedCount);
  } else {	
    printf("FAILS with handCount %d, discardCount %d and playedCardCount %d\n", handCount, discardCount, playedCount);
  }
}


int main () {

  int i, j, r, player, discardCount, handCount, playedCardCount, numTests;
  struct gameState G;
  memset(&G, 0, (sizeof(struct gameState)));
  
  printf ("\nTesting endTurn().\n");

  player = 1;
  G.numPlayers = 2;
  
  printf("\nDiscarded both hand and played cards at end of player's turn:\n"); 
  numTests = 3;
  for (i = 0; i < numTests; i++) {
  G.whoseTurn = player;
  handCount = i*5;
  G.handCount[player] = handCount;
    for (j = 0; j < G.handCount[player]; j++){
      G.hand[player][j] = 10;
    }
  discardCount = i*10;
  G.discardCount[player] = discardCount;
    for (j = 0; j < G.discardCount[player]; j++){
      G.discard[player][j] = 10;
    }
  playedCardCount = (i%2)*i;
  G.playedCardCount = playedCardCount;
    for (j = 0; j < G.playedCardCount; j++){
      G.playedCards[j] = 1;
    }
 
  r = checkDiscardEndTurn(&G, player);
  printDiscardTestResult(r, handCount, discardCount, playedCardCount);
  }

  printf("\nA new hand was drawn at the end of the player's turn:\n"); 
  numTests = 3;
  for (i = 0; i < numTests; i++) {
    G.whoseTurn = player;
    handCount = i*5;
    G.handCount[player] = handCount;
    for (j = 0; j < G.handCount[player]; j++){
      G.hand[player][j] = 10;
    }

    r = checkHandEndTurn(&G, player);
    printHandTestResult(r, handCount);
  }

  int data[4];
  printf("\nAction, buy, phase, and whoTurn values are reset:\n"); 
  numTests = 3;
  for (i = 0; i < numTests; i++) {
    data[0] = G.whoseTurn = i%2;
    data[1] = G.numActions = i*2;
    data[2] = G.numBuys = i*2;
    data[3] = G.phase = i*1;

    r = checkResetEndTurn(&G);
    printResetTestResult(r, data);
  }

  printf("\nThe money in the new player's hand was counted:\n"); 
  numTests = 3;
  int coins;
  for (i = 0; i < numTests; i++) {
    G.whoseTurn = 0;
    player = 1;
    coins = 0;
    G.deckCount[player] = 0;
    for (j = 0; j < i*3; j++){
      if (j > 4) break;
      if (j%2 == 0) {
        G.deck[player][j] = copper;
	coins++;
      } else if (j%3 == 0) {
	G.deck[player][j] = silver;
	coins += 2;
      } else {
	G.deck[player][j] = gold;
	coins += 3;
      }
      G.deckCount[player]++;
    }
    for (j = G.deckCount[player]; j < 5; j++) {
      G.deck[player][j] = estate;
      G.deckCount[player]++;
    }
    r = checkCoinsEndTurn(&G, coins);
    printCoinsTestResult(r, coins);
  }


   return 0;
}
