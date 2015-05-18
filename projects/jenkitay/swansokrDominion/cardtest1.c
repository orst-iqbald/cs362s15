/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 3
- filename: cardtest1.c
- Description: A unit test of the smithy card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm cardtest1.c dominion.o rngs.o -o cardtest1
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

//int smithyCardEffect(struct gameState *state, int handPos);

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
         
         // Test:  play smithy card removes 1 card from hand, adds 3 cards to 
         //        hand, removes 3 from deck, and adds 1 card to discard 
         // Set the size of the hand, and playedCardCount
         state.handCount[p] = handCount;
         state.discardCount[p] = 4;
         state.playedCardCount = 4;
         state.deckCount[p] = 4;
         state.deck[p][0] = adventurer;
         state.deck[p][1] = feast;
         state.deck[p][2] = gold;
         state.deck[p][3] = copper;
         int startHandCount = state.handCount[p];
         int startDeckCount = state.deckCount[p];
         int startDiscardCount = state.discardCount[p];
         int startPlayedCardCount = state.playedCardCount;
         
         
         // set all cards in the hand to kCards[handPos % (length of kCards)] 
         for (handPos = 0; handPos < handCount; handPos++) {
            state.hand[p][handPos] = kCards[handPos % (sizeof(kCards)/sizeof(int))];
         }
         handPos = 0;
         state.hand[p][handPos] = smithy;
         
         #if (NOISY_TEST == 1)
            printf("Pre-conditions:\n handCount = %d\n deckCount = %d\n discardCount = %d\n playedCardCount = %d\n turn = %d\n"
                  , startHandCount, startDeckCount, startDiscardCount, startPlayedCardCount, state.whoseTurn);
         
         #endif
         
         //smithyCardEffect(&state, handPos);
         play_smithy(&state, state.whoseTurn, handPos);
         
         
         #if (NOISY_TEST == 1)
            printf("Post-conditions:\n handCount = %d\n deckCount = %d\n discardCount = %d\n playedCardCount = %d\n turn = %d\n"
                  , state.handCount[p], state.deckCount[p], state.discardCount[p], state.playedCardCount, state.whoseTurn);
         
         #endif
         
         // hand count should have 2 more cards (add 3 minus discard smithy)
         if (state.handCount[p] != startHandCount + 2) {
            fail = 1;
            failcount++;
            printf("FAIL Test 1: handCount did not increase by two\n");
            printf("\tExpected: %d. Returned: %d\n", startHandCount + 2, state.handCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // deckCount should have decreased by 3.
         if (state.deckCount[p] != startDeckCount - 3) {
            fail = 1;
            failcount++;
            printf("FAIL Test 2: deckCount did not decrease by three\n");
            printf("\tExpected: %d. Returned: %d\n", startDeckCount - 3, state.deckCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // discard count should have increased by 1
         if (state.discardCount[p] != startDiscardCount + 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 3: discardCount count not increased by 1\n");
            printf("\tExpected: %d. Returned: %d\n", startDiscardCount + 1, state.discardCount[p]);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         // playedCardCount should have increased by 1
         if (state.playedCardCount != startPlayedCardCount + 1) {
            fail = 1;
            failcount++;
            printf("FAIL Test 4: playedCardCount count not increased by 1\n");
            printf("\tExpected: %d. Returned: %d\n", startPlayedCardCount + 1, state.playedCardCount);
            printf("\tstarting handCount = %d Player = %d\n", startHandCount, p);
         }
         
      }
   }
   
   // Tests Complete
   if (fail) {
      printf("%d smithy tests FAILED\n", failcount);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("All smithy tests PASSED\n");
   #endif
   return 0;
}