// Test the Adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

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
  int i, j, r, rCard, player, playedC, copCk, copCs, silCk, silCs, goldCk, goldCs, handC, deckC, discardC, handPos;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G;
  
  int numTests = 100;
  if (argc == 2) numTests = atoi(argv[1]);
  printf ("\nRandom testing of Adventurer card.\n");

  srand(time(0));
  for (i = 0; i < numTests; i++) {

    initializeGame(2, k, 1, &G);
    goldCk = silCk = copCk = 0;
    goldCs = silCs = copCs = 0;

    player = G.whoseTurn = rand() % 2;
    playedC = G.playedCardCount = rand() % 3;
    handC = G.handCount[player] = randCount(1, MAX_HAND);
    for (j = 0; j < handC; j++){
      G.hand[player][j] = rand() % (treasure_map + 1);
    }
     
    deckC = G.deckCount[player] = randCount(0, MAX_DECK);
    for (j = 0; j < deckC; j++){
      rCard = rand() % 6;
      if (rCard == 0) {
	G.deck[player][j] = gold;
	goldCk++;
      }
      else if (rCard == 1) {
	G.deck[player][j] = silver;
	silCk++;
      }
      else if (rCard == 2) {
	G.deck[player][j] = copper;
	copCk++;
      }
      else G.deck[player][j] = rand() % (treasure_map + 1);
    }
    
    discardC = G.discardCount[player] = randCount(0, MAX_DECK);
    for (j = 0; j < discardC; j++){
      rCard = rand() % 6;
      if (rCard == 0) {
	G.discard[player][j] = gold;
	goldCs++;
      }
      else if (rCard == 1) {
	G.discard[player][j] = silver;
	silCs++;
      }
      else if (rCard == 2) {
	G.discard[player][j] = copper;
	copCs++;
      }
      else G.discard[player][j] = rand() % (treasure_map + 1);
    }

    if (handC < 1) handPos = 0;
    else {
      handPos = rand() % handC;
      G.hand[player][handPos] = adventurer;
    }
    printf("\nTest #%d setup:\n\tDeck total %d (gold %d silver %d copper %d)\n\tDiscard total %d (gold %d silver %d copper %d)\n\tHand total %d, handPos %d\n\tPlayer %d\n\tOriginal played card count %d\n", i+1, deckC, goldCk, silCk, copCk, discardC, goldCs, silCs, copCs, handC, handPos, player, playedC);
  
    r = checkAdventurer(handPos, player, &G);
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

