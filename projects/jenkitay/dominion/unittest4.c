/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: unittest4.c
- Description: A unit test of the discardCard() function in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm unittest4.c dominion.o rngs.o -o unittest4
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
   int p;
   int temp;
   int handPos;
   int trash = 1;
   int noTrash = 0;
   int handCount = 0;
   int handCountMax = 5;
   int fail = 0;
   int failcount = 0;
   srand(randSeed);
   
   // initialize game state
   memset(&state, -1, sizeof(struct gameState)); // initialize game state
   assert(initializeGame(numPlayers, kCards, randSeed, &state) == 0); // initializeGame returns 0 on success
   
   // Begin Tests
   for (handCount = 1; handCount <= handCountMax; handCount++) {
      for (p = 0; p < numPlayers; p++) {
        
         // Test 1   Trash the last card in the hand
         // Set the size of the hand, and playedCardCount
         state.handCount[p] = handCount;
         state.playedCardCount = 0;
         // set all cards in the hand to kCards[handPos % (length of kCards)] 
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = kCards[handPos % (sizeof(kCards)/sizeof(int))];
         }
         // trash the last card in hand
         handPos = handCount - 1;
         discardCard(handPos, p, &state, trash);
         // played card count should remain unchanged
         if (state.playedCardCount != 0) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: playedCardCount was changed on trash\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // handCount should be reduced by 1
         if (state.handCount[p] != handCount - 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: Hand count not reduced by 1\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
      
         // Test 2   Discard last card in hand onto empty discard pile
         // Set the size of the hand, and playedCardCount
         state.handCount[p] = handCount;
         state.playedCardCount = 0;
         // set all cards in the hand to kCards[handPos % (length of kCards)] 
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = kCards[handPos % (sizeof(kCards)/sizeof(int))];
         }
         // discard the last card in hand
         handPos = handCount - 1;
         temp = state.hand[p][handPos];
         discardCard(handPos, p, &state, noTrash);
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] != temp) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: played card did not match card in handPos\n");
            printf("\tExpected: %d. Returned %d.\n", temp, 
                  state.playedCards[state.playedCardCount - 1]);
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] == -1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: played card was out of range for hand\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // played card count should remain unchanged
         if (state.playedCardCount != 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: playedCardCount wasn't incremented on discard\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // handCount should be reduced by 1
         if (state.handCount[p] != handCount - 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: Hand count not reduced by 1\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         
         // Test 3   Discard first card in hand onto discard pile
         // Set the size of the hand, and playedCardCount
         state.handCount[p] = handCount;
         state.playedCardCount = 5;
         // set all cards in the hand to kCards[handPos % (length of kCards)] 
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = kCards[handPos % (sizeof(kCards)/sizeof(int))];
         }
         // discard the first card in hand
         handPos = 0;
         temp = state.hand[p][handPos];
         discardCard(handPos, p, &state, noTrash);
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] != temp) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: played card did not match card in handPos\n");
            printf("\tExpected: %d. Returned %d.\n", temp, 
                  state.playedCards[state.playedCardCount - 1]);
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] == -1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: played card was out of range for hand\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // played card count should remain unchanged
         if (state.playedCardCount != 6) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: playedCardCount wasn't incremented on discard\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // handCount should be reduced by 1
         if (state.handCount[p] != handCount - 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: Hand count not reduced by 1\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         
         // Test 4   Discard second card in hand onto discard pile
         // Set the size of the hand, and playedCardCount
         state.handCount[p] = handCount;
         state.playedCardCount = 3;
         // test second card in hand
         int testPos = 1;
         state.hand[p][testPos] = -1;
         // set all cards in the hand to kCards[handPos % (length of kCards)] 
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = kCards[handPos % (sizeof(kCards)/sizeof(int))];
         }
         // discard the second card in hand
         temp = state.hand[p][testPos];
         handPos = testPos;
         discardCard(handPos, p, &state, noTrash);
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] != temp) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: played card did not match card in handPos\n");
            printf("\tExpected: %d. Returned %d.\n", temp, 
                  state.playedCards[state.playedCardCount - 1]);
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // Should not allow played card out of range of hand
         if (state.playedCards[state.playedCardCount - 1] == -1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: played card was out of range for hand\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // played card count should remain unchanged
         if (state.playedCardCount != 4) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: playedCardCount wasn't incremented on discard\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         // handCount should be reduced by 1
         if (state.handCount[p] != handCount - 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: Hand count not reduced by 1\n");
            printf("\thandCount = %d Player = %d\n", handCount, p);
         }
         
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d discardCard() tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All discardCard() tests PASSED\n");
   #endif
   return 0;
}