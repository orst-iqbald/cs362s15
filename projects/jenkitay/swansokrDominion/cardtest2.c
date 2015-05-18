/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: cardtest2.c
- Description: A unit test of the adventurer card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm cardtest2.c dominion.o rngs.o -o cardtest2
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

// int adventurerCardEffect(struct gameState *state);

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
   //int res;
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
   memset(&state, -1, sizeof(struct gameState)); // initialize game state
   assert(initializeGame(numPlayers, kCards, randSeed, &state) == 0); // initializeGame returns 0 on success
   
   // Begin Tests
   for (handCount = 1; handCount <= handCountMax; handCount++) {
      for (p = 0; p < numPlayers; p++) {
         state.whoseTurn = p;
         
         // Test:  Effect of adventurer card
         //    Reveal cards from your deck until you reveal 2 Treasure cards. 
         //    Put those Treasure cards in your hand and discard the other 
         //    revealed cards.
         
         // initialize player's hand
         state.handCount[p] = handCount;
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = initHand[handPos % (sizeof(initHand)/sizeof(int))];
         }
         
         // initialize counts
         state.discardCount[p] = 0;
         state.playedCardCount = 0;
         
         // initialize deck
         state.deckCount[p] = 7;
         state.deck[p][0] = adventurer;
         state.deck[p][1] = gold;
         state.deck[p][2] = feast;
         state.deck[p][3] = copper;
         state.deck[p][4] = mine;
         state.deck[p][5] = smithy;
         state.deck[p][6] = silver;
         
         handPos = 0;
         
         // save precondition state in variables.
         int startHandCount = state.handCount[p];
         int startDeckCount = state.deckCount[p];
         int startDiscardCount = state.discardCount[p];
         int startPlayedCardCount = state.playedCardCount;
         int startDeck[state.deckCount[p]];
         for (int i = 0; i < state.deckCount[p]; i++) {
            startDeck[i] = state.deck[p][i];
         }
         
         // print preconditions
         #if (NOISY_TEST == 1)
            printf("Pre-conditions:\n handCount = %d\n deckCount = %d\n discardCount = %d\n playedCardCount = %d\n turn = %d\n"
                  , startHandCount, startDeckCount, startDiscardCount, startPlayedCardCount, state.whoseTurn);
         
         #endif
         
         // play adventurer card
         // adventurerCardEffect(&state);
         int tempHand[MAX_HAND];
         play_adventurer(&state, state.whoseTurn, handPos, &tempHand);
         
         // print post conditions
         #if (NOISY_TEST == 1)
            printf("Post-conditions:\n handCount = %d\n deckCount = %d\n discardCount = %d\n playedCardCount = %d\n turn = %d\n"
                  , state.handCount[p], state.deckCount[p], state.discardCount[p], state.playedCardCount, state.whoseTurn);
         
         #endif
         
         // Test 1: hand count should have 2 more cards
         if (state.handCount[p] != startHandCount + 2) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: handCount did not increase by 2\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startHandCount + 2, state.handCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // Test 2: deckCount should have decreased by 4.
         if (state.deckCount[p] != startDeckCount - 4) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: deckCount did not decrease by 4\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDeckCount - 4, state.deckCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // Test 3: discard count should have increased by 2
         if (state.discardCount[p] != startDiscardCount + 2) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: discardCount count not increased by 2\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startDiscardCount + 2, state.discardCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // Test 4: playedCardCount should remain unchanged
         if (state.playedCardCount != startPlayedCardCount) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: playedCardCount changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , startPlayedCardCount, state.playedCardCount);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // Test 5: discard pile should contain mine and smithy in that order.
         if (state.discard[p][0] != startDeck[4] // mine
            && state.discard[p][1] != startDeck[5] ) { // smithy
            fail = 1;
            failcount++;
            printf("FAIL Test 5: discard pile does not contain mine and smithy in that order.\n");
            printf("\tExpected: [%d, %d]. Returned: [%d, %d]\n"
               , mine, smithy, state.discard[p][0], state.discard[p][1]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // Test 6: Last two cards in hand should be silver and copper in that order.
         if (state.hand[p][startHandCount] != startDeck[6] // silver
            && state.hand[p][startHandCount + 1] != startDeck[3] ) { // copper
            fail = 1;
            failcount++;
            printf("FAIL Test 6: Last two cards in hand are not silver and copper in that order.\n");
            printf("\tExpected: [%d, %d]. Returned: [%d, %d]\n", silver, copper
               , state.hand[p][startHandCount], state.hand[p][startHandCount + 1]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d adventurer tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All adventurer tests PASSED\n");
   #endif
   return 0;
}