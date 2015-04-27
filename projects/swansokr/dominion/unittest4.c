#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int checkUpdateCoins(int player, struct gameState *post, int bonus) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r;
  r = updateCoins(player, post, bonus);

  pre.coins += bonus;

  if (memcmp(&pre, post, sizeof(struct gameState)) == 0) {
    return 0;
  } 
  return -1;
}

void printTestResult(int r, int oldBonus, int newBonus) {
  if (r == 0) {	
    printf("PASSES with an old bonus of %d, and a new bonus of %d\n", oldBonus, newBonus);
  } else {
    printf("FAILS with an old bonus of %d, and a new bonus of %d\n", oldBonus, newBonus);
  }
}

int main () {

  int i, j, r, cop, sil, gol, player, coins, handPos[] = {-1, 0, 5, -1, 0, 5}, oldBonus[] = {0, 0, 1, 2, 0, 0}, newBonus[] = {0, 3, 0, 2, 1, 0} , numTests = 6;
  struct gameState G;
  memset(&G, 0, (sizeof(struct gameState)));
  
  printf ("\nTesting updateCoins().\n");

  player = 1;

// Check adding or removing cards from hand is done correctly
  for (i = 0; i < numTests; i++) {
    memset(&G, 0, (sizeof(struct gameState)));
    coins = cop = sil = gol = 0;
    G.handCount[player] = 0;
    for (j = 0; j < i*1.5; j++){
      if (j%2 == 0) {
        G.hand[player][j] = copper;
	coins++;
	cop++;
      } else if (j%3 == 0) {
	G.hand[player][j] = silver;
	coins += 2;
	sil++;
      } else if (j%5 == 0) {
	G.hand[player][j] = gold;
	coins += 3;
	gol++;
      } else {
	G.hand[player][j] = estate;
      }
      G.handCount[player]++;
    }
    G.coins = coins;

printf("\nHand has: %d coppers, %d silvers, %d golds, %d cards, (%d total coins in hand)\n", cop, sil, gol, G.handCount[player], coins);
    if (handPos[i] < 0) {
      printf("No change was made to the hand.\n");
    } else if (handPos[i] > G.handCount[player]) {
       G.hand[player][G.handCount[player]] = copper;
       G.handCount[player]++;
       printf("A copper was added to the hand\n");
       coins++;
    } else {
      if (G.hand[player][handPos[i]] == copper) {
        printf("A copper was discarded from the hand\n");
        coins--;
      } else if (G.hand[player][handPos[i]] == silver) {
        printf("A silver was discarded from the hand\n");
        coins -= 2;
      } else if (G.hand[player][handPos[i]] == gold) {
        printf("A gold was discarded from the hand\n");
	coins -= 3;
      } else {
        printf("An estate was discarded from the hand\n");
      }   
      discardCard(handPos[i], player, &G, 0);
    }
    updateCoins(player, &G, 0);
    if (G.coins == coins) {
      printf("PASSES with correct coin count of %d\n", G.coins);
    } else {
      printf("FAILS with incorrect coin count of %d\n", G.coins);
    }
  }

// Check bonues are added correctly
  for (i = 0; i < numTests; i++) {
    memset(&G, 0, (sizeof(struct gameState)));
    coins = cop = sil = gol = 0;
    G.handCount[player] = 0;
    for (j = 0; j < i*1.5; j++){
      if (j%2 == 0) {
        G.hand[player][j] = copper;
	coins++;
	cop++;
      } else if (j%3 == 0) {
	G.hand[player][j] = silver;
	coins += 2;
	sil++;
      } else if (j%5 == 0) {
	G.hand[player][j] = gold;
	coins += 3;
	gol++;
      } else {
	G.hand[player][j] = estate;
      }
      G.handCount[player]++;
    }
    G.coins = coins + oldBonus[i];

printf("\nHand has: %d coppers, %d silvers, %d golds, %d cards, (%d total coins in hand)\n", cop, sil, gol, G.handCount[player], coins);
    r = checkUpdateCoins(player, &G, newBonus[i]);
    printTestResult(r, oldBonus[i], newBonus[i]);
  }
 
  return 0;
}

