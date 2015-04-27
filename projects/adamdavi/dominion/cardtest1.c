/******************************************************************************
* cardtes1.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the Smithy card within the dominion.c file. 
******************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void addSmithy(struct gameState *state, int pos)
{
  if (pos > state->handCount[0] - 1) {
    state->hand[0][pos] = smithy;
    state->handCount[0]++;
  }
  else {
    state->hand[0][pos] = smithy;
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
  int priorCard;
  int priorDiscard, postDiscard;
  int priorDeck, postDeck;

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("----------------BEGIN TESTING FOR SMITHY CARD---------------\n");
  printf("------------------------------------------------------------\n");

  //test that 3 cards have been added to hand (and -1 for Smithy discard)
  //test that 3 cards came from the deck
  //test that smithy is removed when last card
  addSmithy(&G, G.handCount[0]);    //add smithy as last card in hand
  priorHand = G.handCount[0];
  priorDeck = G.deckCount[0];
  priorCard = G.hand[0][G.handCount[0] - 1];
  playSmithy(&G, 0, G.handCount[0] - 1);
  postHand = G.handCount[0];
  postDeck = G.deckCount[0];

  if ( postHand == (priorHand + 2) ) {
    printf("Smithy: PASS -> Correct number of cards in hand after play of Smithy.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Incorrect number of cards in hand after play of Smithy.\n\n");
    totalFail++;
  }

  if ( postDeck == (priorDeck - 3) ) {
    printf("Smithy: PASS -> Deck lost 3 cards after play of Smithy.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Deck did not lose 3 cards after play of Smithy.\n\n");
    totalFail++;
  }

  if ( G.hand[0][priorCard] != smithy ) {
    printf("Smithy: PASS -> Test Smithy last card: correctly removed from hand after play.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Test Smithy last card: not removed from hand after play.\n\n");
    totalFail++;
  }

  //test that smithy card is removed from hand when 1st card
  addSmithy(&G, 0);
  playSmithy(&G, 0, 0);

  if ( G.hand[0][0] != smithy ) {
    printf("Smithy: PASS -> Test Smithy first card: correctly removed from hand after play.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Test Smithy first card: not removed from hand after play.\n\n");
    totalFail++;
  }

  //test that smithy is removed when middle card
  addSmithy(&G, 3);
  playSmithy(&G, 0, 3);

  if ( G.hand[0][3] != smithy ) {
    printf("Smithy: PASS -> Test Smithy middle card: correctly removed from hand after play.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Test Smithy middle card: not removed from hand after play.\n\n");
    totalFail++;
  }

  //test smithy is removed when only card
  addSmithy(&G, 0);
  G.handCount[0] = 1;
  playSmithy(&G, 0, 0);

  if ( G.hand[0][0] != smithy ) {
    printf("Smithy: PASS -> Test Smithy only card: correctly removed from hand after play.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Test Smithy only card: not removed from hand after play.\n\n");
    totalFail++;
  }

  //test that smithy has been put in discard pile
  //test that discard count is right
  initializeGame(2, k, seed, &G);
  addSmithy(&G, G.handCount[0]);    //add smithy to end
  priorDiscard = G.discardCount[0];
  playSmithy(&G, 0, G.handCount[0] - 1);
  postDiscard = G.discardCount[0];

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("Smithy: PASS -> Discard count was incremented correctly.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Discard count was not incremented to show Smithy discard.\n\n");
    totalFail++;
  }

  if ( G.discard[0][G.discardCount[0] - 1] == smithy ) {
    printf("Smithy: PASS -> Smithy was placed in discard pile correctly.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Smithy was not placed in discard pile.\n\n");
    totalFail++;
  }

  //check that 0 is returned
  addSmithy(&G, G.handCount[0]);

  if ( playSmithy(&G, 0, G.handCount[0] - 1) == 0 ) {
    printf("Smithy: PASS -> Smithy returned 0 after play.\n\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Smithy did not return 0 after play.\n\n");
    totalFail++;
  }

  //test function when smithy is not in pos passed in
  if ( playSmithy(&G, 0, G.handCount[0] - 1) == -1 ) {
    printf("Smithy: PASS -> Card passed in is not a Smithy, correctly returned -1.\n");
    totalPass++;
  }
  else {
    printf("Smithy: FAIL -> Card passed in was not a Smithy, did not return -1.\n");
    totalFail++;
  }

  printf("------------------------------------------------------------\n");
  printf("---------------RESULTS of Smithy card testing---------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
