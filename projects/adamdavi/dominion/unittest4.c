/******************************************************************************
* unittest4.c
* David Adams
* CS 362
* Spring 2015
* Assignment 3
* This file has been added for Assignment 3 in order to provide unit tests
* for the updateCoins() function within the dominion.c file. 
******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
  int maxBonus = 3;
  int handTest = 3;
  int manHandCount;
  int coinValue;
  int priorValue;
  int totalFail = 0;
  int totalPass = 0;
  int i;  //holds number of bonus coin value to add
  int a;  //holds number of gold coins
  int b;  //holds number of silver coins
  int c;  //holds number of copper coins
  int x;

  int coppers[MAX_HAND];
  int silvers[MAX_HAND];
  int golds[MAX_HAND];

  int seed = -1;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

  for (x = 0; x < MAX_HAND; x++) {
    coppers[x] = copper;
    silvers[x] = silver;
    golds[x] = gold;
  }

  initializeGame(2, k, seed, &G);

  //Begin testing--------------------------------------------------------------
  printf("------------------------------------------------------------\n");
  printf("---------------BEGIN TESTING FOR updateCoins()--------------\n");
  printf("------------------------------------------------------------\n");

  //Testing for a negative input for the bonus --------------------------------
  priorValue = G.coins;
  updateCoins(0, &G, -1);
  coinValue = G.coins;
  if (!(coinValue == (priorValue - 1))) {
    printf("updateCoins(): PASS -> denied input of negative bonus.\n\n");
    totalPass++;
  }
  else {
    printf("updateCoins(): FAIL -> accepted input of negative bonus.\n\n");
    totalFail++;
  }

  //Testing for out of Bounds player
  updateCoins(MAX_PLAYERS + 1, &G, 0);
  coinValue = G.coins;

  if (coinValue != 0) {
    printf("updateCoins(): FAIL -> incorrect handling of out of bounds player.\n\n");
    totalFail++;
  }
  else {
    printf("updateCoins(): PASS -> out of bounds player doesn't change coin count.\n\n");
    totalPass++;
  }

  //Testing various combinations of coins in the hand -------------------------
  //need to clear hand for the game
  G.handCount[0] = 0;

  for (i = 0; i < maxBonus; i++) {
    //loop through possible bonus values

    for (a = 0; a < handTest; a++) {
      //loop through possible gold coin values
      manHandCount = a;
      memcpy(G.hand[0], golds, sizeof(int) * a);

      for (b = 0; b < handTest; b++) {
        //loop through possible silver coin values
        manHandCount += b;
        memcpy(G.hand[0] + a, silvers, sizeof(int) * b);

        for (c = 0; c < handTest; c++) {
          //loop through possible copper coin values
          manHandCount += c;
          G.handCount[0] = manHandCount;

          memcpy(G.hand[0] + a + b, coppers, sizeof(int) * c);

          //update coins
          updateCoins(0, &G, i);

          //make sure coins works
          coinValue = (a * 3) + (b * 2) + c + i;

          if (G.coins != coinValue) {
            printf("updateCoins(): FAIL -> ");
            printf("Correct: %d, Observed: %d.\n", coinValue, G.coins);
            printf("\tGolds: %d, Silvers: %d, ", a, b);
            printf("Coppers: %d, Bonus: %d.\n\n", c, i);
            totalFail++;
          }
          else {
            printf("updateCoins(): PASS -> ");
            printf("Correct: %d, Observed: %d.\n", coinValue, G.coins);
            printf("\tGolds: %d, Silvers: %d, ", a, b);
            printf("Coppers: %d, Bonus: %d.\n\n", c, i);
            totalPass++;
          }

          manHandCount -= c;

        }

        manHandCount -= b;
      }
    }
  }  

  printf("------------------------------------------------------------\n");
  printf("--------------RESULTS of updateCoins() testing--------------\n");
  printf("Tests Passed: %d\tTests Failed: %d\n", totalPass, totalFail);
  printf("------------------------------------------------------------\n");

  return 0;
}
