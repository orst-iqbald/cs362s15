/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: cardtest4.c
- Description: A unit test of the great_hall card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm cardtest4.c dominion.o rngs.o -o cardtest4
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

int adventurerCardEffect(struct gameState *state);

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
   int empty = -1;
   int handPos;
   int handCount = 0;
   int handCountMax = 5;
   int fail = 0;
   int failcount = 0;
   int initHand[] = {
      great_hall,
      copper,
      estate,
      copper,
      estate,
   };
      
   /* For Reference, elements of game state struct:
         int whoseTurn;
         int numActions; // Starts at 1 each turn 
         int coins; // Use as you see fit! 
         int numBuys; // Starts at 1 each turn 
         int hand[MAX_PLAYERS][MAX_HAND];
         int handCount[MAX_PLAYERS];
         int deck[MAX_PLAYERS][MAX_DECK];
         int deckCount[MAX_PLAYERS];
         int discard[MAX_PLAYERS][MAX_DECK];
         int discardCount[MAX_PLAYERS];
         int playedCards[MAX_DECK];
         int playedCardCount;
    */
   
   // initialize game state
   memset(&state, empty, sizeof(struct gameState)); // initialize game state
   assert(initializeGame(numPlayers, kCards, randSeed, &state) == 0); // initializeGame returns 0 on success
   
   // Begin Tests
   for (handCount = 1; handCount <= handCountMax; handCount++) {
      for (p = 0; p < numPlayers; p++) {
         state.whoseTurn = p;
         state.numActions = 1;
         state.numBuys = 1;
         for (int i = 0; i < MAX_PLAYERS; i++) {
            state.discard[p][i] = empty;
            state.deck[p][i] = empty;
            state.hand[p][i] = empty;
            state.playedCards[i] = empty;
         }
         
         // Test:  Effect of great_hall card
         //    +1 Card, +1 Action, Victory = 1
         
         // initialize player's hand
         state.handCount[p] = handCount;
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = initHand[handPos % (sizeof(initHand)/sizeof(int))];
         }
         handPos = 0;
         
         // initialize counts
         state.discardCount[p] = 0;
         state.playedCardCount = 0;
         
         // initialize deck
         state.deckCount[p] = 7;
         state.deck[p][0] = adventurer;
         state.deck[p][1] = gold;
         state.deck[p][2] = feast;
         state.deck[p][3] = copper;
         state.deck[p][4] = smithy;
         state.deck[p][5] = mine;
         state.deck[p][6] = silver;
         
         
         // save precondition state in variables.
         int startNumActions = state.numActions;
         int startHandCount = state.handCount[p];
         int startDeckCount = state.deckCount[p];
         int startDiscardCount = state.discardCount[p];
         int startPlayedCardCount = state.playedCardCount;
         /*
         int startDeck[state.deckCount[p]];
         for (int i = 0; i < state.deckCount[p]; i++) {
            startDeck[i] = state.deck[p][i];
         }
         */
         
         // print preconditions
         #if (NOISY_TEST == 1)
            printf("Pre-conditions:\n Player's turn = %d\n handCount = %d\n"
               " deckCount = %d\n discardCount = %d\n playedCardCount = %d\n"
               " Actions = %d\n\n", state.whoseTurn, startHandCount, 
               startDeckCount, startDiscardCount, startPlayedCardCount, 
               startNumActions);
         
         #endif
         
         // play great_hall card
         adventurerCardEffect(&state);
         cardEffect(great_hall, 0, 0, 0, &state, handPos, 0);
         
         // print post conditions
         #if (NOISY_TEST == 1)
            printf("Post-conditions:\n Player's turn = %d\n handCount = %d\n"
               " deckCount = %d\n discardCount = %d\n playedCardCount = %d\n"
               " Actions = %d\n\n", state.whoseTurn, state.handCount[p], 
               state.deckCount[p], state.discardCount[p], state.playedCardCount, 
               state.numActions);
         
         #endif
         
         // Test 1: hand count should remain unchanged
         if (state.handCount[p] != startHandCount) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: handCount changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startHandCount, state.handCount[p]);
         }
         // Test 2: deckCount should have decreased by 1.
         if (state.deckCount[p] != startDeckCount - 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: deckCount did not decrease by 1\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDeckCount - 1, state.deckCount[p]);
         }
         // Test 3: discard count should remain unchanged
         if (state.discardCount[p] != startDiscardCount) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: discardCount count changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDiscardCount, state.discardCount[p]);
         }
         // Test 4: playedCardCount should have increased by 1
         if (state.playedCardCount != startPlayedCardCount + 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: playedCardCount did not increase by 1\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startPlayedCardCount + 1, state.playedCardCount);
         }
         // Test 5: discard pile should remain unchanged
         if (state.discard[p][0] != empty ) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 5: discard pile changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , empty, state.discard[p][0]);
         }
         // Test 6: Actions should increase by 1.
         if (state.numActions != startNumActions + 1 ) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 6: Actions did not increase by 1.\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startNumActions + 1, state.numActions);
         }
         
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d great_hall tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All great_hall tests PASSED\n");
   #endif
   return 0;
}