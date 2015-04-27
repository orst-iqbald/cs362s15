#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

int getPoints(int card, int totalCards) {
  if (card == curse) {
    printf("curse, ");
    return -1;
  }
  if (card == estate) {
    printf("estate, ");
    return 1;
  }
  if (card == duchy) {
    printf("duchy, ");
    return 3;
  }
  if (card == province) {
    printf("province, ");
    return 6;
  }
  if (card == great_hall) {
    printf("great_hall, ");
    return 1;
  }
  if (card == gardens) {
    printf("gardens ");
    return (totalCards/10);
  }

  return 0;
}

void printTestResult(int correctScore, int calcScore) {
  if (correctScore == calcScore) {	
    printf("\nPASSES with score of %d\n\n", correctScore);
  } else {
    printf("\nFAILS with correct score %d and calculated score %d\n\n", correctScore, calcScore);
  }
}

int main () {

  int i, j, r, player, handIndex = -1, discardIndex = -1, deckIndex = -1, totalCards = 0, score = 0, numTests = 13;
  int handC[] = {0, 1, 1, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0}, discardC[] = {0, 0, 0, 0, 3, 1, 1, 1, 1, 1, 0, 0, 0}, deckC[] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 1, 1}, cards[] = {curse, estate, duchy, province, great_hall, gardens}; 
  struct gameState G;
 
  printf ("Testing scoreFor().\n\n");

  player = 1;
  for (i = 0; i < numTests; i++) {
    printf("Test# %d. Parameters:", i+1);
    memset(&G, -1, (sizeof(struct gameState)));
    score = 0;
    printf("\nIn hand: ");
    G.handCount[player] = 0;
    for (j = 0; j < handC[i]; j++) {
      if (j == 0) handIndex++;
      G.handCount[player]++;
      G.hand[player][j] = cards[handIndex];
      if (cards[handIndex] == gardens) {
	if ((i % 2 == 0)) {
	  totalCards = 25;
	  G.handCount[player] = totalCards;
	} else {
	  totalCards = 40;
	  G.handCount[player] = totalCards;
	}
	printf("(score should be %d) ", totalCards/10);
      }
      score += getPoints(cards[handIndex], totalCards);
    }
    printf("\nIn discard: ");
    G.discardCount[player] = 0;
    for (j = 0; j < discardC[i]; j++) {
      if (j == 0) discardIndex++; 
      G.discardCount[player]++;
      G.discard[player][j] = cards[discardIndex];
      if (cards[discardIndex] == gardens) {
	if ((i % 2 == 0)) {
	  totalCards = 25;
	  G.discardCount[player] = totalCards;
	} else { 
	  totalCards = 40;
	  G.discardCount[player] = totalCards;
	}
	printf("(score should be %d) ", totalCards/10);
      }
      score += getPoints(cards[discardIndex], totalCards);
    }
    printf("\nIn deck: ");
    G.deckCount[player] = 0;
    for (j = 0; j < deckC[i]; j++) {
      if (j == 0) deckIndex++;
      G.deckCount[player]++;
      G.deck[player][j] = cards[deckIndex];
      if (cards[deckIndex] == gardens) {
	if ((i % 2 == 0)) {
	  totalCards = 25;
 	  G.deckCount[player] = totalCards;
        } else {
	  totalCards = 40;
	  G.deckCount[player] = totalCards;
	}
	printf("(score should be %d), ", totalCards/10);
      }
      score += getPoints(cards[deckIndex], totalCards);
    }
   r = scoreFor(player, &G);
   printTestResult(score, r);
  }
  return 0;
}
