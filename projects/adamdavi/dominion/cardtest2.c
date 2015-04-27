/******************************************************************************
* cardtes2.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the Adventurer card within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void addAdventurer(struct gameState *state, int pos)
{
  if (pos > state->handCount[0] - 1) {
    state->hand[0][pos] = adventurer;
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
  int priorCard, postCard1, postCard2;
  int priorDiscard, postDiscard;
  int priorDeck;
  int i;

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("--------------BEGIN TESTING FOR ADVENTURER CARD-------------\n");
  printf("------------------------------------------------------------\n");

  //test play of adventure card with adventure card as last card and full deck
  //there will be no shuffle here
  //tests if last 2 cards are now treasure cards
  //tests if cards were added to discard pile
  //tests if post play hand count is correct
  //tests if adventure card was discarded after play
  addAdventurer(&G, G.handCount[0]);
  priorHand = G.handCount[0];
  priorDiscard = G.discardCount[0];
  priorCard = G.handCount[0] - 1;
  playAdventurer(&G, 0);
  postCard1 = G.hand[0][G.handCount[0] - 1];    //last card in hand
  postCard2 = G.hand[0][G.handCount[0] - 2];    //2nd to last card
  postDiscard = G.discardCount[0];
  postHand = G.handCount[0];

  if ( postCard1 == copper || postCard1 == silver || postCard1 == gold ) {
    printf("Adventurer: PASS -> Test adventurer last card in hand: last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer last card in hand: last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postCard2 == copper || postCard2 == silver || postCard2 == gold ) {
    printf("Adventurer: PASS -> Test adventurer last card in hand: 2nd to last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer last card in hand: 2nd to last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postDiscard > priorDiscard ) {
    printf("Adventurer: PASS -> Test adventurer last card in hand: cards were discarded.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer last card in hand: no cards were discarded.\n\n");
    totalFail++;
  }    

  if ( postHand == (priorHand + 1) ) {
    printf("Adventurer: PASS -> Test adventurer last card in hand: hand count went up 1.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer last card in hand: hand count did not increase correctly.\n\n");
    totalFail++;
  }    

  if ( G.hand[0][priorCard] != adventurer ) {
    printf("Adventurer: PASS -> Test adventurer last card in hand: adventurer was discarded from hand.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer last card in hand: adventurer was not discarded from hand.\n\n");
    totalFail++;
  }    

  //test play of adventure card with adventure card as only card in hand
  //there will be no shuffle here
  //tests if last 2 cards are now treasure cards
  //tests if cards were added to discard pile
  //tests if post play hand count is correct
  //tests if adventure card was discarded after play
  initializeGame(2, k, seed, &G);
  addAdventurer(&G, G.handCount[0]);
  G.handCount[0] = 1;
  priorDiscard = G.discardCount[0];
  playAdventurer(&G, 0);
  postCard1 = G.hand[0][G.handCount[0] - 1];    //last card in hand
  postCard2 = G.hand[0][G.handCount[0] - 2];    //2nd to last card
  postDiscard = G.discardCount[0];
  postHand = G.handCount[0];
  
  if ( postCard1 == copper || postCard1 == silver || postCard1 == gold ) {
    printf("Adventurer: PASS -> Test adventurer only card in hand: last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer only card in hand: last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postCard2 == copper || postCard2 == silver || postCard2 == gold ) {
    printf("Adventurer: PASS -> Test adventurer only card in hand: 2nd to last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer only card in hand: 2nd to last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postDiscard > priorDiscard ) {
    printf("Adventurer: PASS -> Test adventurer only card in hand: cards were discarded.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer only card in hand: no cards were discarded.\n\n");
    totalFail++;
  }    

  if ( postHand == (priorHand + 1) ) {
    printf("Adventurer: PASS -> Test adventurer only card in hand: hand count went up 1.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer only card in hand: hand count did not increase correctly.\n\n");
    totalFail++;
  }    

  if ( G.hand[0][0] != adventurer ) {
    printf("Adventurer: PASS -> Test adventurer only card in hand: adventurer was discarded from hand.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer only card in hand: adventurer was not discarded from hand.\n\n");
    totalFail++;
  }    

  //test when deck is empty
  //shuffle has to happen here
  initializeGame(2, k, seed, &G);
  //add deck to discard pile
  priorDeck = G.deckCount[0];
  for (i = 0; i < priorDeck; i++) {
    G.discard[0][G.discardCount[0]] = G.deck[0][i];
    G.deckCount[0]--;
    G.discardCount[0]++;
  }
  addAdventurer(&G, G.handCount[0]);
  //deck is now 0 and addventurer is in hand
  priorHand = G.handCount[0];
  priorDiscard = G.discardCount[0];
  priorCard = G.handCount[0] - 1;
  playAdventurer(&G, 0);
  postCard1 = G.hand[0][G.handCount[0] - 1];    //last card in hand
  postCard2 = G.hand[0][G.handCount[0] - 2];    //2nd to last card
  postDiscard = G.discardCount[0];
  postHand = G.handCount[0];
  
  if ( postCard1 == copper || postCard1 == silver || postCard1 == gold ) {
    printf("Adventurer: PASS -> Test adventurer deck empty: last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer deck empty: last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postCard2 == copper || postCard2 == silver || postCard2 == gold ) {
    printf("Adventurer: PASS -> Test adventurer deck empty: 2nd to last card is now a treasure card.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer deck empty: 2nd to last card is not a treasure card.\n\n");
    totalFail++;
  }  

  if ( postDiscard > priorDiscard ) {
    printf("Adventurer: PASS -> Test adventurer deck empty: cards were discarded.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer deck empty: no cards were discarded.\n\n");
    totalFail++;
  }    

  if ( postHand == (priorHand + 1) ) {
    printf("Adventurer: PASS -> Test adventurer deck empty: hand count went up 1.\n\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer deck empty: hand count did not increase correctly.\n\n");
    totalFail++;
  }    

  if ( G.hand[0][priorCard] != adventurer ) {
    printf("Adventurer: PASS -> Test adventurer deck empty: adventurer was discarded from hand.\n");
    totalPass++;
  }
  else {
    printf("Adventurer: FAIL -> Test adventurer deck empty: adventurer was not discarded from hand.\n");
    totalFail++;
  }    

  printf("------------------------------------------------------------\n");
  printf("-------------RESULTS of Adventurer card testing-------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
