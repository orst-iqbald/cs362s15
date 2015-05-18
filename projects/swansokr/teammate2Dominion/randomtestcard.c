// Test the Cutpurse card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

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

int randCount(int min, int max) {
  switch (rand() % 3) {
    case 0:
      return min;
    case 1:
      if (min < max)
        return min + 1;
      else
        return min;
    default:
      return (rand() % (max - min + 1)) + min;
  }
}

int main (int argc, char* argv[] ) {
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
 
  int i, j, r, rCard, player, otherP, coppers, handC, handPos, discardC;
  struct gameState G;
   
  int numTests = 100;
  if (argc == 2) numTests = atoi(argv[1]);
  
  printf ("\nTesting Cutpurse card.\n");

  srand(time(0));
  for (i = 0; i < numTests; i++) {
    initializeGame(2, k, 1, &G);
    player = G.whoseTurn = rand() % 2;
    otherP = (player + 1) % 2;

    coppers = 0;
    handC = G.handCount[otherP] = G.handCount[player] = randCount(1, MAX_HAND);
    for (j = 0; j < handC; j++){
      G.hand[player][j] = rand() % (treasure_map + 1);
      rCard = rand() % 3;
      if (rCard == 0) {
	coppers++;
        G.hand[otherP][j] = copper;
      }
      else G.hand[otherP][j] = rand() % (treasure_map + 1);
    }
    G.coins = updateCoins(player, &G, 0);;   

    discardC = G.discardCount[otherP] = G.discardCount[player] = randCount(0, MAX_DECK);
    for (j = 0; j < discardC; j++){
      G.discard[player][j] = rand() % (treasure_map + 1);
      G.discard[otherP][j] = rand() % (treasure_map + 1);
    }
 
    if (handC < 1) handPos = 0;
    else {
      handPos = rand() % handC;
      G.hand[player][handPos] = cutpurse;
    }
    printf("\nTest #%d setup: \n\tHand count (both players) %d\n\tCoppers in other player's hand %d\n\tDiscard count (both players) %d\n\tHandPos %d\n\tCurrent player %d\n", i+1, handC, coppers, discardC, handPos, player);
  
    r = checkCutpurse(handPos, player, otherP, &G);
    printTestResult(r);
  }
 
  return 0;
}

