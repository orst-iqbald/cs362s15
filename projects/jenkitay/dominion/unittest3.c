/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: unittest3.c
- Description: A unit test of the updateCoins() function in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm unittest3.c dominion.o rngs.o -o unittest3
*******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#define DEBUG 0
#define NOISY_TEST 1

int main(int argc, char *argv[])
{	
   // Game state variables
   int numPlayers = 2;
   int kCards[10] = {
      adventurer, 
      council_room, 
      feast, 
      gardens, 
      mine, 
      remodel, 
      smithy, 
      village, 
      baron, 
      great_hall};
   int randSeed = 99;
   struct gameState state;
   
   // test variables
   int p, c;
   int handCount = 0;
   int handCountMax = 5;
   int bonus = 0;
   int bonusMax = 10;
   int estateVal = 0;
   int copperVal = 1;
   int silverVal = 2;
   int goldVal = 3;
   int fail = 0;
   int failcount = 0;
   srand(randSeed);
   
   // initialize game state
   memset(&state, 0, sizeof(struct gameState)); // zero game state
   assert(initializeGame(numPlayers, kCards, randSeed, &state) == 0); // initializeGame returns 0 on success
   
   // Begin Tests
   for (handCount = 1; handCount <= handCountMax; handCount++) {
      for (bonus = 0; bonus <= bonusMax; bonus++){
         for (p = 0; p < numPlayers; p++) {
            state.handCount[p] = handCount;
         }
         // Test 1
         // set all cards in players hands to estate and check update coins
         for (p =0; p < numPlayers; p++) {
            for (c = 0; c < handCount; c++) {
               state.hand[p][c] = estate;
            }
            updateCoins(p, &state, bonus);
            // coins should equal handCount * estateVal + bonus
            if (state.coins != handCount * estateVal + bonus) {
               fail = 1;
               failcount++;
               printf("FAIL Test 1: %d estate cards + %d bonus returned %d coins. Expected %d coins.\n"
                  , handCount, bonus, state.coins, handCount * estateVal + bonus);
            }
         }
         // Test 2
         // set all cards in players hands to copper and check update coins
         for (p =0; p < numPlayers; p++) {
            for (c = 0; c < handCount; c++) {
               state.hand[p][c] = copper;
            }
            updateCoins(p, &state, bonus);
            // coins should equal handCount * copperVal + bonus
            if (state.coins != handCount * copperVal + bonus) {
               fail = 1;
               failcount++;
               printf("FAIL Test 2: %d copper cards + %d bonus returned %d coins. Expected %d coins.\n"
                  , handCount, bonus, state.coins, handCount * copperVal + bonus);
            }
         }
         // Test 3
         // set all cards in players hands to silver and check update coins
         for (p =0; p < numPlayers; p++) {
            for (c = 0; c < handCount; c++) {
               state.hand[p][c] = silver;
            }
            updateCoins(p, &state, bonus);
            // coins should equal handCount * silverVal + bonus
            if (state.coins != handCount * silverVal + bonus) {
               fail = 1;
               failcount++;
               printf("FAIL Test 3: %d silver cards + %d bonus returned %d coins. Expected %d coins.\n"
                  , handCount, bonus, state.coins, handCount * silverVal + bonus);
            }
         }
         // Test 4
         // set all cards in players hands to gold and check update coins
         for (p =0; p < numPlayers; p++) {
            for (c = 0; c < handCount; c++) {
               state.hand[p][c] = gold;
            }
            updateCoins(p, &state, bonus);
            // coins should equal handCount * goldVal + bonus
            if (state.coins != handCount * goldVal + bonus) {
               fail = 1;
               failcount++;
               printf("FAIL Test 4: %d gold cards + %d bonus returned %d coins. Expected %d coins.\n"
                  , handCount, bonus, state.coins, handCount * goldVal + bonus);
            }
         }
         // Test 5
         // set all cards in players hands to mix of estate, copper, silver and gold
         // and check update coins
         for (p =0; p < numPlayers; p++) {
            int numE = 0;
            int numC = 0;
            int numS = 0;
            int numG = 0;
            for (c = 0; c < handCount; c++) {
               if (c % 4 == 0) {
                  numE++;
                  state.hand[p][c] = estate;
               }
               if (c % 4 == 1) {
                  numC++;
                  state.hand[p][c] = copper;
               }
               if (c % 4 == 2) {
                  numS++;
                  state.hand[p][c] = silver;
               }
               if (c % 4 == 3) {
                  numG++;
                  state.hand[p][c] = gold;
               }
            }
            updateCoins(p, &state, bonus);
            // coins should equal (numE * estateVal + numC * copperVal 
            //    + numS * silverVal +numG * goldVal + bonus)
            int total = numE * estateVal 
                      + numC * copperVal 
                      + numS * silverVal 
                      + numG * goldVal 
                      + bonus;
            if (state.coins != total) {
               fail = 1;
               failcount++;
               printf("FAIL Test 4: %d mixed cards + %d bonus returned %d coins. Expected %d coins.\n"
                  , handCount, bonus, state.coins, total);
            }
         }
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d updateCoins() tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All updateCoins() tests PASSED\n");
   #endif
   return 0;
}