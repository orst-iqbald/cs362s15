// Test the Cutpurse card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define BAD_HAND_COUNT 1
#define BAD_COIN_COUNT 2
#define BAD_OTHER_HAND 3
#define BAD_PLAYED_COUNT  4
#define BAD_OTHER_DISCARD 5

int checkCutpurse(int handPos, int player, int otherP, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r = cutpurseEffect(cutpurse, 0, 0, 0, post, handPos, 0);
  assert(r == 0);

  //Played cards and current player hand
  pre.handCount[player]--;
  pre.playedCardCount++;

  //Other player hand and discard
  int i, subHand = 0, coppers = 0;
  for (i = 0; i < pre.handCount[otherP]; i++){
    if (pre.hand[otherP][i] == copper) {
      subHand = 1;
      coppers++;
    }
  }
  assert(subHand <= coppers);
  pre.handCount[otherP] -= subHand;
  pre.discardCount[otherP] += subHand;
  coppers -= subHand; 
 
  // Coins
  pre.coins += 2;

  // Check conditions
  if (pre.handCount[otherP] != post->handCount[otherP]){
    return BAD_OTHER_HAND;
  }
  if (pre.discardCount[otherP] != post->discardCount[otherP]){
    return BAD_OTHER_DISCARD;
  }

  for (i = 0; i < post->handCount[otherP]; i++){
    if (post->hand[otherP][i] == copper) {
      coppers--;
    }
  }
  if (coppers != 0) {
    return BAD_OTHER_HAND;
  }
  if (pre.coins != post->coins) {
    return BAD_COIN_COUNT;
  }
  if (pre.playedCardCount != post->playedCardCount) {
    return BAD_PLAYED_COUNT;
  }
  if (pre.handCount[player] != post->handCount[player]) {
    return BAD_HAND_COUNT;
  }
   
  return 0;
}

void printTestResult(int r) {
    switch (r) {
      case BAD_HAND_COUNT:
        printf("FAILS because the hand count is incorrect.\n");
	break;
      case BAD_COIN_COUNT:
        printf("FAILS because the coin count is incorrect.\n");
	break;
      case BAD_OTHER_HAND:
        printf("FAILS because the hand of the other player is incorrect.\n");
	break;
      case BAD_OTHER_DISCARD:
        printf("FAILS because the discard count of the other player is incorrect.\n");
	break;
      case BAD_PLAYED_COUNT:
        printf("FAILS because the played card count is incorrect.\n");
	break;
      default:
	printf("PASSES.\n");
    } 

}

int main () {
  int i, j, r, player, otherP, coppers, handPos[] = {0, 0, 1, 2, 0, 5}, handCount[] = {10, 1, 2, 3, 5, 10}, discardCount[] = {1, 0, 2, 3, 5, 10}, numTests = 6;
  struct gameState G;
  
  printf ("\nTesting Cutpurse card.\n");

  player = 1;
  otherP = 0;
  for (i = 0; i < numTests; i++) {
    memset(&G, -1, (sizeof(struct gameState)));
    printf("\nSetup: hand (both players) %d, discard %d, handPos %d, ", handCount[i], discardCount[i], handPos[i]);

    G.numPlayers = 2;
    G.whoseTurn = player;
    G.handCount[player] = handCount[i];
    G.coins = 0;
    G.handCount[otherP] = handCount[i];
    coppers = 0;
    for (j = 0; j < handCount[i]; j++){
      G.hand[player][j] = cutpurse;
      if (j % 4 == 0) G.hand[otherP][j] = gold;
      else if (j % 3 == 0) {
	coppers++;
        G.hand[otherP][j] = copper;
      }
      else if (j % 2 == 0) G.hand[otherP][j] = silver;
      else G.hand[otherP][j] = estate;   
    }
    printf("coppers (other player) %d\n", coppers);

    G.discardCount[player] = discardCount[i];
    G.discardCount[otherP] = discardCount[i];
    for (j = 0; j < discardCount[i]; j++){
      G.discard[player][j] = estate;
      G.discard[otherP][j] = estate;
    }
  
    r = checkCutpurse(handPos[i], player, otherP, &G);
    printTestResult(r);
  }
 
  return 0;
}

