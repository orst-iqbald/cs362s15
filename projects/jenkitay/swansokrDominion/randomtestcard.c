/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 4
- filename: randomtestcard.c
- Description: A random test of the sea_hag card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm randomtestcard.c dominion.o rngs.o -o randomtestcard
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
#define TEST_COUNT 1000
#define MAX_FAIL 10000

int randrange(int min, int max);

// int sea_hagCardEffect(struct gameState *state);

int main(int argc, char *argv[])
{	
   // Game state variables
   int numPlayers;
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
   struct gameState statecpy;
   
   // test variables
   int p;
   int empty = -1;
   int handPos;
   int handCountMax;
   int fail = 0;
   int failcount = 0;
   int failcount1 = 0;
   int failcount2 = 0;
   int failcount3 = 0;
   int failcount4 = 0;
   int failcount5 = 0;
   int failcount6 = 0;
   int randtestseed = 0;
   
   srand(randtestseed);
   
   
   /* For Reference, elements of game state struct:
         struct gameState {
           int numPlayers; //number of players
           int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
           int embargoTokens[treasure_map+1];
           int outpostPlayed;
           int outpostTurn;
           int whoseTurn;
           int phase;
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
         };
    */
   

   // Begin Random Tests
   for (int testSet = 1; testSet <= TEST_COUNT && failcount <= MAX_FAIL; testSet++) {
      
      // Randomize initial variables:
      numPlayers = randrange(2,MAX_PLAYERS);
      handCountMax = randrange(1, MAX_HAND);
      
      // initialize game state and statecpy
      // initializeGame returns 0 on success
      memset(&state, empty, sizeof(struct gameState)); // initialize game state
      assert(initializeGame(numPlayers, kCards, randSeed, &state) == 0); 
      memset(&statecpy, empty, sizeof(struct gameState)); // initialize game statecpy
      assert(initializeGame(numPlayers, kCards, randSeed, &statecpy) == 0);
      
      
      for (p = 0; p < numPlayers; p++) {
         state.whoseTurn = p;
         
         // Test:  Effect of sea hag card
         //    Each other player discards the top card of his deck, then gains a
         //    Curse card, putting it on top of his deck.
         
         
         // initialize each players' cards
         for (int d = 0; d < numPlayers; d++) {
            
            // empty hand, deck, discard, and playedCards
            for (int e = 0; e < MAX_HAND; e++) {
               state.hand[d][e] = empty;
            }
            for (int e = 0; e < MAX_DECK; e++) {
               state.deck[d][e] = empty;
               state.discard[d][e] = empty;
            }
            
            // randomly build each player's hand
            state.handCount[d] = randrange(1, handCountMax);   
            for (handPos = 0; handPos < state.handCount[d]; handPos++) {
               state.hand[d][handPos] = randrange(0, treasure_map);
            }
            
            // randomly build each player's deck
            state.deckCount[d] = randrange(0, MAX_DECK);
            for (int i = 0; i < state.deckCount[d]; i++) {
               state.deck[d][i] = randrange(0, treasure_map);
            }
            
            // randomly build each player's discard pile
            state.discardCount[d] = randrange(0, MAX_DECK);
            for (int i = 0; i < state.discardCount[d]; i++) {
               state.discard[d][i] = randrange(0, treasure_map);
            }
         }
            
         // randomly initialize played cards
         state.playedCardCount = randrange(0, MAX_DECK);
         for (int i = 0; i < state.playedCardCount; i++) {
            state.playedCards[i] = randrange(0, treasure_map);
         }
         
         // save precondition state in variables.
         memcpy(&statecpy, &state, sizeof(struct gameState));
         
         
         handPos = 0;
         
         // print preconditions
         #if (NOISY_TEST == 1)
         printf("\n\nTest preconditions:\n"
               "\tnumPlayers = %d\n"
               "\twhoseTurn = %d\n"
               "\thandCount = %d\n"
               "\tTop deck card = %d\n"
               "\tdeckCount = %d\n"
               "\tTop discard card = %d\n"
               "\tdiscardCount = %d\n"
               "\tplayedCardCount = %d\n",
               statecpy.numPlayers,
               statecpy.whoseTurn,
               statecpy.handCount[p],
               statecpy.deck[p][statecpy.deckCount[p] - 1],
               statecpy.deckCount[p],
               statecpy.discard[p][statecpy.discardCount[p] - 1],
               statecpy.discardCount[p],
               statecpy.playedCardCount);
         
         #endif
         
         // play sea_hag card
         // sea_hagCardEffect(&state);
         cardEffect(sea_hag, -1, -1, -1, &state, handPos, 0);
         
         // print post conditions
         #if (NOISY_TEST == 1)
         printf("\nTest postconditions:\n"
               "\tnumPlayers = %d\n"
               "\twhoseTurn = %d\n"
               "\thandCount = %d\n"
               "\tTop deck card = %d\n"
               "\tdeckCount = %d\n"
               "\tTop discard card = %d\n"
               "\tdiscardCount = %d\n"
               "\tplayedCardCount = %d\n\n",
               state.numPlayers,
               state.whoseTurn,
               state.handCount[p],
               state.deck[p][state.deckCount[p] - 1],
               state.deckCount[p],
               state.discard[p][state.discardCount[p] - 1],
               state.discardCount[p],
               state.playedCardCount);
         
         #endif
         
         
         // Test 1: hand count should remain unchanged for all players.
         for (int player = 0; player < numPlayers; player++) {
            if (statecpy.handCount[player] != statecpy.handCount[player]) {
               fail = 1;
               failcount1++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 1: handCount changed for player 0\n");
               printf("\tExpected: %d. Returned: %d\n"
                  , statecpy.handCount[player], statecpy.handCount[player]);
               #endif
            }
         }
         // Test 2: deckCount should remain unchanged for all players.
         for (int player = 0; player < numPlayers; player++) {
            if (statecpy.deckCount[player] != state.deckCount[player]) {
               fail = 1;
               failcount2++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 2: deckCount changed for player 0\n");
               printf("\tExpected: %d. Returned: %d\n"
                  , statecpy.deckCount[player], state.deckCount[player]);
               #endif
            }
         }
         // Test 3: discard count should have increased by 1 for all other players only.
         for (int player = 0; player < numPlayers; player++) {
            if (player != p) {
               if (state.discardCount[player] != statecpy.discardCount[player] + 1) {
                  fail = 1;
                  failcount3++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 3a: other player's discardCount count not increased by 1\n");
                  printf("\tExpected: %d. Returned: %d\n"
                     , statecpy.discardCount[player] + 1, state.discardCount[player]);
                  #endif
               }
            }
            else {
               if (state.discardCount[player] != statecpy.discardCount[player]) {
                  fail = 1;
                  failcount3++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 3b: player %d's discardCount count changed\n", player);
                  printf("\tExpected: %d. Returned: %d\n"
                     , statecpy.discardCount[player], state.discardCount[player]);
                  #endif
               }
            }
         }
         // Test 4: playedCardCount should remain unchanged
         if (statecpy.playedCardCount != state.playedCardCount) {
            fail = 1;
            failcount4++;
            #if (NOISY_TEST == 1)
            printf("FAIL Test 4: playedCardCount changed\n");
            printf("\tExpected: %d. Returned: %d\n"
               , statecpy.playedCardCount, state.playedCardCount);
            #endif
         }
         // Test 5: Top of all other players' discard piles should contain prior top of deck.
         for (int player = 0; player < numPlayers; player++) {
            if (player != p) {
               if (state.discard[player][statecpy.discardCount[player]] != 
                  statecpy.deck[player][statecpy.deckCount[player]-1]) { 
                  fail = 1;
                  failcount5++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 5a: Top of other player's discard pile is incorrect.\n");
                  printf("\tExpected: %d. Returned: %d\n", 
                        statecpy.deck[player][statecpy.deckCount[player]-1], 
                        state.discard[player][statecpy.discardCount[player]] );
                  #endif
               }
            }
            else {
               if (state.discard[player][statecpy.discardCount[player]] != empty) { 
                  fail = 1;
                  failcount5++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 5b: Top of current player's discard pile is changed.\n");
                  printf("\tExpected: %d. Returned: %d\n", empty, 
                        state.discard[player][statecpy.discardCount[player]]);
                  #endif
               }
            }
         }
         // Test 6: Top of all other players' decks should contain a curse card.
         for (int player = 0; player < numPlayers; player++) {
            if (player != p) {
               if (state.deck[player][statecpy.deckCount[player]-1] != curse) { 
                  fail = 1;
                  failcount6++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 6a: Top of other player's deck is not a curse card.\n");
                  printf("\tExpected: %d. Returned: %d\n"
                     , curse, state.deck[player][statecpy.deckCount[player]-1]);
                  #endif
               }
            }
            else {
               if (state.deck[player][statecpy.deckCount[player]-1] != 
                     statecpy.deck[player][statecpy.deckCount[player]-1]) { 
                  fail = 1;
                  failcount6++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 6b: Top of current player's deck is changed.\n");
                  printf("\tExpected: %d. Returned: %d\n"
                     , statecpy.deck[player][statecpy.deckCount[player]-1], 
                     state.deck[player][statecpy.deckCount[player]-1]);
                  #endif
               }
            }
         }
      }
      failcount = failcount1 
                + failcount2 
                + failcount3 
                + failcount4 
                + failcount5 
                + failcount6;
   }

   // Tests Complete
   
   if (fail) {
      printf("\n\n%d sea_hag tests FAILED\n", failcount);
      printf("test 1 failed %d times.\n", failcount1);
      printf("test 2 failed %d times.\n", failcount2);
      printf("test 3 failed %d times.\n", failcount3);
      printf("test 4 failed %d times.\n", failcount4);
      printf("test 5 failed %d times.\n", failcount5);
      printf("test 6 failed %d times.\n", failcount6);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("\n\nAll sea_hag tests PASSED\n");
   #endif
   return 0;
}

// Generates a random number in the range min to max, inclusive.
int randrange(int min, int max)
{
   assert(min <= max);
   assert((max - min) < RAND_MAX);
   return rand() % (max - min + 1) + min;
}