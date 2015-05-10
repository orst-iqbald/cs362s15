/******************************************************************************
* randomtestcard.c
* David Adams
* CS 362
* Spring 2015
* Assignment 4
* This file has been added for Assignment 4 in order to provide random tests
* for the Adventurer Card within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//returns the number of tests passed
int testAdventurer(struct gameState *state, int pos)
{
  int priorHand, postHand;
  int priorDiscard, postDiscard;
  int postCard1, postCard2;
  int testsPassed = 0;

  //set up pre conditions
  priorHand = state->handCount[0];
  priorDiscard = state->discardCount[0];

  //play the adventurer card
  playAdventurer(state, 0);

  //set up post conditions
  postHand = state->handCount[0];
  postDiscard = state->discardCount[0];
  postCard1 = state->hand[0][state->handCount[0] - 1];
  postCard2 = state->hand[0][state->handCount[0] - 2];

  //test last card in hand
  if (postCard1 == copper || postCard1 == silver || postCard1 == gold) {
    printf("PASS -> Last card in hand is a treasure card.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Last card in hand is not a treasure card.\n");
  }

  //test 2nd to last card in hand
  if (postCard2 == copper || postCard2 == silver || postCard2 == gold) {
    printf("PASS -> 2nd to last card in hand is a treasure card.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> 2nd to last card in hand is not a treasure card.\n");
  }

  //test hand count
  if (postHand == (priorHand + 1)) {
    printf("PASS -> Hand count after card play is correct.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Hand count after card play is incorrect.\n");
  }

  //test to make sure adventurer card is gone from hand
  if (state->hand[0][pos] != adventurer) {
    printf("PASS -> Adventurer card removed from hand.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Adventurer card not removed from hand.\n");
  }

  //make sure at least some cards were discarded
  if (postDiscard > priorDiscard) {
    printf("PASS -> Cards were added to the discard pile.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Cards were not added to the discard pile.\n");
  }

  return testsPassed;
}


int main ()
{
  int i, n;
  int currentPass = 0;
  int totalPass = 0;
  int totalTests = 0;

  struct gameState G;

  int adventurerPos;

  SelectStream(1);
  PutSeed(-1);
  Random();

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("----------BEGIN RANDOM TESTING FOR ADVENTURER CARD----------\n");
  printf("------------------------------------------------------------\n");

  for (n = 0; n < 2000; n++) {
    //clear out the game state with all random values
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }

    //set random hand
    G.handCount[0] = floor(Random() * MAX_HAND);
    for (i = 0; i < G.handCount[0]; i++) {
      G.hand[0][i] = floor(Random() * 27);
    }

    //set random deck and deck count
    G.deckCount[0] = floor(Random() * MAX_DECK);
    for (i = 0; i < G.deckCount[0]; i++) {
      G.deck[0][i] = floor(Random() * 27);
    }

    //set random discard pile and discard count
    G.discardCount[0] = floor(Random() * MAX_DECK);
    for (i = 0; i < G.discardCount[0]; i++) {
      G.discard[0][i] = floor(Random() * 27);
    }

    //place adventuruer in random spot
    adventurerPos = floor(Random() * G.handCount[0]);
    G.hand[0][adventurerPos] = adventurer;

    printf("Test results for test: %d\n", n);
    currentPass = testAdventurer(&G, adventurerPos);
    printf("Tests passed: %d out of 5\n", currentPass);
    printf("\n");

    totalPass += currentPass;
    totalTests += 5;
  }

  printf("------------------------------------------------------------\n");
  printf("-----------------RESULTS of random testing -----------------\n");
  printf("Total Tests: %d\n", totalTests);
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalTests - totalPass);
  printf("------------------------------------------------------------\n");

  return 0;
}

