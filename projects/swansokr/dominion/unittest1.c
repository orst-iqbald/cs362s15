#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int checkDiscardCard(int handPos, int player, struct gameState *post, int trashFlag) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r;
   
  r = discardCard(handPos, player, post, trashFlag);

  if (pre.handCount[player] > 0) {
    if (trashFlag == 0) {
       pre.playedCards[pre.playedCardCount] = pre.hand[player][handPos];
       pre.playedCardCount++;
    }   
    pre.handCount[player]--;
   
    pre.hand[player][handPos] = pre.hand[player][pre.handCount[player]];
    pre.hand[player][pre.handCount[player]] = post->hand[player][post->handCount[player]];
  }

/*  assert(r == 0);
  assert(pre.handCount[player] == post->handCount[player]);
  assert(pre.playedCardCount == post->playedCardCount);
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
*/
  if (memcmp(&pre, post, sizeof(struct gameState)) == 0) {
    return 0;
  } 
  return -1;
}

void printTestResult(int r, int handCount, int handPos, int discardCount, int trash) {
  if (r == 0) {	
    printf("PASSES with handCount %d, handPos %d, discardCount %d and trashFlag %d\n", handCount, handPos, discardCount, trash);
  } else {
    printf("FAILS with handCount %d, handPos %d, discardCount %d and trashFlag %d\n", handCount, handPos, discardCount, trash);
  }
}

int main () {

  int i, j, r, player, discardCount, handCount, numTests = 8;
  int hands[] = {0, 0, 1, 1, 5, 5, 10, 10}, discards[] = {0, 10, 0, 5, 1, 5, 0, 1}, pos[] = {0, 0, 0, 1, 0, 4, 0, 2}, trash[] = {0, 1, 0, 1, 0, 1, 0, 1}; 
  struct gameState G;
  memset(&G, 0, (sizeof(struct gameState)));
  
  printf ("Testing discardCard().\n");

  player = 1;
  for (i = 0; i < numTests; i++) {
    memset(&G, 0, (sizeof(struct gameState)));

    discardCount = discards[i];
    for (j = 0; j < discardCount; j++){
      G.discard[player][j] = j+1;
    }
    G.discardCount[player] = discardCount;

    handCount = hands[i];;
    for (j = 0; j < handCount; j++){
      G.hand[player][j] = j*2;
    }
    G.handCount[player] = handCount;
    
    r = checkDiscardCard(pos[i], player, &G, trash[i]);
    printTestResult(r, handCount, pos[i], discardCount, trash[i]);
  }
  return 0;
}
