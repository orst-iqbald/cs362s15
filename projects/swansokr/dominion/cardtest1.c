// Test the Smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define BAD_HAND_COUNT 1
#define BAD_DECK_COUNT 2
#define BAD_DISCARD_COUNT 3
#define BAD_PLAYED_COUNT  4

int checkSmithy(int handPos, int player, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r;
  r = play_smithy(post, player, handPos);
  assert(r == 0);

  if (pre.deckCount[player] + pre.discardCount[player] < 3) {
    pre.handCount[player] += pre.deckCount[player] + pre.discardCount[player];
    pre.discardCount[player] = 0;
    pre.deckCount[player] = 0;
  } else if (pre.deckCount[player] < 3) {
    int part = pre.deckCount[player];
    pre.deckCount[player] = pre.discardCount[player];
    pre.discardCount[player] = 0;
    pre.deckCount[player] -= (3 - part);
    pre.handCount[player] += 3;
  } else {
    pre.deckCount[player] -= 3;;
    pre.handCount[player] += 3;
  }
  pre.handCount[player] -= 1;
  pre.playedCardCount += 1;

  if (pre.handCount[player] != post->handCount[player]) {
    return BAD_HAND_COUNT;
  } else if (pre.deckCount[player] != post->deckCount[player]) {
    return BAD_DECK_COUNT;
  } else if (pre.discardCount[player] != post->discardCount[player]) {
    return BAD_DISCARD_COUNT;
  } else if (pre.playedCardCount != post->playedCardCount) {
    return BAD_PLAYED_COUNT;
  }
   
  return 0;
}

void printTestResult(int r, int oldBonus, int newBonus) {
  if (r == 0) {	
    printf("PASSES with an old bonus of %d, and a new bonus of %d\n", oldBonus, newBonus);
  } else {
    printf("FAILS with an old bonus of %d, and a new bonus of %d\n", oldBonus, newBonus);
  }
}

int main () {
  int i, j, r, player, handPos[] = {0, 0, 1, 2, 0, 5}, handCount[] = {1, 1, 2, 3, 5, 10}, deckCount[] = {0, 1, 3, 5, 2, 0}, discardCount[] = {0, 1, 2, 3, 5, 10}, numTests = 6;
  struct gameState G;
  
  printf ("\nTesting Smithy card.\n");

  player = 1;
  for (i = 0; i < numTests; i++) {
    memset(&G, -1, (sizeof(struct gameState)));
    printf("\nSetup: hand %d, deck %d, discard %d, handPos %d\n", handCount[i], deckCount[i], discardCount[i], handPos[i]);
    G.handCount[player] = handCount[i];
    for (j = 0; j < handCount[i]; j++){
      G.hand[player][j] = smithy;
    }
     
    G.deckCount[player] = deckCount[i];
    for (j = 0; j < deckCount[i]; j++){
      G.deck[player][j] = copper;
    }
    
    G.discardCount[player] = discardCount[i];
    for (j = 0; j < discardCount[i]; j++){
      G.discard[player][j] = estate;
    }
  
    r = checkSmithy(handPos[i], player, &G);
    switch (r) {
      case BAD_HAND_COUNT:
        printf("FAILS because the hand count is incorrect.\n");
	break;
      case BAD_DECK_COUNT:
        printf("FAILS because the deck count is incorrect.\n");
	break;
      case BAD_DISCARD_COUNT:
        printf("FAILS because the discard count is incorrect.\n");
	break;
      case BAD_PLAYED_COUNT:
        printf("FAILS because the played card count is incorrect.\n");
	break;
      default:
	printf("PASSES.\n");
    } 
  }
 
  return 0;
}
