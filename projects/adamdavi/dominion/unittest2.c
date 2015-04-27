/******************************************************************************
* unittest2.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the discardCard() function within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void setupHand(struct gameState *state, int *cards)
{
  int i;
  state->handCount[0] = 8;
  state->discardCount[0] = 1;
  state->discard[0][0] = 6;

  for (i = 0; i < state->handCount[0]; i++) {
    state->hand[0][i] = cards[i];
  }
}

int main()
{
  int totalFail = 0;
  int totalPass = 0;
  int seed = -1;

  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

  int priorHand, postHand;
  int priorCard, postCard;
  int priorDiscard, postDiscard;
  int testPos;

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("---------------BEGIN TESTING FOR discardCard()--------------\n");
  printf("------------------------------------------------------------\n");

  //test out of bounds current player
  if (discardCard(0, MAX_PLAYERS + 1, &G, 0) != 0) {
    printf("discardCard(): PASS -> handles out of bounds player.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> does not return error for out of bounds player.\n\n");
    totalFail++;    
  }

  //test out of bounds hand pos
  if (discardCard(MAX_HAND + 1, 0, &G, 0) != 0) {
    printf("discardCard(): PASS -> handles out of bounds hand position.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> does not return error for out of bounds hand position.\n\n");
    totalFail++;    
  }

  //test discard card with trash flag set to 1 = trash card
  setupHand(&G, k);
  testPos = 5;
  priorHand = G.handCount[0];
  priorCard = G.hand[0][testPos];
  priorDiscard = G.discardCount[0];
  discardCard(testPos, 0, &G, 1);
  postHand = G.handCount[0];
  postCard = G.hand[0][testPos];
  postDiscard = G.discardCount[0];

  if ( postHand == (priorHand - 1) ) {
    printf("discardCard(): PASS -> Test trash = 1: decrased hand count correctly to show removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 1: did not decrease hand count to show removed card.\n\n");
    totalFail++;    
  }

  if ( priorCard != postCard ) {
    printf("discardCard(): PASS -> Test trash = 1: correctly replaced removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 1: did not replace removed card.\n\n");
    totalFail++;    
  }

  if ( postDiscard != (priorDiscard + 1) ) {
    printf("discardCard(): PASS -> Test trash = 1: correctly did not increase discard count.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 1: incorrectly increased discard count.\n\n");
    totalFail++;
  }

  if ( G.discard[0][priorDiscard - 1] == G.discard[0][postDiscard - 1] ) {
    printf("discardCard(): PASS -> Test trash = 1: card was not added to discard pile.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 1: card was incorrectly added to discard pile.\n\n");
    totalFail++;    
  }

  //test discard card with trash flag set to 0 = just discard card
  setupHand(&G, k);
  testPos = 5;
  priorHand = G.handCount[0];
  priorCard = G.hand[0][testPos];
  priorDiscard = G.discardCount[0];
  discardCard(testPos, 0, &G, 0);
  postHand = G.handCount[0];
  postCard = G.hand[0][testPos];
  postDiscard = G.discardCount[0];

  if ( postHand == (priorHand - 1) ) {
    printf("discardCard(): PASS -> Test trash = 0: decrased hand count correctly to show removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 0: did not decrease hand count to show removed card.\n\n");
    totalFail++;    
  }

  if ( priorCard != postCard ) {
    printf("discardCard(): PASS -> Test trash = 0: correctly replaced removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 0: did not replace removed card.\n\n");
    totalFail++;    
  }

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("discardCard(): PASS -> Test trash = 0: correctly increased discard count.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 0: did not increase discard count.\n\n");
    totalFail++;
  }

  if ( G.discard[0][priorDiscard - 1] != G.discard[0][postDiscard - 1] ) {
    printf("discardCard(): PASS -> Test trash = 0: card was correctly added to discard pile.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Test trash = 0: card was not added to discard pile.\n\n");
    totalFail++;    
  }

  //test discard hand position last card in hand
  setupHand(&G, k);
  testPos = G.handCount[0] - 1;
  priorHand = G.handCount[0];
  priorCard = G.hand[0][testPos];
  priorDiscard = G.discardCount[0];
  discardCard(testPos, 0, &G, 0);
  postHand = G.handCount[0];
  postCard = G.hand[0][testPos];
  postDiscard = G.discardCount[0];

  if ( postHand == (priorHand - 1) ) {
    printf("discardCard(): PASS -> Discard last card in hand: decreased hand count correctly.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard last card in hand: did not decrease hand count.\n\n");
    totalFail++;    
  }

  if ( priorCard != postCard ) {
    printf("discardCard(): PASS -> Discard last card in hand: correctly replaced removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard last card in hand: did not replace removed card.\n\n");
    totalFail++;    
  }

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("discardCard(): PASS -> Discard last card in hand: correctly increased discard count.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard last card in hand: did not increase discard count.\n\n");
    totalFail++;
  }

  if ( G.discard[0][priorDiscard - 1] != G.discard[0][postDiscard - 1] ) {
    printf("discardCard(): PASS -> Discard last card in hand: card was correctly added to discard pile.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard last card in hand: card was not added to discard pile.\n\n");
    totalFail++;    
  }

  //test discard hand position only 1 card in hand
  G.handCount[0] = 1;
  G.hand[0][0] = 6;
  testPos = G.handCount[0] - 1;
  priorHand = G.handCount[0];
  priorCard = G.hand[0][testPos];
  priorDiscard = G.discardCount[0];
  discardCard(testPos, 0, &G, 0);
  postHand = G.handCount[0];
  postCard = G.hand[0][testPos];
  postDiscard = G.discardCount[0];

  if ( postHand == (priorHand - 1) ) {
    printf("discardCard(): PASS -> Discard only card in hand: decreased hand count correctly.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard only card in hand: did not decrease hand count.\n\n");
    totalFail++;    
  }

  if ( priorCard != postCard ) {
    printf("discardCard(): PASS -> Discard only card in hand: correctly replaced removed card.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard only card in hand: did not replace removed card.\n\n");
    totalFail++;    
  }

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("discardCard(): PASS -> Discard only card in hand: correctly increased discard count.\n\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard only card in hand: did not increase discard count.\n\n");
    totalFail++;
  }

  if ( G.discard[0][priorDiscard - 1] != G.discard[0][postDiscard - 1] ) {
    printf("discardCard(): PASS -> Discard only card in hand: card was correctly added to discard pile.\n");
    totalPass++;
  }
  else {
    printf("discardCard(): FAIL -> Discard only card in hand: card was not added to discard pile.\n");
    totalFail++;    
  }

  printf("------------------------------------------------------------\n");
  printf("--------------RESULTS of discardCard() testing--------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
