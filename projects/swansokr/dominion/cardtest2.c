// Test the Adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define BAD_HAND_COUNT 1
#define BAD_DECK_COUNT 2
#define BAD_PLAYED_COUNT  4

int checkAdventurer(int handPos, int player, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r, temphand[MAX_DECK];
  r = play_adventurer(post, player, handPos, temphand);
  assert(r == 0);

  int i, count = 0, deckPlusDiscard;

  deckPlusDiscard = pre.deckCount[player] + pre.discardCount[player];

  for (i = pre.deckCount[player] - 1; i >= 0; i--){
    if (pre.deck[player][i] == copper || pre.deck[player][i] == silver || pre.deck[player][i] == gold) count++;
    if (count == 2) break;
  }
  if (count < 2) {
    for (i = pre.discardCount[player] - 1; i >= 0; i--){
      if (pre.discard[player][i] == copper || pre.discard[player][i] == silver || pre.discard[player][i] == gold) count++;
    if (count == 2) break;
    }
  }
  pre.handCount[player] += count; 
  pre.handCount[player]--;
  pre.playedCardCount++;  
  deckPlusDiscard -= count;

  if (deckPlusDiscard != post->deckCount[player] + post->discardCount[player]) {
    return BAD_DECK_COUNT;
 } else if (pre.playedCardCount != post->playedCardCount) {
    return BAD_PLAYED_COUNT;
  } else if (pre.handCount[player] != post->handCount[player]) {
    return BAD_HAND_COUNT;
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
  int i, j, r, player, handPos[] = {0, 0, 1, 2, 0, 5}, handCount[] = {10, 1, 2, 3, 5, 10}, deckCount[] = {0, 1, 0, 5, 2, 0}, discardCount[] = {1, 0, 2, 3, 5, 10}, numTests = 6;
  struct gameState G;
  
  printf ("\nTesting Adventurer card.\n");

  player = 1;
  for (i = 0; i < numTests; i++) {
    memset(&G, -1, (sizeof(struct gameState)));
    printf("\nSetup: hand %d, deck %d, discard %d, handPos %d\n", handCount[i], deckCount[i], discardCount[i], handPos[i]);
    G.handCount[player] = handCount[i];
    for (j = 0; j < handCount[i]; j++){
      G.hand[player][j] = adventurer;
    }
     
    G.deckCount[player] = deckCount[i];
    for (j = 0; j < deckCount[i]; j++){
      if (j % 4 == 0) G.deck[player][j] = gold;
      else if (j % 3 == 0) G.deck[player][j] = silver;
      else if (j % 2 == 0) G.deck[player][j] = copper;
      else G.deck[player][j] = estate;
    }
    
    G.discardCount[player] = discardCount[i];
    for (j = 0; j < discardCount[i]; j++){
      if (j % 4 == 0) G.discard[player][j] = gold;
      else if (j % 3 == 0) G.discard[player][j] = silver;
      else if (j % 2 == 0) G.discard[player][j] = copper;
      else G.discard[player][j] = estate;
    }
  
    r = checkAdventurer(handPos[i], player, &G);
    switch (r) {
      case BAD_HAND_COUNT:
        printf("FAILS because the hand count is incorrect.\n");
	break;
      case BAD_DECK_COUNT:
        printf("FAILS because the deck count is incorrect.\n");
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

