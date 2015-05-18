// Test the Sea Hag card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define BAD_HAND_COUNT 1
#define BAD_DECK_COUNT 2
#define BAD_OTHER_DD 3
#define BAD_PLAYED_COUNT 4
#define NO_CURSE 6
#define WRONG_CURSE 7

int checkSeaHag(int handPos, int player, int otherP, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  
  int deckPlusDiscard = post->deckCount[otherP] + post->discardCount[otherP];
  int r = sea_hagCardEffect(post);
  assert(r == 0);

  //Played cards and current player hand
  pre.handCount[player]--;
  pre.playedCardCount++;

  //Other player deck and discard (may need to shuffle discard)
  deckPlusDiscard++;

  // Check top of other player's deck
  if (post->deck[otherP][post->deckCount[otherP] - 1] != curse) {
    return NO_CURSE;
  }
  //Check other conditions
  if (deckPlusDiscard != post->deckCount[otherP] + post->discardCount[otherP]){
    return BAD_OTHER_DD;
  }
  if (pre.playedCardCount != post->playedCardCount) {
    return BAD_PLAYED_COUNT;
  }
  if (pre.handCount[player] != post->handCount[player]) {
    return BAD_HAND_COUNT;
  }
  if (post->deck[player][post->deckCount[player] - 1] == curse) {
    return WRONG_CURSE;
  } 
  if (pre.deckCount[player] != post->deckCount[player]) {
    return BAD_DECK_COUNT;
  }
  return 0;
}

void printTestResult(int r) {
    switch (r) {
      case BAD_HAND_COUNT:
        printf("FAILS because the player'ss hand count is incorrect.\n");
	break;
      case BAD_DECK_COUNT:
        printf("FAILS because the player's deck count is incorrect.\n");
	break;
      case BAD_OTHER_DD:
        printf("FAILS because the deck or discard of the other player is incorrect.\n");
	break;
      case NO_CURSE:
        printf("FAILS because the other player does not have a curse on their deck.\n");
	break;
      case WRONG_CURSE:
        printf("FAILS because player of the Sea Hag has a curse on their deck.\n");
	break;
      case BAD_PLAYED_COUNT:
        printf("FAILS because the played card count is incorrect.\n");
	break;
      default:
	printf("PASSES.\n");
    } 

}

int main () {
  int i, j, r, player, otherP, handPos[] = {0, 0, 1, 2, 0, 5}, handCount[] = {10, 1, 2, 3, 5, 10}, deckCount[] = {0, 0, 1, 2, 5, 10}, discardCount[] = {1, 0, 2, 3, 5, 10}, numTests = 6;
  struct gameState G;
  
  printf ("\nTesting Sea Hag card.\n");

  player = 1;
  otherP = 0;
  for (i = 0; i < numTests; i++) {
    memset(&G, -1, (sizeof(struct gameState)));
    printf("\nSetup (both players): hand %d, deck %d, discard %d, handPos %d\n", handCount[i], deckCount[i], discardCount[i], handPos[i]);

    G.numPlayers = 2;
    G.whoseTurn = player;
    G.playedCardCount = i/2;
    G.handCount[player] = handCount[i];
    G.handCount[otherP] = handCount[i];
    for (j = 0; j < handCount[i]; j++){
      G.hand[player][j] = sea_hag;
      G.hand[otherP][j] = estate;   
    }

    G.deckCount[player] = deckCount[i];
    G.deckCount[otherP] = deckCount[i];
    for (j = 0; j < deckCount[i]; j++){
      G.deck[player][j] = copper;
      G.deck[otherP][j] = copper;
    }

    G.discardCount[player] = discardCount[i];
    G.discardCount[otherP] = discardCount[i];
    for (j = 0; j < discardCount[i]; j++){
      G.discard[player][j] = estate;
      G.discard[otherP][j] = estate;
    }
  
    r = checkSeaHag(handPos[i], player, otherP, &G);
    printTestResult(r);
  }
 
  return 0;
}

