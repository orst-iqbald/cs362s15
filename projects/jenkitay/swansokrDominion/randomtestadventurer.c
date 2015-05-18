/*******************************************************************************
- Taylor Jenkins
- jenkitay@onid.oregonstate.edu
- CS 362 - Software Engineering II
- Assignment 4
- filename: randomtestadventurer.c
- Description: A random tester for the adventurer card in dominion.c.
- Compile instruction: 
gcc -g -Wall -std=c99 -fpic -coverage -lm randomtestadventurer.c dominion.o rngs.o -o randomtestadventurer
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
   int randtestseed = 0;
   int printcount = 0;
   int addedcoins = 0;
   
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
         
         // Test:  Effect of adventurer card
         //    Reveal cards from your deck until you reveal 2 Treasure cards. 
         //    Put those Treasure cards in your hand and discard the other 
         //    revealed cards.
         
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
         
         int numcardsdrawn = 0;
         int foundcoins = 0;
         int foundcoinsindeck = 0;
         int foundcoinsindiscard = 0;
         for (int n = 1; n <= statecpy.deckCount[p]; n++) {
            numcardsdrawn++;
            if (statecpy.deck[p][statecpy.deckCount[p] - n] == copper 
                  || statecpy.deck[p][statecpy.deckCount[p] - n] == silver 
                  || statecpy.deck[p][statecpy.deckCount[p] - n] == gold) {
               foundcoinsindeck++;
               if (foundcoinsindeck >= 2) break;
            }
         }
         for (int n = 1; n <= statecpy.discardCount[p]; n++) {
            // numcardsdrawn++;
            if (statecpy.discard[p][statecpy.discardCount[p] - n] == copper 
                  || statecpy.discard[p][statecpy.discardCount[p] - n] == silver 
                  || statecpy.discard[p][statecpy.discardCount[p] - n] == gold) {
               foundcoinsindiscard++;
               if (foundcoinsindiscard >= 2) break;
            }
         }
         foundcoins = foundcoinsindeck + foundcoinsindiscard;
         if (foundcoins > 2) {
            addedcoins = 2;
         }
         else {
            addedcoins = foundcoins;
         }
         
         
         // play adventurer card
         // adventurerCardEffect(&state);
         int tempHand[MAX_HAND];
         play_adventurer(&state, p, handPos, &tempHand);
         
         
         
         // Test 1: current player hand count should now show 2 more cards
         for (int player = 0; player < numPlayers; player++) {
            if (player == p) {
               if (state.handCount[player] != statecpy.handCount[player] + addedcoins) {
                  fail = 1;
                  failcount1++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 1a: current player handCount did not increase by %d\n", addedcoins);
                  printf("\tExpected: %d. Returned: %d\n"
                     , statecpy.handCount[player] + addedcoins, state.handCount[player]);
                  #endif
               }
            }
            else { // other player hand counts should remain the same
               if (state.handCount[player] != statecpy.handCount[player]) {
                  fail = 1;
                  failcount1++;
                  #if (NOISY_TEST == 1)
                  printf("FAIL Test 1b: handCount changed for other player\n");
                  printf("\tExpected: %d. Returned: %d\n"
                     , statecpy.handCount[player], state.handCount[player]);
                  #endif
               }
            }
         }
         // Test 2: If 2 coins found in deck, deckCount should have decreased by numcardsdrawn.
         if (foundcoinsindeck == 2) {
            if (state.deckCount[p] != statecpy.deckCount[p] - numcardsdrawn) {
               fail = 1;
               failcount2++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 2: deckCount did not decrease by %d.\n", numcardsdrawn);
               printf("\tExpected: <= %d. Returned: %d\n"
                  , statecpy.deckCount[p] - 2, state.deckCount[p]);
               #endif
            }
         }
         // Test 3: If 2 coins found in deck, discard count should have increased by 2 less than numcardsdrawn
         if (foundcoinsindeck == 2) {
            if (state.discardCount[p] != statecpy.discardCount[p] + numcardsdrawn - 2) {
               fail = 1;
               failcount3++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 3a: discardCount not increased by %d\n", numcardsdrawn - 2);
               printf("\tExpected: %d. Returned: %d\n"
                  , statecpy.discardCount[p] + numcardsdrawn - 2, state.discardCount[p]);
               #endif
            }
         }
         else {
            if (state.discardCount[p] < numcardsdrawn - 1) {
               fail = 1;
               failcount3++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 3b: discardCount is too low.");
               printf("\tExpected greater than: %d. Returned: %d\n"
                  , numcardsdrawn - 2, state.discardCount[p]);
               #endif
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
         
         // Test 5: Up to 2 discovered coin cards should be added to end of hand.
         if (foundcoins >= 2) {
            if (state.hand[p][statecpy.handCount[p]] < copper 
                  || state.hand[p][statecpy.handCount[p]] > gold 
                  || state.hand[p][statecpy.handCount[p]+1] < copper 
                  || state.hand[p][statecpy.handCount[p]+1] > gold) {
               fail = 1;
               failcount5++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 5a: Two coins were not added to hand.\n");
               printf("\tExpected: two from %d, %d, or %d. Returned: %d and %d\n", 
                     copper, silver, gold, state.hand[p][statecpy.handCount[p]]
                  , state.hand[p][statecpy.handCount[p+1]]);
               #endif
            }
         }
         if (foundcoins == 1) {
            if (state.hand[p][statecpy.handCount[p]] < copper 
                  || state.hand[p][statecpy.handCount[p]] > gold) {
               fail = 1;
               failcount5++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 5b: One coin only was not added to hand.\n");
               printf("\tExpected: one of [%d, %d, or %d]. Returned: %d\n", 
                     copper, silver, gold, state.hand[p][statecpy.handCount[p]]);
               #endif
            }
         }
         if (foundcoins == 0) {
            if (state.hand[p][statecpy.handCount[p]] > empty  
               && state.handCount[p] != statecpy.handCount[p]) {
               fail = 1;
               failcount5++;
               #if (NOISY_TEST == 1)
               printf("FAIL Test 5c: No cards should have been added to hand.\n");
               printf("\tExpected: %d. Returned: %d\n", 
                     statecpy.hand[p][statecpy.handCount[p]-1], state.hand[p][state.handCount[p]-1]);
               #endif
            }
         }
      
         failcount = failcount1 
                   + failcount2 
                   + failcount3 
                   + failcount4 
                   + failcount5 ;
            
         if (failcount > printcount) {
            // print preconditions
            #if (NOISY_TEST == 1)
            printf("\nTest preconditions:\n"
                  "\tnumPlayers = %d\n"
                  "\twhoseTurn = %d\n"
                  "\thandCount = %d\n"
                  "\tTop deck card = %d\n"
                  "\tdeckCount = %d\n"
                  "\tTop discard card = %d\n"
                  "\tdiscardCount = %d\n"
                  "\tplayedCardCount = %d\n"
                  "\tfoundcoinsindeck = %d\n"
                  "\tfoundcoinsindiscard = %d\n",
                  statecpy.numPlayers,
                  statecpy.whoseTurn,
                  statecpy.handCount[p],
                  statecpy.deck[p][statecpy.deckCount[p] - 1],
                  statecpy.deckCount[p],
                  statecpy.discard[p][statecpy.discardCount[p] - 1],
                  statecpy.discardCount[p],
                  statecpy.playedCardCount, 
                  foundcoinsindeck,
                  foundcoinsindiscard);
            
            #endif
                   
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
                  "\tplayedCardCount = %d\n\n\n",
                  state.numPlayers,
                  state.whoseTurn,
                  state.handCount[p],
                  state.deck[p][state.deckCount[p] - 1],
                  state.deckCount[p],
                  state.discard[p][state.discardCount[p] - 1],
                  state.discardCount[p],
                  state.playedCardCount);
            
            #endif
            printcount = failcount;
         }
      }
   }
   
   // Tests Complete
   
   if (fail) {
      printf("\n\n%d adventurer tests FAILED\n", failcount);
      printf("test 1 failed %d times.\n", failcount1);
      printf("test 2 failed %d times.\n", failcount2);
      printf("test 3 failed %d times.\n", failcount3);
      printf("test 4 failed %d times.\n", failcount4);
      printf("test 5 failed %d times.\n", failcount5);
      return -1;
   }
   #if (NOISY_TEST == 1)
      printf("\n\nAll adventurer tests PASSED\n");
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