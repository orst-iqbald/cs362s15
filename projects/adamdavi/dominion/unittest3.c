/******************************************************************************
* unittest3.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the gainCard() function within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int totalFail = 0;
  int totalPass = 0;

  int seed = -1;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

  int NUM_TEST_CARDS = 3;
  int testCards[NUM_TEST_CARDS];
  int i, x;
  int priorSupply, postSupply;
  int priorHand, postHand;
  int priorDeck, postDeck;
  int priorDiscard, postDiscard;

  SelectStream(1);
  PutSeed(-1);
  Random();

  for (i = 0; i < NUM_TEST_CARDS; i++) {
    testCards[i] = k[(int)floor(Random() * 10)];
  }

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("-----------------BEGIN TESTING FOR gainCard()---------------\n");
  printf("------------------------------------------------------------\n");

  //Test out of bounds input for card to get ie. card that does not exist
  if (gainCard(treasure_map + 2, &G, 0, 0) == -1) {
    printf("gainCard(): PASS -> handles non existent card.\n\n");
    totalPass++;
  }
  else {
    printf("gainCard(): FAIL -> does not handle non existent card.\n\n");
    totalFail++;
  }

  //test empty supply pile ie. all cards are gone of that type
  G.supplyCount[curse] = 0;
  if (gainCard(curse, &G, 0, 0) == -1) {
    printf("gainCard(): PASS -> handles empty supply pile.\n\n");
    totalPass++;
  }
  else {
    printf("gainCard(): FAIL -> does not handle empty supply pile.\n\n");
    totalFail++;
  }

  //Test for out of bounds player
  if (gainCard(copper, &G, 0, MAX_PLAYERS + 1) == -1) {
    printf("gainCard(): PASS -> handles out of bounds player.\n\n");
    totalPass++;
  }
  else {
    printf("gainCard(): FAIL -> does not exit on out of bounds player.\n\n");
    totalFail++;
  }

  //Test to make sure anything other than 1 or 2 adds card to discard pile
  priorSupply = G.supplyCount[copper];
  priorDiscard = G.discardCount[0];
  gainCard(copper, &G, 3, 0);
  postSupply = G.supplyCount[copper];
  postDiscard = G.discardCount[0];
  if (postSupply == (priorSupply - 1)) {
    printf("gainCard(): PASS -> decrements supply count on flag not equal to 1 or 2.\n\n");
    totalPass++;
  }
  else {
    printf("gainCard(): FAIL -> does not decrement supply count on flag not equal to 1 or 2.\n\n");
    totalFail++;
  }
  
  if ( postDiscard == (priorDiscard + 1) && G.discard[0][postDiscard - 1] == copper ) {
    printf("gainCard(): PASS -> correctly discards card on flag not equal to 1 or 2.\n\n");
    totalPass++;
  }
  else {
    printf("gainCard(): FAIL -> did not discard card on flag not equal to 1 or 2.\n\n");
    totalFail++;
  }

  //Test scenario of adding card to the discard pile
  //test scenario of adding card to the deck
  //test scenario of adding card to the hand
  //The following uses NUM_TEST_CARDS number of random cards to test to make
  //sure that the cards are gained in either the discard, deck or hand
  for (x = 0; x < NUM_TEST_CARDS; x++) {
    
    //testing gaining card x and adding it to the deck
    priorSupply = G.supplyCount[testCards[x]];
    priorDeck = G.deckCount[0];
    gainCard(testCards[x], &G, 1, 0);   //add card to deck
    postSupply = G.supplyCount[testCards[x]];
    postDeck = G.deckCount[0];

    if ( postDeck == (priorDeck + 1) ) {
      if ( G.deck[0][postDeck - 1] == testCards[x] ) {
        printf("gainCard(): PASS -> Test card %d gained correctly to deck.\n\n", testCards[x]);
        totalPass++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d incremented deck count but was not correctly added to deck.\n\n", testCards[x]);
        totalFail++;
      }
    }
    else {
      if ( G.deck[0][postDeck - 1] == testCards[x] ) {
        printf("gainCard(): FAIL -> Test card %d was added to deck but did not increment deck count.\n\n", testCards[x]);
        totalFail++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d was not added to deck and did not increment deck count.\n\n", testCards[x]);
        totalFail++;
      }
    }

    if ( postSupply == (priorSupply - 1) ) {
      printf("gainCard(): PASS -> Test card %d decreased supply pile after added to deck.\n\n", testCards[x]);
      totalPass++;    
    }
    else {
      printf("gainCard(): FAIL -> Test card %d did not decrease supply pile after added to deck.\n\n", testCards[x]);
      totalFail++;      
    }

    //testing gaining card x and adding it to the hand
    priorSupply = G.supplyCount[testCards[x]];    
    priorHand = G.handCount[0];
    gainCard(testCards[x], &G, 2, 0);   //add card to hand
    postSupply = G.supplyCount[testCards[x]];
    postHand = G.handCount[0];

    if ( postHand == (priorHand + 1) ) {
      if ( G.hand[0][postHand - 1] == testCards[x] ) {
        printf("gainCard(): PASS -> Test card %d gained correctly to hand.\n\n", testCards[x]);
        totalPass++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d incremented hand count but was not correctly added to hand.\n\n", testCards[x]);
        totalFail++;
      }
    }
    else {
      if ( G.hand[0][postHand - 1] == testCards[x] ) {
        printf("gainCard(): FAIL -> Test card %d was added to hand but did not increment hand count.\n\n", testCards[x]);
        totalFail++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d was not added to hand and did not increment hand count.\n\n", testCards[x]);
        totalFail++;
      }
    }    

    if ( postSupply == (priorSupply - 1) ) {
      printf("gainCard(): PASS -> Test card %d decreased supply pile after added to hand.\n\n", testCards[x]);
      totalPass++;      
    }
    else {
      printf("gainCard(): FAIL -> Test card %d did not decrease supply pile after added to deck.\n\n", testCards[x]);
      totalFail++;      
    }

    //testing gaining card x and adding it to discard
    priorSupply = G.supplyCount[testCards[x]];
    priorDiscard = G.discardCount[0];
    gainCard(testCards[x], &G, 0, 0);   //add card to discard
    postSupply = G.supplyCount[testCards[x]];
    postDiscard = G.discardCount[0];

    if ( postDiscard == (priorDiscard + 1) ) {
      if ( G.discard[0][postDiscard - 1] == testCards[x] ) {
        printf("gainCard(): PASS -> Test card %d gained correctly to discard.\n\n", testCards[x]);
        totalPass++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d incremented discard count but was not correctly added to discard.\n\n", testCards[x]);
        totalFail++;
      }
    }
    else {
      if ( G.discard[0][postDiscard - 1] == testCards[x] ) {
        printf("gainCard(): FAIL -> Test card %d was added to discard but did not increment discard count.\n\n", testCards[x]);
        totalFail++;
      }
      else {
        printf("gainCard(): FAIL -> Test card %d was not added to discard and did not increment discard count.\n\n", testCards[x]);
        totalFail++;
      }
    }    

    if ( postSupply == (priorSupply - 1) ) {
      printf("gainCard(): PASS -> Test card %d decreased supply pile after added to discard.\n\n", testCards[x]);
      totalPass++;      
    }
    else {
      printf("gainCard(): FAIL -> Test card %d did not decrease supply pile after added to deck.\n\n", testCards[x]);
      totalFail++;      
    }    
    
  }

  printf("------------------------------------------------------------\n");
  printf("----------------RESULTS of gainCard() testing---------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
