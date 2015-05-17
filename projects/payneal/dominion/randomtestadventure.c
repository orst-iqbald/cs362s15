/* -----------------------------------------------------------------------
 *Ali Payne
 * SE2 Assignmnet 4
 * randomtestadventurer.c
 * - random tester for adveture card
 *
 *compile:
 *      gcc -g Wall -std -fpic coverage -lm randomtestadventurer.c dominion.o rngs.o -o randomtestadventure
 * -----------------------------------------------------------------------
 */

#include <stdlib.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#include <time.h>
#include <math.h>

#define TEST_COUNT 1000

// set NOISY_TEST to 0 to remove prints from output
#define NOISY_TEST 1


//function descriptions
//int testrandomAdventureCard(int )

int main() {
   
    //set up the random number
    srand(time(NULL));
    
    // set seed
    int seed = rand();
    
    int players = 2;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    // start the new game
    struct gameState play;
    
    int loopAlltest;
    
    //holds the amount of failures and passes
    int fails=0;
    int passes=0;
    
    #if (NOISY_TEST == 1)
        printf ("________RANDOM TESTING ADVENTURER________\n");
    #endif

    
    for (loopAlltest = 0; loopAlltest < TEST_COUNT; loopAlltest++)
    {
        //hold value of treasures before and after calling adventure card
        int treasuresbefore =0;
        int treasureafter= 0;
        
        // clear the game
        memset(&play, 23, sizeof( struct gameState));
        
        //initialize new game
        int start = initializeGame(players, k, seed, &play);
       
        //no need to contine if this fails
        assert( start == 0);
        
        
        //should of used rand generator in rngs.c
        int cardsinDeck1 = play.deckCount[0] =  (rand() % MAX_DECK +1);
        int cardsinHand1= play.handCount[0] =  (rand() % MAX_HAND +1);
     
        
        #if (NOISY_TEST == 1)
            printf(" this is the number of cards in player ones hand %i\n", cardsinHand1);
            printf(" this is the number of cards in the players dekc %i\n", cardsinDeck1);
        #endif
        
        int i;
        //put cards in deck and hand
        for(i = 0; i < play.deckCount[0]; i++)
        {
            play.deck[0][i] = floor(rand() % 17 + 1);
        }
        for(i = 0; i < play.handCount[0]; i++)
        {
            play.hand[0][i] = floor(rand() % 17 + 1);
        }

        // store the number of treasures originally in hand
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold || play.hand[0][i] == silver || play.hand[0][i] == copper )
            {
                treasuresbefore++;
            }
        }
        
        #if (NOISY_TEST == 1)
            printf(" this si the amount of treasures before adventure was called %i\n",
                   treasuresbefore );
        #endif
        
        
        

        //calling the adventure card
        int check = cardAdventurer(&play, 0);
        //should always return 0
        assert(check == 0);
        
        
        // store the number of treasures after calling adventurer
        for (i = 0; i < play.handCount[0]; i++)
        {
            if ( play.hand[0][i] == gold || play.hand[0][i] == silver || play.hand[0][i] == copper )
            {
                treasureafter++;
            }
        }
        
        
       int cardsinHand1After = play.handCount[0];
        int cardsinDeck1After = play.deckCount[0];
        
        #if (NOISY_TEST == 1)
            printf(" this si the amount of treasures after adventure was called %i\n", treasureafter );
        printf(" this is the number of cards in player ones hand %i\n", cardsinHand1After);
        printf(" this is the number of cards in the players dekc %i\n\n", cardsinDeck1After);
    #endif
        
        
        if( treasuresbefore +2 == treasureafter && cardsinHand1 < cardsinHand1After && cardsinDeck1 > cardsinDeck1After)
        {
            passes += 1;
        }
        else
        {
            fails += 1;
        }
    }
    
    #if (NOISY_TEST == 1)
        printf("Passed = %i\n", passes);
        printf("fails = %i\n", fails);
    
        if ( passes == 1000)
        {
            printf("Program is coreccect");
        }
        else
        {
            printf("there are logical errors in this program");
        }
    
    #endif
    

    return 0;
}
