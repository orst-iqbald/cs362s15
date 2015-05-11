/******************************************************************************
* randomtestcard.c
* David Adams
* CS 362
* Spring 2015
* Assignment 4
* This file has been added for Assignment 4 in order to provide random tests
* for the Smithy Card within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//returns the number of tests passed
int testSmithyCard(struct gameState *state, int pos)
{
  int priorHand, postHand;
  int priorDiscard, postDiscard;
  int testsPassed = 0;

  //set up pre conditions
  priorHand = state->handCount[0];
  priorDiscard = state->discardCount[0];

  //play the smithy
  playSmithy(state, 0, pos);

  //set up post conditions
  postHand = state->handCount[0];
  postDiscard = state->discardCount[0];

  //check that 3 cards were added to hand
  if (postHand == (priorHand + 2)) {
    printf("PASS -> 3 cards were added to hand.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Did not add 3 cards to hand.\n");
  }

  //check that smithy was removed from hand
  if (state->hand[0][pos] != smithy) {
    printf("PASS -> Smithy was removed from hand.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Smithy was not removed from hand.\n");
  }

  //check that smithy was discarded
  if (postDiscard == (priorDiscard + 1)) {
    printf("PASS -> Smithy was discarded.\n");
    testsPassed++;
  }
  else {
    printf("FAIL -> Smithy was not discarded.\n");
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

  int smithyPos;

  SelectStream(1);
  PutSeed(-1);
  Random();

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("------------BEGIN RANDOM TESTING FOR SMITHY CARD------------\n");
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

    //place smithy in random spot
    smithyPos = floor(Random() * G.handCount[0]);
    G.hand[0][smithyPos] = smithy;

    //set random deck count
    G.deckCount[0] = floor(Random() * MAX_DECK);

    //set random discard count
    G.discardCount[0] = floor(Random() * MAX_DECK);

    printf("Test results for test: %d\n", n);
    currentPass = testSmithyCard(&G, smithyPos);
    printf("Tests passed: %d out of 3\n", currentPass);
    printf("\n");

    totalPass += currentPass;
    totalTests += 3;
  }

  printf("------------------------------------------------------------\n");
  printf("-----------------RESULTS of random testing -----------------\n");
  printf("Total Tests: %d\n", totalTests);
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalTests - totalPass);
  printf("------------------------------------------------------------\n");

  return 0;
}

