/******************************************************************************
* cardtes3.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the Great Hall card within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
  int priorAction;

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("-------------BEGIN TESTING FOR GREAT HALL CARD--------------\n");
  printf("------------------------------------------------------------\n");

  //test great hall has last card in hand
  //test to make sure action has increased
  //test to make sure card has been added to hand
  //test to make sure great hall card was discarded after use
  G.hand[0][G.handCount[0]] = great_hall;
  G.handCount[0]++;
  priorAction = G.numActions;
  priorHand = G.handCount[0];
  priorDiscard = G.discardCount[0];
  cardEffect(great_hall, -1, -1, -1, &G, G.handCount[0] - 1, 0);
  G.numActions--;
  postHand = G.handCount[0];
  postDiscard = G.discardCount[0];

  if ( G.numActions == priorAction ) {
    printf("Great Hall: PASS -> Test last card in hand: Action + 1 was successfull.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test last card in hand: Action was not given +1.\n\n");
    totalFail++;
  }  

  if ( priorHand == postHand && G.hand[0][postHand - 1] != great_hall ) {
    printf("Great Hall: PASS -> Test last card in hand: Card was added to hand.\n\n");
    printf("Great Hall: PASS -> Test last card in hand: Great hall was removed from hand.\n\n");
    totalPass++;
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test last card in hand: Card was not added to hand.\n\n");
    printf("Great Hall: FAIL -> Test last card in hand: Great hall was not removed from hand.\n\n");
    totalFail++;
    totalFail++;
  }  

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("Great Hall: PASS -> Test last card in hand: Discard count was increased.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test last card in hand: Discard count was not increased.\n\n");
    totalFail++;
  }  

  if ( G.discard[0][postDiscard - 1] == great_hall ) {
    printf("Great Hall: PASS -> Test last card in hand: Card was added to discard pile.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test last card in hand: Card was not added to discard pile.\n\n");
    totalFail++;
  }  

  //test great hall as only card in hand
  //test to make sure action has increased
  //test to make sure card has been added to hand
  //test to make sure great hall card was discarded after use
  initializeGame(2, k, seed, &G);
  G.hand[0][0] = great_hall;
  G.handCount[0] = 1;
  priorAction = G.numActions;
  priorHand = G.handCount[0];
  priorDiscard = G.discardCount[0];
  cardEffect(great_hall, -1, -1, -1, &G, G.handCount[0] - 1, 0);
  G.numActions--;
  postHand = G.handCount[0];
  postDiscard = G.discardCount[0];

  if ( G.numActions == priorAction ) {
    printf("Great Hall: PASS -> Test only card in hand: Action + 1 was successfull.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test only card in hand: Action was not given +1.\n\n");
    totalFail++;
  }  

  if ( priorHand == postHand && G.hand[0][postHand - 1] != great_hall ) {
    printf("Great Hall: PASS -> Test only card in hand: Card was added to hand.\n\n");
    printf("Great Hall: PASS -> Test only card in hand: Great hall was removed from hand.\n\n");
    totalPass++;
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test only card in hand: Card was not added to hand.\n\n");
    printf("Great Hall: FAIL -> Test only card in hand: Great hall was not removed from hand.\n\n");
    totalFail++;
    totalFail++;
  }  

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("Great Hall: PASS -> Test only card in hand: Discard count was increased.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test only card in hand: Discard count was not increased.\n\n");
    totalFail++;
  }  

  if ( G.discard[0][postDiscard - 1] == great_hall ) {
    printf("Great Hall: PASS -> Test only card in hand: Card was added to discard pile.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test only card in hand: Card was not added to discard pile.\n\n");
    totalFail++;
  }  

  //test great hall as middle card in hand
  //test to make sure action has increased
  //test to make sure card has been added to hand
  //test to make sure great hall card was discarded after use
  initializeGame(2, k, seed, &G);
  priorCard = 2;
  G.hand[0][priorCard] = great_hall;
  priorAction = G.numActions;
  priorHand = G.handCount[0];
  priorDiscard = G.discardCount[0];
  cardEffect(great_hall, -1, -1, -1, &G, priorCard, 0);
  G.numActions--;
  postHand = G.handCount[0];
  postDiscard = G.discardCount[0];

  if ( G.numActions == priorAction ) {
    printf("Great Hall: PASS -> Test middle card in hand: Action + 1 was successfull.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test middle card in hand: Action was not given +1.\n\n");
    totalFail++;
  }  

  if ( priorHand == postHand && G.hand[0][priorCard] != great_hall ) {
    printf("Great Hall: PASS -> Test middle card in hand: Card was added to hand.\n\n");
    printf("Great Hall: PASS -> Test middle card in hand: Great hall was removed from hand.\n\n");
    totalPass++;
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test middle card in hand: Card was not added to hand.\n\n");
    printf("Great Hall: FAIL -> Test middle card in hand: Great hall was not removed from hand.\n\n");
    totalFail++;
    totalFail++;
  }  

  if ( postDiscard == (priorDiscard + 1) ) {
    printf("Great Hall: PASS -> Test middle card in hand: Discard count was increased.\n\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test middle card in hand: Discard count was not increased.\n\n");
    totalFail++;
  }  

  if ( G.discard[0][postDiscard - 1] == great_hall ) {
    printf("Great Hall: PASS -> Test middle card in hand: Card was added to discard pile.\n");
    totalPass++;
  }
  else {
    printf("Great Hall: FAIL -> Test middle card in hand: Card was not added to discard pile.\n");
    totalFail++;
  }  

  printf("------------------------------------------------------------\n");
  printf("------------RESULTS of Great Hall card testing--------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
