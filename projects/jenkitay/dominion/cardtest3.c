/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: cardtest3.c
- Description: A unit test of the sea_hag card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm cardtest3.c dominion.o rngs.o -o cardtest3
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

int sea_hagCardEffect(struct gameState *state);

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
      sea_hag, 
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
      adventurer,
      copper,
      estate,
      copper,
      estate,
   };
      
   /* For Reference, elements of game state struct:
         int whoseTurn;
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
         
         // Test:  Effect of sea hag card
         //    Each other player discards the top card of his deck, then gains a
         //    Curse card, putting it on top of his deck.
         
         // initialize both players' decks
         for (int d = 0; d < numPlayers; d++) {
            // initialize each player's hand
            state.handCount[d] = handCount;
            for (handPos = 0; handPos < handCount; handPos++) {
               state.hand[d][handPos] = initHand[handPos % (sizeof(initHand)/sizeof(int))];
            }
            
            // initialize counts
            state.discardCount[d] = 0;
            state.playedCardCount = 0;
            
            // initialize deck
            state.deckCount[d] = 7;
            state.deck[d][0] = adventurer;
            state.deck[d][1] = gold;
            state.deck[d][2] = feast;
            state.deck[d][3] = copper;
            state.deck[d][4] = mine;
            state.deck[d][5] = smithy;
            state.deck[d][6] = silver;
         }
         
         // save precondition state in variables.
         int startHandCountP0 = state.handCount[0];
         int startHandCountP1 = state.handCount[1];
         int startDeckCountP0 = state.deckCount[0];
         int startDeckCountP1 = state.deckCount[1];
         int startDiscardCountP0 = state.discardCount[0];
         int startDiscardCountP1 = state.discardCount[1];
         int startDeckP0[state.deckCount[0]];
         for (int i = 0; i < state.deckCount[0]; i++) {
            startDeckP0[i] = state.deck[0][i];
         }
         int startDeckP1[state.deckCount[1]];
         for (int i = 0; i < state.deckCount[1]; i++) {
            startDeckP1[i] = state.deck[1][i];
         }
         int startPlayedCardCount = state.playedCardCount;
         handPos = 0;
         
         // variables to access other player info with current player number.
         int op[] = {1, 0};
         int opstartDiscardCount[] = {startDiscardCountP1, startDiscardCountP0};
         int opstartDeckCount[] = {startDeckCountP1, startDeckCountP0};
         
         // print preconditions
         #if (NOISY_TEST == 1)
            printf("Pre-conditions for player 0:\n handCount = %d\n deckCount = %d\n"
                  " discardCount = %d\n playedCardCount = %d\n player's turn = %d\n"
                  " Top of player 0's deck = %d\n Top of player 0's discard = %d\n\n"
                  , startHandCountP0, startDeckCountP0
                  , startDiscardCountP0, startPlayedCardCount, state.whoseTurn
                  , startDeckP0[6], state.discard[0][6]);
            printf("Pre-conditions for player 1:\n handCount = %d\n deckCount = %d\n"
                  " discardCount = %d\n playedCardCount = %d\n player's turn = %d\n"
                  " Top of player 1's deck = %d\n Top of player 1's discard = %d\n\n"
                  , startHandCountP1, startDeckCountP1
                  , startDiscardCountP1, startPlayedCardCount, state.whoseTurn
                  , startDeckP1[6], state.discard[1][6]);
         
         #endif
         
         // play sea_hag card
         sea_hagCardEffect(&state);
         
         // print post conditions
         #if (NOISY_TEST == 1)
            printf("Post-conditions for player 0:\n handCount = %d\n deckCount = %d\n"
                  " discardCount = %d\n playedCardCount = %d\n player's turn = %d\n"
                  " Top of player 0's deck = %d\n Top of player 0's discard = %d\n\n"
                  , state.handCount[0], state.deckCount[0]
                  , state.discardCount[0], state.playedCardCount, state.whoseTurn
                  , state.deck[0][6], state.discard[0][6]);
            printf("Post-conditions for player 0:\n handCount = %d\n deckCount = %d\n"
                  " discardCount = %d\n playedCardCount = %d\n player's turn = %d\n"
                  " Top of player 1's deck = %d\n Top of player 1's discard = %d\n\n"
                  , state.handCount[1], state.deckCount[1]
                  , state.discardCount[1], state.playedCardCount, state.whoseTurn
                  , state.deck[1][6], state.discard[1][6]);
         
         #endif
         
         // Test 1: hand count should remain unchanged.
         if (state.handCount[0] != startHandCountP0) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: handCount changed for player 0\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startHandCountP0, state.handCount[0]);
         }
         if (state.handCount[1] != startHandCountP1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: handCount changed for player 1\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startHandCountP1, state.handCount[1]);
         }
         // Test 2: deckCount should remain unchanged.
         if (state.deckCount[0] != startDeckCountP0) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: deckCount changed for player 0\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDeckCountP0, state.deckCount[0]);
         }
         if (state.deckCount[1] != startDeckCountP1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: deckCount changed for player 1\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDeckCountP1, state.deckCount[1]);
         }
         // Test 3: discard count should have increased by 1 for other player only.
         if (state.discardCount[op[p]] != opstartDiscardCount[p] + 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: other player's discardCount count not increased by 1\n");
            printf("\tExpected: %d. Returned: %d\n"
               , opstartDiscardCount[p] + 1, state.discardCount[op[p]]);
         }
         if (state.discardCount[p] != opstartDiscardCount[op[p]]) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: player %d's discardCount count changed\n", p);
            printf("\tExpected: %d. Returned: %d\n"
               , opstartDiscardCount[op[p]], state.discardCount[p]);
         }
         // Test 4: playedCardCount should remain unchanged
         if (state.playedCardCount != startPlayedCardCount) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: playedCardCount changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startPlayedCardCount, state.playedCardCount);
         }
         // Test 5: Top of other player's discard pile should contain a silver card.
         if (state.discard[op[p]][0] != silver) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 5: Top of other player's discard pile is not silver.\n");
            printf("\tExpected: %d. Returned: %d\n", silver, state.discard[op[p]][0]);
         }
         if (state.discard[p][0] != empty) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 5: Top of current player's discard pile is not empty.\n");
            printf("\tExpected: %d. Returned: %d\n", empty, state.discard[p][0]);
         }
         // Test 6: Top of other player's deck should contain a curse card.
         if (state.deck[op[p]][opstartDeckCount[p]] != curse) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 6: Top of other player's deck is not a curse card.\n");
            printf("\tExpected: %d. Returned: %d\n"
               , curse, state.deck[op[p]][opstartDeckCount[p]]);
         }
         if (state.deck[op[p]][opstartDeckCount[p]] != silver) { 
            fail = 1;
            failcount++;
            printf("FAIL Test 6: Top of current player's deck is not a silver card.\n");
            printf("\tExpected: %d. Returned: %d\n"
               , silver, state.deck[p][opstartDeckCount[op[p]]]);
         }
         
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d sea_hag tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All sea_hag tests PASSED\n");
   #endif
   return 0;
}