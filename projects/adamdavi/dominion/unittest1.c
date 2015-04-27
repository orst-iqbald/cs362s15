/******************************************************************************
* unittest1.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the isGameOver() function within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//This function clears out the supply count for the amount of 
//cards passed in my num. So, if num = 3, then 3 piles of supply
//cards will be cleared. 
void emptySupply(struct gameState *state, int *cards, int num)
{
  int i;
  int randNum;
  int card;

  for (i = 0; i < num; i++) {
    randNum = (int)floor(Random() * 17);
    if (randNum < 7) {
      //random number is going to represent non-action supply card
      state->supplyCount[randNum] = 0;
    }
    else {
      //random number is going to represent an action card
      card = cards[randNum - 7];
      state->supplyCount[card] = 0;
    }
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

  SelectStream(1);
  PutSeed(-1);
  Random();  

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("---------------BEGIN TESTING FOR isGameOver()---------------\n");
  printf("------------------------------------------------------------\n");

  //test when no supply piles are empty
  if (isGameOver(&G) == 0) {
    printf("isGameOver(): PASS -> returns 0 when no supply piles are empty.\n\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> returned 1 when no supply piles are empty.\n\n");
    totalFail++;
  }

  //test if province cards are empty
  G.supplyCount[province] = 0;
  if (isGameOver(&G) == 1) {
    printf("isGameOver(): PASS -> returns 1 when province pile is empty.\n\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> incorrectly returned 0 when provice pile is empty.\n\n");
    totalFail++;
  }
  initializeGame(2, k, seed, &G);

  //The following series of tests on supply piles, chooses which supply
  //piles to make empty at random
  //test if 1 supply pile is empty
  emptySupply(&G, k, 1);
  if (isGameOver(&G) == 0) {
    printf("isGameOver(): PASS -> returned 0 when only one supply pile is empty.\n\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> incorrectly returned 1 when only 1 supply pile is empty.\n\n");
    totalFail++;
  }
  initializeGame(2, k, seed, &G);

  //test if 2 supply piles are empty
  emptySupply(&G, k, 2);
  if (isGameOver(&G) == 0) {
    printf("isGameOver(): PASS -> returned 0 when 2 supply piles are empty.\n\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> incorrectly returned 1 when 2 supply piles are empty.\n\n");
    totalFail++;
  }
  initializeGame(2, k, seed, &G);

  //test if 3 supply piles are empty
  emptySupply(&G, k, 3);
  if (isGameOver(&G) == 0) {
    printf("isGameOver(): PASS -> returned 1 when 3 supply piles are empty.\n\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> incorrectly returned 0 when 3 supply piles are empty.\n\n");
    totalFail++;
  }
  initializeGame(2, k, seed, &G);

  //test if 4 supply piles are empty
  emptySupply(&G, k, 4);
  if (isGameOver(&G) == 0) {
    printf("isGameOver(): PASS -> returned 1 when 4 supply piles are empty.\n");
    totalPass++;
  }
  else {
    printf("isGameOver(): FAIL -> incorrectly returned 0 when 4 supply piles are empty.\n");
    totalFail++;
  }


  printf("------------------------------------------------------------\n");
  printf("--------------RESULTS of isGameOver() testing---------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
